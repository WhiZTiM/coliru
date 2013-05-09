require 'rubygems' # must be first!
require 'fileutils'
require 'json'
require 'net/http'
require 'popen4'
require 'pp'
require 'sinatra'


set :port, ENV['COLIRU_PORT']
$semaphore = Mutex.new
$feedback_semaphore = Mutex.new
$timeout_semaphore = Mutex.new

def get_timeout
    $timeout_semaphore.synchronize do
        begin
            [60, File.read('timeout.txt').to_i ].min.to_s
        rescue Exception => e
            20.to_s
        end
    end
end


def set_timeout(t)
    $timeout_semaphore.synchronize do
        File.open('timeout.txt', 'w') { |f| f << t }
    end
end

# @param [String] cmd Command to be executed.
def safe_popen(cmd)
    begin
        Timeout.timeout(get_timeout.to_i) do
            @stdout = IO.popen("#{cmd} 2>&1 ")
            until @stdout.eof?
                yield @stdout.readline
            end
            Process.wait @stdout.pid
        end
    rescue Timeout::Error => e
        Process.kill 9, @stdout.pid
        Process.wait @stdout.pid
        yield e.to_s
    rescue Exception => e
        e.to_s
    end
end


get '/' do
    File.read('index.html')
end


get '/*.html' do |file|
    File.read("#{file}.html")
end


get '/favicon.ico' do
    File.read('favicon.ico')
end


post '/feedback' do
    $feedback_semaphore.synchronize do
        File.open('feedback.txt', 'a') do |file|
            file.puts(request.body.read)
        end
    end
end


get '/feedback' do
    stream do |out|
        out << '<html><body><ul>'
        $feedback_semaphore.synchronize do
            File.readlines("feedback.txt").reverse.each { |l| out << "<li>#{l.gsub('<', '&lt;').gsub('>', '&gt;')}</li>" }
        end
        out << '</ul></body></html>'
    end
end


post '/compile' do
    $semaphore.synchronize do
        json_obj = JSON.parse(request.body.read)
        File.open('cmd.sh', 'w') { |f| f << json_obj['cmd'] }
        File.open('main.cpp', 'w') { |f| f << json_obj['src'] }
        stream do |out|
            safe_popen('./sandbox.sh') { |line| out << line }
        end
    end
end


post '/compile2' do
    $semaphore.synchronize do
        parts = request.body.read.split("__COLIRU_SPLIT__");
        File.open('cmd.sh', 'w') { |f| f << parts[0] }
        File.open('main.cpp', 'w') { |f| f << parts[1] }
        stream do |out|
            safe_popen('./sandbox.sh') { |line| out << line }
        end
    end
end


post '/timeout' do
    stream do |out|
        set_timeout(request.body.read.to_i)
        get_timeout
    end
end


get '/timeout' do
    get_timeout
end


post '/share' do
    $semaphore.synchronize do
        result = nil
        json_obj = JSON.parse(request.body.read)
        File.open('cmd.sh', 'w') { |f| f << json_obj['cmd'] }
        File.open('main.cpp', 'w') { |f| f << json_obj['src'] }

        safe_popen('./share.sh') do |line|
            result = result || line
            next # we want to wait for the process to completely finish
        end
        stream { |out| out << result }
    end
end


get '/view' do
    File.read('view.html')
end


get '/external' do
    stream do |out|
        uri = URI.parse(params[:url])
        http_get_request = Net::HTTP::Get.new(uri.path)
        result = Net::HTTP.start(uri.host, uri.port) { |http| http.request(http_get_request) }
        out << result.body
    end
end


get '/Archive/*' do |file|
    begin
        real_file = "#{ENV['COLIRU_ARCHIVE']}/#{file}"
        if File.directory? real_file
            Dir.entries(real_file).join("\n").to_s
        else
            File.read(real_file)
        end
    rescue Exception => e
        e.to_s
    end
end


get '/archive' do
    get_contents = Proc.new do |name|
        begin
            File.read("#{ENV['COLIRU_ARCHIVE']}/#{params[:id]}/#{name}")
        rescue Exception => e
            ""
        end
    end

    $semaphore.synchronize do
        {
            :cmd => get_contents.call('cmd.sh'),
            :src => get_contents.call('main.cpp'),
            :output => get_contents.call('output')
        }.to_json
    end
end

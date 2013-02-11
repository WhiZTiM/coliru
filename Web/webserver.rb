require 'rubygems'
require 'fileutils'
require 'mongrel'
require 'popen4'
require 'pp'
require 'thread'

$semaphore = Mutex.new
$pid = 0


class SimpleHandler < Mongrel::HttpHandler
    def process(request, response)
        response.start(200) do |head,out|
            head["Content-Type"] = "text/html"
            loc = get_location(request)
            case loc
            when ""
                FileUtils.copy_stream(File.new("index.html"), out)
            when "cmd.html"
                FileUtils.copy_stream(File.new("cmd.html"), out)
            when "index.html"
                FileUtils.copy_stream(File.new("index.html"), out)
            when "frame-top.html"
                FileUtils.copy_stream(File.new("frame-top.html"), out)
            when "frame-bottom.html"
                FileUtils.copy_stream(File.new("frame-bottom.html"), out)
            when "md5-min.js"
                FileUtils.copy_stream(File.new("md5-min.js"), out)
            when "compile"
                $semaphore.synchronize {
                    safe_compile(request, "sandbox", out)
                }
            when "share"
                $semaphore.synchronize {
                    share(request, out)
                }
            when "view"
                FileUtils.copy_stream(File.new("view.html"), out)
            when "favicon.ico"
                FileUtils.copy_stream(File.new("favicon.png", "rb"), out)
            else
                $semaphore.synchronize {
                  out.write(File.read("Archive/#{loc}/main.cpp") + "__COLIRU_SEP__" + File.read("Archive/#{loc}/output"))
                }
            end
        end
    end

    def share(req, out)
        $pid = 0;
        puts "$pid is #{$pid}"
        begin
            Timeout.timeout(20) do
                File.open("main.cpp", 'w') { |f| f.write(req.body.string) }
                status = POpen4::popen4("./share.sh 2>&1") do |stdout, stderr, stdin, pid|
                    $pid = pid
                    puts "$pid is assigned to #{$pid}"
                    stdin.close()
                    out.write(stdout.readline())
                end
            end
        rescue Timeout::Error => e
            puts e
        end
    end


    def safe_compile(req, script, out)
        $pid = 0;
        puts "$pid is #{$pid}"
        begin
            Timeout.timeout(20) do
                compile(req, script, out)
            end
        rescue Timeout::Error => e
            out.write("The operation timed out.")
            Thread.new do 
                puts "Killing myself to live."
                sleep(0.01)
                POpen4::popen4("pkill -u 2002") {} 
                POpen4::popen4("pkill -u 2001") {} 
            end
        end
    end

    def compile(request, script, out)
        File.open("main.cpp", 'w') { |f| f.write(request.body.string) }
        status = POpen4::popen4("./#{script}.sh 2>&1") do |stdout, stderr, stdin, pid|
            $pid = pid
            puts "$pid is assigned to #{$pid}"
            stdin.close()
            out.write(stdout.read())
        end
    end

    # Returns the location. E.g: if the URL is "http://localhost.com/compile" then "ccompile" will be returned.
    def get_location(request)
        return request.params["REQUEST_PATH"][1..-1]
    end

end


if ARGV.length != 2
    puts "Usage ruby webserver.rb Host Port"
    exit
end


$host = ARGV[0]
$port = ARGV[1]


puts "Start listening to #{$host}:#{$port}"
h = Mongrel::HttpServer.new($host, $port)
h.register("/", SimpleHandler.new)
h.register("/Archive", Mongrel::DirHandler.new("Archive"))
puts "h.num_processors: #{h.num_processors}"
h.run.join


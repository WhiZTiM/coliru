#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <future>


std::unordered_map<long,unsigned int> do_work(int index, int work, const std::vector<long>& data)
{
    auto begin_iter = std::next(data.begin(),index*work);
    auto end_iter   = std::next(begin_iter,work);
    std::unordered_map<long,unsigned int> histogram;
    
    std::for_each(begin_iter,end_iter,[&hist=histogram](long val)
    {
        ++hist[val]; 
    });
    
    return histogram;
}

std::unordered_map<long,unsigned int> do_work2(int index, int work, const std::vector<std::vector<long>>& data)
{
    auto begin_iter = std::next(data.begin(),index*work);
    auto end_iter   = std::next(begin_iter,work);
    std::unordered_map<long,unsigned int> histogram;
    
    std::for_each(begin_iter,end_iter,[&hist=histogram](const std::vector<long>& inner)
    {
        for(long val : inner)
        {
            ++hist[val];
        }
    });
    
    return histogram;
}

void extend(const std::vector<std::vector<long>>& vec)
{
    unsigned long total_size = 0;
    for(const auto&  inner : vec)
        total_size += inner.size();
        
    std::vector<long> extended;
    extended.reserve(total_size);
    
    for(auto&  inner : vec)
        extended.insert(extended.end(),inner.begin(),inner.end());
    

    int num_cores = std::thread::hardware_concurrency();
    std::vector<std::future<std::unordered_map<long,unsigned int>>> tasks(num_cores);
    
    const int work = extended.size() / tasks.size();
    for(unsigned int i = 0; i < tasks.size(); ++i)
    {
        tasks[i] = std::move(std::async(std::launch::async,do_work,i,work,std::cref(extended)));
        
    }
    
    std::unordered_map<long,unsigned int> results;
    
    // do the rest of the work on the main thread
    for(unsigned int i = tasks.size() * work; i < extended.size(); ++i)
    {
        ++results[extended[i]];
    }
    
    for(auto& task : tasks)
    {
        std::unordered_map<long,unsigned int> task_res = task.get();
        for(const auto& value : task_res)
        {
            results[value.first] += value.second;
        }
        
    }
    
    std::cout << results[277] << "\n";
}

void no_extend(const std::vector<std::vector<long>>& vec)
{
    int num_cores = std::thread::hardware_concurrency();
    std::vector<std::future<std::unordered_map<long,unsigned int>>> tasks(num_cores);
    
    const int work = vec.size() / tasks.size();
    for(unsigned int i = 0; i < tasks.size(); ++i)
    {
        tasks[i] = std::move(std::async(std::launch::async,do_work2,i,work,std::cref(vec)));
        
    }
    
    std::unordered_map<long,unsigned int> results;
    
    // do the rest of the work on the main thread
    auto begin_iter = std::next(vec.begin(),tasks.size()*work);
    
    std::for_each(begin_iter,vec.end(),[&results=results](const std::vector<long>& inner)
    {
        for(long val : inner)
        {
         ++results[val];
        }
    });
    
    for(auto& task : tasks)
    {
        std::unordered_map<long,unsigned int> task_res = task.get();
        for(const auto& value : task_res)
        {
            results[value.first] += value.second;
        }
        
    }
    
    std::cout << results[277] << "\n";
}
int main()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<long> distribution(0,400);
    std::vector<std::vector<long>> vec(5000);
    
    // simulate large data
    std::for_each(vec.begin(),vec.end(),[&gen=generator,&dist=distribution](std::vector<long>& vec)
                 {
                   vec.resize(100);
                   std::generate(vec.begin(),vec.end(),[&gen=gen,&dist=dist](){ return dist(gen);});   
          
                 });
                
                
//    extend(vec);    // perform calculation with the large vector<vector<long>> decomposed into a single vector<long> 
    
      no_extend(vec);  // perform the calculation with the large vector<vector<long>> as is
    
   
    
}
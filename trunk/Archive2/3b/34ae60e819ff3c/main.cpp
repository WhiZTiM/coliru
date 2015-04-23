#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

typedef std::pair<double, uint32_t> TotalTimeAndCount;

struct ScopeLogTime
{
    ScopeLogTime(const std::string& InName, TotalTimeAndCount* InCumulative = nullptr) :
        StartTime(std::chrono::system_clock::now()),
        Name(InName),
	    Cumulative(InCumulative)
    {}
    
	~ScopeLogTime()
    {
        const std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();
    	const double scopedTime = std::chrono::duration<double>(endTime - StartTime).count();
    	if (Cumulative)
    	{
    		Cumulative->first += scopedTime;
    		++Cumulative->second;
    
    		const double average = Cumulative->first / Cumulative->second;
            std::cout << "ScopedLog - " << Name << ": " << scopedTime * 1000 << " ms " << Cumulative->first << " s / " << Cumulative->second << " / " << average << " s" << std::endl;
    	}
    	else
    	{
            std::cout << "ScopedLog - " << Name << ": " << scopedTime * 1000 << " ms" << std::endl;
    	}
    }

protected:
	const std::chrono::time_point<std::chrono::system_clock> StartTime;
	const std::string Name;
	TotalTimeAndCount* Cumulative;
};

//typedef __m128 vec4f;

struct MyStruct1
{
    int64_t m_Total = 0;
    void UpdateTotal(const float* values, int count)
    {
        for (int i = 0; i < count; ++i)
            m_Total += values[i];
    }
};

struct MyStruct2
{
    int64_t m_Total = 0;
    void UpdateTotal(const float* values, int count)
    {
        uint64_t total = 0;
        for (int i = 0; i < count; ++i)
            total += values[i];
        m_Total = total;
    }
};

void Run()
{
    std::srand(std::time(0));
    
    const int count = 10 * 1000000;
    std::vector<float> arr1(count);
    std::vector<float> arr2(count);
    
    for (auto& v : arr1)
        v = std::rand() * std::rand() % 3 ? 4 : -7;
        
    for (auto& v : arr2)
        v = std::rand() * std::rand() % 2 ? -3 : 5;

    {
        ScopeLogTime log("MyStruct1", nullptr);
    
        MyStruct1 m;
        m.UpdateTotal(&arr1[0], arr1.size());
        std::cout << m.m_Total << std::endl;
    }

    {
        ScopeLogTime log("MyStruct2", nullptr);
    
        MyStruct2 m;
        m.UpdateTotal(&arr2[0], arr2.size());
        std::cout << m.m_Total << std::endl;
    }
}

int main()
{
    std::cout << "Hello" << std::endl;
    
    Run();
}



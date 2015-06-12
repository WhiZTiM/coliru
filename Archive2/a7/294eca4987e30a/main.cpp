#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

class Project {
    public:
    Project();
    int DoWork();
    private:
    class Nest;
    std::unique_ptr<Nest> nest_;
};

class Project::Nest {
    public:
    int DoMoreWork();
    int count_;
};

Project::Project() : nest_(new Nest()) { 
    nest_->count_ = 0;
}

int Project::DoWork() { 
    ++nest_->count_; 
    nest_->DoMoreWork(); 
    return nest_->count_;
}

int Project::Nest::DoMoreWork() {
    count_ += 3;
    return count_;
}

int main()
{
    Project* project = new Project();
    printf("%d\n", project->DoWork());
}

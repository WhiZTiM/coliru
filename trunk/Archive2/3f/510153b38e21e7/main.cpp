#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

struct MySweetPOD {
    int check_this;
    int sweet_pod_out;
    double its_awesome;
};

using namespace std;

int main()
{
    // create temp MySweetPod with args, copy all members of temp MySweetPod to allocated MySweetPod
    shared_ptr<MySweetPOD> pod0 = make_shared<MySweetPod>(MySweetPod{ 1,2,3.0 });

    // allocate MySweetPod with args
    shared_ptr<MySweetPod> pod1(new MySweetPod{1,2,3.0});

    return 0;
}

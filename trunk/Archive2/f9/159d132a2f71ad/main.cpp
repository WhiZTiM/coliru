#include <tbb/concurrent_queue.h>
#include <thread>
#include <functional>
#include <iostream>

struct resource {
    int n = 0;
};

using response = int;

struct request {
    int value;
    tbb::concurrent_bounded_queue<response> respond_to;
};

void manage_resource(tbb::concurrent_bounded_queue<request*>& requests) {
    resource res;
    for (;;) {
        request* req;
        requests.pop(req);
        res.n += req->value;
        req->respond_to.push(res.n);
    }
}

int main() {
    tbb::concurrent_bounded_queue<request*> requests;
    std::thread(manage_resource, std::ref(requests)).detach();

    request req;
    req.value = 2;
    requests.push(&req);

    int value;
    req.respond_to.pop(value);
    std::cout << value << '\n';

    return 0;
}
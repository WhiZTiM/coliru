#include <iostream>
#include <thread>


class Server {
public:
    Server() {}
	void run() {
		std::cout << "Server running!\n";
	}

	void operator()() {
		run();
	}
};

int main() {
	Server server;

	std::thread t(server);
	t.join();

    // The same as
    std::thread t2([&](){server.run();});
	t2.join();


}

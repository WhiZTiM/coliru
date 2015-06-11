#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

namespace readerThread {

    /*
	 * Function		: start
	 * Description	: Thread entry point
	 * Parameters	: port: The serial port to use
	 * Return		: -
	 */
	void start(int id)
	{
		while (1)
		{
			std::cout << "Reader " << id << " running..." <<  std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}

}


int main() 
{

        int readers[] = { 1, 2, 3 };
        
		std::vector<std::thread> readerThreads;

		for (int &reader : readers)
		{
			std::thread th(readerThread::start, reader);
			readerThreads.push_back(th);
		}

		while(true)
		{
			std::cout << "Waiting..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		}
        
        return 0;
}



#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

class MySerialClass {

    public:
		MySerialClass(std::string port);
		virtual ~MySerialClass();

		void openSerial();
		void closeSerial();
		void configureSerial();
		void writeSerial(std::vector<char> data);
		void readSerial(std::vector<char> &data, unsigned int numBytes);

	private:

		int fd = 0; // The serial file descriptor
		fd_set fdset; // The set to check on select
		std::string portName = "";
};


MySerialClass::MySerialClass(std::string port) : portName(port) {}
MySerialClass::~MySerialClass() {}

void MySerialClass::openSerial()
{
	fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

	FD_ZERO(&fdset); 
	FD_SET(fd, &fdset); 
}

void MySerialClass::closeSerial()
{
	close(fd);
}

void MySerialClass::configureSerial()
{
	struct termios config = { 0 };

	tcgetattr(fd, &config);

	config.c_iflag = IGNPAR | ICRNL;
	config.c_oflag = 0;
	config.c_lflag = ICANON;

	config.c_cc[VINTR]    = 0;     /* Ctrl-c */
	config.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
	config.c_cc[VERASE]   = 0;     /* del */
	config.c_cc[VKILL]    = 0;     /* @ */
	config.c_cc[VEOF]     = 4;     /* Ctrl-d */
	config.c_cc[VTIME]    = 0;     /* inter-character timer unused */
	config.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
	config.c_cc[VSWTC]    = 0;     /* '\0' */
	config.c_cc[VSTART]   = 0;     /* Ctrl-q */
	config.c_cc[VSTOP]    = 0;     /* Ctrl-s */
	config.c_cc[VSUSP]    = 0;     /* Ctrl-z */
	config.c_cc[VEOL]     = 0;     /* '\0' */
	config.c_cc[VREPRINT] = 0;     /* Ctrl-r */
	config.c_cc[VDISCARD] = 0;     /* Ctrl-u */
	config.c_cc[VWERASE]  = 0;     /* Ctrl-w */
	config.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
	config.c_cc[VEOL2]    = 0;     /* '\0' */

	speed_t sp = B9600;
	config.c_cflag |= CSIZE;
	config.c_cflag |= CS8;

	cfsetispeed(&config, sp);
	cfsetospeed(&config, sp);

	tcsetattr(fd, TCSAFLUSH, &config);
}

void MySerialClass::writeSerial(std::vector<char> data)
{
	char buffer[1024];

	if (data.size() > 1024)
		return;

	int index = 0;
	for (char &item : data)
		buffer[index++] = item;

	unsigned int size = data.size();
	write(fd, &buffer[0], size);
}

void MySerialClass::readSerial(std::vector<char> &data, unsigned int numBytes)
{
	char buffer[1024];
	data.clear();

	if (numBytes > 1024)
		return;

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	int ret = select(fd + 1, 0, 0, 0, &tv);

	std::cout << "Select returns: " << ret << std::endl;

	if (!ret)
		return;

	read(fd, &buffer[0], numBytes);

	/*
	 * Copy to output buffer
	 */
	for (unsigned int i = 0; i < numBytes; i++)
		data.push_back(buffer[i]);
}

int main()
{
    MySerialClass serial("/dev/ttyS1");
    serial.openSerial();
    serial.configureSerial();
    
    while(1)
    {
    	std::vector<char> retData;
	    serial.readSerial(retData, 100);
        
		std::string retString(retData.begin(), retData.end());
        
        if (retString == "END")
        {
            serial.closeSerial();
            break;
        }
    }
}

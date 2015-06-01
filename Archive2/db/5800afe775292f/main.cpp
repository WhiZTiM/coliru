#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/date_time/date.hpp>

using namespace boost;
using namespace std;

boost::thread thread_obj;
boost::thread thread_obj1;

void func(void)
{
    char x;
    cout << "enter y to interrupt" << endl;
    cin >> x;
    if (x == 'y') {
        cout << "x = 'y'" << endl;
        thread_obj.interrupt();
        cout << "thread interrupt" << endl;
    }
}

void real_main() {
    boost::system_time const timeout = boost::get_system_time() + boost::posix_time::seconds(atoi(argv[1]));
    try {
        boost::this_thread::sleep(timeout);
    }
    catch (boost::thread_interrupted &) {
        cout << "thread interrupted" << endl;
    }
}

int main()
{
    thread_obj1 = boost::thread(&func);
    thread_obj = boost::thread(&real_main);
    thread_obj.join();
}

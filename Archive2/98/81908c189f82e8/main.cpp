#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>

namespace /*static*/ {
    boost::atomic<int> data;
    boost::atomic<int> num_threads_done;

    struct Work {
        void signal_slave()
        {
            boost::lock_guard<boost::mutex> lock(data_ready_mutex);
            data_ready = true;
            cond.notify_all();
        }

        void slave_thread()
        {
            static boost::atomic_int _id_gen(0);
            id = _id_gen++;

            std::cout << "(" << id << ") slave_thread created\n";
            while (true) {

                boost::unique_lock<boost::mutex> lock(data_ready_mutex);
                cond.wait(lock, [&]{ return data_ready; });

                data_ready = false;

                data++;

                num_run++;

                num_threads_done++;
            }
        }

      private:
        int id          = 0;
        bool data_ready = false;
        int  num_run    = 0;

        boost::mutex data_ready_mutex;
        boost::condition_variable cond;

    };

}

#include <boost/chrono.hpp>
#include <boost/chrono/chrono_io.hpp>

using hrc = boost::chrono::high_resolution_clock;

int main()
{
    boost::thread_group tg;

    size_t nThreads = 10;

    std::vector<Work> works(nThreads);

    for (size_t i = 0; i < nThreads; i++) {
        tg.create_thread(boost::bind(&Work::slave_thread, boost::ref(works[i])));
    }

    while (true) {
        auto start_time = hrc::now();

        for (auto& w : works)
            w.signal_slave();

        std::cout << "Elapsed Time = " << (hrc::now()-start_time) << std::endl;
    }

    tg.join_all();
}

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

static boost::posix_time::time_duration elapsed() {
    using namespace boost::posix_time;
    static ptime const t0 = microsec_clock::local_time();
    return (microsec_clock::local_time() - t0);
}

class Clock {
  public:
    using callback_t = std::function<void(int, Clock &)>;
    using duration_t = boost::posix_time::time_duration;

  public:
    Clock(boost::asio::io_service &io, callback_t callback = nullptr,
          duration_t duration = boost::posix_time::seconds(1), bool enable = true)
            : m_timer(io), m_duration(duration), m_callback(callback), m_enabled(false), m_count(0ul) 
    {
        if (enable)
            start();
    }

    void start() {
        if (!m_enabled) {
            m_enabled = true;
            m_timer.expires_from_now(m_duration);
            m_timer.async_wait(boost::bind(&Clock::tick, this, _1)); // std::bind _1 issue ?
        }
    }

    void stop() {
        if (m_enabled) {
            m_enabled = false;
            size_t c_cnt = m_timer.cancel();
#ifdef DEBUG
            printf("[DEBUG@%p] timer::stop : %lu ops cancelled\n", this, c_cnt);
#endif
        }
    }

    void tick(const boost::system::error_code &ec) {
        if (ec != boost::asio::error::operation_aborted) {
            m_timer.expires_at(m_timer.expires_at() + m_duration);
            m_timer.async_wait(boost::bind(&Clock::tick, this, _1));
            if (m_callback)
                m_callback(++m_count, *this);
        }
    }

    void reset_count()                     { m_count = 0ul;         } 
    size_t get_count() const               { return m_count;        } 

    void set_duration(duration_t duration) { m_duration = duration; } 
    const duration_t &get_duration() const { return m_duration;     } 

    void set_callback(callback_t callback) { m_callback = callback; } 
    const callback_t &get_callback() const { return m_callback;     } 

  private:
    boost::asio::deadline_timer m_timer;
    duration_t m_duration;
    callback_t m_callback;
    bool m_enabled;
    size_t m_count;
};

#include <iostream>

int main() {
    boost::asio::io_service ios;

    bool c1_active = true;

    Clock c1(ios, [&](int i, Clock& self)
            { 
                std::cout << elapsed() << "\t[C1 - fast] tick" << i << " (c1 active? " << std::boolalpha << c1_active << ")\n";
            },
            boost::posix_time::millisec(1)
            );

#if 1
    Clock c2(ios, [&](int i, Clock& self)
            {
                std::cout << elapsed() << "\t[C2 - slow] tick" << i << "\n";
                c1_active = (i % 2 == 0);
                
                if (c1_active)
                    c1.start();
                else
                    c1.stop();
            },
            boost::posix_time::millisec(10)
        );
#endif

    ios.run();
}

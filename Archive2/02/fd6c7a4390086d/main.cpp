#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <mqueue.h>

namespace bip = boost::interprocess;

typedef boost::shared_ptr<boost::interprocess::message_queue> mq_ptr;

struct mq_item_t {
    char data[24];
};

struct sink {
    std::string m_t2b_queue_name;
    std::string m_b2t_queue_name;
    mq_ptr m_t2b_queue;
    mq_ptr m_b2t_queue;

    sink(const char * conn_id, bool is_parent)
        : 
        m_t2b_queue_name(conn_id + std::string("_t2b")),
        m_b2t_queue_name(conn_id + std::string("_b2t"))
    {
        const int MAX_MESSAGE_NUMBER = 100000;

        if( is_parent )
        {
            bip::message_queue::remove(m_t2b_queue_name.c_str());
            bip::message_queue::remove(m_b2t_queue_name.c_str());

            bip::permissions perm;
            perm.set_unrestricted();
            m_t2b_queue.reset(new bip::message_queue(bip::create_only, m_t2b_queue_name.c_str(), MAX_MESSAGE_NUMBER, sizeof(mq_item_t), perm));
            m_b2t_queue.reset(new bip::message_queue(bip::create_only, m_b2t_queue_name.c_str(), MAX_MESSAGE_NUMBER, sizeof(mq_item_t), perm));
        }
        else
        {
            m_t2b_queue.reset(new bip::message_queue(bip::open_only, m_t2b_queue_name.c_str()));
            m_b2t_queue.reset(new bip::message_queue(bip::open_only, m_b2t_queue_name.c_str()));
            std::cout << "t2b max msg size = " << m_t2b_queue->get_max_msg_size() << "\n";
            std::cout << "b2t max msg size = " << m_b2t_queue->get_max_msg_size() << "\n";
        }    
    }
};

#include <sys/types.h>
#include <sys/wait.h>

int main() {
    std::cout << "Before: " << getpid() << "\n";

    if (int child = fork()) {
        std::cout << "Parent: " << getpid() << "\n";
        sink parent("ffqs5hbKgFs", true);

        int status;
        waitpid(child, &status, 0);
    } else {
        std::cout << "Child: " << getpid() << "\n";
        sink parent("ffqs5hbKgFs", false);
    }
}

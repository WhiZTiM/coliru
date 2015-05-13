#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/variant.hpp>

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

namespace Todo
{
    class None {
        void Do() const {};
    };

    class Exec {
      public:
        Exec(std::string const &command = "") : _command(command){};
        void Do() const { std::cout << "foo: " << getCommand() << std::endl; };

        std::string getCommand() const { return _command; };

      private:
        friend class boost::serialization::access;
        template <class Archive> void serialize(Archive &ar, unsigned) {
            ar &_command;
        }

        std::string _command;
    };

    using Todo = boost::variant<None, Exec>;

    struct Factory {
        static std::string save(Todo const& todo) {
            std::string out;
            {
                namespace io = boost::iostreams;
                io::stream<io::back_insert_device<std::string> > os(out);

                boost::archive::text_oarchive archive(os);
                archive << todo;
            }

            return out;
        }

        static Todo load(std::string const &s) {
            Todo todo;
            {
                namespace io = boost::iostreams;
                io::stream<io::array_source> is(io::array_source{ s.data(), s.size() });
                boost::archive::text_iarchive archive(is);
                archive >> todo;
            }
            return std::move(todo);
        }
    };
}

namespace visitors {
    namespace detail {
        template <typename F> struct internal_vis : boost::static_visitor<void> {
            internal_vis(F& f) : _f(f) {}
            template <typename... T>
                void operator()(T&&... a) const { return _f(std::forward<T>(a)...); }
            private:
                F& _f;
        };
    }

    template <typename F, typename V>
    void apply(F const& f, V const& v) { return boost::apply_visitor(detail::internal_vis<F const>(f), v); }

    template <typename F, typename V>
    void apply(F const& f, V& v) { return boost::apply_visitor(detail::internal_vis<F const>(f), v); }
}

namespace Todo { namespace Actions { template <typename T>
        void Do(T const& todo) {
            visitors::apply([](auto const& cmd) { cmd.Do(); }, todo);
        }
} }

int main() {
    using namespace Todo;
    Factory factory;

    // ROUNDTRIP save,load
    auto todo = factory.load(
            factory.save(
                Exec("ls -al /home/ajonen")
            )
        );

    std::cout << "Type: " << std::hex << std::showbase << todo.which() << std::endl;

    Actions::Do(todo);

}

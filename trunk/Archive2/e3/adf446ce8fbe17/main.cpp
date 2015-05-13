#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/unique_ptr.hpp>

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

namespace Todo
{
    struct BaseTodo {
        using Ptr = std::unique_ptr<BaseTodo>;

        virtual ~BaseTodo() = default;
        virtual void Do() = 0;
        virtual unsigned getInitType() { return 0x00; };

      private:
        friend class boost::serialization::access;
        template <class Ar> void serialize(Ar &, unsigned) {}
    };

    class Exec : public BaseTodo {
      public:
        Exec(std::string const &command = "") : _command(command){};

        virtual unsigned getInitType() { return 0x01; };
        virtual void Do() { std::cout << "foo: " << getCommand() << std::endl; };

        std::string getCommand() const { return _command; };

      private:
        friend class boost::serialization::access;
        template <class Archive> void serialize(Archive &ar, unsigned) {
            boost::serialization::base_object<BaseTodo>(*this);
            ar &_command;
        }

        std::string _command;
    };
}

//BOOST_CLASS_EXPORT(BaseTodo)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Todo::BaseTodo)
BOOST_CLASS_EXPORT(Todo::Exec)

namespace Todo 
{
    class Factory {
        Factory() = default;
      public:
        using Ptr = BaseTodo::Ptr;
        using FactoryPtr = std::shared_ptr<Factory>;

        static FactoryPtr create() { return FactoryPtr(new Factory); }

        static std::string save(Ptr todo) {
            std::string out;
            {
                namespace io = boost::iostreams;
                io::stream<io::back_insert_device<std::string> > os(out);

                boost::archive::text_oarchive archive(os);
                archive << todo;
            }

            return out;
        }

        static Ptr load(std::string const &s) {
            Ptr p;
            {
                namespace io = boost::iostreams;
                io::stream<io::array_source> is(io::array_source{ s.data(), s.size() });
                boost::archive::text_iarchive archive(is);
                archive >> p;
            }
            return std::move(p);
        }

        Ptr createExec(std::string command) { return BaseTodo::Ptr(new Exec(command)); }
    };
}

int main() {
    auto factory = Todo::Factory::create();

    // ROUNDTRIP save,load
    auto todo = factory->load(
            factory->save(
                factory->createExec("ls -al /home/ajonen")
            )
        );

    std::cout << "Type: " << std::hex << std::showbase << todo->getInitType() << std::endl;
    todo->Do();
}

#include <iostream>
#include <limits.h>

struct DALICommand
{
    const int command_number;
    const bool data_required;
    
    DALICommand(int command_number, bool data_required):
        command_number(command_number),
        data_required(data_required)
    {
    };
};

namespace DALI
{
    namespace StandardCommand
    {
        enum class TargetType_t
        {
            BROADCAST,
            ROTARY_GROUP,
            GROUP,
            ADDRESS
        }
        static const DALICommand CMD_OFF(0, false);
        static const DALICommand CMD_ON(5, false);
    }
    
    namespace SpecialCommand
    {
        enum class TargetType_t
        {
            BROADCAST,
            ROTARY_GROUP,
            GROUP,
            ADDRESS
        }
        static const DALICommand CMD_OFF(0, false);
        static const DALICommand CMD_ON(5, false);
    }
}

class GenericTarget
{
    public:
        virtual int GetTargetType() = 0;
        virtual int GetAddress() = 0;
};

class StdTarget : public GenericTarget
{
    public:
        int GetTargetType()
        {
            return 1;
        };
        
        int GetAddress()
        {
            return 2;
        };
};

class GenericCommand
{
    public:
        GenericCommand(GenericTarget *target, DALICommand command):
            target(target),
            command(command)
        {
        };
        
        GenericTarget *target;
        DALICommand command;
};

class StdDALICommand : public GenericCommand
{
    public:
        StdDALICommand(StdTarget target, DALICommand command):
            GenericCommand(&target_parent, command)
        {
            target_parent = target;
        }
        StdTarget target_parent;

};


void DALICommand ( GenericCommand command )
{
    std::cout << "Command Number: " << command.command.command_number <<std::endl;
    std::cout << "Address: " <<command.target->GetAddress() <<std::endl;
}

int main()
{
    DALICommand( StdDALICommand( StdTarget(), StandardDaliCommand::CMD_ON ) );
    
}

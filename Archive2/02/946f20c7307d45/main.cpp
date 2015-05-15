#include <iostream>
#include <limits.h>

enum class AllTargetTypes : int
{
    BROADCAST = 0,
    ROTARY_GROUP = 1,
    GROUP = 2,
    ADDRESS = 3,
};

class GenericTarget
{
    public:
        GenericTarget(){}
        GenericTarget(AllTargetTypes target_type, int target):
            target_type(target_type),
            target(target)
        {
        }
        
        AllTargetTypes GetTargetType()
        {
            return this->target_type;
        };
        
        int GetAddress()
        {
            return target;
        };
        
        AllTargetTypes target_type;
        int target;
};

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


namespace DALI
{
    namespace Standard
    {
        enum class TargetType : int
        {
            BROADCAST = AllTargetTypes::BROADCAST,
            ROTARY_GROUP = AllTargetTypes::ROTARY_GROUP,
            GROUP = AllTargetTypes::GROUP,
            ADDRESS = AllTargetTypes::ADDRESS,
        };
        
        class Target : public GenericTarget
        {
            public:
                Target(){};
                Target(TargetType target_type, int target):
                    GenericTarget( (AllTargetTypes)target_type, target)
                {
                };
        };
        
        class Command : public GenericCommand
        {
            public:
                Command(Target target, DALICommand command):
                    GenericCommand(&target_parent, command)
                {
                    target_parent = target;
                }
                Target target_parent;
        
        };   
        
        static const DALICommand CMD_OFF(0, false);
        static const DALICommand CMD_ON(5, false);
    }
}



void SendDALICommand ( GenericCommand command )
{
    switch ( command.target->GetTargetType() )
    {
        case AllTargetTypes::BROADCAST:
            std::cout << "Target: Broadcast" << std::endl;
            break;
        default:
            std::cout << "Target: Unknown" <<std::endl;
            break;
    }
    std::cout << "Address: " << command.target->GetAddress() <<std::endl;
    std::cout << "Command Number: " << command.command.command_number <<std::endl;
}

int main()
{
    DALI::Standard::Target target = DALI::Standard::Target(DALI::Standard::TargetType::BROADCAST, 1);
    DALI::Standard::Command command = DALI::Standard::Command( target, DALI::Standard::CMD_ON );
    SendDALICommand( command );
}

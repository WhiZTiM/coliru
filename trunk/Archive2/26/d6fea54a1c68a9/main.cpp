#include <iostream>
#include <climits>
#include <vector>

// This will have all the possible target types
enum class AllTargetTypes : int
{
    BROADCAST = 0,
    ROTARY_GROUP = 1,
    GROUP = 2,
    ADDRESS = 3,
};

// This is the parent target class where you can pull out all target related stuff, such as
// the target type and the address
class GenericTarget
{
    public:
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

// Here's our special generic command class. In this class we can pull out all the information
// related to the class such as the command number, which dtr's are required, all the config flags etc.
class GenericCommand
{
public:
    const int command_number;
    const int device_family;
    const bool dtr1_required;
    const bool dtr2_required;
    
    // Default constructor used for settings all params in this class
    GenericCommand(int command_number_, int device_family_, bool dtr1_required_, bool dtr2_required_)
            : command_number(command_number_)
            , device_family(device_family_)
            , dtr1_required(dtr1_required_)
            , dtr2_required(dtr2_required_)
    {
    }
};

// Just a parent container class for storing GenericTarget and GenericCommand
class GenericExtended
{
    public:
        GenericExtended(GenericCommand command, GenericTarget target)
                : command(command)
                , target(target)
        {
        }
        
        const GenericCommand command;
        const GenericTarget target;
};


namespace DALI
{
    namespace Standard
    {
        // Here's our standard dali supported target types. Here we select from AllTargetTypes the
        // targets we support within our DALI::Standard namespace.
        enum class TargetType : int
        {
            BROADCAST = AllTargetTypes::BROADCAST,
            GROUP = AllTargetTypes::GROUP,
            ADDRESS = AllTargetTypes::ADDRESS,
        };
        
        class Target : public GenericTarget
        {
        public:
            Target(TargetType target_type, int target):
                GenericTarget( (AllTargetTypes)target_type, target)
            {
            }
        };
        
        // Here's our DALI::Standard::Command type which is the object we use for creating
        // "GenericCommand". This class just makes i
        class Command : public GenericCommand
        {
        public:
            // All we do is set the params we need in the GenericCommand constructor, and specify 
            // defaults for the other stuff. You can also use constructor chaining here to centralise 
            // the code abit more.
            Command(int command_number, bool dtr1_required)
                    : GenericCommand(command_number, 0, dtr1_required, false)
            {
                
            }
        };
        
        // Here's the container which ensures that we specify explicit types that this namespace supports.
        // This will be the object we create when passing into the serialise method.
        class Extended : public GenericExtended
        {
        public:
            // Extended only accepts Command and Target types (the subclasses of GenericTarget and GenericCommand
            // within this namespace).
            Extended(Command command, Target target) 
                    : GenericExtended(command, target)
            {
            }
            
            
        };
        
        // Here is where the magic happens. We will literally have a million of these defined for each namespace
        // (eg. emergency commands, switch sensor commands) and they will have their own "Extended" class which
        // takes an explicit "Command" such as below, and "Target" such as the class above in here.
        static const Command CMD_OFF(0, false);
        static const Command CMD_ON(5, false);
    }
}

// Our special serialise free function which will just read everything in GenericExtended and serialise straight to payload_out
void SerialiseExtended(const GenericExtended& extended_command, std::vector<uint8_t>& payload_out)
{
    std::cout << "Target type: " << int(extended_command.target.target_type) << std::endl;
    std::cout << "Target address: " << extended_command.target.target << std::endl;
    
    std::cout << "Command Number: " << extended_command.command.command_number << std::endl;
    std::cout << "Device Family: " << extended_command.command.device_family << std::endl;
    std::cout << "DTR1 required: " << extended_command.command.dtr1_required << std::endl;
    std::cout << "DTR2 required: " << extended_command.command.dtr2_required << std::endl;
}

int main()
{
    std::vector<uint8_t> result_payload;
    
    std::cout << "------Serialise CMD_ON------" << std::endl;
    SerialiseExtended( 
            DALI::Standard::Extended(
                    DALI::Standard::CMD_ON,
                    DALI::Standard::Target(DALI::Standard::TargetType::BROADCAST, 1)
            ),
            result_payload
    );
    
    std::cout << std::endl << "------Serialise CMD_OFF------" << std::endl;
    SerialiseExtended( 
            DALI::Standard::Extended(
                    DALI::Standard::CMD_OFF,
                    DALI::Standard::Target(DALI::Standard::TargetType::ADDRESS, 50)
            ),
            result_payload
    );
}

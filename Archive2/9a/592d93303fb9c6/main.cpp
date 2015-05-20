#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
#include <iterator>
#include <string>



enum class Operation : uint8_t
{
    Start   = 0x00,
    Poll    = 0x01,
    Stop    = 0x02,
};

enum class Command : uint8_t
{
    CheckForNewDevices          = 0x00,
    AddressNewDevice            = 0x01,
    RefreshFromTarget           = 0x02,
    IdentifyTarget              = 0x03,
    RestoreTargetFromDatabase   = 0x04,
    DeleteTarget                = 0x05,
    DestroyTarget               = 0x06,
    CurrentCommand              = 0x07,
};

//=========================================== Target ==================================================//

enum class TargetType : uint8_t
{
    STD = 0x00,
    GRP = 0x01,
    ADG = 0x02,
    ROT = 0x03,
    ARG = 0x04,
    ADA = 0x05,
    ATA = 0x06,
    BCT = 0x07,
};

// In this example, target has two constructors where one constructor accepts both the target type
// and the target address, and the other constructor accepts just the target type and sets the target
// address to 255 (this would be used for targets such ARG and ADG which require an address of 255).
struct Target
{
    static const uint8_t DefaultAddress = 255;
    
    // Public locals
    TargetType type;
    uint8_t address;
    
    // Need a default constructor
    Target()
    { }
    
    Target(TargetType type_, uint8_t address_)
            : type(type_)
            , address(address_)
    {
        Sanitise();
    }
    
    Target(TargetType type_)
            : Target(type_, DefaultAddress)
    { }
    
    void Sanitise()
    {
        switch (this->type)
        {
        case TargetType::STD:
            if (this->address > 127)
            {
                throw std::runtime_error("Invalid address.");   
            }
            break;
        
        case TargetType::GRP:
            if (this->address > 15)
            {
                throw std::runtime_error("Invalid address.");   
            }
            break;
        
        case TargetType::ROT:
            if (this->address > 31)
            {
                throw std::runtime_error("Invalid address.");
            }
            break;
        
        case TargetType::ADG:
        case TargetType::ARG:
            if (this->address != DefaultAddress)
            {
                throw std::runtime_error("Invalid address.");
            }
            break;
        
        case TargetType::ADA:
        case TargetType::ATA:
        case TargetType::BCT:
            if (this->address > 2)
            {
                throw std::runtime_error("Invalid address.");
            }
            break;

        default:
            throw std::runtime_error("Unrecognised target type.");
        }
    }
};

//=========================================== Request (Client) Payload ==================================================//

struct ControlRequest
{
    static const uint16_t DefaultData = 65535;
    
    // Public locals
    Operation operation;
    Command command;
    Target target;
    uint16_t data_1;
    uint16_t data_2;
    std::vector<uint8_t> dynamic_data;

    // Copy constructor
    ControlRequest(const ControlRequest& other)
            : ControlRequest(other.operation, other.command, other.target, other.data_1, other.data_2, other.dynamic_data)
    { }
    
    // Need a default for deserialise. Just doesn't initialise anything, please implement some sort of initialisation though just to
    // prevent UB when reading out of the integral types.
    ControlRequest()
    { }

    ControlRequest(Operation operation_, Command command_, Target target_)
            : ControlRequest(operation_, command_, target_, DefaultData)
    { }
    
    ControlRequest(Operation operation_, Command command_, Target target_, uint16_t data_1_)
            : ControlRequest(operation_, command_, target_, data_1_, DefaultData)
    { }
    
    ControlRequest(Operation operation_, Command command_, Target target_, uint16_t data_1_, uint16_t data_2_)
            : ControlRequest(operation_, command_, target_, data_1_, data_2_, {})
    { }
    
    ControlRequest(
            Operation operation_, 
            Command command_, 
            Target target_, 
            uint16_t data_1_, 
            uint16_t data_2_, 
            const std::vector<uint8_t>& dynamic_data_)
            : operation(operation_)
            , command(command_)
            , target(target_)
            , data_1(data_1_)
            , data_2(data_2_)
            , dynamic_data(dynamic_data_)
    {
        Sanitise();
    }
    
    void Sanitise()
    {
        // Here you would check all the parameters based on the command.
        //
        // The commands fall into one or more of the following groups:
        // - A command which supports all operations
        // - A command which supports a selection of operations
        // - A command which requires data_1
        // - A command which requires data_2
        // - A command which requires dynamic_data
        // - A command which supports all target types
        // - A command which supports a selection of target types
        //
        // Note: If a field is not required by a command, (eg. data is not required by command CheckForNewDevices),
        // the unused field should be defaulted to 255 (0xFF).
    }
};

//=========================================== Serialise/deserialise ==================================================//

// The serialise method doesn't need to worry about sanitising the ControlRequest as the request was already sanitised
// on construction. Thus, this method becomes alot simpler as it is now only responsible for serialising into the actual
// payload. Another added benefit is that the function is now a free function and doesn't need to be a member of ControlRequest.
// You can make it a member if you want, but having it outside completely removes the dependency on knowing the payload positions
// for each byte etc.
void Serialise(const ControlRequest& request, std::vector<uint8_t>& payload_out)
{
    payload_out.push_back(static_cast<uint8_t>(request.operation));
    payload_out.push_back(static_cast<uint8_t>(request.command));
    payload_out.push_back(static_cast<uint8_t>(request.target.type));
    payload_out.push_back(request.target.address);
    payload_out.push_back(static_cast<uint8_t>(request.data_1 >> CHAR_BIT));
    payload_out.push_back(static_cast<uint8_t>(request.data_1));
    payload_out.push_back(static_cast<uint8_t>(request.data_2 >> CHAR_BIT));
    payload_out.push_back(static_cast<uint8_t>(request.data_2));
    payload_out.push_back(255);     // Reserved
    payload_out.insert(std::end(payload_out), std::begin(request.dynamic_data), std::end(request.dynamic_data));
}

void Deserialise(ControlRequest& request_out, const std::vector<uint8_t>& payload_in)
{
    if (payload_in.size() < 9)
    {
        throw std::length_error("Payload to short brus.");
    }
    
    request_out.operation = static_cast<Operation>(payload_in[0]);
    request_out.command = static_cast<Command>(payload_in[1]);
    request_out.target.type = static_cast<TargetType>(payload_in[2]);
    request_out.target.address = payload_in[3];
    
    request_out.data_1 = payload_in[4];
    request_out.data_1 = static_cast<uint16_t>((request_out.data_1 << CHAR_BIT) | payload_in[5]);
    request_out.data_2 = payload_in[6];
    request_out.data_2 = static_cast<uint16_t>((request_out.data_1 << CHAR_BIT) | payload_in[7]);
    
    std::vector<uint8_t> dynamic_data;
    
    // Check if has dynamic data
    if (payload_in.size() > 9)
    {
        request_out.dynamic_data.assign(std::begin(payload_in) + 9, std::end(payload_in));
    }
    
    // Explicitly call sanitise as we have modified member variables.
    request_out.Sanitise();
}


//=========================================== Example ==================================================//
int main()
{
    ControlRequest request_serialise(Operation::Start, Command::DeleteTarget, Target(TargetType::STD, 63), 43690, 43537, {1,2,3,4});
    
    std::vector<uint8_t> payload;
    
    Serialise(request_serialise, payload);
    
    std::copy(std::begin(payload),std::end(payload),std::ostream_iterator<int>(std::cout, " " ));
    
    
    ControlRequest request_deserialise;
    
    Deserialise(request_deserialise, payload);
    
    std::cout << "\n\n*** Deserialise ***" << std::endl;
    
    std::cout << "Command: " << std::to_string(static_cast<uint8_t>(request_deserialise.command)) << std::endl;
    std::cout << "Operation: " << std::to_string(static_cast<uint8_t>(request_deserialise.operation)) << std::endl;
    std::cout << "Target type: " << std::to_string(static_cast<uint8_t>(request_deserialise.target.type)) << std::endl;
    std::cout << "Target address: " << std::to_string(request_deserialise.target.address) << std::endl;
    std::cout << "Data 1: " << std::to_string(request_deserialise.data_1) << std::endl;
    std::cout << "Data 2: " << std::to_string(request_deserialise.data_2) << std::endl;
    std::cout << "Dynamic data: ";
    std::copy(std::begin(request_deserialise.dynamic_data),std::end(request_deserialise.dynamic_data),std::ostream_iterator<int>(std::cout, " " ));
}

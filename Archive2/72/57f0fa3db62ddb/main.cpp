#include <iostream>
#include <string>
#include <vector>

namespace Daliset
{
    //#include "DALICommandAccess.inc"
    //#include "DALICommandGROUP.inc"
    //#include "DALICommandAccess2.inc"
    
    //Here is sample
    enum DALICommandAccess
    {
        BASE_CONTROL = 1,
    };

}

struct Command
{
	int access_value;
	int command_type_value;
	int command_group_value;
	int command_value;
};
    
int main()
{
	#define CREATE_COMMAND( access_type, access_value, command_type_type, command_type_value, command_group_type, command_group_value, command_type, command_value, x, y, z, j) \
        Command command_type = {access_value, command_type_value, command_group_value, command_value};
        
    
    //#include "DALI_Commands_Standard.inc"- We'll include two samples to make it run
	CREATE_COMMAND ( BASE_CONTROL, 1, DALI_COMMAND, 0, STANDARD, 1, CMD_OFF, 0, false, false, 0x00, false )
    CREATE_COMMAND ( BASE_CONTROL, 1, DALI_COMMAND, 0, STANDARD, 1, CMD_RECALL_MAX, 5, false, false, 0x00, false )
    
	#undef CREATE_COMMAND

	std::cout << "Command Number: " << CMD_OFF.command_value << std::endl;
    std::cout << "Command Number: " << CMD_RECALL_MAX.command_value << std::endl;
}
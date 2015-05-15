#include <iostream>
#include <string>
#include <cstring>
 
int main()
{
    std::string shader = {
                  "#version 430\n" 
                  "void main(void)\n"
                  "{\n"
                  "     gl_Position = vec4(1.0);\n"
                  "}"};
                  
    
    
    /*
    std::cout << "length is " << shader.length() << "\n";
    std::cout << "c_str() length is " << strlen(shader.c_str()) << "\n";
    */
    
    const char * shaderCstr = shader.c_str();
    
    for(char i = shaderCstr[0]; i < strlen(shaderCstr); ++i)
    {
        std::cout << &i;
    }
        
    //std::cout << shader;
}
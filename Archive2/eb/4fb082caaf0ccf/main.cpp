#include <algorithm>
#include <iostream>
#include <string>

bool IsMobile(const Wt::WEnviroment& env) 
{
    if (env.agentIsIEMobile())    
        return true;
        
    if (env.agentIsMobileWebKit())
        return true;
    
    std::string userAgent = env.userAgent();
    std::transform(std::begin(userAgent), std::end(userAgent), 
                    std::begin(userAgent), ::tolower);
                    
    return userAgent.find("mobile") != std::string::npos;
}


int main() { 
}

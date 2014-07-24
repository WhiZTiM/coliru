/***************************************************************************** 
* 
* xclm.c - A replacement license server for Microchip embedded compilers 
* 
*****************************************************************************/
    
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
    
enum
{ 
    LICENSE_FREE, 
    LICENSE_STANDARD, 
    LICENSE_PRO, 
    LICENSE_NULL, 
    LICENSE_NOCPP, 
    LICENSE_CPPFREE, 
    LICENSE_CPPFULL 
}; 
    
/* Padded keystring for XC8 compiler */
const char XC8_KEY[] = 
"120205690315959428539973816151144999076498629234049888"
"179227155534183820578631309018645587360933525814619915"
"779526071941849199599867328321377639683720790016145394"
"178294936006671919157552224249424396156390966410329115"
"909578096551465127991840510571525598801543710978110203"
"982753256678760352233698494166181105701471577863949973"
"752378527793703095602570185318279000307654710756304884"
"332086971157374238079344503160762531771453544441183117"
"818224971852635709182448998796203508335756172022603393"
"785870328131267807990054177348691152537065623705744096"
"622171290262732073236149224291304052855537234103307757"
"779806424202430488281521000914602653822069627155202082"
"274335001015294801198690117625951676366998171835575234"
"880703719555742347294083595208861666202572853755813079"
"282586487282173705566196898952662018776810629200817792"
"338135876828426412432431480282173674506720693507626895"
"304345939375032966363775750624733239923482883107733905"
"27680200757984356120205690"; 
    
int main(int argc, char *argv[]) 
{ 
    int license = LICENSE_FREE; 
    int ii; 
    
    for (ii = 0; ii < argc; ++ii) 
    { 
        if (!strcmp(argv[ii], "swxc32") || 
            !strcmp(argv[ii], "swxc16") || 
            !strcmp(argv[ii], "swxc8")) 
        { 
            license = LICENSE_PRO; 
        } 
        else if (!strcmp(argv[ii], "swxcpp32")) 
        { 
            license = LICENSE_CPPFULL; 
        } 
        else if (!strcmp(argv[ii], "-hash")) 
        { 
            int index = atoi(argv[ii+1]); 
            printf("%.10s", &XC8_KEY[index]); 
        } 
    } 
    
    return license; 
}
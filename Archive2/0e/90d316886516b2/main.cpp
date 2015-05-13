#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// for temp
#define NBITS 5
#define NSUCCLIST 3

class Constants
{
private :
    PreferenceCore *preferencesCore ;
    int nbits ;
    int idlen ;
    int nfiggers ;
    int nsuccessors ;
    int bufsize ;
    int stabilize_period ;
    int max_wellknown ;
} ;

#endif // constants.h
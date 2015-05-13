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
    int pint_thresh ;
    BitInt two ;
    // int FIND_SUCCESSOR =1 ;
    BitInt ChordSpace ;
    
public :
    ChordId MaxChordId ;
    ChordId MinChordId ;
    Constants( PreferencesCore *prefer ) ;
    void init () ;
    int getNbits () ;
    int getIdlen () ;
    int getNfigngers () ;
    int getNsuccessors () ;
    int getBufsize () ;
    int getStabilize_period () ;
    int getMax_wellknown () ;
    BitInt getChordSpace () ;
} ;

#endif // constants.h
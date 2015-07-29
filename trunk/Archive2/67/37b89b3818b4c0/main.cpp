/**
 * file                       : main.cpp
 *------------------------------------------
 * Author                     : Christophe Angeli
 * Improvements & portability : Arnaud Calmettes
 *
 */
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
 
#ifndef __unix__
# include <windows.h>
#endif
 
 
// Note/Octave/Frequency matching
 
int NOTES[12][9] =
{
    {16, 33, 65, 131, 262, 523, 1046, 2093, 4186},
    {17, 35, 69, 139, 277, 554, 1109, 2217, 4435},
    {18, 37, 73, 147, 294, 587, 1175, 2349, 4699},
    {19, 39, 78, 155, 311, 622, 1244, 2489, 4978},
    {21, 41, 82, 165, 330, 659, 1328, 2637, 5274},
    {22, 44, 87, 175, 349, 698, 1397, 2794, 5588},
    {23, 46, 92, 185, 370, 740, 1480, 2960, 5920},
    {24, 49, 98, 196, 392, 784, 1568, 3136, 6271},
    {26, 52, 104, 208, 415, 831, 1661, 3322, 6645},
    {27, 55, 110, 220, 440, 880, 1760, 3520, 7040},
    {29, 58, 116, 233, 466, 932, 1865, 3729, 7459},
    {31, 62, 123, 245, 494, 988, 1975, 3951, 7902}
};
 
enum
{
    SILENCE = -1,
    DO = 0,
    DO_ = 1,
    RE = 2,
    RE_ = 3,
    MI = 4,
    FA = 5,
    FA_ = 6,
    SOL = 7,
    SOL_ = 8,
    LA = 9,
    LA_ = 10,
    SI = 11
};
 
enum
{
    OCTAVE_0 = 0,
    OCTAVE_1 = 1,
    OCTAVE_2 = 2,
    OCTAVE_3 = 3,
    OCTAVE_4 = 4,
    OCTAVE_5 = 5,
    OCTAVE_6 = 6,
    OCTAVE_7 = 7,
    OCTAVE_8 = 8,
};
 
std::map<std::string, int> noteMap;
 
// Global variables
int TEMPO = 250;
int DURATION=TEMPO;
int OCTAVE = 0;
 
#ifdef __unix__
/**
 * Linux (dirty) adaptation from <windows.h>'s Beep function
 */
void Beep(int freq, int length)
{
    std::stringstream ossBeep;
    ossBeep << "beep -f " << freq << " -l " << length;
    system(ossBeep.str().c_str());
}
#endif
 
 
/**
 * Reads the music sheet
 */
int readFile( const char *file )
{
    std::ifstream musicFile(file);
    if (! musicFile.is_open() )
        return 1;
     
    int octave = 0;
    double duration = 0;   
    std::string duration_str;  
    std::string line;
    std::string note;
     
     
    while ( std::getline( musicFile, line ) )
    {
        note = "";
        octave = 0;
        duration = 0;
        duration_str = "";
 
        std::stringstream lineStream(line);
        lineStream >> note >> octave >> duration_str;
         
        // Empty line skipping
        if( note == "" )
            continue;
 
        // Tempo management
        std::string::size_type pos = note.find("TEMPO");
        if( pos  != std::string::npos )
    {
            if( octave != 0)
            {          
                TEMPO = octave;
                DURATION = TEMPO;
                continue;
            }
        }
     
        // Octave management   
        if( octave )
        {
            OCTAVE = octave;
    }
 
        // Duration management
        // (this looks dirty because of fraction interpretation)
        if( duration_str != "" )
        {
            pos = duration_str.find('/');
            if( pos != std::string::npos)
            {
                std::istringstream numerateur( duration_str.substr(0,pos+1) );
                std::istringstream denominateur (duration_str.substr(pos+1, duration_str.size()-(pos + 1)) );
                int num = 1;
                int den = 1;
                numerateur >> num;
                denominateur >> den;
                DURATION = (int) (TEMPO * num / den);
            }
            else
            {
                std::istringstream stream(duration_str);
                stream >> duration;
                DURATION = (int) (TEMPO * duration);
            }
        }
 
        // Silence management
        if (noteMap[note.c_str()] == SILENCE)
            Beep(1, DURATION);
        else
            // Finally, play the note !
            // This calls the "Beep" system function under windows
            // Or the custom one under Linux
            Beep(NOTES[ noteMap[note.c_str()] ][ OCTAVE ], DURATION);
    }
    return 0;
}
 
 
// Main : Basic declarations and parameter parsing
int main(int argc, char* argv[])
{
    noteMap["DO"] = DO;
    noteMap["DO_"] = DO_;
    noteMap["RE"] = RE;
    noteMap["RE_"] = RE_;
    noteMap["MI"] = MI;
    noteMap["FA"] = FA;
    noteMap["FA_"] = FA_;
    noteMap["SOL"] = SOL;
    noteMap["SOL_"] = SOL_;
    noteMap["LA"] = LA;
    noteMap["LA_"] = LA_;
    noteMap["SI"] = SI;
    noteMap["_"] = SILENCE;
 
 
    if( argc == 0 || ( argc != 0 && readFile(argv[1]) == 1 ))
        std::cout << "Usage : " << argv[0] << " FILENAME \n" << std::endl;
 
    return 0;
}
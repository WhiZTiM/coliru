    #include <iostream>
    #include <regex>
    #include <string>
    using namespace std;

    int main()   
    {
        regex matcher("a*(needle)b*");
        smatch findings;
        string haystack("aaaaaaaaneedlebbbbbbbbbbbbbb");
    
        if( regex_match(haystack, findings, matcher) )
        {
            // What do I put here to know how the offset of "needle" in the 
            // string haystack?
    
            // This is the position of the entire, which is
            // always 0 with regex_match, with regex_search
            cout << "smatch::position - " << findings.position() << endl;
    
            // Is this just a string, or what?
            cout << "Needle - " << findings[1] << endl;
        }
        
        return 0;
    }
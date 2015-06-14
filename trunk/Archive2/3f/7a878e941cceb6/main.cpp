/***************************************************************************************
 * 
 * This program was written by Julien LE BOUCHER
 * on June 14, 2015 and was endded at 2 : 50 AM
 * after he discovered an interesting way to learn C++.  
 *
 * He specially wants to use this section to thank the author for his terrific guide. 
 * .
 * THANK YOU;
 * 
 * I also want to say that I opted for the GNU indent style which rocks the more.
 *  
 **************************************************************************************/
  #include <iostream>

int
main (int argc, char *argv[] ) 
// je ne suis pas sûr d'avoir bien compris cette histoire d'argc et d'argv.
// ça ressemble à la voie de communication entre l'OS et le programme.
// Qu'est-ce que ça peut éventuellement contenir, à part le nom de mon programme ?
{     
    std::cout << "argc :" << argc << std::endl;
    int i(0);
    while(i<argc)
     {
        std::cout <<argv[i]<< std::endl;
        i++;
     }
} 
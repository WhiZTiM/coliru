#include <iostream>

int garland(std::string word){
    int garlandDegree { -1 };
    int maxDegree;
    if(word.size() % 2 == 1){
        char rightLetter, leftLetter;
        int centerLetter = word.size() / 2 + 1;
        maxDegree = word.size() / 2;
        
        do{
            garlandDegree++;
            rightLetter = word[garlandDegree];
            leftLetter = word[garlandDegree + centerLetter];
        }while (rightLetter == leftLetter && garlandDegree < maxDegree);
    }
    else{
        std::string leftLetters = word.substr(0, word.size() / 2);
        std::string rightLetters = word.substr(word.size() / 2);
        maxDegree = word.size() / 2;
        do{
            garlandDegree++;
        }while (leftLetters[garlandDegree] == rightLetters[garlandDegree] && garlandDegree < maxDegree);
        
    }
    
    return garlandDegree;
}


int main()
{
    std::cout << garland("onion");
}

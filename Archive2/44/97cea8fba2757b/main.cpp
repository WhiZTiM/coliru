#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

/*
std::string getCurrentWorkingDirectory() {
    char cCurrentPath[FILENAME_MAX];
    char *result;
    //result = 'c';
#ifdef WIN32
    //result = _getcwd(cCurrentPath, sizeof(cCurrentPath));
#else
    //result = getcwd(cCurrentPath, sizeof(cCurrentPath));
#endif

    if (result == NULL) {
        std::cout << "COMPAT WARNING: cannot get current working path!" << std::endl;
        return std::string("");
    }

    return std::string(cCurrentPath);
}
*/

double getSqrtt(int x){
    int i = 1;
    double solution = 1;
    double solution2 = 1;
    double solutionSwap;
    while (i<=x){
        std::cout << "fib: " << solution << " | Teta: " << solution/solution2 << std::endl;
        
        solutionSwap = solution;
        solution = solution2 + solution;
        solution2 = solutionSwap;
        i++;
        if (((int)solution)%3==0){
            std::cout << "Gerade: ";
        }
        else{
            std::cout << "Ungerade: ";
        }
    }
    return solution; 
}

void cubeSolver(int x){
    std::string yolo = "bam";
    std::sort(yolo.begin(), yolo.end());
    std::cout << yolo <<std::endl;
}
std::string removeQuotations(std::string str)
{
    std::size_t place = 0;
    place = str.find("\""); // has to be tested one time before you get in the while loop. otherwise the first letter will not be tested.
    if (place != std::string::npos){
        str.replace(str.begin()+place, str.begin()+place+1,"\\\"");
    }
    while(place != std::string::npos){
        place = str.find("\"", place +2);
        if (place != std::string::npos){
            str.replace(str.begin()+place, str.begin()+place+1,"\\\"");
        }
    }
    return str;
}

std::string runnerParser(std::string parameters)
{
    std::vector<std::string> splittedParameters;
    std::string word = "";
    bool in_escaped = false;
    bool in_slash = true;
    for (std::string::const_iterator iter = parameters.begin(); iter != parameters.end(); ++iter) {
            switch (*iter) {
            case '\\':
                std::cout << "nTest: " << word << std::endl;
                in_slash = true;
                word += '\\';
                ++iter;
                //break;

            case '\"':
                if (in_slash){
                    std::cout << "nTest2" << std::endl;
                    word = word.substr(0, word.size()-1);  //nTest weiter testen was raus kommt!
                    word+= '"';
                    iter++;
                    in_slash = false;
                    break;
                }
                else{
                    in_slash = false;
                    in_escaped = !in_escaped;
                    iter++;
                }


            default:
                in_slash = false;
                break;
            }

            if (iter == parameters.end())
                break;

            if ((*iter == ' ' || *iter == '\t') && !in_escaped) {
                while ((*iter == ' ' || *iter == '\t') && iter != parameters.end())
                    ++iter;

                if (*iter == '"'){
                    in_escaped = !in_escaped;
                    ++iter;
                }
                splittedParameters.push_back(word);
                word = "";
            }

            if (iter == parameters.end())
                break;

            word += *iter;
        }
    return word;
}


int main(){
    cubeSolver(3);
    std::cout << removeQuotations("/home/noll/Documents/test/test\"folder") << std::endl;
    std::cout << runnerParser(removeQuotations("/home/noll/Documents/test/test\"folder")) << std::endl;
    //getCurrentWorkingDirectory();
    //std::cout << getSqrtt(200) << std::endl;
}
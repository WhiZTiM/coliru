echo **** Compilation du programme C++ avec les avertissements ****
clang++ main.cpp -o mon_programme -std=c++14 -Wall -Wextra -pedantic -O2
echo **** Compilation du programme C++ sans les avertissements ****
clang++ main.cpp -o mon_programme -std=c++14 -O2
echo **** Exécution du programme C++ ****
./mon_programme
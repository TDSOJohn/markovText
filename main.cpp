#include <iostream>


#include "Markov.hpp"



int main()
{
    std::string incipit1, incipit2;

    MarkovChain mkv(2);

//    mkv.readData("save.txt");

    mkv.trainFromFile("Text/repubblica.txt");

    mkv.saveData("save.txt");

//    mkv.printData();

    std::cout << "\n\n\tInserisci un incipit di due parole:\n\n\tprima:";
    std::cin >> incipit1;

    std::cout << "\n\tseconda:";
    std::cin >> incipit2;

    mkv.generateData(400, incipit1, incipit2);

    return 0;
}

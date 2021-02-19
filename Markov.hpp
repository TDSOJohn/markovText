//
//  Markov.hpp
//  TextGenerator
//
//  Created by Giovanni Basso on 08/02/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef markov_hpp
#define markov_hpp


#include <string>
#include <vector>
#include <deque>
#include <map>



//  Prefix is a sequence of NPREF (best value = 2) words
typedef std::deque<std::string>    Prefix;

//  NONWORD is used at beginning or end of string
const std::string NONWORD = "\n";


class MarkovChain
{
public:
    MarkovChain(int nprefIn);
    void                train(std::string stringIn);
    void                trainFromFile(std::string fileName);
    void                reset();

    void                printData();
    void                saveData(std::string fileName);
    void                readData(std::string fileName);

    void                generateData(int maxWords, std::string incipit1 = "\n", std::string incipit2 = "\n");


private:
    std::map<Prefix, std::vector<std::string> > stateTab;
    const int                                   mNPREF;


private:
    //  add a word to suffix deque, update prefix keeping it at NPREF words max
    void                                        add(Prefix& prefixIn,
                                                    const std::string& stringIn);



};


#endif //markov_hpp

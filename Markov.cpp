//
//  Markov.cpp
//  TextGenerator
//
//  Created by Giovanni Basso on 08/02/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>


#include "Markov.hpp"
#include "json.hpp"



using json = nlohmann::json;


MarkovChain::MarkovChain(int nprefIn):
mNPREF(nprefIn)
{
    srand(time(NULL));
}


void MarkovChain::train(std::string stringIn)
{
    Prefix prefix;

    //  l'add iniziale con NONWORD rompe l'output su stringa del JSON perché
    //  mette le {} e i :
    /*    for (int i = 0; i < mNPREF; i++)
     add(prefix, NONWORD);
     */

    size_t                      pos = 0;
    std::string                 token;
    std::string                 delimiter = " ";
    std::regex                  words_regex("[a-zA-Z.:,;]+[']*");

    auto                        words_begin = std::sregex_iterator( stringIn.begin(),
                                                                   stringIn.end(),
                                                                   words_regex);
    auto words_end = std::sregex_iterator();

    for(std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        token = (*i).str();
        this->add(prefix, token);
        //        stringIn.erase(i);
    }
    /*    token = (*i).str();
     this->add(prefix, token);*/
}


void MarkovChain::trainFromFile(std::string fileName)
{
    std::ifstream   readFile;
    std::string     line;

    readFile.open(fileName);

    if(readFile.is_open())
    {
        while(getline(readFile, line))
            train(line);
        readFile.close();
    } else
    {
        std::cout << "Could not open file!\n\n";
    }
}


void MarkovChain::reset()
{

}


void MarkovChain::printData()
{
    for(auto elem : stateTab)
    {
        std::cout << "-->" << elem.first[0] << " " << elem.first[1] << "<--" << "\n";
        for(auto i : elem.second)
            std::cout << i << "\t";
        std::cout << "\n\n";
    }
}


void MarkovChain::saveData(std::string fileName)
{
    json jmap = json::array();
    int counter = 0;
    //  Manual insertion of std::map data into json structure (bugs were happening)
    for(auto el : stateTab)
    {
        jmap[counter] = json::array();
        jmap[counter][0] = json::array();
        jmap[counter][1] = json::array();

        for(int i = 0; i < mNPREF; i++)
            jmap[counter][0][i] = el.first[i];

        for(int i = 0; i < el.second.size(); i++)
            jmap[counter][1][i] = el.second[i];
        counter++;
    }

    std::string jmap_str = jmap.dump();

    std::ofstream saveFile;
    saveFile.open(fileName);

    if(saveFile.is_open())
    {
        saveFile << jmap_str;
        saveFile.close();
    } else
    {
        std::cout << "Could not open file!\n\n";
    }
}


void MarkovChain::readData(std::string fileName)
{
    std::ifstream readFile;
    std::string line;
    std::stringstream fileData;

    json dataIn;

    readFile.open(fileName);
    if(readFile.is_open())
    {
        readFile >> dataIn;
    } else
    {
        std::cout << "Could not open file!\n\n";
    }
    stateTab = dataIn.get<std::map<Prefix, std::vector<std::string>>>();
}


void MarkovChain::generateData(int maxWords, std::string incipit1, std::string incipit2)
{
    Prefix prefix;

    prefix.push_back(incipit1);
    prefix.push_back(incipit2);

    for (int i = 0; i < maxWords; i++)
    {
        auto found = stateTab.find(prefix);
        if(found == stateTab.end())
            break;

        std::vector<std::string>& suf = found->second;
        const std::string& w = suf[rand() % suf.size()];

        std::cout << w << " ";
        prefix.pop_front();
        prefix.push_back(w);
    }
    std::cout << "\n\n";
}


void MarkovChain::add(Prefix& prefixIn, const std::string& stringIn)
{
    if(prefixIn.size() == mNPREF)
    {
        stateTab[prefixIn].push_back(stringIn);
        prefixIn.pop_front();
    }
    prefixIn.push_back(stringIn);
}

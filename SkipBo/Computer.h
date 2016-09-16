#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"


class Computer : public Player {
    friend class SkipBo;
public:
    
    Computer(std::string name);
    Computer(std::string name, std::vector<int> pStock, std::vector<int> pHand, std::vector<int> d1,
             std::vector<int> d2, std::vector<int> d3, std::vector<int> d4);
    
    ~Computer();
    
    void move(Deck * deck, std::vector<BuildPile*>  buildPiles, std::vector<int> & finished, int choice, int numPlayers);
    
    
} ;









#endif

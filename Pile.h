#ifndef PILE_H
#define PILE_H

//Abstract class Piles

#include <vector>
#include <string>
class Pile {
    friend class SkipBo;
protected:
    std::vector<int> cards;
    
public:
    
    Pile();
    virtual ~Pile() { };
    //There is already a function writted for this called
    //random shuffle in the algorithm library
    void shuffle();
    
    int  getSize();
    
    std::string returnsPileNums();
    
} ;


#endif

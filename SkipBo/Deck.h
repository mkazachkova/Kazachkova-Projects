#ifndef DECK_H
#define DECK_H

#include "Pile.h"

class Deck : public Pile {
    friend class SkipBo;
private:
    //Make sure you always increment position when
    //the deck is changed
    
public:
    Deck ();
    Deck(std::vector<int> temp);
    
    ~Deck();
    
    //Called on the deck object. WHEN DECK SIZE IS 0
    //Copy everything from temp build pile to deck
    //and clear the temp build pile
    void addBuildPile(std::vector<int> & finishedPile);
    int removeOneCard();
    
    
} ;





#endif

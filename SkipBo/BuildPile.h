#ifndef BUILDPILE_H
#define BUILDPILE_H

#include "Pile.h"

class BuildPile : public Pile {
    friend class SkipBo;
    
    
    public :
    BuildPile();
    ~BuildPile();
    BuildPile(std::vector<int> &tempPile);
    //returns the data of the last card put into the build pile
    unsigned long peek();
    //Occurs when the numcards equals 12. Puts card into the temp build pile
    //When deck runs out, temp buildPile will be shuffled. This sets everything
    //in the build pile that it's called onto 0
    void reset(std::vector<int> & finishedPile);
    bool addToBuildPile(int cardNum, std::vector<int> & finishedPile);
    
    
    
} ;




#endif

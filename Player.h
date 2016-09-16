#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <stack>
#include <vector>
#include "Deck.h"
#include "BuildPile.h"
#include "Pile.h"

//Abstract class

class invalid_card: public std::exception {
public:
    virtual const char* what() const throw() // override what() to customize error string
    {  return "This card was not a valid choice. Please try again.";  }
};

class invalid_pile: public std::exception {
public:
    virtual const char* what() const throw() // override what() to customize error string
    {  return "This pile was not a valid choice. Please try again.";  }
};


class Player {
    friend class SkipBo;
protected:
    std::string name;
    std::stack<int> * stock;
    std::vector<int>  hand;
    //Stores four discard piles
    std::vector<std::stack<int>*> *  myDiscards;
    
public:
    
    //constructor
    Player();
    Player(std::string name);
    int topCard();
    //Call at the beginning of every turn and when the hand
    //equals 0 prior to a discard
    //"num" is the number of cards currently in the hand
    void draw(Deck *deck);
    
    void loadStockPiles(Deck *deck, int numCardsPerPile);
    
    virtual ~Player() { };
    
    bool addToDiscard(int pileNum, int cardNum) throw(invalid_card, invalid_pile);
    
    //Takes a card from the hand and adds it to the build pile
    bool handToBP(BuildPile * chosen, int cardNum, Deck * deck, std::vector<int> & finishedPile) throw(invalid_card, invalid_pile);
    
    //Takes a card from specified discard pile and adds to build pile
    bool discardToBP(BuildPile *  chosen, int fromPileNum, std::vector<int> & finishedPile) throw(invalid_card, invalid_pile);
    
    //Takes a card from the stock pile and adds to it the specified buildPile
    bool stockToBP(BuildPile * chosen, std::vector<int> & finishedPile) throw(invalid_pile);
    
    void order();
    std::string printOwnInfo(std::vector<BuildPile*> * buildpiles);
    void virtual move(Deck * deck, std::vector<BuildPile*> buildPiles, std::vector<int> & finished, int choice, int numPlayers) = 0;
    std::string returnsStockPile();
    
    

    std::string returnsHandAndDiscardPiles();
    
    bool winner(std::vector<Player*> players);
    
    //Return top of stock
    int topOfStock();
    
    //Return a string of myDiscard
    std::string toStringDiscard();
    
    //Return name of player
    std::string getName();
    
    //Return stock pile for testing purpose
    std::string returnsTestStock();
    
} ;



#endif

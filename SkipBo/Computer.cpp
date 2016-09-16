/* Team Project Part B 600.120 Spring 2015
 
 Emily Brahma - 9492327727 - ebrahma1
 Mariya Kazachkova - 4407150989 - mkazach1
 Jonathan Liu - 2039138618 - jliu118
 William Yao - 4436917571 - wyao7
 600.120
 Due May 1, 2015
 
 */


#include "Computer.h"
#include<iostream>
//#include "Deck.cpp"
//#include "Deck.h"
//#include "BuildPile.h"
//#include "Player.h"

#include "Pile.h"
Computer::Computer(std::string name): Player(name){
    this->name = name;
    
}

Computer::Computer(std::string name, std::vector<int> pStock, std::vector<int> pHand, std::vector<int> d1,
                   std::vector<int> d2, std::vector<int> d3, std::vector<int> d4) : Player(name){
    this -> name = name;
    int size = pStock.size();
    for(int i = 0; i < size; i++) {
        this -> stock -> push(pStock[i]);
    }
    
    this -> hand = pHand;
    this -> myDiscards = new std::vector<std::stack<int>*>(4);
    
    for(int i = 0; i < 4; i++) {
        std::stack<int> *  x = new std::stack<int>;
        this -> myDiscards-> at(i) = x;
    }
    
    int s1 = d1.size();
    for(int i = 0; i < s1; i++) {
        this ->myDiscards -> at(0) -> push(d1[i]);
    }
    
    int s2 = d2.size();
    for(int i = 0; i < s2; i++) {
        this ->myDiscards -> at(1) -> push(d2[i]);
    }
    
    int s3 = d3.size();
    for(int i = 0; i < s3; i++) {
        this ->myDiscards -> at(2) -> push(d3[i]);
    }
    
    int s4 = d4.size();
    for(int i = 0; i < s4; i++) {
        this ->myDiscards -> at(3) -> push(d4[i]);
    }
    
}






Computer::~Computer(){
    //  name.clear();
    //  delete stock;
    //  hand.clear();
    //  delete myDiscards;
    
    delete stock;
    for (auto it = myDiscards -> begin() ; it != myDiscards -> end(); ++it){
        delete (*it);
        
    }
    
    myDiscards -> clear();
    delete myDiscards;
    
}



void Computer::move(Deck * deck, std::vector<BuildPile*> buildPiles, std::vector<int> & finished, int choice, int numPlayers){
    //Doing something with int choice (useless, but needed to compile)
    if (choice == 0) {
        choice = 1;
    }
    
    if (numPlayers == 0) {
        numPlayers = 1;
    }
    
    
    
    //Round Start
    draw(deck);
    order();
    bool addedCard = false;
    
    //Add to buildPiles with Stock
    for (unsigned int i = 0; i < 4; i++){
        
        //If a card has been added, check the same pile
        if (addedCard == true){
            i--;
        }
        addedCard = false;
        
        for (int k = 0; k < 4; k++){
            
            //Add to buildPiles with Stock
            if ((buildPiles[k] -> getSize() + 1 == stock -> top()) || (stock -> top() == 13)){
	      if (stock -> top() == 13) 
		std::cout << "adding [Skip-Bo] from stock to bui\
ldpile #" << (k + 1) << "\n";
	      else
		std::cout << "adding [" << stock -> top() << "] from stock to buildpile #" << (k + 1) << "\n";
                stockToBP(buildPiles[k], finished);
                if (stock -> size() == 0){
                    return;
                }
            }
            
            
        }
        
        if (stock -> size() == 0){
            return;
        }
        
        //Add to buildPiles with Hand
        for (unsigned int l = 0; l < hand.size(); l++){
            if ((buildPiles[i] -> getSize() + 1 == hand[l]) || (hand[l] == 13)){
	      if (hand[l] == 13) 
		std::cout << "adding [Skip-Bo] from hand to buildpile #\
" << (i + 1) << "\n";
	      else
		std::cout << "adding [" << hand[l] << "] from hand to buildpile #" << (i + 1) << "\n";
                handToBP(buildPiles[i], hand[l], deck, finished);
                addedCard = true;
                
            }
            
        }
        
        //If a card was added, check if top of stock pile can be a valid move again
        if (addedCard == true){
            continue;
        }
        
        //Add to buildPiles with Discard
        for (int p = 0; p < 4; p++){
            if (!myDiscards -> at(p) -> empty()) {
                
                if (buildPiles[i] -> getSize() + 1 == myDiscards -> at(p) -> top()){
		  std::cout << "Adding [" << myDiscards -> at(p) -> top() << "] from discard pile #" << (p + 1) << " to BuildPile #" << i << "\n";
                    discardToBP(buildPiles[i], p, finished);
                    addedCard = true;
                }
            }
            
        }
        
        //If a card was added, check if top of stock pile can be a valid move again
        if (addedCard){
            continue;
        }
        
    }
    
    
    
    //Order before Discard to discard the largest
    order();
    
    //Add to Empty Discard Piles First
    for (int i = 0; i < 4; i++){
        
        if (myDiscards -> at(i) -> size() == 0){
            if (hand[hand.size() - 1] != 13){
	      std::cout << "Discarding [" << hand[hand.size() - 1] << "] to discard pile #" << (i + 1) << "\n";
                addToDiscard(i, hand[hand.size() - 1]);
                return;
            } else {
	      std::cout << "Discarding [" << hand[hand.size() - 2] << "] to discard pile #" << (i + 1) << "\n";
                addToDiscard(i, hand[hand.size() - 2]);
                return;
            }
        }
    }
    
    
    //Add to Discard Piles with same number
    //If not
    //Add to Discard Piles with lower by 1
    //If not
    //Add to Discard Piles with lower by 2
    //.
    //.
    //.
    for (int i = 0; i < 4; i++){
        for (int x = 0; x < 11; x++){
            for (unsigned int j = 1; j < hand.size() + 1; j++){
                
                
                if (myDiscards -> at(i) -> top() - x == hand[hand.size() - j]){
		  std::cout << "Discarding [" << hand[hand.size() - j] << "] to discard pile #" << (i  + 1) << "\n";
                    addToDiscard(i, hand[hand.size() - j]);
                    return;
                }
                
            }
        }
    }
    
    
    
}

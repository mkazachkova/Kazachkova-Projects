#include <string>
#include <stack>
#include <vector>
#include "Player.h"
#include <algorithm>
#include <sstream>
#include <iostream>
//#include "Game.h"
using std::string;
using std::vector;
using std::stack;

Player::Player(string yourName) {
    this -> name = yourName;
    this -> stock = new stack<int>;
    this -> myDiscards = new vector<std::stack<int>*>(4);
    for (int i = 0; i < 4; i++) {
        stack<int> *  x = new stack<int>;
        this -> myDiscards-> at(i) = x;
    }
}



int Player::topCard() {
    return stock->top();
}


void Player::draw(Deck *deck) {
    auto toBeDrawn = 5 - this -> hand.size();
    for (unsigned int i = 0; i < toBeDrawn; i++) {
        int added = deck -> removeOneCard();
        this -> hand.push_back(added);
        
    }
    
}

//numCardsPerPile will be prompted from user when we start
void Player::loadStockPiles(Deck *deck, int numCardsPerPile) {
    for (int i = 0; i < numCardsPerPile; i++) {
        int added = deck -> removeOneCard();
        this -> stock -> push(added);
    }
}


//*****should be error if card not in hand, or discard pile is not 1-4************
//throws invalid_pile exception if pile isn't from 1-4
//throws invalid_card exception if card is not in hand
bool Player::addToDiscard(int pileNum, int cardNum) throw(invalid_card, invalid_pile) {
    
    invalid_card cardError;
    invalid_pile pileError;
    
    
    if(pileNum < 0 || pileNum > 3) {
        throw pileError;
    }
    
    bool inHand = false;
    for (unsigned int i = 0; i < this -> hand.size(); i++) {
        if (this -> hand[i] == cardNum) {
            this -> hand.erase(this -> hand.begin() + i); //there is no card there anymore
            inHand = true;
        }
    }
    if (inHand == true) {
        
        this -> myDiscards -> at(pileNum) -> push(cardNum); //now added to specified discard pile
    } else {
        //card is not in the hand
        throw cardError;
    }
    
    
    return inHand;
}



//**********should be error if card not in hand, or can't put that number on chosen buildPile*******
//throws invalid_pile exception if card doesn't go into specified pile
//throws invalid_card exception if card is not in hand
bool Player::handToBP(BuildPile * chosen,int cardNum, Deck * deck, std::vector<int> & finishedPile) throw(invalid_card, invalid_pile){
    invalid_card cardError;
    invalid_pile pileError;
    bool inHand = false;
    unsigned int top = cardNum;
    //checking to make sure card can be added to this pile
    if ((chosen -> peek() + 1) != top && cardNum != 13) {
        throw pileError;
        //return false;
    }
    
    for (unsigned int i = 0; i < this -> hand.size(); i++) {
        if (this -> hand[i] == cardNum) {
            this -> hand.erase(this -> hand.begin() + i); //there is no card there anymore
            
            inHand = true;
            break;
        }
    }
    if (inHand == true) {
        chosen -> addToBuildPile(cardNum, finishedPile);
        if (this -> hand.size() == 0) {
            this -> draw(deck);
        }
    } else if(!inHand) {
        //if the card is not in the hand
        throw cardError;
    }
    
    return inHand;
    
}

//*******should be error if the card on the top of the stockPile doesn't come next on the chosen BuildPile**********
//throws invalid_pile exception if card doesn't go onto specified buildPile*****
bool Player::stockToBP(BuildPile * chosen, std::vector<int> & finishedPile) throw(invalid_pile) {
    invalid_pile pileError;
    unsigned int top = this -> stock -> top();
    if ((chosen -> peek() + 1) != top && top != 13 ) {
        throw pileError;
    }
    this -> stock -> pop();
    chosen -> addToBuildPile(top, finishedPile);
    return true;
}

//*********Should be error if fromPileNum isn't 1-4, or the top card from selected discard pile doesn't come next on the chosen BuildPile********
//throws invalid_pile exception if pile isn't from 1-4
//throws invalid_card exception if card doesn't go onto specified buildPile
bool Player::discardToBP(BuildPile * chosen, int fromPileNum, std::vector<int> & finishedPile) throw(invalid_card, invalid_pile){
    invalid_card cardError;
    invalid_pile pileError;
    
    if(fromPileNum < 0 || fromPileNum > 3) {
        throw pileError;
    }
    unsigned int top = this -> myDiscards -> at(fromPileNum) -> top();
    if ((chosen -> peek() + 1) != top && top != 13) {
        throw cardError;
    }
    this -> myDiscards -> at(fromPileNum) -> pop();
    chosen -> addToBuildPile(top, finishedPile);
    return true;
}

void Player::order() {
    sort(this -> hand.begin(), this -> hand.end());
}


std::string Player::printOwnInfo(std::vector<BuildPile*> * buildpiles) {
    string hand = "Your hand: ";
    std::ostringstream oss;
    oss << hand;
    for (unsigned int i = 0; i < this -> hand.size(); i++) {
        if (this -> hand[i] == 13) {
            oss << "Skip-Bo ";
        }
        else {
            oss << this -> hand[i] << " ";
        }
    }
    oss << "\n";
    
    oss << "The top of your stock Pile: ";
    if (this -> stock -> size() == 0) {
        oss << "[Empty] ";
    }
    else {
        if (this -> stock -> top() == 13) {
            oss << "[Skip-Bo] " << "Cards left: " << this -> stock -> size();
        }
        else {
            oss << "[" << this -> stock -> top() << "] Cards left: " << this -> stock -> size();
        }
    }
    oss << "\n";
    oss << "Your discard piles, in order: ";
    for (int i = 0; i < 4; i++) {
        if (this -> myDiscards -> at(i) -> size() == 0) {
            oss << "[Empty] ";
        }
        else {
            if (this -> myDiscards -> at(i) -> top() == 13) {
                oss << "[Skip-Bo] ";
            }
            else {
                oss << "[" << this -> myDiscards -> at(i) -> top() << "] ";
            }
        }
    }
    
    oss << "\n";
    oss << "BuildPiles, in order: ";
    for (int i = 0; i < 4; i++) {
        if (buildpiles -> at(i) -> getSize() == 0) {
            oss << "[Empty] ";
        }
        else {
            oss << buildpiles -> at(i) -> getSize() << " ";
        }
    }
    return oss.str();
    
}

std::string Player::returnsStockPile() {
    std::ostringstream oss;
    std::vector<int> temp;
    while (stock -> size() != 0) {
        temp.push_back(stock -> top());
        stock -> pop();
    }
    std::reverse(temp.begin(), temp.end());
    for (unsigned int j = 0; j < temp.size(); j++) {
        oss << temp.at(j) << " ";
    }
    oss << "end \n";
    return oss.str();
    
}



std::string Player::returnsHandAndDiscardPiles() {
    std::ostringstream oss;
    std::vector<int> temp;
    oss << hand.size() << " ";
    for (unsigned int i = 0; i < hand.size(); i++) {
        oss << hand[i] << " ";
    }
    oss << "\n";
    for (unsigned int i = 0; i < 4; i++) {
        bool empty = false;
        int k = 0;
        if (this -> myDiscards -> at(i) -> size() == 0) {
            empty = true;
            int x = -1;
            oss << x << " "; //-1 will represent that it needs to be displayed as empty
        }
        else {
            while (!(myDiscards -> at(i) -> size() == 0) && !empty ) {
                temp.push_back(myDiscards -> at(i) -> top());
                myDiscards -> at(i) -> pop();
                k++;
            } 
            std::reverse(temp.begin(), temp.end());
            for (unsigned int j = 0; j < temp.size(); j++) {
                oss << temp.at(j) << " ";
            }
        }
        oss << "end \n"; //each discard pile is on a new line 
    }
    return oss.str();
}


bool Player::winner(std::vector<Player*> players) {
    for (unsigned int i = 0; i < players.size(); i++) {
        if (players[i] -> stock -> size() == 0) {
            return true;
        }
    }
    
    return false;
}

int Player::topOfStock(){
    return stock->top();
}

std::string Player::toStringDiscard(){
    std::ostringstream oss;
    for (int i = 0; i < 4; i++){
        if (myDiscards->at(i)->size() == 0 ){
            oss << "[Empty] ";
        }else{
	  if (myDiscards->at(i)->top() == 13) {
	    oss << "[Skip-Bo] ";
	  }
	  else {
            oss << "[" << myDiscards->at(i)->top() << "] ";
	  }
        }
        
    }
    
    return oss.str();
}

std::string Player::getName(){
    return name;
}

std::string Player::returnsTestStock(){
    std::ostringstream oss;
    std::vector<int> temp;
    
    for (std::stack<int> dump = *stock; !dump.empty(); dump.pop()){
        temp.push_back(dump.top());
    }
    
    std::reverse(temp.begin(), temp.end());
    for (unsigned int j = 0; j < temp.size(); j++) {
        oss << temp.at(j) << " ";
    }
    
    oss << "end \n";
    
    return oss.str();
    
}

//#include "Player.h"
//#include "Player.cpp"

#include "Human.h"
#include <iostream>



Human::Human(std::string name) : Player(name) {
    this -> name = name;
}


Human::Human(std::string name, std::vector<int> pStock, std::vector<int> pHand, std::vector<int> d1,
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




Human::~Human() {

  delete stock;
  for (auto it = myDiscards->begin();it != myDiscards->end(); it++)
      delete (*it);

  myDiscards->clear();

  delete myDiscards; 

}



//before calling this, we should do printOnwInfo so player sees own hand. Also maybe print whole game?
void Human::move(Deck * deck, std::vector<BuildPile*> buildPiles, std::vector<int> & finished, int choice, int numPlayers) {
    
    switch (choice) {
            //order
        case 1: {
            order();
            break;
        }
            //Add a card to build pile from your hand
        case 2: {
            std::cout << "Card to add: \n";
            std::string temp;
            int cardNum;
            std::cin >> temp;
            if (temp == "Skip-Bo" || temp == "skip-bo") {
                cardNum = 13;
            }
            else {
                cardNum = atoi(temp.c_str());
            }
            std::cout << "buildPile to add to: \n";
            int pileNum;
            std::cin >> pileNum;
            pileNum = pileNum - 1;
            handToBP(buildPiles[pileNum], cardNum, deck, finished);
            break;
        }
            //Add a card to build pile from your stock pile
        case 3: {
            int num;
            std::cout << "buildPile to add to: \n";
            std::cin >> num;
            num = num - 1;
            stockToBP(buildPiles[num], finished); //supposed to be boolean. Has some error checking built in, make sure to use later
            break;
        }
            //Add a card to build pile from discard pile
        case 4: {
            int fromPile;
            std::cout << "discard pile to take from: \n";
            std::cin >> fromPile;
            fromPile = fromPile -1;
            int toPile;
            std::cout << "buildPile to add to: \n";
            std::cin >> toPile;
            toPile = toPile - 1;
            discardToBP(buildPiles[toPile], fromPile, finished);
            break;
        }
            //Add a card froom hand to buildPile
        case 5: {
            std::cout << "card to add: \n";
            std::string temp;
            int cardNum;
            std::cin >> temp;
            if (temp == "Skip-Bo" || temp == "skip-bo") {
                cardNum = 13;
            }
            else {
                cardNum = atoi(temp.c_str());
            }
            
            
            int pileNum;
            std::cout << "discard pile to add to: \n";
            std::cin >> pileNum;
            pileNum = pileNum - 1;
            addToDiscard(pileNum, cardNum);
            break;
        }
    case 8: {

      std::cout << "Attempting to cheat..." << std::endl;
      
      int num;
      srand((unsigned int)time(NULL)); //seed the random
      num = rand()%numPlayers; //generate the random number
      if(num == 1 && (this -> stock -> size() > 1)){
	int top = this->stock->top();
	finished.push_back(top);
	this->stock->pop();
	std::cout << "Cheating was successful! Congratulations!" << std::endl;
      } else {
	this->loadStockPiles(deck, 3);
	std::cout << "Rats! You were caught, 3 cards were added to your stock from the deck." << std::endl;
      }
      break;

    }
            
            
    }
    
}

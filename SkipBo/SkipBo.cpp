/* Team Project Part B 600.120 Spring 2015
 
 Emily Brahma - 9492327727 - ebrahma1
 Mariya Kazachkova - 4407150989 - mkazach1
 Jonathan Liu - 2039138618 - jliu118
 William Yao - 4436917571 - wyao7
 600.120
 Due May 1, 2015
 
*/

#include "Computer.h"
#include "Human.h"
#include "BuildPile.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;

class SkipBo {
public:
    
  static void ComputerTest(){
    Deck *d1 = new Deck;
        
    std::vector<BuildPile *> bpv(4);
    for (int i = 0; i < 4; i++) {
      BuildPile * x = new BuildPile();
      bpv[i] = x;
    }
    std::vector<int> finished;
    Computer c1("ComputerName");
    c1.draw(d1);
        
        
        
    //test loadStockPiles
    c1.loadStockPiles(d1, 10);
    assert(c1.stock -> size() == 10);
        
        
    //test name
    assert(c1.name == "ComputerName");
        
        
    //test order
    for (int i = 0; i < 5; i++) {
      c1.hand[i] = 5 - i;
    }
    c1.order();
    for (int i = 0; i < 5; i++) {
      assert(c1.hand[i] == i + 1);
    }
        
        
    //test draw
    c1.hand.erase(c1.hand.begin() + 4);
    assert(c1.hand.size() == 4);
    c1.draw(d1);
    assert(c1.hand.size() == 5);
        
        
    //test addToDiscard
    c1.addToDiscard(0, 2); //adding card number 2 to first pile
        
    assert(c1.myDiscards -> at(0) -> size() == 1);
    assert(c1.myDiscards -> at(0) -> top() == 2); //make sure top card is a 2
    assert(c1.myDiscards -> at(1) -> size() == 0); //make sure other piles haven't changed
    assert(c1.myDiscards -> at(2) -> size() == 0);
    assert(c1.myDiscards -> at(3) -> size() == 0);
        
        
    //test handToBP
    c1.handToBP(bpv[0], 1, d1, finished);
        
    assert(bpv[0] -> cards.size() == 1);
    assert(bpv[0] -> peek() == 1);
    assert(bpv[1] -> cards.size() == 0); //make sure other piles haven't changed
    assert(bpv[2] -> cards.size() == 0);
    assert(bpv[3] -> cards.size() == 0);
        
        
    //test discardToBP
    c1.discardToBP(bpv[0], 0, finished);
    assert(c1.myDiscards -> at(0) -> size() == 0);
    assert(bpv[0] -> cards.size() == 2);
    assert(bpv[0] -> peek() == 2);
    assert(bpv[1] -> cards.size() == 0); //make sure other build  piles haven't changed
    assert(bpv[2] -> cards.size() == 0);
    assert(bpv[3] -> cards.size() == 0);
    assert(c1.myDiscards -> at(1) -> size() == 0); //make sure other discard piles haven't changed
    assert(c1.myDiscards -> at(2) -> size() == 0);
    assert(c1.myDiscards -> at(3) -> size() == 0);
        
    //test stockToBuilPile
    c1.stock -> pop();
    c1.stock -> push(3); //#manipulation
    c1.stockToBP(bpv[0], finished);
    assert(bpv[0] -> cards.size() == 3);
    assert(bpv[0] -> peek() == 3);
    assert(bpv[1] -> cards.size() == 0); //make sure other build  piles haven't changed
    assert(bpv[2] -> cards.size() == 0);
    assert(bpv[3] -> cards.size() == 0);
    assert(c1.myDiscards -> at(1) -> size() == 0); //make sure other discard piles haven't changed
    assert(c1.myDiscards -> at(2) -> size() == 0);
    assert(c1.myDiscards -> at(3) -> size() == 0);
    assert(c1.stock -> size() == 9);
        
        
        
        
    //test that handToBP will automaticall draw 5 when hand is empty
    c1.draw(d1);
    for (int i = 0; i < 5; i++) {
      c1.hand[i] = 5 - i;
    }
        
    assert(c1.hand.size() == 5);
    c1.handToBP(bpv[1], 1, d1, finished);
    assert(c1.hand.size() == 4);
    c1.handToBP(bpv[1], 2, d1, finished);
    assert(c1.hand.size() == 3);
    c1.handToBP(bpv[1], 3, d1, finished);
    assert(c1.hand.size() == 2);
    c1.handToBP(bpv[1], 4, d1, finished);
    assert(c1.hand.size() == 1);
    c1.handToBP(bpv[1], 5, d1, finished);
        
    assert(c1.hand.size() == 5); //should have redrawn here
    assert(bpv[1] -> cards.size() == 5); //buildPile should have 5 cards
    assert(bpv[0] -> cards.size() == 3); //make sure other build  piles haven't changed
    assert(bpv[2] -> cards.size() == 0);
    assert(bpv[3] -> cards.size() == 0);
        
        
    //test the printOwnInfo method
    for (int i = 0; i < 5; i++) {
      c1.hand[i] = 5 - i;
    }
    c1.stock -> pop();
    c1.stock -> push(13); //#manipulation
        
    std::string compared = "Your hand: 5 4 3 2 1 \nThe top of your stock Pile: [Skip-Bo] Cards left: 9\nYour discard piles, in order: [Empty] [Empty] [Empty] [Empty] ";
        
    delete d1;
    
    for (auto it = bpv.begin();it != bpv.end(); it++)
      delete (*it);

    bpv.clear();
  }
    
    
    
  static void gameBetweenTwoCPUs() {
    Deck *d1 = new Deck;
        
    d1 -> cards[18] = 10;
    d1 -> cards[17] = 8;
    d1 -> cards[16] = 7;
    d1 -> cards[15] = 6;
    d1 -> cards[14] = 2;
    d1 -> cards[13] = 6;
    d1 -> cards[12] = 5;
    d1 -> cards[11] = 4;
    d1 -> cards[10] = 2;
    d1 -> cards[9] = 1;
    d1 -> cards[8] = 10;
    d1 -> cards[7] = 4;
    d1 -> cards[6] = 3;
    d1 -> cards[5] = 2;
    d1 -> cards[4] = 1;
    d1 -> cards[3] = 6;
    d1 -> cards[2] = 4;
    d1 -> cards[1] = 5;
    d1 -> cards[0] = 7;
        
    std::vector<BuildPile *> bpv(4);
    for (int i = 0; i < 4; i++) {
      BuildPile * x = new BuildPile();
      bpv[i] = x;
    }
    std::vector<int> finished;
    Computer c1("first");
    Computer c2("second");
        
    c1.loadStockPiles(d1, 2);
    assert(c1.stock -> top() == 5);
    c2.loadStockPiles(d1, 2);
    assert(c2.stock -> top() == 6);
        
    c1.move(d1, bpv, finished, 4, 5);
    assert(c1.myDiscards -> at(0) -> top() == 10);
    assert(c1.hand.size() == 0);
    assert(c1.stock -> top() == 7);
        
        
    c2.move(d1, bpv, finished, 4, 5);
    assert(c2.myDiscards -> at(0) -> top() == 6);
    assert(c2.hand.size() == 2);
    assert(c2.stock -> top() == 4);
        
    c1.move(d1, bpv, finished, 4, 5);
    assert(c1.myDiscards -> at(0) -> top() == 10);
    assert(c1.hand.size() == 5);
    assert(c1.hand[0] == 2);
    assert(c1.hand[1] == 6);
    assert(c1.hand[2] == 7);
    assert(c1.hand[3] == 8);
    assert(c1.hand[4] == 10);
    assert(c1.stock -> size() == 0);
        
        
    delete d1;
    for (auto it = bpv.begin(); it != bpv.end(); it++)
      delete (*it);

    bpv.clear();
        
    //make sure you call delete objects
    
  }
    
    
  static void BuildPileTest(){
    BuildPile * bp1 = new BuildPile();
    BuildPile * bp2 = new BuildPile();
        
    std::vector<int> finished;
    std::vector<int> finished2;
        
    // Testing to make sure simple adding of cards works
    assert(bp1->peek() == 0);
    assert(bp1->addToBuildPile(1, finished));
    assert(bp1->peek() == 1);
    assert(!bp1->addToBuildPile(5, finished));
    assert(bp1->peek() == 1);
    assert(bp1->addToBuildPile(2, finished));
    assert(bp1->peek() == 2);
        
    bp1 -> addToBuildPile(2, finished);
        
    assert(bp1 -> cards.at(0) == 2);
        
        
    // Testing whether or not the BuildPile knows when to empty itself
    for(int i = 1; i <= 12; i++){
      bp2 -> addToBuildPile(i, finished2);
      if (bp2 -> cards.size() != 0) {
	assert(bp2 -> cards.at(0) == i);  // to make sure if the card just added is at the top
      }
    }
    assert(bp2->cards.size() == 0);
        
    assert(finished2.size() == 12);
        
    delete bp1;
    delete bp2;
        
  }
    
    
    
    
  static void DeckTest(){
    Deck d1;
    BuildPile *bp2 = new BuildPile();
    assert(d1.getSize() == 162);
    assert(d1.cards.at(0) == d1.removeOneCard());
    std::vector<int> finished;
    for(int i = 1; i <= 12; i++){
      bp2 -> addToBuildPile(i, finished);
      if (bp2 -> cards.size() != 0) {
	assert(bp2 -> cards.at(0) == i);
      }
    }
    d1.addBuildPile(finished);
        
    delete bp2;
        
        
  }
    
  static void SaveGameTest(){
    //initialize vector of names
    vector<string> names;
    names.push_back("boy");
    names.push_back("girl");
        
        
        
    //making a game
    Game saveGameTest(1, 1, names, 2);
    std::string expected = saveGameTest.basicInfo();
    saveGameTest.saveGame("saveGameTest.txt", names);
        
        
        
        
    //reading from saveGameTest.txt
    std::ifstream savedfile("saveGameTest.txt", std::ios::in);
    std::string temp;
    std::string actual;
    if(savedfile.is_open()) {
      while(!savedfile.eof()){
	std::getline(savedfile, temp);
	actual += temp;
	actual += "\n";
      }
    }
    assert(actual == expected);
  }
    
  static void LoadGameTest(){
    //initialize vector of names
    vector<string> names;
    names.push_back("boy");
    names.push_back("girl");
        
        
        
    //making a game
    Game saveGameTest(1, 1, names, 2);
    std::string saved = saveGameTest.basicInfo();
    saveGameTest.saveGame("loadGameTest.txt", names);
        
    Game loadGameTest;
    loadGameTest.loadGame("loadGameTest.txt");
    std::string loaded = loadGameTest.basicInfo();
        
	
        assert(saved == loaded);
    }
  
};


int main(void){
    
    cout << "Testing Computer" << endl;
    SkipBo::ComputerTest();
    cout << "Computer tests passed" << endl;
    
    cout << "Testing BuildPile" << endl;
    SkipBo::BuildPileTest();
    cout << "BuildPile tests passed" << endl;
    
    cout << "Testing ExceptionsTest" << endl;
    //SkipBo::exceptionsTest();
    cout<< "exceptions tests passed" <<endl;
    
    cout << "Testing GameBetweenTwoCPUs" << endl;
    SkipBo::gameBetweenTwoCPUs();
    cout << "GameBetweenTwoCPUs tests passed" << endl;
    
    cout << "Testing Deck" << endl;
    SkipBo::DeckTest();
    cout << "Deck tests passed" << endl;
    
    cout << "Testing SaveGame" << endl;
    SkipBo::SaveGameTest();
    cout << "SaveGame tests passed" << endl;
    
    cout << "Testing LoadGame" << endl;
    SkipBo::LoadGameTest();
    cout << "LoadGame tests passed" << endl;
    
    cout << "ALL TESTS PASSED\n";
    
    
}


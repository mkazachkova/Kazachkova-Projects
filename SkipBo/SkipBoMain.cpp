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

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::vector;



int main(){
  int input = 0;
  cout << "Welcome to Skipbo" << endl;
  cout << "1) Start New Game" << endl;
  cout << "2) Load Game" << endl;
  cin >> input;


  if(input == 1) {
    int numHumans;
    int numComps;
    vector<string> names;
    string temp;
    int cardsPerStock;
            
    cout << "How many human players are in the game?" << endl;
    cin >> numHumans;
    
    while (numHumans < 0 || numHumans > 6) {
      cout << "\nNot a valid number of players. Try again:\n";
      cin >> numHumans;
    }


        
    cout << "How many computer players are in the game?" << endl;
    cin >> numComps;

    while (numComps < 0 || numComps > 6 || (numComps + numHumans) > 6) {
      cout << "\nNot a valid number of players. Try again:\n";
      cin >> numComps;
    }

    if (numComps == 0 && numHumans == 0) {
      cout << "No players to pplay the game. Goodbye.\n";
      return -1;
    }

    int counter = 0;
    cout << "What are the names of players? (Input in the format: name1, name2, name3, etc with human names first" << endl;
    for(int i = 0; i < (numHumans + numComps); i++) {
      cin >> temp;
      names.push_back(temp);
      counter++;
    }


            
    cout << "How man cards should each stock pile contain?" << endl;
    cin >> cardsPerStock;


    while (((numHumans + numComps) > 4 && cardsPerStock > 20) || ((numHumans + numComps) > 4 && cardsPerStock < 0)) {
      cout << "You need to enter a number 20 or less (but over 0). Try again:\n";
      cin >> cardsPerStock;
    }

    while (cardsPerStock > 30 || cardsPerStock < 0) {
      cout << "You need to enter a number 30 or less (but over 0). Try again:\n";
      cin >> cardsPerStock;
    }

   


            
            
    Game game(numHumans, numComps, names, cardsPerStock);
    int end = game.playGame();

    if(end >= 0) {
      cout<< names[end] + " won the game!\n";
    }
  }  
  else if(input == 2) {
    string fileName;
    cout << "What is the name of the file you wish to load from?" << endl;
    cin >> fileName;
    Game loadGame;
    loadGame.loadGame(fileName);
    int end2 = loadGame.playGame();

    if(end2 >= 0) {
      cout<< loadGame.players[end2] -> getName() + " won the game!\n";
    }
  } 
    
    
}

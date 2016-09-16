/* Team Project Part B 600.120 Spring 2015
 
 Emily Brahma - 9492327727 - ebrahma1
 Mariya Kazachkova - 4407150989 - mkazach1
 Jonathan Liu - 2039138618 - jliu118
 William Yao - 4436917571 - wyao7
 600.120
 Due May 1, 2015
 
 */

#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;


Game::Game() {
    
}


Game::Game(int numHumans, int numComps, vector<string> names, int cardsPerStock){
    
    this -> numHumans = numHumans;
    this -> numComputers = numComps;
    this -> numInStockPile = cardsPerStock;
    this -> names = names;
    
    this -> deck = new Deck;
    this -> temp = new Deck;
    this -> buildpiles = new vector<BuildPile*>(4);
    for (int i = 0; i < 4; i++) {
        
        BuildPile * temp = new BuildPile;
        buildpiles -> at(i) = temp;
    }
    
    
    
    
    // Creating the Human and Computer Objects
    for(int i = 0; i < numHumans; i++){
        Human * htemp = new Human(names.at(i));
        htemp -> loadStockPiles(this->deck, cardsPerStock);
        htemp -> draw(deck);
        this->players.push_back(htemp);
    }
    
    
    for(int j = numHumans; j < (numHumans + numComps); j++){
        Computer * ctemp = new Computer(names.at(j));
        ctemp -> loadStockPiles(this->deck, cardsPerStock);
        ctemp -> draw(deck);
        this->players.push_back(ctemp);
    }
    
    
}



Game::~Game() {
  
  for (auto it = buildpiles->begin();it != buildpiles->end(); it++)
      delete (*it);

  buildpiles->clear();
 

  delete deck;
  delete buildpiles;
  for (unsigned int i = 0; i < players.size(); i++) {
    delete players[i];
  }
  
}



int Game::getFirstPlayer() {
    int maxcard = 0;
    int maxindex = 0;
    for(int i = 0; i < (numHumans + numComputers); i++){  // this for loop makes sure maxcard holds the value of the max card
        if(this->players.at(i)->topCard() > maxcard){
            maxcard = this->players.at(i)->topCard();
            maxindex = i;
        }
    }
    return maxindex;
}


void Game::saveGame(std::string name, vector<string> names) {
    std::ofstream out;
    out.open(name);
        
    //to write do out <<
    out << this -> numHumans << " " << this -> numComputers << " " << this -> numInStockPile << "\n"; //ends with new line
    //the names of all the players in order, separated by spaces, ending with new line
    for (unsigned int i = 0; i < players.size(); i++) {
        out << names[i] << " ";
    }
    out << "\n";
    //the four build piles in order
    for (int i = 0; i < 4; i++) {
        out << (buildpiles -> at(i) -> returnsPileNums());
        out << "end \n";
    }
    //every players' stock folowed by followed by discard piles
    for (unsigned int i = 0; i < players.size(); i++) {
        out << players[i] -> returnsStockPile();
        out << players[i] -> returnsHandAndDiscardPiles();
    }
    //the deck
    out << deck -> returnsPileNums() << "end \n";
    out.close();
    
}






void Game::loadGame(std::string fileName) {
    std::ifstream ifile(fileName, std::ios::in);
    std::string s1;
    string s2;
    std::string s3;
    
    int numHumans = 0;
    int numComputers = 0;
    std::getline(ifile, s1, ' ');
    std::getline(ifile, s2, ' ');
    std::getline(ifile, s3);
    numHumans = atoi(s1.c_str());
    numComputers = atoi(s2.c_str());
    numInStockPile = atoi(s3.c_str());
    vector<string> names;
    string name;
    vector<int> bp1;
    vector<int> bp2;
    vector<int> bp3;
    vector<int> bp4;
    
    
    //get the names of a player into a vector
    for(int i = 0; i < numHumans + numComputers; i++) {
        getline(ifile, name, ' ');
        names.push_back(name);
    }
    getline(ifile, name);
    string number = "";
    number = "";
    int nextNum;
    
    
    bool end = false;
    while((!(number == "end")) && !end) {
        getline(ifile, number, ' ');
        if(!(number == "end")) {
            nextNum = atoi(number.c_str());
            if(nextNum == -1) {
                end = true;
                break;
            }
            else {
                bp1.push_back(nextNum);
            }
        }
        
    }
    
    getline(ifile, number);
    
    //get all four build piles
    end = false;
    number = "";
    while((!(number == "end")) && !end) {
        getline(ifile, number, ' ');
        if(!(number == "end")) {
            nextNum = atoi(number.c_str());
            if(nextNum == -1) {
                end = true;
                break;
            }
            else {
                bp2.push_back(nextNum);
            }
        }
        
    }
    
    
    getline(ifile, number);
    
    end = false;
    number = "";
    while((!(number == "end")) && !end) {
        getline(ifile, number, ' ');
        if(!(number == "end")) {
            nextNum = atoi(number.c_str());
            if(nextNum == -1) {
                end = true;
                break;
            }
            else {
                bp3.push_back(nextNum);
            }
        }
        
    }
    
    getline(ifile, number);
    
    end = false;
    number = "";
    while((!(number == "end")) && !end) {
        getline(ifile, number, ' ');
        if(!(number == "end")) {
            nextNum = atoi(number.c_str());
            if(nextNum == -1) {
                end = true;
                break;
            }
            else {
                bp4.push_back(nextNum);
            }
        }
        
    }
    getline(ifile, number);
    
    //pick up the \n
    
    vector<vector<int>> playerstock;
    vector<vector<int>> playerHand;
    vector<vector<int>> playerDiscard1;
    vector<vector<int>> playerDiscard2;
    vector<vector<int>> playerDiscard3;
    vector<vector<int>> playerDiscard4;
    int stockSize = 0;
    for(int i = 0; i < numHumans + numComputers; i++) {
        vector<int> thand;
        vector<int> tstock;
        vector<int> d1;
        vector<int> d2;
        vector<int> d3;
        vector<int> d4;
        
        end = false;
        number = "";
        
        while((!(number == "end")) && !end) {
            getline(ifile, number, ' ');
            if(!(number == "end")) {
                nextNum = atoi(number.c_str());
                if(nextNum == -1) {
                    end = true;
                    break;
                }
                else {
                    stockSize++;
                    tstock.push_back(nextNum);
                }
            }
            
        }
        playerstock.push_back(tstock);
        getline(ifile, number);//get \n
        
        getline(ifile, number, ' '); //get the size of the hand
        int size = atoi(number.c_str());
        //get the hand
        for(int j = 0; j < size; j++) {
            getline(ifile, number, ' ');
            nextNum = atoi(number.c_str());
            thand.push_back(nextNum);
        }
        playerHand.push_back(thand);
        
        getline(ifile, number);//get \n
        
        end = false;
        number = "";
        while((!(number == "end")) && !end) {
            getline(ifile, number, ' ');
            if(!(number == "end")) {
                nextNum = atoi(number.c_str());
                if(nextNum == -1) {
                    end = true;
                    break;
                }
                else {
                    d1.push_back(nextNum);
                }
            }
        }
        playerDiscard1.push_back(d1);
        getline(ifile, number); //get \n
        
        end = false;
        number = "";
        while((!(number == "end")) && !end) {
            getline(ifile, number, ' ');
            if(!(number == "end")) {
                nextNum = atoi(number.c_str());
                if(nextNum == -1) {
                    end = true;
                    break;
                }
                else {
                    d2.push_back(nextNum);
                }
            }
        }
        playerDiscard2.push_back(d2);
        getline(ifile, number); //get \n
        
        end = false;
        number = "";
        while((!(number == "end")) && !end) {
            getline(ifile, number, ' ');
            if(!(number == "end")) {
                nextNum = atoi(number.c_str());
                if(nextNum == -1) {
                    end = true;
                    break;
                }
                else {
                    cout<<nextNum << " ";
                    d3.push_back(nextNum);
                }
            }
        }
        playerDiscard3.push_back(d3);
        getline(ifile, number); //get \n
        
        end = false;
        number = "";
        while((!(number == "end")) && !end) {
            getline(ifile, number, ' ');
            if(!(number == "end")) {
                nextNum = atoi(number.c_str());
                if(nextNum == -1) {
                    end = true;
                    break;
                }
                else {
                    d4.push_back(nextNum);
                }
            }
        }
        playerDiscard4.push_back(d4);
        getline(ifile, number); //get \n
    }
    
    vector<int> deck1;
    end = false;
    number = "";
    while((!(number == "end")) && !end) {
        getline(ifile, number, ' ');
        if(!(number == "end")) {
            nextNum = atoi(number.c_str());
            if(nextNum == -1) {
                end = true;
                break;
            }
            else {
                deck1.push_back(nextNum);
            }
        }
        
    }
    
    
    //PASTE START
    this -> numHumans = numHumans;
    this -> numComputers = numComputers;
    this -> numInStockPile = (stockSize/(numHumans + numComputers));
    
    //adding humans to player vector
    for(int i = 0; i < numHumans; i++) {
        string name = names[i];
        Human *htemp = new Human(name, playerstock[i], playerHand[i], playerDiscard1[i], playerDiscard2[i], playerDiscard3[i], playerDiscard4[i]);
        this->players.push_back(htemp);
    }
    
    for(int i = numHumans; i < (numHumans + numComputers); i++){
        string name = names[i];
        Computer * ctemp = new Computer(name, playerstock[i], playerHand[i], playerDiscard1[i], playerDiscard2[i], playerDiscard3[i], playerDiscard4[i]);
        this->players.push_back(ctemp);
    }
    
  //initializing all the build piles
    BuildPile *b1 = new BuildPile(bp1);
    BuildPile *b2 = new BuildPile(bp2);
    BuildPile *b3 = new BuildPile(bp3);
    BuildPile *b4 = new BuildPile(bp4);
    
    this -> buildpiles = new vector<BuildPile*>;
    this -> buildpiles ->push_back(b1);
    this -> buildpiles ->push_back(b2);
    this -> buildpiles ->push_back(b3);
    this -> buildpiles ->push_back(b4);
    
    
    Deck *d1 = new Deck(deck1);
    this -> deck = d1;
    
    
    
}











void Game::printInfoOfPlayer(int num) {
    std::cout << this->players.at(num) -> printOwnInfo(buildpiles);
}


int Game::playGame() {
    std::cout << "\n\n\n";
    int choice = 0;
    bool endTurn = false;
    int i = getFirstPlayer();
    int printedInfo = 0;
    bool toNotEndTurn = false;
    while (!(players[i] -> winner(players))) {
        if (deck -> getSize() < 5) {
            if (finished.size() != 0) {
                deck -> addBuildPile(finished);
            }
            else {
                deck = temp;
            }
        }
        std::cout << "\n\n";
	
        i = i % (numHumans + numComputers);
        std::cout << "****************    " << players[i] -> getName() << "'s Turn     ***************\n\n";
        endTurn = false;
       
	players[i] -> draw(this -> deck);
	if (i < numHumans)
	  std::cout << players[i] -> printOwnInfo(buildpiles);
        std::cout << "\n";
        std::cout << "\n";
        printedInfo++;
	if (i < numHumans)
	  printMenu();
        while (endTurn == false) {
	  toNotEndTurn = false;
            if (deck -> getSize() < 5) {
                if (finished.size() != 0) {
                    deck -> addBuildPile(finished);
                }
                else {
                    deck = temp;
                }
            }
            
            if (i < numHumans) {
                if (printedInfo == 0){
		  std::cout << players[i] -> printOwnInfo(buildpiles) << "\n";
                }
                printedInfo = 0;
                std::cout << "\n";
                std::cout << "\n";
                std::cout << "choice: \n";
                std::cin >> choice;
		std::cout << "\n\n";
                if (choice != 5 && choice != 6) {
		  try{
		    players[i] -> move(this->deck, *(this->buildpiles), this->finished, choice, (int) this -> players.size());
		  }
		  catch (invalid_card & e) {
		    cout << "**********This was not a valid card or build pile. Please try again.\n\n";
		    printMenu();
		  }
		  catch (invalid_pile & e) {
		    cout << "**********This was not a valid card or build pile. Please try again.\n\n";
		    printMenu();
		  }

                }
                if (choice == 6) {
                    std::cout << "name of file to save to: \n";
                    string name;
                    std::cin >> name;
                    saveGame(name, names);
		    return -1;
                    
                }
                if (choice == 5) {
                    
		  try {
		    players[i] -> move(this->deck, *(this->buildpiles), this->finished, choice, (int) this -> players.size());
		  }
		  catch (invalid_card & e) {
		    cout << "********This was not a valid card or discard pile. Please try again.\n";
		    printMenu();
		    toNotEndTurn = true;
		  }
		  catch (invalid_pile & e) {
		    cout << "*********This was not a valid card or discard pile. Please try again.\n";
		    printMenu();
		    toNotEndTurn = true;
		  }
		  if (toNotEndTurn == true) {
		    endTurn = false;
		  }
		  else {
		    endTurn = true;
		    break;
		  }
                }
		if (choice == 7) {
		  std::cout << "\n\n" << *this << "\n\n";
		}
            }
            
            else {
                
                std::cout << "\n\n";
                //std::cout << players[i] -> printOwnInfo(buildpiles) << "\n\n";;
                if (deck -> getSize() < 5) {
                    if (finished.size() != 0) {
                        deck -> addBuildPile(finished);
                    }
                    else {
                        deck = temp;
                    }
                }
                players[i] -> move(this->deck, *(this->buildpiles), this->finished, 6, (int) this -> players.size());
		std::cout << "\n\n";
                //std::cout << players[i] -> printOwnInfo(buildpiles);
                std::cout << "\n\n";
                endTurn = true; //next one moves
            } 
        }
        i++;
        std::cout << "\n\n";
    }
    return (i-1);
}

std::ostream &operator<<(std::ostream& stream, const Game &game){
    //stream << x.name;
    
    stream << "Build Piles: ";
    for (int j = 0; j < 4; j++){
        if (game.buildpiles->at(j)->peek() == 0 ){
            stream << "[Empty] ";
        }else{
	
            stream << "[" << game.buildpiles->at(j)->peek() << "] ";
	  
        }
    }
    stream << "\n";
    
    for (int x = 0; x < (game.numComputers + game.numHumans); x++){
        stream << game.players[x] -> getName()  << ":\n";
	if (game.players[x] -> topOfStock() == 13) {
	  stream << "Stock: [Skip-Bo]\n";
	}
	else {
	  stream << "Stock: [" << game.players[x] -> topOfStock() << "]\n";
        }
	stream << "Discard:" << game.players[x] -> toStringDiscard() << "\n";
        
    }
    
    return stream;
}

std::string Game::basicInfo(){
    std::ostringstream oss;
    oss << numHumans << " " << numComputers << " " << numInStockPile << "\n";
    for (int i = 0; i < (numHumans + numComputers); i++){
        oss << players[i]->getName() << " ";
    }
    oss << "\n";
    
    for (int x = 0; x < 4; x++){
        if (buildpiles->at(x)->peek() == 0){
            oss << "-1 end \n";
        }
    }
        
    for (int i = 0; i < (numHumans + numComputers); i++){
        
        oss << players[i]->returnsTestStock();
        
        oss << players[i]->returnsHandAndDiscardPiles();
    }
    
    oss << deck->returnsPileNums();
    oss << "end \n\n";
    
    return oss.str();
}



void Game::printMenu() {
    cout<< "1) Order your hand" <<endl;
    cout<< "2) Add from hand to the build pile" <<endl;
    cout<< "3) Add from stock to build pile" <<endl;
    cout<< "4) Add from discard to build pile" <<endl;
    cout<< "5) Add from hand to discard pile" <<endl;
    cout<< "6) End game" <<endl;
    cout<< "7) Display whole game" <<endl;
    cout<< "8) (Cheat;)" <<endl;

}



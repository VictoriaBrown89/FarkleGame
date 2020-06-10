#pragma once
#include <vector>

using namespace std;

class farkleGame
{
public:
	
	// Member functions are declared for class 

	void readRules();
	int diceRoll();
	int reroll();
	void printRoll();
	string playerNames(int numPlayers);
	int scoring(int *playerScore);
	int playerTurn(int numPlayers, int *playerScore);
	int firstTurn(int *playerScore);
	void RunGame();


};


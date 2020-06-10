#include "pch.h"
#include "farkleGame.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <random>

using namespace std;

// Global variables declared to store various types
int dice[6]; 
vector<string> players; // Vector holds player names
bool rerollPosition[6] = { false };
int scoreVar, totalDice, rerollDice, firstRoll, totalScore;
string name;

// Function reads rules from file
void farkleGame::readRules() 
{
	string fileText;
	ifstream myFile;
	myFile.open("farkleRules.txt"); 
	while (getline(myReadFile, fileText)) // Loop reads each line of the file and prints to window
	{
		cout << fileText << '\n';
	}
	myFile.close(); // File is closed
}


// Function gets and stores player names into vector
string farkleGame::playerNames(int numPlayers)
{

	for (int i = 0; i <= (numPlayers - 1); i++)
	{
		cout << "Enter the name of player " << (i + 1) << ": " << endl;
		while (cin >> name) {
			players.push_back(name);
			break;
		}
		cout << "" << endl;
	}
	return name;
}


// Function rolls dice using randon number generator
int farkleGame::diceRoll() 
{
	for (int i = 0; i < 6; i++)
	{
		dice[i] = (rand() % 6 + 1);
	}
	return dice[6]; // Roll values are returned
}


// Function prints the dice array to window
void farkleGame::printRoll()
{
	for (int i = 0; i <= 5; i++)
	{
		cout << dice[i] << "   ";
	}
}


// Function uses info from scoring function to determine which
// index of dice array to reroll
int farkleGame::reroll() 
{
	for (int i = 0; i < 6; i++)
	{
		if (rerollPosition[i] == true)
		{
			dice[i] = (rand() % 6 + 1);
		}
	}
	return dice[6];
}


// Function determines the score from the roll, if an element/index
// will be a reroll position, and checks for multiple die of the same value,
// updating the score accordingly
int farkleGame::scoring(int *playerScore) 
{
	int tripleOne = 0, tripleTwo = 0, tripleThree = 0, tripleFour = 0, tripleFive = 0, tripleSix = 0;
	scoreVar = 0; 

	rerollDice = 0; // Number of die to reroll is reset each time function is called

	// Loop checks for 1s and 5s, and increment counters used to determine
	// like valued die
	for (int i = 0; i < 6; i++)
	{
		switch (dice[i])
		{
		case 1:
			scoreVar += 100;
			tripleOne++;
			break;
		case 2:
			tripleTwo++;
			rerollDice++;
			rerollPosition[i] = true;
			break;
		case 3:
			tripleThree++;
			rerollDice++;
			rerollPosition[i] = true;
			break;
		case 4:
			tripleFour++;
			rerollDice++;
			rerollPosition[i] = true;
			break;
		case 5:
			scoreVar += 50;
			tripleFive++;
			break;
		case 6:
			tripleSix++;
			rerollDice++;
			rerollPosition[i] = true;
			break;
		}
	}

	// Statements determine if a position is a reroll position (non-scoring)
	// and updates round score if like-valued triple die are rolled
	if (rerollDice == 6)
	{
		cout << "You rolled Farkle! You didn't roll any scoring dice, and any score gained this turn is lost" << endl;
		scoreVar = 0;
	}
	else
	{
		if (tripleOne >= 3) 
		{
			scoreVar = (scoreVar - 300) + 1000; // If three 1s are rolled, score is changed from 300 to 1000

		}
		else if (tripleTwo >= 3)
		{
			scoreVar += 200;
			for (int i = 0; i < 6; i++)
			{
				if (dice[i] == 2) { rerollPosition[i] = false; }
			}
			rerollDice -= 3;
		}
		else if (tripleThree >= 3)
		{
			scoreVar += 300;
			for (int i = 0; i < 6; i++)
			{
				if (dice[i] == 3) { rerollPosition[i] = false; }
			}
			rerollDice -= 3;
		}
		else if (tripleFour >= 3)
		{
			scoreVar += 400;
			for (int i = 0; i < 6; i++)
			{
				if (dice[i] == 4) { rerollPosition[i] = false; }
			}
			rerollDice -= 3;
		}
		else if (tripleFive >= 3)
		{
			scoreVar = (scoreVar - 150) + 500; // If three 5s are rolled, score is changed from 150 to 500
		}
		else if (tripleSix >= 3)
		{
			scoreVar += 600;
			for (int i = 0; i < 6; i++)
			{
				if (dice[i] == 6) { rerollPosition[i] = false; }
			}
			rerollDice -= 3;
		}
	}
	firstRoll = scoreVar; // Players cannot advance beyond first round with scoring at least 1000
	cout << "Score this roll: " << scoreVar << endl;

	return rerollDice, *playerScore;
}

// Function handles first round condition, rerolls die until score reaches 1000 points
int farkleGame::firstTurn(int *playerScore)
{
	diceRoll();
	printRoll();
	scoring(playerScore);
	rerollDice = 0;

	return *playerScore;
}

// Function for player turns
// Handles reroll conditions, allows player to either reroll or pass
// Updates score array based on results of turn
int farkleGame::playerTurn(int numPlayers, int *playerScore) 
{
	char rerollCheck; // Checks user input for y(Y) or n(N)
	for (int i = 0; i < numPlayers; i++) // Repeats the turn based on how many players are playing
	{
		cout << players[i] << ", let's roll the dice: " << endl; // Names player whose turn it is
		diceRoll(); // Dice roll function
		printRoll(); // Print roll function
		scoring(playerScore); // Scoring function
		if (rerollDice == 0)
		{
			cout << "All dice are scoring dice! You can roll all 6 again for a higher score!" << endl;
			playerScore[i] += scoreVar;
			diceRoll();
			printRoll();
			scoring(playerScore);
		}
		else if (rerollDice != 6)
		{
			cout << endl << "Reroll the " << rerollDice << " non scoring dice? (Y/N)" << endl; 
			cin >> rerollCheck;
			if (rerollCheck == 'y' || rerollCheck == 'Y') // If y(Y), die in non-scoring positions rerolled
			{
				reroll(); //Dice roll function
				printRoll(); //Print dice roll
				scoring(playerScore); //Score reroll
			}
			else if (rerollCheck == 'n' || rerollCheck == 'N') // If n(N), program will not reroll
			{
				cout << "Your turn is now over." << endl;
				rerollDice = 0;
			}
		}

		for (int i = 0; i < 6; i++) { rerollPosition[i] = false; }

		cout << players[i] << ", your score from that round: " << scoreVar << endl;
		playerScore[i] += scoreVar; // Player score is added to score in array
		totalScore += scoreVar; // Total score is updated

		cout << "Total score after this round: " << totalScore << endl << endl;

	}
	return *playerScore;

}



// Function controls flow of game, gets/stores number of players, defines 'win' condition,
// and calls member functions for game flow
void farkleGame::RunGame()
{
	srand((unsigned)time(0));
	cout << "Welcome to Farkle! Here are the rules: " << endl << endl;

	readRules(); // Read file function called
	int numPlayers;

	cout << endl << endl << "How many players are there?" << endl;
	cin >> numPlayers;
	
	playerNames(numPlayers); // Player name function called
	cout << "" << endl;

	int *playerScore = new int[numPlayers]; // Scoring array declared to hold individual scores

	for (int i = 0; i < numPlayers; i++) {
		playerScore[i] = 0; 
	}// Score array initialized to zero

	cout << "Let's begin by rolling until the first player reaches 1000 points." << endl << endl;
	while (firstRoll < 1000) { 
		firstTurn(playerScore); 
	} // First turn condition controlled by loop

	cout << endl;

	while (totalScore < 10000) // 'Win' condition defined in loop for first player to get score over 10,000
	{
		cout << endl;
		playerTurn(numPlayers, playerScore);
		if (totalScore >= 10000)
		{
			cout << "Congratulations, you win!" << endl << endl;
			break;
		}
	}
	system("PAUSE");
}
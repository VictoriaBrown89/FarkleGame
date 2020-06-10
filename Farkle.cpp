// Farkle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;


int dice[6]; //Global variables
string players[5];
bool rerollPosition[6] = { false };
int score, totalDice, rerollDice, firstScore, totalScore; //More global variables


int diceRoll() //Dice roll function, restricts possible numbers between 1 and 6
{
	for (int i = 0; i < 6; i++)
	{
		dice[i] = (rand() % 6 + 1); //Numbers restricted to between 1 and 6 to simulate dice

	}

	return dice[6]; //Returns roll values
}


int reroll() // Reroll function, usees rerollPosition bool array to only reroll the positions that don't score the first time
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


void printRoll()
{
	for (int i = 0; i <= 5; i++) // Prints dice values from the roll
	{
		std::cout << dice[i] << "   ";
	}
}


string playerNames(int numPlayers) //Function to establish player name array, set it's size and take name input
{
	for (int i = 0; i <= (numPlayers - 1); i++) //Loop to get the names of all players
	{
		std::cout << "Enter the name of player " << (i + 1) << ": ";
		std::cin >> players[i];

	}
	return players[5];
}


int scoring(int *playerScore) //Scoring function
{
	int oneCount = 0, twoCount = 0, threeCount = 0, fourCount = 0, fiveCount = 0, sixCount = 0; //Variable counts for each roll possibility
	score = 0; //Reset score each time the function is run

	rerollDice = 0; // Reset the number of dice to reroll each time the function is run
	for (int i = 0; i < 6; i++) // check for 1's and 5's as well as increment the individual number counters
	{
		switch (dice[i])
		{
		case 1:
			score += 100;
			oneCount++;
			break;
		case 2:
			twoCount++;
			rerollDice++;
			rerollPosition[i] = true;
			break;
		case 3:
			threeCount++;
			rerollDice++;
			rerollPosition[i] = true;
			break;
		case 4:
			fourCount++;
			rerollDice++;
			rerollPosition[i] = true;
			break;
		case 5:
			score += 50;
			fiveCount++;
			break;
		case 6:
			sixCount++;
			rerollDice++;
			rerollPosition[i] = true;
			break;
		}
	}
	if (rerollDice == 6)
	{
		std::cout << "Farkle! You didn't roll any scoring dice, any score gained this turn is lost" << endl;
		score = 0;
	}
	else
	{
		if (oneCount >= 3) // If statements to check for triple rolls and add to the score accordingly
		{
			score = (score - 300) + 1000; //Removes original 300 score before adding 1000

		}
		else if (twoCount >= 3)
		{
			score += 200;
			for (int i = 0; i < 6; i++)
			{
				if (dice[i] == 2) { rerollPosition[i] = false; }
			}
			rerollDice -= 3;
		}
		else if (threeCount >= 3)
		{
			score += 300;
			for (int i = 0; i < 6; i++)
			{
				if (dice[i] == 3) { rerollPosition[i] = false; }
			}
			rerollDice -= 3;
		}
		else if (fourCount >= 3)
		{
			score += 400;
			for (int i = 0; i < 6; i++)
			{
				if (dice[i] == 4) { rerollPosition[i] = false; }
			}
			rerollDice -= 3;
		}
		else if (fiveCount >= 3)
		{
			score = (score - 150) + 500; //Removes 150 from score before adding 500
		}
		else if (sixCount >= 3)
		{
			score += 600;
			for (int i = 0; i < 6; i++)
			{
				if (dice[i] == 6) { rerollPosition[i] = false; }
			}
			rerollDice -= 3;
		}
	}
	firstScore = score; // Initial turn variable that has to exceed 1000 to continue in the game
	std::cout << "Score from that roll: " << score << endl;

	return rerollDice, *playerScore;
}


int playerTurn(int numPlayers, int *playerScore) //Function that handles individual player turns
{
	char rerollCheck; // Variable for Y or N reroll input
	for (int i = 0; i < numPlayers; i++) // Repeats the turn based on how many players are playing
	{
		std::cout << players[i] << " let's roll the dice: " << endl; //Says which player is currently rolling
		diceRoll(); //Dice roll function
		printRoll(); //Prints dice roll
		scoring(playerScore); //Scores the roll
		if (rerollDice == 0)
		{
			std::cout << "All dice are scoring dice, you get to roll all 6 again for more score";
			playerScore[i] += score;
			diceRoll();
			printRoll();
			scoring(playerScore);
		}
		else if (rerollDice != 6)
		{
			std::cout << endl << "Do you want to reroll the " << rerollDice << " non scoring dice? (Y/N)" << endl; //Gives the option to reroll the non scoring dice or not
			std::cin >> rerollCheck;
			if (rerollCheck == 'y' || rerollCheck == 'Y') //reroll is performed based on the number of non scoring dice
			{
				reroll(); //Dice roll function
				printRoll(); //Print dice roll
				scoring(playerScore); //Score reroll
			}
			else if (rerollCheck == 'n' || rerollCheck == 'N') //If user chooses no their turn is over and rerollDice is set to 0 so that the dice total will be reset properl
			{
				std::cout << "Your turn is now over" << endl;
				rerollDice = 0;
			}
		}

		for (int i = 0; i < 6; i++) { rerollPosition[i] = false; }
		std::cout << players[i] << " your score from that round: " << score << endl;
		playerScore[i] += score; //Adds the score total to the individual player score array
		totalScore += score; //Built the game to work single player to check functionality

		std::cout << "Your total score after that round: " << totalScore << endl << endl;

	}
	return *playerScore;

}


int firstTurn(int *playerScore) // First turn that handles the rolls before the initial 1000+ roll, executes on it's own until it happens
{
	diceRoll();
	printRoll();
	scoring(playerScore);
	rerollDice = 0;
	return *playerScore;
}


int main(string* players[])
{
	srand(time(0)); //Seeds the random number generator
	std::cout << "Welcome to Farkle!" << endl << endl;
	int numPlayers;

	std::cout << endl << endl << "How many players are there?" << endl;
	while (!(std::cin >> numPlayers))//Number of players input
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Please enter a whole number" << std::endl;
	}
	playerNames(numPlayers); // Get the names of the players
	int *playerScore = new int[numPlayers]; // Scoring array to hold individual player scores

	for (int i = 0; i < numPlayers; i++) { playerScore[i] = 0; }//Initializes score arry to a 0 value after it's size is determined
	while (firstScore < 1000) { firstTurn(playerScore); } //First turn won't end until player rolls over 1000 on a single roll
	std::cout << endl; // Basic separation from the first round spam

	while (totalScore < 10000) //Win condition, game lasts until a player hits or exceeds 10,000 points
	{
		std::cout << std::endl;
		playerTurn(numPlayers, playerScore);
		if (totalScore >= 10000)
		{
			std::cout << "Congratulations, you win!" << endl << endl;
			break;
		}
	}
	system("PAUSE");
	return 0;
}


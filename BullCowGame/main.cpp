/*This is the console executable, that make the use of FBullCow class.
* This acts as the view in the MVC pattern, and is responsible
* for all the user interactions. For game logic see the FBullCow class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
void PrintGuess(FText);
bool AskToPlayAgain();
//provide a method for counting bulls and cows, and increment the current turn #

FBullCowGame BCGame; //instantiate a new game

//Entry point of the application
int main()
{
	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; //End of the application
}

void PrintIntro() 
{
	//Intro to the game
	constexpr int32 WORD_LENGTH = 5;
	std::cout << "Welcome to Bulls and Cows Game, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";

	return;
}

void PlayGame() 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//Get the guess and Print Guess till the number of turns
	//TODO change from FOR to WHILE once we are validating tries 
	for (int32 count = 1; count <= MaxTries; count++) {
		FText Guess = GetGuess(); //TODO make a check to validate guess

		//submit valid guess to the game
		//print the bulls and cows
		PrintGuess(Guess);
		std::cout << std::endl;
	}

	//TODO summarise game
}

FText GetGuess() 
{
	int32 CurrentTry = BCGame.GetCurrentTry();

	//Get a guess from player
	std::cout << "Try" << CurrentTry <<". Enter your guess: ";
	FText Guess = "";
	getline(std::cin, Guess);

	return Guess;
}

void PrintGuess(FText Guess) 
{
	//print the guess inputed by the player
	std::cout << "Your guess was: " << Guess << std::endl;

	return;
}

bool AskToPlayAgain() 
{
	//Ask player to play again
	std::cout << "Do you want to play again(y/n)? ";
	FText Response = "";
	getline(std::cin, Response);

	return(Response[0] == 'y' || Response[0] == 'Y');
}
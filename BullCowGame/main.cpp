/*This is the console executable, that make the use of FBullCow class.
* This acts as the view in the MVC pattern, and is responsible
* for all the user interactions. For game logic see the FBullCow class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game, which we reuse across plays

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
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

// plays a single games to completion
void PlayGame() 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guess while the game
	//is not won and there are tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		FText Guess = GetValidGuess(); 

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows<<"\n\n";
	}
	PrintGameSummary();

	return;
}

//loop continually until player gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do{
		//get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry <<" of " << BCGame.GetMaxTries() <<". Enter your guess: ";
		getline(std::cin, Guess);

		//check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			//assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get an error
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
	//ask player to play again
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl;

	return(Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) { //if game is won
		std::cout << "WELL DONE - YOU WIN!";
	}
	else { //if all tries are exhausted
		std::cout << "BETTER LUCK NEXT TIME";
	}
	std::cout << std::endl;

	return;
}

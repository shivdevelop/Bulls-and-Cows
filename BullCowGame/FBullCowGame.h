#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all values initialised to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame 
{
public:
	FBullCowGame();

	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	bool IsGameWon() const;
	
	void Reset(); //TODO make a more rich return value
	bool CheckGuessValidity(FString); //TODO make a more rich return value
	FBullCowCount SubmitGuess(FString);


	// ^^ Please try and ignore this and focus on the interface above ^^
private:
	//see construtor for initialisation
	int32 MyCurrentTry = 1;
	int32 MyMaxTries = 5;
	FString MyHiddenWord;
};
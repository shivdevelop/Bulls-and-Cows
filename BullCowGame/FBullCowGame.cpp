#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMaxTries() const{ return MyMaxTries; }

bool FBullCowGame::IsGameWon() const
{
	return false;
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	return;
}

bool FBullCowGame::CheckGuessValidity(FString)
{
	return false;
}

//receives a valid guess, increments turn and returns bulls and cows count
FBullCowCount FBullCowGame::SubmitGuess(FString)
{
	//increments the turn #
	MyCurrentTry++;

	//setup a return variable
	FBullCowCount BullCowCount;

	//loop through all letters in the guess
		//compare letters against the hidden word
			//if they match then
				//if in same place
					//increment bulls
				//else
					//increment cows

	return BullCowCount;
}

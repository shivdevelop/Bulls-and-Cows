#pragma once

#include "FBullCowGame.h"
#include <map>

#define TMap std::map // to make syntax Unreal friendly

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10},{6,15},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "place"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess isnt an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) //if the guess inst all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else //otherwise
	{
		return EGuessStatus::OK;
	}
}

//receives a valid guess, increments turn and returns bulls and cows count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (MyHiddenWord[MHWChar] == Guess[GChar]) {
				if (MHWChar == GChar) { //if in same place
					BullCowCount.Bulls++; //increment bulls
				}
				else { //else
					BullCowCount.Cows++;//increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms

	if (Word.length() <= 1) { return true; }

	TMap<char, bool>LetterSeen;//setup a map
	for (auto Letter : Word) { //loop through the guess letters
		Letter = tolower(Letter); //handle mixed cases
		if (LetterSeen[Letter]) { //if letter is in map 
			return false; //we do NOT have an isogram
		} else { //otherwise 
			LetterSeen[Letter] = true;	//add the letter to map as seen
		}
	}

	return true; //for example in case if /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) { // loop through all letters
		if (!islower(Letter)) {// if not a lowecase letter 
			return false;
		}
	}

	return true;
}

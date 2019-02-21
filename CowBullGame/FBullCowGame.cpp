#pragma once
#include "FBullCowGame.h"
#include <map>

//to make the syntax unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame()//default contructor
{
	Reset();
}


int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTries;}
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20} }; //braced initializer syntax
	return WordLengthToMaxTries[MyHiddenWord.length()];

}

bool FBullCowGame::CheckIfIsogram(FString guess) const
{
	//treat 0 and 1 letter words as isograms
	if (guess.length() <= 1) { return true; }

	TMap<char, bool> Letterseen;

	for (auto letter : guess)
	{
		letter = tolower(letter);

		if (Letterseen[letter]) {//is the letter already in the word
			return false;
		}
		else {
			Letterseen[letter] = true;//otherwise, add the letter to the map
		}

	}
	return true; //in cases where /0 are entered
}

bool FBullCowGame::IsLowerCase(FString guess) const
{
	for (auto letter : guess) 
	{
		if (!islower(letter)) {
			return false;
		}
	}
	return true;
}

void FBullCowGame::Reset()
{
	bGameIsWon = false;

	return;
}

void FBullCowGame::ChoseWordLength(FString wordLength) {

	TMap<FString, FString> ChoseWordLength{ {"3","ant"},{"4","duck"},{"5","penut"},{"6","planet"},{"7","overply"} }; //braced initializer syntax
	auto word = ChoseWordLength.find(wordLength);
	FString HIDDEN_WORD = "";

	if (word != ChoseWordLength.end()) {

		HIDDEN_WORD = ChoseWordLength[wordLength]; //this must be an isogram
		MyCurrentTries = 1;
		MyHiddenWord = HIDDEN_WORD;
	}
	else {
		HIDDEN_WORD = "ant";
		MyCurrentTries = 1;
		MyHiddenWord = HIDDEN_WORD;
	}
	
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) 
{	
	int32 len = GetHiddenWordLength();

	if (!CheckIfIsogram(guess)) {
		return EGuessStatus::Not_isogram;
	}
	else if (len != guess.length()) {
		return EGuessStatus::Wrong_Word_Length;
	}
	else if (!IsLowerCase(guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else {

		return EGuessStatus::OK;
	}
	
}

//receives a valid guess and increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	// increment the turn number
	MyCurrentTries++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming the same length as guess

	// loop through all letters in the hidden word
	
	for (int32 MHChar = 0; MHChar < WordLength; MHChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match
			if (guess[GChar] == MyHiddenWord[MHChar]) {
				if (MHChar == GChar) {//if the indexes are the same
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
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

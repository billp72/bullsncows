/*The game logic (no view code or direct interaction)
  The game is a simple word game based on Mastermind
*/

#pragma once
#include <string>

//to make the syntax unreal friendly
using FString = std::string;
using int32 = int;

// Two integers initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};
//class is used to encapsolate enum values--takes them out of global scope
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_isogram,
	Wrong_Word_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); //constuctor
	void Reset();
	void ChoseWordLength(FString);
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	
	EGuessStatus CheckGuessValidity(FString);
	//provide a method of counting Bulls and Cows, an increasing turn number
	FBullCowCount SubmitValidGuess(FString);
	
private:
	//see constuctor for initialization
	int32 MyCurrentTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool CheckIfIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
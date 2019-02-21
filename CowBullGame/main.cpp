/*This is the console executable that makes use of the BullCow class
  This acts as the view in the MVC pattern and is responsible for all
  user interaction. For game logic, see FBullCowGame class
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make the syntax unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void printIntro();
int main();
void PlayGame();
FText getValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate new game, which we reuse across playes

int main() 
{
	bool restart = false;
	do {
		printIntro();
		PlayGame();
		restart = AskToPlayAgain();
	} while (restart);
	
	return 0;
}

//plays a signal game to completion
void PlayGame()
{
	int32 myMaxTries = BCGame.GetMaxTries();
	//loop asking for guesses while the game is NOT won
	//and there are still tries remaining
	
		do
		{
			FText guess = getValidGuess();
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);

			std::cout << "Bulls = " << BullCowCount.Bulls;
			std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
		} while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= myMaxTries);

	PrintGameSummary();

	return;
}

void printIntro() 
{
	FString WordLength = "";
	//TODO add asccii art
	std::cout << "\n\nWelcome to Bulls & Cows, a fun word game\n";
	std::cout << "Can you guess the isogram I'm thinking of?\n\n";
	std::cout << "Choosing a word by entering the number of letters between 3 and 7";
	std::cout << std::endl;
	std::getline(std::cin, WordLength);
	BCGame.ChoseWordLength(WordLength);

	return; //always add even when nothing is returned.
}

//loop continually untill you get a valid guess
FText getValidGuess()
{
	FText Guess = "";
	EGuessStatus status = EGuessStatus::Invalid_Status;
	do {
		int32 tries = BCGame.GetCurrentTry();
		std::cout << tries << " of " << BCGame.GetMaxTries() << " Attempts";
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess); //will take entire FText, including spaces, up to delimiter or \n
		status = BCGame.CheckGuessValidity(Guess);
		switch (status)
		{
		case EGuessStatus::Wrong_Word_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n\n";
			break;
		case EGuessStatus::Not_isogram:
			std::cout << "Letters in the word must not repeat\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "All letters must be lowercase\n\n";
			break;
		default:
			break;
			//assume guess is valid
		}
		

	} while (status != EGuessStatus::OK);

	return Guess;
}

bool AskToPlayAgain()
{
	BCGame.Reset();
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	
	bool boolean = (toupper(Response[0]) == 'Y') || false;
	std::cout << std::endl;

	return boolean;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "GOOD JOB! YOU'VE WON\n";
	}
	else {
		std::cout << "SORRY. BETTER LUCK NEXT TIME\n";
	}
}
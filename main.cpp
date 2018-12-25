/* This is the console excutable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = FString;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGuess();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;	// instantiate a new game, which we re-use across plays


// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}

	while (bPlayAgain);
	return 0; 
}

// Introduce the game
void PrintIntro()
{

	std::cout << "Welcome to Bulls and Cows, a fun word game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCouwCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCouwCount.Bulls;
		std::cout << ", Cows = " << BullCouwCount.Cows << "\n\n";

		std::cout << std::endl;

		PrintGameSummary();
		return;
	}
}


// loop continually until the use gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess : ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); 
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)" << std::endl;
	FText Response = "";
	getline(std::cin, Response);
	return 	(Response[0] == 'Y') || (Response[0] == 'y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!!\n";
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME!\n";
	}
}

// repeat the guess back to them
void PrintGuess()
{
	FText Guess = GetValidGuess();
	std::cout << "your Guess was : " << Guess << std::endl;
	std::cout << std::endl;
}


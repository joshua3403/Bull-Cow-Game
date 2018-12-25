/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// all values initialised to zero
struct FBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); 
	void Reset();	

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	FBullCowCount SubmitValidGuess(FString);
	// TODO Make a interface that player can choice the legnth of word



// Please try and ignore this and focus on the interface above ^^
private:

	int32 MyCurrentTry;
	FString MyHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool bGameIswon;
};
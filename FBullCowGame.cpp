#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,6}, {5,10}, {6,13} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIswon;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // This must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIswon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))	
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))	
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength())	
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	
	int32 WorldLength = MyHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < WorldLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WorldLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WorldLength)
	{
		bGameIswon = true;
	}
	else
	{
		bGameIswon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; 
	for (auto Letter : Word)	
	{
		Letter = tolower(Letter);	
		if (LetterSeen[Letter])		
		{
			return false;			
		}
		else	
		{
			LetterSeen[Letter] = true;	
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

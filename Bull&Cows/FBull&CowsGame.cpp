#pragma once
#include "FBull&CowsGame.hpp"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() // the constructor
{
    Reset();
};

void FBullCowGame::Reset() 
{
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
};

int32 FBullCowGame::getMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries {{3, 4}, {4, 7}, {5, 10}, {6, 15}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
};


int32 FBullCowGame::getCurrentTry() const
{
    return MyCurrentTry;
};

bool FBullCowGame::IsGameWon() const
{
    return bGameIsWon;
};

int32 FBullCowGame::getHiddenWordLength() const
{
    return MyHiddenWord.length();
};

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            if (MyHiddenWord[MHWChar] == Guess[GChar])
            {
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++;
                } else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    if (Guess == MyHiddenWord) {
        bGameIsWon = true;
    }
    return BullCowCount;
};


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)){
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowerCase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != getHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    } 
};

bool FBullCowGame::IsIsogram(FString Guess) const
{
    if (Guess.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    
    for (auto Letter : Guess)
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
};

bool FBullCowGame::IsLowerCase(FString Guess) const
{
    if (Guess.length() == 0 || Guess == "\0") { return true; }
    else
    {
        for (auto Letter : Guess)
        {
            if (Letter != tolower(Letter)) { return false; }
        }
    }
    return true;
};

void FBullCowGame::SetMyHiddenWord(int32 WordLength) 
{
    TMap<int32, FString> Words {{3, "end"}, {4, "love"}, {5, "plant"}, {6, "planet"}};
    MyHiddenWord = Words[WordLength];
    return;
}

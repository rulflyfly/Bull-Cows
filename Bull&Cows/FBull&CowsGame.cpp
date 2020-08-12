#include "FBull&CowsGame.hpp"
#include <map>
#define TMap std::map

void FBullCowGame::Reset() 
{
    constexpr int32 MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;
    
    const FString HIDDEN_WORD = "end";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
};

int32 FBullCowGame::getMaxTries() const
{
    return MyMaxTries;
};


int32 FBullCowGame::getCurrentTry() const
{
    return MyCurrentTry;
};

bool FBullCowGame::IsGameWon() const
{
    return bGameIsWon;
};

FBullCowGame::FBullCowGame()
{
    Reset();
};

int32 FBullCowGame::getHiddenWordLength() const
{
    return MyHiddenWord.length();
};

//receives a valid guess, increments count,and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    //increment the turn number
    MyCurrentTry++;
    //set up a return variable
    FBullCowCount BullCowCount;
    //loop through all letters in the guess and get Buuls and Cows
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
}

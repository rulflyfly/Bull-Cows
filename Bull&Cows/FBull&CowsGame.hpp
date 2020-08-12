#ifndef FBull_CowsGame_hpp
#define FBull_CowsGame_hpp

#include <stdio.h>
#include <string>
#include <map>
#define TMap std::map

#endif /* FBull_CowsGame_hpp */

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame
{
public:
    FBullCowGame();
    int32 getMaxTries() const;
    int32 getCurrentTry() const;
    int32 getHiddenWordLength() const;
    bool IsGameWon() const;
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
    void SetMyHiddenWord(int32);
    
    void Reset();
    EGuessStatus CheckGuessValidity(FString) const;
    
    FBullCowCount SubmitValidGuess(FString);
    
private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
};

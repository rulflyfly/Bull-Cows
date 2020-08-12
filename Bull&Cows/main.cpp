/*
 This is a console executable that makes use of the
 BullCow class;
 This acts as a view in an MVC pattern, and is responsible
 for all user interaction;
 For game logic see the FBUllCowGame class;
 */

#include <iostream>
#include <string>
#include "FBull&CowsGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro ();
FText GetGuess ();
void GiveUserFeedback ();
void PlayGame ();
bool AskToPlayAgain();

FBullCowGame BCGame;

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

void PrintIntro ()
{
    int32 WORD_LENGTH = BCGame.getHiddenWordLength();
    std::cout << "Welcome to Bulls and Cows!\n";
    std::cout << "Can you guess a " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
    std::cout << "\n";
    return;
}

FText GetGuess ()
{
    int32 CurrentTry = BCGame.getCurrentTry();
    std::cout << "Try " << CurrentTry << ": ";
    std::cout << "Enter your guess ";
    
    FText Guess = "";
    getline(std::cin, Guess);
    
    return Guess;
}

void GiveUserFeedback(FText Guess)
{
    EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
    
    switch (Status)
    {
        case EGuessStatus::Not_Isogram:
            std::cout << "Your guess must be an isogram\n";
            return;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Your guess must be in lowercase\n";
            return;
        case EGuessStatus::Wrong_Length:
            std::cout << "Please, enter a " << BCGame.getHiddenWordLength() << " letter word\n";
            return;
        default:
            FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
            std::cout << "Bulls: " << BullCowCount.Bulls << "; Cows: " << BullCowCount.Cows << "\n";
            std::cout << "\n";
            return;
    }
    
    
    
}

void PlayGame ()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.getMaxTries();
    
    while (BCGame.getCurrentTry() != MaxTries && !BCGame.IsGameWon())
    {
        GiveUserFeedback(GetGuess());
    }
}

void PrintGameSumary (bool GameIsWon)
{
    if (GameIsWon)
    {
        std::cout << "YOU WON!!!\n\n";
    }
    else
    {
        std::cout << "You lose. Better luck next time!\n\n";
    }
}

bool AskToPlayAgain ()
{
    PrintGameSumary(BCGame.IsGameWon());
    std::cout << "Do you want to play again? (y/n) ";
    FText Response = "";
    getline(std::cin, Response);
    
    return (Response[0] == 'y' || Response[0] == 'Y');
}

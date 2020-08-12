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
#include <sstream>

using FText = std::string;
using int32 = int;

void PrintIntro ();
FText GetGuess ();
void GiveUserFeedback ();
void PlayGame ();
bool AskToPlayAgain();
int32 ChooseAHiddenWordLength();

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
};

int32 ChooseAHiddenWordLength()
{
    std::cout << "To choose a word length enter a number from 3 to 6: ";
    FString WordLengthString = "";
    getline(std::cin, WordLengthString);
    
    std::stringstream geek(WordLengthString);
    int32 WordLengthNum = 0;
    geek >> WordLengthNum;
    
    BCGame.SetMyHiddenWord(WordLengthNum);
    
    return WordLengthNum;
};

void PrintIntro ()
{
    
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "\n";
    int32 WORD_LENGTH = ChooseAHiddenWordLength();
    std::cout << "Can you guess a " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
    std::cout << "\n";
    return;
}

FText GetGuess ()
{
    int32 CurrentTry = BCGame.getCurrentTry();
    std::cout << "Try " << CurrentTry << " of "<< BCGame.getMaxTries() << " : ";
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
            std::cout << "Your guess must be an isogram\n\n";
            return;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Your guess must be in lowercase\n\n";
            return;
        case EGuessStatus::Wrong_Length:
            std::cout << "Please, enter a " << BCGame.getHiddenWordLength() << " letter word\n\n";
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
    
    while (BCGame.getCurrentTry() <= MaxTries && !BCGame.IsGameWon())
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

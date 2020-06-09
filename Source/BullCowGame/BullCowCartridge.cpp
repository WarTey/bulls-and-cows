// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) {
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    } else {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame() {
    HiddenWord = TEXT("About");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("The Hidden Word is %s!"), *HiddenWord);
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives!"), Lives);
    PrintLine(TEXT("Type in your guess..."));
    PrintLine(TEXT("And press enter to continue..."));
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) {
    if (Guess.Equals(HiddenWord)) {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    if (HiddenWord.Len() != Guess.Len()) {
        PrintLine(TEXT("The Hidden Word is %i letters long!"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guess again!"));
        PrintLine(TEXT("You have %i lives remaining!"), Lives);
        return;
    }

    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The Hidden Word was %s!"), *HiddenWord);
        EndGame();
        return;
    }

    PrintLine(TEXT("Guess again, you have %i lives left!"), Lives);
}

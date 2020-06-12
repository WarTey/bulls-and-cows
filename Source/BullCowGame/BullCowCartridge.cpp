// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
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

    if (!IsIsogram(Guess)) {
        PrintLine(TEXT("No repeating letters, guess again!"));
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

bool UBullCowCartridge::IsIsogram(const FString& Word) const {
    for (int32 Index = 0; Index < Word.Len() - 1; Index++)
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
            if (Word[Index] == Word[Comparison])
                return false;
    return true;
}

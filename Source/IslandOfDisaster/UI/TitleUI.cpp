// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUI.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UTitleUI::NativeConstruct()
{
	Super::NativeConstruct();

	BStart->OnClicked.AddDynamic(this, &UTitleUI::Start);
	BHelp->OnClicked.AddDynamic(this, &UTitleUI::Help);
	BQuit->OnClicked.AddDynamic(this, &UTitleUI::Quit);
}

void UTitleUI::Start()
{
	UGameplayStatics::OpenLevel(this, TEXT("Play"));
}

void UTitleUI::Help()
{

}

void UTitleUI::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
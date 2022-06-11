#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KODOBUR_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// pure virtual function - no implementation
	virtual void StartGame() PURE_VIRTUAL(UOburGameInstance::StartGame);
	virtual void RestartGame() PURE_VIRTUAL(UOburGameInstance::RestartGame);
	virtual void LoadMainMenu() PURE_VIRTUAL(UOburGameInstance::LoadMainMenu);
};

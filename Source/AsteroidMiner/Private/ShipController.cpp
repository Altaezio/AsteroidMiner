#include "ShipController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <EnhancedInputComponent.h>

// Sets default values
AShipController::AShipController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Instantiating your class Components

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Sphere);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	// Attaching your class Components to the default character's Skeletal Mesh Component.

	SpringArmComp->SetupAttachment(Sphere);

	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	//Setting class variables of the spring arm

	SpringArmComp->bUsePawnControlRotation = true;

	//Setting class variables of the Character movement component

	//GetCharacterMovement()->bOrientRotationToMovement = true;

//	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	//GetCharacterMovement()->bIgnoreBaseRotation = true;
}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PEI->BindAction(InputForward, ETriggerEvent::Triggered, this, &AShipController::MoveForward);
}

void AShipController::MoveForward(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;

	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (MoveValue.Y == 0.f) return;

	// Find out which way is forward
	const FRotator Rotation(0, Controller->GetControlRotation().Yaw, 0);

	// Get forward vector
	const FVector Direction = Rotation.RotateVector(FVector::ForwardVector);
	AddMovementInput(Direction, MoveValue.Y);
}
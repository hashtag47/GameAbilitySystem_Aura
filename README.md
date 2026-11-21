**This Project followed by Stephen Ulibarri of his Patreon Courses**

- GAS Implementation Pipeline
**Character Build :** 
  - CharacterBaseClass (Abstract)
        1. Removed InputComponent and BeginPlay
        2.  Added TObjectPtr to USkeletalMeshComponent to the Weapon
        3.  SetupAttachment to Character Mesh to the Socket WeaponHandSocket

  -  Character and Enemy Inherited from CharacterBase Class
         1. Stored in Blueprints folder in UE
         2.  Character with BP_Character_Name and ABP_Character_Name
         3.  Set State Machine and EventGraph in ABP
         4.  Set Slot as Montage for State Machine
         5.  Set EventBlueprintInitializeAnimation and EventBlueprintUpdateAnimation
         6.  Enemy Inherited from Animation Template ABP
         7.  ABP_Enemy Use Blendspace Player Connecting to Output Animation Pose

  -  PlayerController Setup
         1. Added PlayerController Inherited from PlayerController Class
         2. Added Constructor to the PlayerController
         3. Added BeginPlay and SetupInputComponent
         4. Added UInputMappingContext and UInputAction to the property
         5. Added Move function as the Callback 
         6. Attached to UEnhancedInputLocalPlayerSubsystem to BeginPlay and AddMappingContext to Current Context
         7. Attached Cursor settings to BeginPlay with FInputModeGameAndUI
         8. BindAction via EnhancedInputComponent from InputComponent
         9. Set Callback function with AddMovementInput()

    - GameMode Setup
  
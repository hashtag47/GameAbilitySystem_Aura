**This Project followed by Stephen Ulibarri of his Patreon Courses**
I Only Used Development Configuration Now Without Debug Mode of UE

- GAS Implementation Pipeline
**Section 1 :** 
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
          1. Inherited from GameModeBase
          2. Created BP_GameMode and Set Current Game Mode to it
          3. Set Default Pawn Character as the Main Character
          4. Set the UCameraComponent and USpringArmComponent to the Character

    - Enemy Interface
          1. CursorTrace created in PlayerController
          2. CursorHit returns FHitResult
          3. Interactive GetHitResultUnderCursor(ECC_Visibility, false, CursorHit)
          4. Created EnemyInterface in Interaction Folder
          5. When Cursor Interactive with the Enemy Actors, applies Highlight and UnHighlight
          6. Enemy Actors implemented from EnemyInterface (Abstract in default)
     
     - Post-Process Highlight
           1. Create BP_EnemyBase in Character folder and set BP_EnemyX Class Setting inherited from BP_EnemyBase
          2. Add Post Process Volume into the Scene and search for infinite to Set the infinite extended bounds
          3. Find custom depth setting in Project Settings
          4. Check Custom Depth-Stencil Pass with Enabled with Stencil
          5. Select Post Process Volumn object and add PP_Effect into the Post Process Materials array
          6. Set HighlightActor() and UnhighlightActor() in Enemy class
          7. GetMesh() -> SetRenderCustomDepth() / GetMesh() -> SetCustomDepthStencilValue()
          8. Do remember our design pattern which CharacterBase has USkeletalMeshComponent for Weapon

**Section 2 :**
-  Gameplay Ability System in General
          1. Ability System Component
          2. Attribute Set
          3. Gameplay Ability
          4. Ability Task
          5. Gameplay Effect
          6. Gameplay Cue
          7. Gameplay Tag
          8. For this project, Enemy Character will be directly link to Ability System Component and Attribute Set
          9. For this project, Player Controlled Character will use Player State as the coordinator
          10. Player State / Ability System Component / Attribute Set

- Player State Class
          1. Create C++ Class for Player State Class
          2. Set NetUpdateFrequency to 100.f, Lyra and Fornite follows this
          3. Create BP_PlayerState and set Player State from GameMode to BP_PlayerState
      
  - Ability System Component and Attribute Set
          1. ASC is the plug-in in Unreal Engine, search for Gameplay Ability
          2. Create C++ Class Inherited from AbilitySystemComponent
          3. Create C++ Class Inherited from AttributeSet
          4. PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });       

- GAS in Multiplayer
          1. Server ------ Client
          2. Dedicated Server (No human player / No rendering to a screen)
          3. Listen Server (Is a human player / Host has the advantage - no Lag)
          4. Server is the Authority ("Correct" version of the game, do "important" things on the server)
          5. Game Mode only exists on Server
          6. Controllers exist on both Server and Clients, but PC_x could only exists on itself
          7. Player State for each player all exists on the Server and also on the Clients
          8. HUD and Widgets only exists on the Clients, each client only has own HUD and widgets
          9. Replication only works one way from Server to Client with replicated variables
          10. Remote procedure calls
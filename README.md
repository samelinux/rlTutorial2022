# rlTutorial2022
RoguelikeDev Does The Complete Roguelike Tutorial 2022. [Link](https://www.reddit.com/r/roguelikedev/comments/vhfsda/roguelikedev_does_the_complete_roguelike_tutorial/)

- - -

<details>
<summary><b>Week 0- Tues June 21th</b></summary>

Bolerplate code. Here you can find the partial source: [tag](https://github.com/samelinux/rlTutorial2022/releases/tag/week0)

- [keyboard.c](keyboard.c)

  This file contains some functions to easly setup, reset and use the keyboard.

- [macro.h](macro.h)

  This fail contains just some macro that could be usefull in the future

- [main.c](main.c)

  This file contains the main function of the program and for now it's just a placeholder to show some "engine" functionality

- [position.c](position.c)

  This file contains a rough implementation of 2d positions structure and functions, we will expand this during the tutorial ... or we can scrapp it if not usefull

- [random.c](random.c)

  This file contains a straight copy and paste of a Lehmer random number generation function from wikipedia and some utility.
  
  We will mostly only use two functions randomSetup and randomDice

- [screen.c](screen.c)

  This file contains a rough and semplified ncurses implementation with way less functions but way easier to understand.
  
  It is base on ansi escape codes which is a fancy way to say "codes to instruct the terminal on how to draw things".
  
  With this you can print character and string anywhere on the terminal using foreground and background colors ... i think this will be enough for the tutorial, but we can expand this if we need to.

- [signal.c](signal.c)

  This file contains some code to help people which are less familiar with C debug some crashes.
  
  Nothing special, it just register some callback for handling signals the operating system may throw at your game in case we write something wrong (think of it as a way more destructive try/catch which always and with a crash and a stack trace 8p ).

- [time.c](time.c)

  This file contains just a function to get the current timestamp in milliseconds, it may come handy to profile some map generation/pathfinding algorithm.
  
  I'm not 100% sure we will need this, but if costs nothing to have it laying around.

</details>

- - -

<details>
<summary><b>Week 1- Tues June 28th</b></summary>

<details>
<summary> Part 0 - Setting Up </summary>

  - Build automation

    We will use [make] to automate the building process. You can find it [here](https://www.gnu.org/software/make/) but it can be already installed on your system if you choose to install some developer tool (Xcode on macos, gcc toolchain on linux)

  - Compiler

    We will use [gcc] to compile our code. You can find it [here](https://gcc.gnu.org/install/) but it come as a package in most linux distribution and as part of Xcode on macos.

  - Editor

    To edit your code you can use any editor you like, i personally use [vim](https://www.vim.org/) but [clion](https://www.jetbrains.com/clion/), [visual studio code](https://code.visualstudio.com/) and [Xcode](https://developer.apple.com/xcode/) are good alternatives.

  - Terminal

    All linux distro and macos come with a preinstalled terminal.
    
    I'm pretty sure you can use any terminal you want as long as it supports at last the original ansi 8 colors specification.

 - Testing the environment

   To test your environment you can use the boilerplate code i created in week 0 which you can find [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week0).
   - Download the zip and unpack it (or checkout the project and then checkout the week0 tag)
   - open your favorite terminal and move to the code directory (using the command 'cd')
   - start the build using the command 'make'
   - start the compiled program with the command './target'
   If all went right you should see something like this:
   
- Result

   ![part0 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part0_001.png "Part 0 screenshot")

</details>

<details>
<summary> Part 1 - Drawing the '@' symbol and moving it around </summary>

You can find the code from Week 1, Part 1 [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week1part1).

- Player structure

  We start by creating a structure to represent the player and give it a name.
  
  For now we just need his coordinates, but we will add property to the player structure as we go on.
```c
struct player_t
{
 int x;
 int y;
};
typedef struct player_t player_t;
```

- Player input handling

  Next we need a way to work with a player: initialize it and modify it base on the game and the player state.
  
  For now playerInit just set the player coordinates to 0, but later we will add more properties initializations (like hit point, stat values, ...).
  
  Since the player is basycally just composed of his coordinates, playerHandleInput just handle the input to move the player around.
  
  Since there's no world player movements are free, no collision, no enemies to attack, ... not much to do.
  
  For this purpose we have created two functions:
```c
void playerInit(player_t* player);
void playerHandleInput(player_t* player,char input);
```

- main flow

  The next thing to do is to modify the main function to implement a minimalistic game loop: display the player, move the player base on his input and quit.
  
  As you can see the code is quite commented so i'll not go much into datails on the implementation or the code itself, you can download each week and each part separately and take a look/play with it.
  
  All this logic is implemented in
```c
while(command!='q')
 {
  //clear the screen
  screenClear();

  //draw the player and a hint on how to quit
  screenPut(player.x,player.y,'@');
  screenPrint(0,screenHeight,"Press 'q' to quit");

  //get player input
  command=keyboardRead();
  //handle the input based on game/player status
  playerHandleInput(&player,command);
 }
```

- Extra

  I've uniformed all "libraries" init/deinit function names to have the same structure.
  
  I've added an init and a deinit function to screen basically to hide/show the terminal cursor and clear the screen/attributes (this is just a convenience)
  
  I've also added some comments to some file ... expect this since sometime i'll forget to add all comments 8p
  
- Result

  ![part1 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part1_001.png "Part 1 screenshot")

</details>

</details>

- - -

<details>
<summary><b>Week 2- Tues July 5th</b></summary>

<details>
<summary> Part 2 - The generic Entity, the render functions, and the map </summary>

You can find the code from Week 2, Part 2 [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week2part2).

- [main.c](main.c)

  In Part2 we added map and monster to the main loop (for now just initialization and drawing). We also removed the player variable since we're going to isolate it inside [player.c](player.c)
  
- [player.c](player.c)

  We moved the player variable here and modified all functions accordingly. Also we've added two checks during player movements:
  
  1. map boundaries to limit the player movements inside the map
  2. tile walkable flag to to limit the player movements on walkable tiles
  
  We also added a convenience function to render the player
  
- [map.c](map.c)

  This file will contain all map related functions and data types.
  
  Take a look at [map.c](map.c) to have a better understanding of all map related functions, they are quite commented.
  
  For now all maps data types we need are:
```c
enum mapType_t
{
 MAP_NONE=0,
 MAP_EMPTY,
 MAP_SAMPLE,
 MAP_MAX,
};
typedef enum mapType_t mapType_t;
```
  This enum is basically a list of all "buildable" maps.
```c
struct map_t
{
 mapType_t type;
 tile_t tiles[MAP_WIDTH*MAP_HEIGHT];
};
typedef struct map_t map_t;
```
  This struct is the representation of a map containing its type and all its tiles.
  
- [mapSample.c](mapSample.c)

  To separate all map types on their own file we created the file so we can implement the "building" of MAP_SAMPLE maps type. There's not much going on for now, this is just a basic map, we will add more in Part3
  
- [monster.c](monster.c)

  This file will contain all single monster related functions and data type. Here we will implement combat, movement and the fundation of a single monster AI.
  
  For now we wrote some simple functions like monsterInit to initialize a monster based on its type.
  
  There are also a "family" of functions, that we will expand in the future, which basically act as a "database" of monster property like monsterGlyph and monsterColor.
  
  In [monster.h](monster.h) we will define all monster data type like:
```c
enum monsterType_t
{
 MONSTER_NONE=0,
 MONSTER_RAT,
 MONSTER_MAX,
};
typedef enum monsterType_t monsterType_t;
```
  Which is basically a list of all existing monster in the game.
```c
struct monster_t
{
 monsterType_t type;
 int16_t x;
 int16_t y;
 char glyph;
 int8_t color;
};
typedef struct monster_t monster_t;
```
  Which is the representation of a single monster with all its characteristics
  
- [monsters.c](monsters.c)

  This file will contain functions related to all existing monsters like start their turn, render them, add/remove a monster from existence, ...
  
- [tile.c](tile.c)

  This file will contain all tile related functions and data types.
  
  Take a look at [tile.c](tile.c) to have a better understanding of all tiles related functions, they are quite commented.

  We added some function to work with tiles like tileInit which initialize a tile based on its type and, as we did with [monster.c](monster.c), a family of functions, that we will expand in the future, which basically act as a "database" of tiles property like tileGlyph, tileFGColor, tileBGColor, tileWalkable and tileBlockFOV.
  
  For now, all tiles data types we need are:
```c
enum tileType_t
{
 TILE_NONE=0,
 TILE_FLOOR,
 TILE_WALL,
 TILE_MAX,
};
typedef enum tileType_t tileType_t;
```
  Which is basically a list of all existing tile type in the game (we will add TILE_WATER, TILE_LAVA, ... for example)
```c
struct tile_t
{
 tileType_t type;
 char glyph;
 int8_t fgColor;
 int8_t bgColor;
 bool walkable;
 bool blockFOV;
};
typedef struct tile_t tile_t;
```
  Which is the representation of a single tile with all its characteristics
  
- Result

  ![part2 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part2_001.png "Part 2 screenshot")
  
</details>

<details>
<summary> Part 3 - Generating a dungeon </summary>

You can find the code from Week 2, Part 3 [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week2part3).

- [mapCave.c](mapCave.c)

  The big changes of Part 3 are all in this file. This is part of a family of files that we will expand to implement other types of map.
  
  The main and only functions in this type of files is in the form map(TYPE)Build which is responsable of building the type of map we want, in this case a cave.
  
  To build a cave we use a model called "cellular automata", to know more about them take a look here: [wikipedia](https://en.wikipedia.org/wiki/Cellular_automaton). 
  Maybe you are familiar with [Conway's game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) which you can play around with [here](https://playgameoflife.com/) ... to generate caves we simply change the rules!
  
  Take a look at [mapCave.c](mapCave.c) to have a better understanding of how we implemented a cellular automata and how we used it to generate our map.
  
- [monster.c](monster.c) and [player.c](player.c)

  We had to modify how we place entities in the map since now not all tiles are walkable and we do not want to bury alive neither monsters nor the player.
  
- position.c

  I choose to remove position_t and its relative files from the project since this is a tutorial and I want to keep things as simple as possible.
  
- [map.c](map.c)

  We added some convenience functions inside the map basic file to ease maps generation, the most important being [mapIsConnected](https://github.com/samelinux/rlTutorial2022/blob/9facbc8874a7a542177c1b25e88f33ccb71972be/map.c#L68) which we use to ensure our maps are fully connected.
  
- [signal.c](signal.c)

  We added a special signal handler for SIGINT so when the player press ctrl+c to halt the game we do not leave the terminal and the screen messed up (I noticed that when closing with ctrl+c the cursor did not become visible again).
  
- Result

  ![part3 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part3_001.png "Part 3 screenshot")

</details>

</details>

- - -

<details>
<summary><b>Week 3 - Tues July 12th</b></summary>

<details>
<summary> Part 4 - Field of View </summary>

You can find the code from Week 3, Part 4 [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week3part4).

- [bresenham.c](bresenham.c)

  added a "line drawing" function wich for now is only used to calculate the player field of view inside the map. This uses the Bresenham's line algorithm that calculate "digital" lines (digital intended as pixel perfect, without antialiasing).

  I'm not going much into details about the algorithm itself since it is explained quite well in its [wikipedia page](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm).
  
  We use it to trace lines from the player position to each tile inside his line of sight distance, checking whatever an unobstructed line can be made (without hitting any wall for now, but in the future there could be other tiles/object that block the line of sight). The set of tiles which a player can see it's called his field of view.
  
- [macro.h](macro.h)

  added math.h to the import since is uses the sqrt function. Now it generates a compiler error because we are using the distance macro. Before, since macro are exapanded in place (literally sobstituting the defined "string" for the "difining" string) this was not a problem.

- [main.c](main.c)

  We added field of view reset and calculation inside the main loop. This refresh the player field of view after each action giving us the opportunity to explore the map instead of having it fully visible from the start.
 
- [map.c](map.c)

  We added mapResetFOV to reset the tiles visible attribute so we can calculate the player field of view "fresh" each turn. This basically set all tiles in the map as non visible, afther this function you should always call playerCalculateFOV otherwise no tile will be visible on the next map rendering call.
  
  We modified the render function to render only visible and seen tiles. Now that a player has his own filed of view we can fully render only the tiles he sees and the tile marked as "to be remembered" (more on this later). As said before, this create a nice feel ofexploration and a character memory of the map, almost as if the here draws the maps edge while exploting to remember the way back.
  
- [monster.c](monster.c)

  I added a missing return at end of file (my OCD was tilting).
  
- [monsters.c](monsters.c)

  We modified the render function to render only visible monsters (a visible monster is one staying on a visible tile). This create the uncertainty of knowing the position of monsters outside the player field of view, is the monster still there?
 
- [player.c](player.c)

  We adde playerCalculateFOV which calcuate the actual player field of view inside the map. As said before this has to be called, almost always, in pairs with mapResetFOV to have a "fresh" field of view each turn. No one is forcing you to only call playerCalculateFOV and never cal mapResetFOV, this will generate a prefect memory of the map from the player prospective! Try it!
  
- [tile.c](tile.c)

  We added visible and seen property to all tiles (to implement field of view and map memory). visible is used to mark a tile actually visible from the player point of view while seen is used to implement character memory: an hero in a dungeon can not remember all the map details, just the walls outline to track his way back.
  
  We added tileRememberViewed to implement map memory on a tileType_t basis, with this we can have the character remember only important tiles (for now only walls) which the player can use at his own advantage (think about remembering traps position ...).

- Result

   ![part4 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part4_001.png "Part 4 screenshot")

</details>

<details>
<summary> Part 5 - Placing Enemies and kicking them (harmlessly) </summary>

You can find the code from Week 3, Part 5 [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week3part5).

- [main.c](main.c)

  We moved some code to have more consistent logic blocks, now the "engine" initialization is all in one block.

  We removed the rat generation we used in past weeks, we do not need it anymore since we are generating way more monsters to make floors more "enjoyable". For now monsters generation is done inside [map.c](map.c) but we can move it inside map types specific files so we can customize each floor.

  We added monster turns handling when the player takes a turn ... this seems fair even if, for now, monsters have no artificial intelligence so they do nothing 8)

- [map.c](map.c)

  We added monsters spawn after map generation by adding a call to [monsterPoolSpawn](https://github.com/samelinux/rlTutorial2022/blob/e7e9f8955dce594fcc1f761e361e6ad6a3e3bdf5/map.c#L28) after generating the map. This, as said before, can be moved in map types specific files so we can customize each floor.

  We added a check in map coordinates randomization so we do not pick monsters occupied tiles. This is usefull when searching for a coordinate to spawn (or teleport) the player and for spawning monsters (so we do not pile up them!).

- [monsters.c](monsters.c)

  We removed the file to keep the code simpler, we do not need to separate single monster functions from multi-monsters functions.

- [monster.c](monster.c)

  We renamed some functions (which where in monsters.c) to make it clear that they are "pool functions" (monsterPoolInit for example which initialize the pool of monsters). This is not necessary, but i think this is better from a tutorial prospective.

  We added a name to monsters and loaded it in monsterInit. This way we can better comunicate to the player what monsters are doing and what the player is interacting with.

  We changed some monsterType_t character representation to '?' so we see if we miss a case in monsterGlyph. If you add more monster types and forget to add their case in [monsterGlyph](https://github.com/samelinux/rlTutorial2022/blob/e7e9f8955dce594fcc1f761e361e6ad6a3e3bdf5/monster.c#L38) you will see a '?' instead of a blank tile, this is way easier to spot.

  We added two type of new monsters: orc and troll.

  We added monsterPoolSpawn which is used during map generation to popolate floors and, as said before, we can move it inside map types specific files so we can customize each floor. For now it is way easier to have it centralizedin just one point, but feel free to try having a different number of monsters for each different map type.

  We added monsterPoolAt to easly retrive monsters given their coordinates, this is usefull when checking for player movements but also while spawning monsters.

  We added monsterPoolHandleTurn which generate a new turn for all monsters when the player takes a turn ... this is fair because monsters have thier right too!
  
- player.c/h

  We modified playerHandleInput to return a boolean value which inform the main loop that the player has or has not taken a turn so we can make monster take their turns. For now all player actions generate a new turn, but in the future we can have actions that do not take a turn: think about a player wanting to look at his surrounding, it makes sense that this action should not consume a turn.

  We added the basics to implement "bump combat" in playerHandleInput, if the player moves toward a monster occupied tile then he attack the monsters instead of moving. This is basically all we need to implement hand-to-hand combat ... it is taht simple!

- tile.c

  We changed some tileType_t character representation to '?' so we see if we miss a case in tileGlyph. Take a look above at the comments for monster.c to better understand why.
  
- Result

  ![part5 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part5_001.png "Part 5 screenshot")

</details>

</details>

- - -

<details>
<summary><b>Week 4 - Tues July 19th</b></summary>

<details>
<summary> Part 6 - Doing (and taking) some damage </summary>

You can find the code from Week 4, Part 6 [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week4part6).

- general

  I changed all the #include directives to be more precise. Until now there
   where no problems including all the necessary header inside other header
   files, but now we have some header cycles. To avoid any further problem,
   now each source/header file include only the needed headers.

   I also changed some memset parameters, they worked anyway but with this
    changes the call is more correct.

- [keyboard.c](keyboard.c)

  We added support for numpad movement and for diagonal movement while using
   arrows via home,end,pageUp and pageDown.

- [macro.h](macro.h)

  Since distance uses sqrt which returns a double I added a cast to int16_t
   so it should not cause any problems with conversion.

- [main.c](main.c)

  I removed a unnecessary mapResetFOV since it is already done in
   playerCalculateFOV.

- [map.c](map.c)

  We added an implementatio of Dijkstra map to perform monsters pathfinding.
   You can learn more about Dijkstra maps on [roguebasin](http://www.roguebasin.com/index.php/Dijkstra_Maps_Visualized) and on [wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm).

   Basically we create three functions to clear and compute Dijkstra maps and
   to retrive its values.

- [monster.c](monster.c)

  We added some stats to monsters: maxHitPoints, hitPoints, attack and
   defence. These stats are used to implement the combat which, for now, is
   quite easy and completly predictable.

  We also added the Dijkstra map calculation before each monsters turn because
   other monsters obstruct passing on the tile they occupy.

  Next we added a basic artificial intelligence to make monsters alive. For
   now they just move towards the player (using the Dijkstra maps pathfinding)
   and attack him when in reach.

  You can easly add other artificial inteligence, for example a
   MONSTER_AI_WANDER which just move randomly and attack the player if in
   reach. It is just a simpler MONSTER_AI_HOSTILE which does not take into
   account the pathfinding. Try it!

  To ease the creation of multiple monster artificial intelligence we added a
   function [monsterBestMoveToReachPlayer](https://github.com/samelinux/rlTutorial2022/blob/68ac51471761f2f1b154a388e320d5f9609f0823/monster.c#L227) which move the monster toward the
   players. This function will be usefull when wrinting more artificial
   intelligence.

- [player.c](player.c)

  We added the same monsters stats to the player: maxHitPoints, hitPoints,
   attack and defence. Now the player can attack monster and get attacked ...
   and eventually die.

  Since moveing in just in the four cardinal direction is limiting, tedious
   during exploration and monsters can move diagonally, we also added diagonal
   movement for the player.

  In [playerRender](https://github.com/samelinux/rlTutorial2022/blob/6fd26f54caf0567f42a5550dfbc6fd1b8f02c776/player.c#L116) we added an indication of the player hitPoints and
   maxHitPoints. For now it is writtein in the upper left corner of the screen
   over the map, in the next Part we will polish the interface and move it in
   a better place.

  We also added three functions to implement combat, one to calculate if a
   monster is in attack range, one to implement player to monster attacks and
   one to implement monster to player attack. I've decided to have them
   separate as the data structure to represent the player and the monsters so
   we can optimize more the single data structures to fit more its uses.
   The combat is quite simple: attacking a target deals (attacker attack
   stat)-(defender defence) damage. This is completely predictable, we will
   add some randomness in the future, for now it is more than enough to kill
   and be killed.
   One important note: dead monsters do not leave corpses because I am
   planning to implement them as item.

- [signal.c](signal.c)

  I added screenDeinit and keyboardDeinit inside [signalHandler](https://github.com/samelinux/rlTutorial2022/blob/6fd26f54caf0567f42a5550dfbc6fd1b8f02c776/signal.c#L47) so even in
  case of a crash the terminal should recover to its original settings.

- [monsterAIHostile.c](monsterAIHostile.c)

  In this file we added a basic "seek and destroy" artificial intelligence for
   our monsters. They will basically move toward the player and try to kill
   him. They do not need line of sight to start being aggressive and do not
   lose interest/will/sight ... they are basically the perfect killing
   machine!

  You can easly add more artificial intelligence in files named monsterAIXXX
   to create a family of files. For example you can create, as mentioned
   before, a monsterAIWander which make a monster wander through the level and
   switch to monsterAIHostile in case it sees the player (remember, if the
   player sees the monster, the opposite is also true!).

- Dijkstra map example

  By modifying the [mapRender](https://github.com/samelinux/rlTutorial2022/blob/6fd26f54caf0567f42a5550dfbc6fd1b8f02c776/map.c#L129) you can easly print the Dijkstra maps value
  (modulo 10 to have a clearer result) and visualize them directly in game.

  ![part6 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part6_001.png "Part 6 Dijkstra map example")

- Result

  As I said before, these monsters artificial intelligence are a little bit
   overtuned; they will find you anywhere in the level, they will surround you
   and they will kill you!

  ![part6 002](https://github.com/samelinux/rlTutorial2022/raw/main/images/part6_002.png "Part 6 screenshot")


</details>

<details>
<summary> Part 6.5 - Creating a better loop </summary>

You can find the code from Week 4, Part 6.5 [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week4part6.5).

- [main.c](main.c)

  I deeply changed the main loop of the game by adding [player states](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/player.h#L9).

  Player states are used to separate the input and update logic of various
   screen/logic block of the game into separate files and functions. For example
   the STATE_MAP handle all player input specific to the map screen which for
   now is just movement.

  We created the function [mainQuit](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/main.c#L45) which can be used everywhere in the code
   to safetly exit the program, deinitializing all "engine" system and
   returning the terminal to its initial configuration.

- [map.c](map.c)

  We splitted the map initialization from the map generation and added a
   function to deinitialize the map. For now the [mapDeinit](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/map.c#L24) function is now
   veryusefull because we allocate the map statically, but its utility will
   become clear in the future if we decide to allocate the map dinamically.

- [monster.c](monster.c)

  We adde a deinitialization function as in [map.c](map.c) for the monsters pool
   for the same reason.

- [player.c](player.c)

  We adde a deinitialization function as in [map.c](map.c) for the player for the
   same reason.

  We changed a bit how the player is initializaed.
  Now the [playerInit](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/player.c#L19) function just setup the player state so the game start
   in the main menu screen.
  The [playerNewGame](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/player.c#L32) function setup the player to start a new game, we will
   eventually create also a playerLoadGame function.

  [playerUpdate](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/player.c#L44) is now just a wrapper which calls the correct stateXXXUpdate
   function. Also [playerRender](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/player.c#L61) become a wrapper to the correct
   stateXXXRender function.
  This is quite usefull because let us separate various update and render code
   for the different screen/logic block of the game.

  We also added a state change in [playerAttackedBy](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/player.c#L158) function to move the
   player to the game over screen if he reach 0 hit points.

- [stateGameOver.c](stateGameOver.c)

  This file contains the update and render function for the game over screen.

  [stateGameOverUpdate](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/stateGameOver.c#L8) is quite simple, when the player press return move
   him to the main menu.

  [stateGameOverRender](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/stateGameOver.c#L21) for now is also quite simple, it just prints "You
   died" in the middle of the screen. Note that we do not clear the screen
   in this state so the last map rendered remain visible and the player can see
   his last moment of life.

- [stateMainMenu.c](stateMainMenu.c)

  This file contains the update and render function for the main menu screen.
  It is just a basic main menu, but in the future we will add a real menu for
   the player to start a new game, load a saved one if present and maybe change
   some game options.

- [stateMap.c](stateMap.c)

  This file contains the update and render function for the main game screen.

  [stateMapUpdate](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/stateMap.c#L11) handle all the input needed to let the player move in the
   map. In the future we will add others keys to let the player perform other
   actions like: access his backpack, examine the map, ...

  [stateMapRender](https://github.com/samelinux/rlTutorial2022/blob/e7496a7a7f56890988c6d74ce2d27f3e5947b6f2/stateMap.c#L113) just render the map. In the next part we will polish this
   screen to print more usefull informations.

</details>

<details>
<summary> Part 7 - Creating the Interface </summary>

You can find the code from Week 4, Part 7 [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week4part7).

- [map.c](map.c)

  We modified the [mapRender](https://github.com/samelinux/rlTutorial2022/blob/2a1d6cce6f26034bffa5e2bc8f6cd2196960bb28/map.c#L141) function to render the map from a specific point
   of view. This enable us to render the map from the player perspective or,
   while examining the map, from a tile perspective.

- [monster.c](monster.c)

  We added a function to draw a monster from a specific point of view to be able
   to draw monster from the player perspective and from any tile perspective.
   This is usefull to implement the map examination command.

  We also modified [monsterPoolRender](https://github.com/samelinux/rlTutorial2022/blob/2a1d6cce6f26034bffa5e2bc8f6cd2196960bb28/monster.c#L202) to take advantage of the new monster
   render function.

- [player.c](player.c)

  We added some field to the player structure to implement some nice feature.

  We added a journal for the player to read where every important event gets
   logged up to 100 events. In the map state, only the last few events get
   printed. To ease the reading we also added a state to view the full journal.
   To write to the journal we created the [playerLog](https://github.com/samelinux/rlTutorial2022/blob/2a1d6cce6f26034bffa5e2bc8f6cd2196960bb28/player.c#L109) function.
   Since now we have a journal, all combat event gets written to it instead of
   the terminal.

  We added two coordinates examineMapX and examineMapY which are used in the
   STATE_EXAMINE_MAP to move around the selection. This state is quite usefull
   for the player since it enables the player to move according to threats he
   spots on the map from further away.

  We also added a functon to render the player from a specific point of view.
   This function is used while examining the map to easly draw the player with
   inverted colors.

- [stateGameOver.c](stateGameOver.c)

  We added an hack in this state to have an updated map in the death screen so
   the player can see the killing blow log and his hit points after dieing.

- [stateMap.c](stateMap.c)

  We added two new command to the map screen: 'x' to eXamine the map and 'J' to
   view the Journal.

  The bulk of the UI update is in this state:

  1. we constrained the map to MAP_VIEWPORT_WIDTH x MAP_VIEWPORT_HEIGHT
  2. we move the player stats to the remaining space on the right
  3. we added the last lines of the journal in the remaining space under the map

- [tile.c](tile.c)

  We added a name to all tile so we can display it when the player examine map
   tiles.

  We also added a utility function to draw tiles.

- [stateExaminemap.c](stateExaminemap.c)

  This state handle all the game logic that let the player examine the map, from
   handling the input to move the selection, to drawing a modified versione of
   the map and some info on the selected tile. To have a better understanding of
   it take a look at the implementation, it is quite easy and indipendent from
   the rest of the code.

- [stateJournal.c](stateJournal.c)

  This state handle all the game logic that let the player view the full journal
   of the last 100 events, from handling the scrolling to drawing it. The code
   is very very simple, take a look at the file to have a better idea of how it
   works.

  This is a perfect example and should clarify why we created the states in
   first place: to separate the varius game block in separate files which are
   smaller and easier to understand.

- New UI result

  ![part7 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part7_001.png "Part 7 new UI")

- Examine command result

  ![part7 002](https://github.com/samelinux/rlTutorial2022/raw/main/images/part7_002.png "Part 7 examine command")

</details>

</details>

- - -

<details>
<summary><b>Week 5 - Tues July 26th</b></summary>

<details>
<summary> Part 8 - Items and Inventory </summary>

</details>

<details>
<summary> Part 9 - Ranged Scrolls and Targeting </summary>

</details>

</details>

- - -

<details>
<summary><b>Week 6 - Tues August 2rd</b></summary>

<details>
<summary> Part 10 - Saving and loading </summary>

</details>

<details>
<summary> Part 11 - Delving into the Dungeon </summary>

</details>

</details>

- - -

<details>
<summary><b>Week 7 - Tues August 9th</b></summary>

<details>
<summary> Part 12 - Increasing Difficulty </summary>

</details>

<details>
<summary> Part 13 - Gearing up </summary>

</details>

</details>

- - -

<details>
<summary><b>Week 8 - Tues August 16th</b></summary>

Share you game / Conclusion

</details>

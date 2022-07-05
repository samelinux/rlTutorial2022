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
  
![part2 001](https://github.com/samelinux/rlTutorial2022/raw/main/images/part2_001.png "Part 2 screenshot")
  
</details>

<details>
<summary> Part 3 - Generating a dungeon </summary>

</details>

</details>

- - -

<details>
<summary><b>Week 3 - Tues July 12th</b></summary>

<details>
<summary> Part 4 - Field of View </summary>

</details>

<details>
<summary> Part 5 - Placing Enemies and kicking them (harmlessly) </summary>

</details>

</details>

- - -

<details>
<summary><b>Week 4 - Tues July 19th</b></summary>

<details>
<summary> Part 6 - Doing (and taking) some damage </summary>

</details>

<details>
<summary> Part 7 - Creating the Interface </summary>

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

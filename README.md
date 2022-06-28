# rlTutorial2022
RoguelikeDev Does The Complete Roguelike Tutorial 2022. [Link](https://www.reddit.com/r/roguelikedev/comments/vhfsda/roguelikedev_does_the_complete_roguelike_tutorial/)

- - -
## Week 0- Tues June 21th
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

- - -
## Week 1- Tues June 28th
Part 0 - Setting Up

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
   
   ![part0 001](https://github.com/samelinux/rlTutorial2022/raw/3a43ec5a247e7e739a9fb36c2311e7a461d58729/images/part0_001.png "Part 0 screenshot")

Part 1 - Drawing the '@' symbol and moving it around
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

- - -
## Week 2- Tues July 5th
Part 2 - The generic Entity, the render functions, and the map

Part 3 - Generating a dungeon

- - -
## Week 3 - Tues July 12th
Part 4 - Field of View

Part 5 - Placing Enemies and kicking them (harmlessly)

- - -
## Week 4 - Tues July 19th
Part 6 - Doing (and taking) some damage

Part 7 - Creating the Interface

- - -
## Week 5 - Tues July 26th
Part 8 - Items and Inventory

Part 9 - Ranged Scrolls and Targeting

- - -
## Week 6 - Tues August 2rd
Part 10 - Saving and loading

Part 11 - Delving into the Dungeon

- - -
## Week 7 - Tues August 9th
Part 12 - Increasing Difficulty

Part 13 - Gearing up

- - -
## Week 8 - Tues August 16th
Share you game / Conclusion

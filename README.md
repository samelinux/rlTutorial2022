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

  This file contains a straight copy and paste of a Lehmer random number generation function from wikipedia and some utility. We will mostly only use two functions randomSetup and randomDice

- [screen.c](screen.c)

  This file contains a rough and semplified ncurses implementation with way less functions but way easier to understand. It is base on ansi escape codes which is a fancy way to say "codes to instruct the terminal on how to draw things". With this you can print character and string anywhere on the terminal using foreground and background colors ... i think this will be enough for the tutorial, but we can expand this if we need to.

- [signal.c](signal.c)

  This file contains some code to help people which are less familiar with C debug some crashes. Nothing special, it just register some callback for handling signals the operating system may throw at your game in case we write something wrong (think of it as a way more destructive try/catch which always and with a crash and a stack trace 8p ).

- [time.c](time.c)

  This file contains just a function to get the current timestamp in milliseconds, it may come handy to profile some map generation/pathfinding algorithm. I'm not 100% sure we will need this, but if costs nothing to have it laying around.

- - -
## Week 1- Tues June 28th
Part 0 - Installing the toolchain

  - Build automation
    We will use [make] to automate the building process. You can find it [here](https://www.gnu.org/software/make/) but it can be already installed on your system if you choose to install some developer tool (Xcode on macos, gcc toolchain on linux)

  - Compiler
    We will use [gcc] to compile our code. You can find it [here](https://gcc.gnu.org/install/) but it come as a package in most linux distribution and as part of Xcode on macos.

  - Editor
    To edit your code you can use any editor you like, i personally use [vim](https://www.vim.org/) but [clion](https://www.jetbrains.com/clion/), [visual studio code](https://code.visualstudio.com/) and [Xcode](https://developer.apple.com/xcode/) are good alternatives.

  - Terminal
    All linux distro and macos come with a preinstalled terminal. I'm pretty sure you can use any terminal you want as long as it supports at last the original ansi 8 colors specification.

 - Testing the environment
   To test your environment you can use the boilerplate code i created in week 0 which you can find [here](https://github.com/samelinux/rlTutorial2022/releases/tag/week0).
   - Download the zip and unpack it (or checkout the project and then checkout the week0 tag)
   - open your favorite terminal and move to the code directory (using the command 'cd')
   - start the build using the command 'make'
   - start the compiled program with the command './target'
   If all went right you should see something like this:
   
   ![part0 001](https://github.com/samelinux/rlTutorial2022/raw/3a43ec5a247e7e739a9fb36c2311e7a461d58729/images/part0_001.png "Part 0 result")

Part 1

- - -
## Week 2- Tues July 5th
Parts 2 & 3

- - -
## Week 3 - Tues July 12th
Parts 4 & 5

- - -
## Week 4 - Tues July 19th
Parts 6 & 7

- - -
## Week 5 - Tues July 26th
Parts 8 & 9

- - -
## Week 6 - Tues August 2rd
Parts 10 & 11

- - -
## Week 7 - Tues August 9th
Parts 12 & 13

- - -
## Week 8 - Tues August 16th
Share you game / Conclusion

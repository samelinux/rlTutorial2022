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
Parts 0 & 1

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

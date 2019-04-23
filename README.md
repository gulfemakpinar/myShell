# Shell


This is a command line interpreter with some extra feature.

## New Features!

  - commands seperated by ";" runs concurrently.
  - commands seperated by "|" runs sequentially.
  - if it detects a quit, it will exit from program after it process this line.


# Design Overview

Firstly, the code checks the number of arguments to determine whether the code will work in batch mode, interactive mode or warn if the argument number is wrong. If it has one argument, it will work on interactive mode, read a line from the user and process it until user types "quit" command somewhere in the cammand. If it has two arguments, it will work in batch mode and take the file name in arguments. Then, it opens file (if it couldn't it will warn user) and read it line by line and process it untill it hit a "quit" command or EOF. When it gets the line, it checks whether it is too long or not. Then it echo the line if it is in batch mode.

It check if there is a quit in the line by tracing the line and marks the index of the begining of the quit. Then, it removes the quit. Does this step until all quits are gone and store whether it will quit end of this process or not. After this input line could has some problems such as there is not any characters or alphabetic character. It will handle these situations.

By using an array it marks places of all white spaces after an ";" or "|" and by using a loop it removes these white spaces to split the command correctly.
Finally, Our input is ready to process. Program will split the input by ";" and create same number of treads. these treads will get each splitted part of the input and runs method called myProcess to run each part in a treaded fashion.

In myProcess, it split the input by "|" and runs the commands sequentially.

The program waits all treads to finish by using thread_join and gets the next input or line.

# Complete Specification
  - It works in batch and interactive mode.
 It handles:
    - An incorrect number of command line arguments to your shell program. 
    - The batch file does not exist or cannot be opened. 
    - A very long command line.
    - An empty command line. 
    - Extra white spaces within a command line. 
    - Batch file ends without quit command.
    - Multiple ";" and "|" in a command line and lines without alpabetic characters.
  - if it detects a quit, it will exit from program after it process this line.
  - commands seperated by ";" runs concurrently.
  - commands seperated by "|" runs sequentially.
  - runs in combination of both


# Known Bugs or Problems
  - A command does not exist or cannot be executed. 



# Installation

Run these after entering the the file that contains the program.
To build it.
```sh
$ make
```
For interactive mode:
```sh
$ ./shell
```
For batch mode:
for example with a file named test.bat
```sh
$ ./shell test.bat
```
To uninstall
```sh
$ make clean
```

# Creator:
Gülfem Akpınar
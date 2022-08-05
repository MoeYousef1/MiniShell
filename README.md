Authored by Mohammad Ulayan
Ex2

==Description==
The program displays the current path for the user and waits for the user to enter a command.
 If the user entered a command other than done history or cd, it will send that command to an array in order to pass it to execvp so it gets executed, if the execvp failed to execute the command, it returns an error message, also the command should be with no spaces after or before the command, or the program wont pass it to execvp and it will return a NO SPACE ALLOWED message.
In my code, the inputs (done, cd, only enter, only spaces and the input with spaces before or after the command) won’t enter the history file, every other input/command will enter the history file even the word (history) enters the history file.
If the user pressed enter without anything else, it will continue without doing anything and the current path will be displayed again, the same thing will happen if the user entered just spaces and then pressed enter.
If the user enters the string (cd) the program will print COMMAND NOT SUPPORTED (YET), also (cd) won’t enter the history file.
If the user enters the string (history) the program will display all the commands that were saved in the history file, and if the history was empty, it prints NO HISTORY YET, at the same time the word (history) will enter the history file too.
If the user enters the word (done) it will print the NUM OF COMMANDS, THE TOTAL NUMBER OF WORDS IN ALL COMMANDS, then the ALLOCATED MEMORY will be freed, and the program will be exited, also (done) won’t enter the history file.
In my program everything counts as a COMMAND except (only enter, only spaces).

Program DATABASE:
History: it contains the strings which were entered by the user before, and we can get to them just by entering the string (history).
Array of chars (str):  it’s used to store all the characters of each string, it must be up to 512 chars, it’s also used to read the strings from the history file.
Command Array: it’s used with strtok to pass the words of each command into the (argv Array).
Argv Array: stores the commands, each word in a different index.
Array path: to store the current dir.

Functions:
3 main functions 
    1) wordCounter: this method receives a string and counts the number of words the string has
    2) charCounter: this method receives a string and counts the number of chars the string has, skipping spaces.
3)fakeMain: it does all the things mentioned above.

==Program Files==
ex2a.c  contains the main and the functions 

==How to compile==
Run: ex2a.c
Or through the Terminal using gcc ex2a.c -o main
Then running it by typing  ./ex2a
same thing for ex2b.c

==Input==
A string (command)

==Output==
If the string is history, the output will be the history containing all the previous commands that were entered, if there were no previous commands then the output will be NO HISTORY YET.
If the sting is done, the output will be the NUM OF COMMANDS and the TOTAL NUM OF WORDS IN ALL COMMANDS and the program will be exited.
If the string is cd, the output will be COMMAND NOT SUPPORTED (YET)
If the string was entered with spaces before or after it, the output will be NO SPACE ALLOWD
If the user pressed only enter or spaces then enter, there will be no output.
In every time enter is pressed the path will be printed again.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ex2b

==Description==
Everything is the same as ex2a but there are some additional things.
If the first character in the string was (!) and after it was a number with no spaces between any of them the program will print the command that is in the line that’s equal to the number that was entered after (!) and it will send that command to the child process to execute it, and the command will be saved into the history too.
If the number that we entered was equal to a line that has the word history in it, it will print the history of previous commands and the word history will be saved in the file too.
If there were spaces after the (!) then it will print, LINE WAS NOT FOUND.

Program DATABASE:
Same as ex2a but there is an additional thing 
curToChar Array: it will store integers after converting them into strings using sprint method.

Functions:
ex2b.c      contains the main and the functions 

==Program Files==
Same as ex2a

==How to compile==
Same as ex2a

==Input==
Same as ex2a

==Output==
Same as ex2a
And the additional things were written in the description.

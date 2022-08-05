//Name: Mohammad Ulayan
//ID: 207793456

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <linux/limits.h> // used it to get the PATH_MAX

#define	MAX_COMMANDS	32
#define MAXIMUM 512

int wordCounter(const char *str); // count number of words in entered string
int charCounter(const char *str); // count number of chars in entered string
void fakeMain(); // main method

int main()
{
    fakeMain();
    return 0 ;
}

void fakeMain(){
    char *str = (char *)malloc(sizeof(char) * MAXIMUM); // allocate memory for the string

    if (str == NULL) // check if we manged to allocate memory
    {
        perror("Allocation Failed");// if not then we print Allocation Failed
        exit(1);
    }

    int i;
    int save=0 , keep=0; //variable (save: counts Total number of words in all commands)
    //variable (keep: counts Num of commands
    FILE *fp;
    char *command; // pointer to use it with strtok method
    char *argv[MAX_COMMANDS]; // pointer array for execvp
    char path[PATH_MAX]; // array for the path <current dir>
    getcwd(path, sizeof(path)); // using getCwd in order to get the path

    while (1) { // infinite loop

        printf("%s>", path);// printing the path or the current dir
        fgets(str, MAXIMUM, stdin); // get user input

        if ((strlen(str) > 0) && (str[strlen(str) - 1] == '\n')) { // if the string is not NULL
            str[strlen(str) - 1] = '\0';                          //and if the last char is \n
        }                                                        //then we change the \n int a \0

        if (strlen(str) == 0 || charCounter(str) == 0) {
            continue; // if the string is NULL or if there are no characters
        }            // then continue without doing anything
            // in case if the string was only spaces or enter key
        else {
            save += wordCounter(str); // every time the string is not NULL
            // add the wordCount to the save
            keep += 1;              // and add one to the keep
            //both variables will be back to zero after the loop is exited

            if (str[0] == ' ') { // if the first character is a space
                save -= 1; // decrease the save by one and print a message
                printf("Spaces BEFORE/AFTER commands are not allowed\n");
            }

            else if (str[strlen(str) - 1] == ' ' && str[0]==' ') {// if both first and last characters are spaces
                //decrease the save
                save-=1;
            }

            else if (str[strlen(str) - 1] == ' ') {// if only the last character is a space, print a message
                printf("Spaces BEFORE/AFTER commands are not allowed\n");
            }

            else if (strcmp(str, "done") == 0) {// if the string was equal to done
                printf("Num of commands: %d\n", keep);// print Num of commands
                printf("Total number of words in all commands: %d !\n", save - 1);//print Total num of words -1
                // cuz we don't count (done) here
                free(str);// free the allocated memory
                exit(0); // exit the loop
            }

            else if (strcmp(str, "cd") == 0) {// if the string was cd then print a message
                printf("command not supported (Yet)\n");
            }

            else if (strcmp(str, "history") == 0) {// if the string was history
                fp = fopen("file.txt", "r+"); // open the file for read/write

                if (fp == NULL) { // if the file is NULL
                    printf("There is no HISTORY atm\n"); //message

                    fp = fopen("file.txt", "w"); // open the file to write
                    fprintf(fp, "%s\n", str); // write the string (history) in it
                }

                else {
                    i = 1; // start from 1
                    while (fscanf(fp, "%[^\n]%*c", str) != EOF) {// read from the file
                        // %[^\n]%*c , will help you to get an entire sentence
                        // until the next line isn’t encountered “\n” or enter is pressed

                        printf("%d: %s\n", i, str); // print strings from the history to the screen , (numbered)
                        i++;
                    }
                    fprintf(fp, "%s\n", "history"); // here we print (history) in the file too
                }
                fclose(fp); // close the file
            }
            else {// if the string is other than history, done , cd or with spaces before and after
                fp = fopen("file.txt", "a"); // open file , and the file is created if it does not exist
                fprintf(fp, "%s\n", str); // write entered string to the file
                fclose(fp);// close the file

                command = strtok(str, " ");// using strtok to separate the string
                // if the string is ls -l then ls will enter the array first , then -l will enter the array
                i = 0;
                while (command != NULL) { // unless command is NULL
                    argv[i] = command; // we add the separated string to the array
                    i++;
                    command = strtok(NULL, " "); // in order to get all the separated words in the string
                    // we pass NULL to strtok , if there are no more words
                    // it returns NULL
                }
                argv[i] = NULL;// last index is NULL

                pid_t pid = fork(); // using fork to create another process
                if (pid < 0) { // if pid is less than 0 , it means the child process was not entered
                    perror("Child process was not entered");
                    exit(1);

                }
                else if (pid == 0) { // if the pid is 0 , means we are at the child process

                    if (execvp(argv[0], argv) <= -1) // if the execvp gave a negative value , print error message
                        perror("Execvp error");
                    exit(0);
                }

                else {
                    waitpid(pid, NULL, 0); // the father process waits for the child to finish running
                }
            }
        }
    }
}

int wordCounter(const char *str){
    int counter =0; // word counter
    int i = 0;

    while (str[i] != '\0')// till we reach the end of the string
    {
        if (str[i+1]!=' '&& str[i] == ' ')//  if we have a space ,and after it is not a space we increase the counter
        {
            counter++;
        }
        if (str[i + 1] == '\0' && str[i] == ' ')// if we reach the end of the string,
            // and we have one or more spaces at the end we return the counter
        {
            return counter;
        }
        i++;
    }
    return counter + 1; // +1 in order to include the first word
}

int charCounter(const char *str){
    int counter =0; // char counter
    int i =0;
    while(str[i]!='\0') // till we reach the end of the string
    {
        if(str[i]!=' ') // if we are not at a space then increase the counter
        {
            counter++;
        }
        i++;
    }
    return counter;
}
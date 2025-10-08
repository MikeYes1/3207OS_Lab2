#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "helpers.h"
#include <sys/wait.h>

#define ID_LEN 257

/*
 * void help(){
 *     massive printf message
 * }
 * 
 */

void help(){
     printf("~~Manual~~\n\nBuilt-in Commands:\n\"exit\": Ends interaction with"
       " the shell.\n\n\"pwd\": Prints the full path of the current working directory."
       "\n\n\"cd\": Change the working directory with this command. Provide the full "
       "path of a directory as an argument \nEx: \"cd fun/house/pit\"\n\n\n");
}

/*
 * int exit(){
 *      probably unnecessary
 * }
 */
 
 /*
  * char? void? *pwd(){
  * 
  *     getcwd(char buffer[some size], size_t size) returns a pointer to a string which 
  *         is an absolute pathname. NULL in case name exceeds size bytes. Check for NULL.
  * 
  * }
  */

void pwd(){
    
    char buffer[ID_LEN];
    char *ceedoubleyoudee = getcwd(buffer, ID_LEN);
    if(ceedoubleyoudee == NULL){
        printf("Path name exceeded size of bytes\n");
    }
    printf("%s\n", ceedoubleyoudee);

    //not printing lab2?? Linux not running my program!! <-- uh oh!
}
  
  /*
   * int? void? cd(char* path?){
   * 
   *    chdir(). Returns an integer, 0 on success and -1 on fail. Accepts a string
   *        which is a path.
   * 
   * }
   */
 
void cd(char *path){
    
    int ceedee = chdir(path);
    if(ceedee == -1){
        printf("Invalid path, try to include the full path to a directory if it"
        "'s not working.\n");
    }
}

char *obtainPath(char *fileName){
    
    char *pathEnv = getenv("PATH");//check for error, also this returns a read-only pointer
    if(pathEnv == NULL){
        printf("Error: Could not obtain PATH environment variable"); //Make sure that PATH exists
        return NULL;
    }
    
    char *buffer = strdup(pathEnv); //buffer will recieve changes from strtok
    
    char *token = strtok(buffer, ":"); //I asked ChadGPT how the strtok pointer works
    char filePath[4096];
    struct stat sBuf;
                                
    while(token!=NULL){
        strcpy(filePath, token);
        strcat(filePath, "/");      //this series of strcpy and cats is to build a safe string with the full path.
        strcat(filePath, fileName);
        
        printf("Checking: %s\n", filePath);
        
        if(stat(filePath, &sBuf)==0){
            printf("FOUND: %s\n", filePath);
            free(buffer);
            char *returnString = strdup(filePath);
            return returnString;
        }
        token = strtok(NULL, ":"); //token is read only! had a lot of trouble with modifying read only strings.
    }
    
    free(buffer);
    return NULL;
    
    /*my coding of this function destroyed my mental, had to thouroughly use chatgpt so 
     * i could understand my many, many, many mistakes. it was my only hope.*/
}



void pe(char **fileArray){
    struct stat sBuf;
    pid_t pid;
    printf("\n");
    if (stat(fileArray[0], &sBuf)==-1){
        fileArray[0] = obtainPath(fileArray[0]); //Run PATH function
    } 
    
    if(fileArray[0] == NULL){
        printf("Command not found\n");
        return;
    }
    
    pid = fork(); //use Cygwin or use wsl
    
    if(pid<0){
        perror("fork failed");
        return /*1*/;
    }
 
    if(pid == 0){ //child process
        printf("Child executing %s using execv()\n", fileArray[0]);
        execv(fileArray[0], fileArray);
        
        perror("Invalid Input");
        exit(1);
    } else{
        printf("Parent: waiting for child (PID %d)\n", pid);
        wait(NULL);
        printf("\nChild finished\n"); //%d status?
    }

} 


/*
 * void pe(char *stream){
 * 
 *      struct stat statBuffer;
 * 
 *      fork()
 *      if(pid == child... 0){
 *          execv(stream[full path of program])
 *      }
 * 
 * //stat("path", buffer to stat struct); 
 * stat itself returns an int,-1 if fail, the struct has the meat
 * 
 * Needs to have normal full path in tact. execv uses full path, what uses PATH environment? is exists... then call a 
 * path function?
 * 
 * if input is gibberish, then there will be an error in the exec.
 * 
 * part 1. how tf do i get a conditional to run this/do i need a conditional?
 *          Use else.
 * part 2. how do i register the path string, do i run PATH?
 *          path is not a function, use a loop after trying with full path first
 * part 3. actually getting new programs to run
 * 
 */
 
 /*
  * And pathing environment variables, this translates user input to full path
  * 
  * getenv("PATH") gets the magic path variable
  * 
  * part 1. wtf is a path environment variable, how does it birth
  *     It is born when the computer wakes up. it's like... here are env vars, and PATH is -----. Can be added to in UNIX.
  * part 2. what do i program here if it needs to exist
  *     
  */
 
 /*
  * Then piping '|'
  */

 /*
  * And lastly, background execution '&'
  */

int main(int argc, char **argv)
{
    /*
     * int counter = 0;
     * int i = 0;
     * char *thing = malloc(257);
     * char **thingArr = NULL;
     * 
     * while(strcmp(thing, "exit") != 0){  
     *     printf("%d: ", counter)
     *     scanf("%s", &string); Allow for input of multiple words
     *     while(charat(thing) != end of string){
     *         if(charat(thing != whitespace){
     *             Function to add the character to strarr[i];
     *         } else {
     *             i++;
     *         }
     *     counter++;
     *     i = 0;
     * }
     * 
     * something to measure thing and exact input to match function names
     * 
     * 
     * free(thing);
     * 
     * 
     */
    
    
    
    //initialized outside the loop in order to use the condition with no issues
    
        
    char _line[1000];
    fgets(_line, 1000, stdin);
    char *line = strdup(_line);
    char **array = parse(line," \n");

    if (array == NULL) {
        exit(1);
    }

    int i = 0;
    while (array[i]!=NULL) {
        printf("%s\n",array[i++]);
    }


    while(strcmp(array[0], "exit") != 0){
        if(strcmp(array[0], "help") == 0){
            help();
        } else if (strcmp(array[0], "pwd") == 0){
            pwd();
        } else if (strcmp(array[0], "cd") == 0){
            cd(array[1]);
        }else{
            pe(array);
        }
        printf("\n");
        
        fgets(_line, 1000, stdin);
        line = strdup(_line);
        array = parse(line," \n");
        
    }
        //the file/file path is one thing...
        //first word is  



    free(array);
    free(line);
    printf("you made it!\n");
    

    
    return 0;
}

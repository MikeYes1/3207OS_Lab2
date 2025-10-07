#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

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
       "path of a directory as an argument, Ex: \"cd fun/house/pit\"\n\n\n");
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
    
    char *pathEnv = getenv("PATH");//check for error
    char *token = strtok(pathEnv, ":"); //I asked ChadGPT how the strtok pointer works
    char *filePath;
    struct stat sBuf;
    //int fileExists = 0;
    
    
    while(token!=NULL){
        filePath = strcat(token, fileName);
        if(stat(filePath, &sBuf)==0){
            return filePath;
        }
        token = strtok(NULL, ":");
    }
    /*if(fileExists == 0){
        filePath = NULL;
    }*/
    
    return NULL;
}



void pe(char *fileName){
    struct stat sBuf;
    pid_t pid;
    
    if (stat(fileName, &sBuf)==-1){
        fileName = obtainPath(fileName); //Run PATH
    } 
    
    pid = fork(); //use Cygwin or use wsl
    
    if(pid<0){
        perror("fork failed");
        return /*1*/;
    }
    
    if(pid == 0){ //child process
        printf("Child executing %s using execv()\n", fileName);
        execv(fileName/*, passed an array like argv*/);
        
        perror("Invalid Input");
        exit(1);
    } else{
        printf("Parent: waiting for child (PID %d)\n", pid);
        wait(NULL);
        printf("Child finished with status \n"); //%d status?
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
    
    int counter = 0;
    int i = 0; //general purpose, but mainly parses the characters of the input string
    int j = 0; //measures the strings in the array
    int k = 0; //parses the characters of the individual strings
    
    //initialized outside the loop in order to use the condition with no issues
    char **stringArr = malloc(10 * sizeof(char*));
    
    while(strcmp(stringArr[0], "exit") != 0){
        char *thing = malloc(ID_LEN);
        for (int i = 0; i < 10; i++){ // You input too many words, it dies.
            stringArr[i] = calloc((ID_LEN+1), 1);
        }
        
        i = 0;
        j = 0;
        k = 0;
        printf("%d: ", counter);
        fgets(thing, ID_LEN, stdin);
        
        /*This while loop is to get rid of the new line character, so using strcmp  
         * becomes easier. */
        while(thing[i] != '\n'){
            i++;
        }
        thing[i] = ' ';
        i = 0;
        
        while(thing[i] != '\0'){
            if(thing[i] != ' '){
                stringArr[j][k] = thing[i];
                k++;
            } else {
                stringArr[j][k+1] = '\0'; //?? add null terminator at the end, maybe useless
                j++;
                k = 0;
            }
            i++;
        }
        
        //delete later
        for(i = 0; i < 10; i++){
            printf("%s\n", stringArr[i]);
        }

        //else for the program comparisons?
        //reach else, then put path into an exec command, if it errors then you
        //say the error message
        if(strcmp(stringArr[0], "help") == 0){
            help();
        } else if (strcmp(stringArr[0], "pwd") == 0){
            pwd();
        } else if (strcmp(stringArr[0], "cd") == 0){
            cd(stringArr[1]);
        }else{
            ;
        }
        //the file/file path is one thing...
        //first word is  

        counter++;
        //These strings are freed to avoid regurgitated values from previous loops
        free(thing);
        for(i = 0; i < 10; i++) free(stringArr[i]);
    }
    
    free(stringArr);
    
    printf("you made it!\n");
    

    
    return 0;
}

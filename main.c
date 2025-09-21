#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_LEN 256

/*
 * void help(){
 *     massive printf message
 * }
 * 
 */

void help(){
     printf("~~Manual~~\n\nBuilt-in Commands:\n\"exit\": Ends interaction with"
       " the shell.\n\n\"pwd\": Prints the full path of the current working directory."
       "\n\n\"cd\": Change the working directory with this command. Provide the path"
       " of a directory as an argument, Ex: \"cd fun/house/pit\"\n\n\n");
}

/*
 * int exit(){
 *      probably unnecessary
 * }
 */
 
 /*
  * char? void? *pwd(){
  * 
  *     getcwd()
  * 
  * }
  */
  
  
  /*
   * int? void? cd(char* path?){
   * 
   *    takes path as argument somewhere
   *    chdir()
   * 
   * }
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
        char *thing = malloc(257);
        for (int i = 0; i < 10; i++){ // You input too many words, and it dies.
            stringArr[i] = calloc((ID_LEN+1), 1);
        }
        
        i = 0;
        j = 0;
        k = 0;
        printf("%d: ", counter);
        fgets(thing, ID_LEN+1, stdin);
        
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
        //ble
        
        //else for the program comparisons?
        //reach else, then put path into an exec command, if it errors then you
        //say the error message
        if(strcmp(stringArr[0], "help") == 0){
            help();
        } else if (strcmp(stringArr[0], "pwd") == 0){
            ;
        } else if (strcmp(stringArr[0], "cd") == 0){
            ;
        }else{
            ;
        }
        

        counter++;
        //These strings are freed to avoid regurgitated values from previous loops
        free(thing);
        for(i = 0; i < 10; i++) free(stringArr[i]);
    }
    
    free(stringArr);
    
    printf("you made it!\n");
    

    
    return 0;
}

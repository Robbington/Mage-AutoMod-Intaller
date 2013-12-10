
// Function Prototypes
char * appendSlash( char *dir );
char * getInput(char message[], int len);
int file_exist (char *filename);


/*
*
* Append A Slash To a String If there is not one
* Returns Copy of Original String
*
*/

char * appendSlash( char *str ){
    int sLen = strlen(str);
    char * strSlash;
    int addSlash = 0;
    if(str[sLen - 1] != '/'){ 
        sLen += 2;
        addSlash = 1;
    }  
    
    strSlash = malloc( sizeof(char *) * (sLen) );
    strcpy(strSlash, str);

    if(addSlash == 1){
        strcat(strSlash, "/");
    }
    
    return strSlash;
}

/*
*
* Displays Message and Retrieves User Input 
* Returns *Char 
*
*/

char * getInput(char message[], int len){
    char *input = malloc(sizeof (char *)  * (len));
    printf("\n%s\n", message);
    scanf("%s", input);    
    return input;
}

/*
*
* Simple Test If File Exists, requires <sys/stat.h>
* Returns *Char 
*
*/

int file_exist (char *filename){
    struct stat   buffer;   
    return (stat (filename, &buffer) == 0);
}
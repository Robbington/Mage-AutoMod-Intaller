

char MAGE[13]   = "app/Mage.php";
char *LOCAL  = "app/code/local/";
char *COMMUN = "app/code/community/";

char *MAGEDIR;
char *PACKAGE;
char *MODULE;
char *MODPATH;


// Function Prototypes
int setup();
int getMageDir();
int getPackageName();
int getModName();
int verify();

int setup(){
    if(
        getMageDir() &&
        getPackageName() &&
        getModName() 
    ){
        if(verify()){
            return 1;
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}

int getMageDir(){
    
    char *dir = getInput("Please Enter Path To Magento Root:", 255);
    struct stat s;
    
    MAGEDIR = appendSlash(dir);
    int isDir = stat(MAGEDIR, &s);
   
    char *MagePath = malloc(strlen(MAGEDIR) + strlen(MAGE) + 1);
    int validMagePath = -1;
    
    if(isDir == 0){ 
        strcpy(MagePath, MAGEDIR);
        strcat(MagePath, MAGE);

        if(file_exist(MagePath)){
            validMagePath = 0;
        }else{
             printf("\n Path Supplied is not Magento Root\n ");
        }
    }else{
        printf("\n %s Is not a path \n ", dir );
    }
    
    free(MagePath);
    free(dir);
    
    if(validMagePath == -1){
        getMageDir();
    }else{
        return 1;
    }
}

int getPackageName(){
    PACKAGE = getInput("Enter Mage Package Name: ", 255);
    return 1;
}

int getModName(){
    MODULE = getInput("Enter Module Name: ", 255);
    return 1;
}

int verify(){
    char *path;
    char *loc = getInput("Enter Code Pool: \n (1)Local: \n (2)Community:", 255);
    
    if(loc[0] == '1'){
        path = LOCAL;
    }else if(loc[0] == '2'){
        path = COMMUN;
    }else{
        printf("\n Invalid Choice, code pool set to local \n ");
        path = LOCAL;
    }

    char *pack = appendSlash( PACKAGE );
    char *mod  = appendSlash( MODULE );

    MODPATH = malloc( strlen(MAGEDIR) + strlen(path) + strlen(pack) + strlen(mod) + 1 );
    strcat(MODPATH, MAGEDIR);
    strcat(MODPATH, path);
    strcat(MODPATH, pack);
    struct stat s;
    int isDir = stat(MODPATH, &s);
   
    if(isDir != 0){
        char *buildPack = getInput("Package Givent not a Current Package, create it?: \n (1)Yes: \n (2)Exit:", 255);
        if(buildPack[0] == '1'){
            if(mkdir(MODPATH, S_IRGRP) != 0){
                printf("\n Failed To Write Directory, inadequate permissions \n ");
                exit(0);
            }
        }else{
            exit(0);
        }
        free(buildPack);
    }

    strcat(MODPATH, mod);
    int isModDir = stat(MODPATH, &s);
    if(isModDir != 0){
        if(mkdir(MODPATH, S_IRGRP) != 0){
            printf("\n Failed To Write Module Directory\n ");
            exit(0);
        }
    }
    
    free(pack); 
    free(mod);
    free(loc); 
    free(MODPATH);
    free(PACKAGE);
    free(MODULE);
    free(MAGEDIR);
    return 0;
}



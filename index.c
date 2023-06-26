#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h> 

#define MAX_FILE_NAME 70
#define PYTHON "py "


char* createString(const char* text) {
    size_t size = strlen(text) + 1;
    char* string = (char*)malloc((int)size * sizeof(char));

    if(string == NULL){
        printf("Erro ao alocar memória\n");
    }
    else{
        strcpy(string, text);
    }
    return string;
}


void concatString(char** string, const char* text) {
    // Determina o tamanho necessário para a nova string
    size_t current_size = strlen(*string);
    size_t text_size = strlen(text);
    size_t new_size = current_size + text_size + 1;

    // Realoca a memória para a nova string
    char* new_string = (char*)realloc(*string, (int)new_size * sizeof(char));

    if(new_string == NULL) {
        printf("Erro ao alocar memória. \n");
    } else{
    // Concatena o novo texto à string existente
    strcat(new_string + current_size, text);

    // Atualiza o ponteiro para a nova string
    *string = new_string;
    }
    
}

void freeString(char* string) {
    free(string);
}

// remove extension from the image file name 
char* getFileNameWithoutExtension(char *filename){
    for (int i = 0; i < strlen(filename); i++){
        if ( filename[i] == '.' ) {
            filename[i] = '\0';
            return filename;
        }
    }
}

// generate a descriptor path based on the filename
char* getDescriptorPath(char* extractor_dir, char* filename)
{
    char* descriptor_path = createString(extractor_dir);
    concatString(&descriptor_path, "/");
    concatString(&descriptor_path, getFileNameWithoutExtension(filename));
    return descriptor_path;
}

// count the quantity of images from de index file
int counter_img(DIR *dir, struct dirent *lsdir, struct dirent *lsimg){
    int imgcounter = 0;
    dir = opendir("./base/img");
    
    /*  scan all the directories and files from "img" folder and save them into a text file (.txt) */
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        DIR *location;

        char img_path[MAX_FILE_NAME] = "./base/img/";
        char folder_name[MAX_FILE_NAME] = "";

        strcat(folder_name, lsdir->d_name);
        strcat(img_path, folder_name);
        int backfolder = strcmp(img_path, "./base/img/..");
        int samefolder = strcmp(img_path, "./base/img/.");

        // verify if the current folder detected is not set to the back or the current folder 
        if ( !(!backfolder || !samefolder) ){
            location = opendir(img_path);

            while ( (lsimg = readdir(location)) != NULL ) 
            {
                char imgext[MAX_FILE_NAME];
                char filename[MAX_FILE_NAME];

                strcpy(filename, lsimg->d_name);
                strcpy(imgext, filename);

                int backfolder1 = strcmp(imgext, "..");
                int samefolder1 = strcmp(imgext, "."); 

                if ( !(!backfolder1 || !samefolder1) )
                {           
                    imgcounter++;
                }
            }
            closedir(location);
        } 
    }
    closedir(dir);

    return imgcounter;
}

// create the descriptor file
void create_descriptor(char *img_path, char *descriptor_path){
    char command[150] = PYTHON;
    char file[40] = "extractor/extractor.py ";

    strcat(command, file);
    strcat(command, img_path);
    strcat(command, " ");
    strcat(command, descriptor_path);

    system(command);
}

int main(void)
{   
    // time_t begin = time(NULL);

    //create the dir variable
    DIR *dir;
    struct dirent *lsdir, *lsimg;
    dir = opendir("./base/img");

    // create the file that save the locations (used on query after)
    FILE *loc;
    loc = fopen("./base/locations.txt", "wt");
    if(loc == NULL) {
        printf("Erro ao criar arquivo"); 
        return 0;
    }

    // create the index file 
    FILE *fhist;
    fhist = fopen("index_histogram-extractor.txt", "w");
    if(fhist == NULL) {
        printf("Erro ao criar arquivo"); 
        return 0;
    }
    fprintf(fhist, "%d\n", counter_img(dir, lsdir, lsimg));

    /* 
    scan all the directories and files from "img" folder and save them in a text file (.txt)
    */
    while (( lsdir = readdir(dir) ) != NULL )
    {
        DIR *location;
        char img_path[MAX_FILE_NAME] = "./base/img/";
        char folder_name[MAX_FILE_NAME] = "";

        strcat(folder_name, lsdir->d_name);
        strcat(img_path, folder_name);
        int backfolder = strcmp(img_path, "./base/img/..");
        int samefolder = strcmp(img_path, "./base/img/.");

        // verify if the current folder detected is not set to the back or the current folder 
        if ( !(!backfolder || !samefolder) ){
            // Command to create a new folder 

            // access the location folder
            location = opendir(img_path);
            fprintf(loc, "%s \n", folder_name);

            // create the extractor folder 
            char* extractor_dir = createString("./base/extractor_");
            concatString(&extractor_dir, folder_name);

            char* command = createString("mkdir ");
            concatString(&command, extractor_dir);

            system(command);

            // walks through images from the location folder
            while ( (lsimg = readdir(location)) != NULL ) 
            {
                char *filename = createString(lsimg->d_name);

                int backfolder1 = strcmp(filename, "..");
                int samefolder1 = strcmp(filename, "."); 

                if ( !(!backfolder1 || !samefolder1) )
                {
                    char* img_file = createString(img_path);
                    concatString(&img_file, "/");
                    concatString(&img_file, filename);

                    fprintf(fhist, "%s ", img_file);

                    // generate the descriptor path
                    char* descriptor_path = getDescriptorPath(extractor_dir, filename);

                    // run the python file
                    create_descriptor(img_file, descriptor_path);

                    fprintf(fhist, "%s ", descriptor_path);
                    fprintf(fhist, "%s\n", folder_name);

                    freeString(img_file);
                    freeString(descriptor_path);
                }
                freeString(filename);
            }
            closedir(location);
            freeString(command);
        }
    }
    closedir(dir);
    fclose(loc);
    fclose(fhist);

    // time_t end = time(NULL);
 
    // // calcula o tempo decorrido encontrando a diferença (end - begin)
    // int time = end - begin;
    // printf("The elapsed time is %d seconds", time);
 
    return 0;
}
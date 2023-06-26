
#include "functions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


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
char* getDescriptorPath(char* extractor_dir, char* filename, int op)
{
    char* descriptor_path = createString(extractor_dir);
    concatString(&descriptor_path, "/");
    if (op == 1){
        concatString(&descriptor_path, filename);
        concatString(&descriptor_path, ".txt");
    } else {
        concatString(&descriptor_path, getFileNameWithoutExtension(filename));
    }
    return descriptor_path;
}

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
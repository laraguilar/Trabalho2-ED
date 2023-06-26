#ifndef FUNCTIONS_C
#define FUNCTIONS_C

char* getFileNameWithoutExtension(char *filename);

char* getDescriptorPath(char* extractor_dir, char* filename, int op);

char* createString(const char* text);

void concatString(char** string, const char* text);

#endif
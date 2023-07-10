#ifndef DIRECTORY
#define DIRECTORY

#include <dirent.h>
#include "linkedlists.h"
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

LinkedList* listdir(char* dirAddress) {
    LinkedList* linkl = createList();
    DIR *directory;
    struct dirent *entry;
    directory = opendir(dirAddress);
    if (directory == NULL) {
        return NULL;
    }
    while ((entry = readdir(directory)) != NULL) {
        if(
            strcmp(entry->d_name, "..") == 0 
            || strcmp(entry->d_name, ".") == 0 
            || strcmp(entry->d_name, "desktop.ini") == 0
        ){
            continue;
        }
        if (entry->d_type == DT_REG) {
            append(linkl, entry->d_name, true);
        }else if(entry->d_type == DT_DIR){
            append(linkl, entry->d_name, false);
        }
    }
    return linkl;
}

char* getThisDirectory(){
    char dir[PATH_MAX]; 
    getcwd(dir, sizeof(dir));
    char* dir2 = (char*)malloc(sizeof(dir));
    strcpy(dir2, dir);
    return dir2;
}

char* fileExtension(char* fileName){
    char* name[PATH_MAX];
    strcpy(name, fileName);
    char* extension = NULL;
    extension = strchr(name, '.');
    if(extension != NULL){
        return extension;
    }else{
        return "";
    }
}

//newName need not have the file extension, we will automatically add it.
int renameFile(char* pathInput, char* oldName, char* newName){
    //concatenate the pesky backslash
    char path[PATH_MAX];
    strcpy(path, pathInput);
    strcat(path, "\\");
    //get the old and new name strings.
    char old[PATH_MAX];
    char new[PATH_MAX];
    strcpy(old, oldName);
    strcpy(new, newName);
    //add the file extension to newName, get file extension from oldName.
    char extension[PATH_MAX];
    strcpy(extension, fileExtension(old));
    strcat(new, extension);
    //concatenate the old and new names onto the path string, store then in 'original' and 'changed'.
    char original[PATH_MAX];
    char changed[PATH_MAX];
    strcpy(original, path);
    strcpy(changed, path);
    strcat(original, old);
    strcat(changed, new);
    //proceed to rename.
    if(MoveFile(original, changed) != 0){
        printf("Successfully renamed from %s to %s.\n", old, new);
    }else{
        printf("Error renaming %s.\n");
    }
    return 0;
}

#endif
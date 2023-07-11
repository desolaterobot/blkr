#ifndef DIRECTORY
#define DIRECTORY

#include <dirent.h>
#include "linkedlists.h"
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

#define PATH_MAX 200

// header file for directory and file related functions.

// converts a directory into a linked list.
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

// opens the file or directory in a window
void openDirectory(char* parentPathInput, char* fileName){
    char parentPath[PATH_MAX];
    strcpy(parentPath, parentPathInput);
    strcat(parentPath, "/");
    strcat(parentPath, fileName);
    char command[PATH_MAX];
    sprintf(command, "start \"\" \"%s\"", parentPath);
    system(command);
}

//deletes a file or directory
void deleteDirectory(char* parentPathInput, char* fileName){
    char parentPath[PATH_MAX];
    strcpy(parentPath, parentPathInput);
    strcat(parentPath, "/");
    strcat(parentPath, fileName);
    remove(parentPath);
}

//get current directory as a string
char* getThisDirectory(){
    char dir[PATH_MAX]; 
    getcwd(dir, sizeof(dir));
    char* dir2 = (char*)malloc(sizeof(dir));
    strcpy(dir2, dir);
    return dir2;
}

//gets only the file extension from a filename.
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

//renames a file, given the parent path, old name and new name. new name does not need the file extension.
int renameFile(char* pathInput, char* oldName, char* newName){
    //concatenate the pesky backslash
    char path[PATH_MAX];
    strcpy(path, pathInput);
    strcat(path, "\\");
    //copy the old and new name strings.
    char old[PATH_MAX];
    char new[PATH_MAX];
    strcpy(old, oldName);
    strcpy(new, newName);
    //get file extension from oldName, add the file extension to newName
    char extension[PATH_MAX];
    strcpy(extension, fileExtension(old));
    strcat(new, extension);
    //concatenate the old and new names onto the path string, store them in 'original' and 'changed'.
    char original[PATH_MAX];
    char changed[PATH_MAX];
    strcpy(original, path);
    strcpy(changed, path);
    strcat(original, old);
    strcat(changed, new);
    //proceed to rename.
    if(rename(original, changed) == 0){
        printf("Successfully renamed from %s to %s.\n", old, new);
    }else{
        printf("Error renaming %s to %s.\n", old, new);
        printf("%s may be an invalid filename or is already taken in the file.\n", new);
        return -1;
    }
    return 0;
}

#endif
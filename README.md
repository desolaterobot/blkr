# blkr - bulk rename files in Windows.

This project, written completely in C 😎, allows you to loop through a folder for each file or subdirectory one-by-one, in order to rename each of them. While looping through the directory list, an option will given to either open (in case you forget what the name of the file corresponds to) or delete that file as well for convenience.

This program aims to declutter and tidy your directories, freeing up space and promoting ease of use.

## How to use?
1) Open `blkr.exe` then enter the directory address.
2) The program will then list our the subdirectories and files in the chosen directory. Confirm that you want to bulk-rename this directory.
3) The program will begin listing out the items in the chosen directory one-by-one, and you can enter the new name for each item. Not entering anything then pressing `ENTER` would not rename the file. Typing `open` will open the file and typing `del` will delete the file unrecoverably.
4) After looping through the whole directory, you will be prompted to revert all your name changes (deletions not included).

## How does it work?
The program loops through the directory, and appends each item (file or subdirectory) into a linked list. Each node contains a pointer to string of the name of the item, as well as bool that determines if the item is a file or subdirectory:
```c
typedef struct n{
    char* value;
    struct n* next;
    bool isFile;
}Node;

typedef struct ll{
    Node* head;
    Node* tail;
    int size;
}LinkedList;
```
We then iterate through the linked list and for each node, we prompt the user for the new name of the item, then rename the item accordingly using the following ugly function:
```c
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
    //get file extension from oldName, add the file extension to newName.
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
```
As we iterate, the newNames are appended into a seperate linked list, in case the user decides to revert later. At each iteration, the user is also given the option to open or delete the item, which are given by the following functions:
```c
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
```
The `openDirectory()` function requires the `system()` function from `<stdlib.h>`, which executes string input into the command line. In this case, the way to open a file is by using the following command structure: 
```bat
start "" "C:/path"
```
The `deleteDirectory()` function uses the `remove()` function, from `<stdio.h>`, which just takes in a file path as a string, and deletes accordingly.
## Why?
cuz i felt silly and goofy and thought that making a C project that's heavily dependent on strings was a good idea 💀
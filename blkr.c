#include "directory.h"
#include "linkedlists.h"
#include <string.h>

char* input(char* message){
    char* input = NULL;
    size_t buffer_size = 0;
    printf(message);
    getline(&input, &buffer_size, stdin);
    input[strcspn(input, "\n")] = '\0';
    return input;
}

//one-by-one renaming method.
void bulkRenameList(LinkedList* ll, char* pathInput){
    //copy the path input first
    LinkedList* newNameList = createList();
    printf("Program will now cycle through the files one-by-one for renaming.\n");
    printf("Pressing ENTER without typing anything will not rename the file.\n");
    printf("File extensions not required, they are added automatically.\n");
    char path[PATH_MAX];
    strcpy(path, pathInput);
    Node* iter = ll->head;
    int fileCount = 0;
    int dirCount = 0;
    while(iter){
        if(iter->isFile){
            fileCount++;
        }else{
            dirCount++;
        }
        printf("Renaming %s %d: %s to: ", iter->isFile ? "FILE":"DIRECTORY", iter->isFile ? fileCount:dirCount, iter->value);
        char* newName = input("");
        if(strcmp(newName, "") == 0){
            append(newNameList, NULL, iter->isFile);
            iter = iter->next;
            continue;
        }
        renameFile(path, iter->value, newName);
        //before appending to the newNameList, newName must be appended with the file extension.
        char* ext = fileExtension(iter->value);
        strcat(newName, ext);
        append(newNameList, newName, iter->isFile);
        //cycle to next file on the linkedlist
        iter = iter->next;
    }
    printf("%s has been successfully renamed. \nWould you like to revert? (Y/N)\n>> ", path);
    char* inp = input("");
    if(strcmp(inp, "y") == 0 || strcmp(inp, "Y") == 0){
        //revert everything back.
        printf("Reverting %s back to original.\n", path);
        Node* iter = newNameList->head;
        Node* iter2 = ll->head;
        while(iter){
            if(iter->value){
                char name[PATH_MAX];
                strcpy(name, iter2->value);
                //chop off the extension from iter2->value to prevent adding another extension to it
                char* dot = strchr(name, '.');
                if(dot){
                    *dot = '\0';
                }
                //because renameFile() automatically adds the extension
                renameFile(path, iter->value, name);
            }
            iter = iter->next;
            iter2 = iter2->next;
        }
    }
    destroyList(newNameList);
}

int main() {
    //keep on prompting user...
    while(1){
        //ask for directory
        char* directory = input("Enter a directory: ");
        if(strcmp(directory, "this") == 0){
            directory = getThisDirectory();
            printf("Selected directory: %s\n", directory);
        }
        LinkedList* targetDirectoryList = listdir(directory);
        printList(targetDirectoryList);
        if(targetDirectoryList == NULL || targetDirectoryList->head == NULL){
            destroyList(targetDirectoryList);
            continue;
        }
        //by this point, we should have an non-empty targetDirectoryList.
        //confirm if user wants to bulk-rename this folder.
        char* choose = input("Would you like to bulk-rename this folder? (Y/N)\n>> ");
        if(!strcmp(choose, "y") && !strcmp(choose, "Y")){
            destroyList(targetDirectoryList);
            continue;
        }
        //ready to bulk-rename. one by one method.
        bulkRenameList(targetDirectoryList, directory);
        //done with list, destroy it!
        destroyList(targetDirectoryList);
        char* again = input("Would you like to bulk-rename another directory? (Y/N)\n>> ");
        if(strcmp(again, "y") == 0 || strcmp(again, "Y") == 0){
            continue;
        }
        break;
    }
    return 0;
}
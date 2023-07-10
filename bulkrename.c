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
    char path[PATH_MAX];
    strcpy(path, pathInput);
    Node* iter = ll->head;
    while(iter){
        //TODO while iterating through the linkedlist
        iter = iter->next;
    }
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
            continue;
        }
        //by this point, we should have an non-empty targetDirectoryList.
        //confirm if user wants to bulk-rename this folder.
        char* choose = input("Would you like to bulk-rename this folder? (Y/N)\n>> ");
        if(!strcmp(choose, "y") && !strcmp(choose, "Y")){
            continue;
        }
        //ready to bulk-rename. one by one method.
        bulkRenameList(targetDirectoryList, directory);
        break;
    }
    return 0;
}
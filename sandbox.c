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

int main() {
    printf("%s\n", fileExtension("something.py"));
    printf("%s\n", fileExtension("something.exe"));
    printf("%s\n", fileExtension("something.rtt"));
    renameFile("C:\\CODE\\c\\projects", "somethingElse.py", "hello");
}
#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// header file for string linked lists

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

//initializes an empty linked list
LinkedList* createList(){
    LinkedList* ll = (LinkedList*)malloc(sizeof(LinkedList));
    ll->head = NULL;
    ll->size = 0;
    ll->tail = NULL;
    return ll;
}

//prints a linked list of files
void printList(LinkedList* ll){
    if(ll == NULL){
        printf("Unable to open directory. Did you enter it correctly?\n");
        return;
    }
    if(ll->head == NULL){
        printf("This directory is empty. Nothing to rename here.\n");
        return;
    }
    printf("The directory contains these items:\n");
    Node* iter = ll->head;
    int fileCount = 0;
    int dirCount = 0;
    while(iter){
        if(iter->isFile){
            fileCount++;
        }else{
            dirCount++;
        }
        printf("%s %d: %s\n", iter->isFile ? "FILE" : "SUBDIRECTORY", iter->isFile ? fileCount : dirCount, iter->value);
        iter = iter->next;
    }
    printf("Total %d files and %d subdirectories in this target directory.\n", fileCount, dirCount);
}

//appends a node at the end of a linked list
void append(LinkedList* ll, const char* value, bool isFile){
    //create the node.
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->value = strdup(value);
    newNode->isFile = isFile;
    ll->size++;
    //if linkedlist is empty, head and tail will be the new node
    if(ll->head == NULL){
        ll->head = newNode;
        ll->tail = newNode;
        return;
    }
    ll->tail->next = newNode;
    ll->tail = newNode;
    return;

    /* //linear search for appending is redundant if tail pointer is used.
    Node* iter = ll->head;
    while(iter->next){
        iter = iter->next;
    }
    iter->next = newNode; */
}

//frees the linked list.
void destroyList(LinkedList* ll){
    if(ll == NULL){
        free(ll);
        return;
    }
    LinkedList* list = ll;
    Node* iter = ll->head;
    while(iter){
        Node* temp = iter;
        iter = iter->next;
        free(temp);
    }
    free(list);
    return;
}

#endif
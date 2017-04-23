/*
 *
 * CCPS305 - Assignment 3 
 * trie.h
 * By: Theo Dule, Rahul Gupta and Martin Ristov
 *
 */
#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "american-english-no-accents.txt"
#define MAX_INPUT_SIZE 24
#define BUFFER_SIZE 53 // a-zA-Z and '

typedef struct node {
    char *word;
    int index;
    struct node **key;
    struct node *node;
} Node;

int getCharacterPosition(char);
void inititializeNode(Node *);
int insertInTrie(Node *, char *);
void printTrie(Node *, char *);
void readFile(Node *, const char[]);
void printWords(Node *, Node *, int);

#endif
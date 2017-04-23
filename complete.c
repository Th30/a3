/*
 *
 * CCPS305 - Assignment 3 
 * complete.c
 * By: Theo Dule, Rahul Gupta and Martin Ristov
 *
 */
#include "trie.h"
#include <string.h>
int main() {

    int quitCheck = 0;  // check for ctrl-d input
    char inputWord[(MAX_INPUT_SIZE + 1)]; // user search word
    Node *rootNode = (Node *)malloc(sizeof(Node)); // Create and initialize node
    inititializeNode(rootNode);

    readFile(rootNode, INPUT_FILE); // load the file and fill the tree

    while(1) {
        // Clear buffer for each new run 
        memset(inputWord, 0, sizeof(inputWord));

        printf("Enter String: ");
        fscanf(stdin, "%s", inputWord);

        // Quit on CTRL+D 
        if(inputWord[0] == 0) {
            break;
        }

        printTrie(rootNode, inputWord);
    }

    free(rootNode);

    printf("\r\n");

    return 0;
}

void readFile(Node *theRoot, const char fileName[]) {

    FILE *file = fopen(fileName, "r");
    int wordSize1 = 0;
    char* checkFile = (char*) 1; // XXX: To allow loop to iterate the first run.
    char buff[255], wordTemp[sizeof(buff)]; // storing

    if (file == NULL) {
        printf("%s: File not found!\n", __FUNCTION__);
        exit(0);
    }
    // read and print files
    do {
        checkFile = fgets(buff, sizeof(buff), file);

        if (!strcmp(wordTemp, buff)) // End word was repeating, this fixes that
            break;

        insertInTrie(theRoot, buff);
        strcpy(wordTemp, buff); // store to make sure end word doesn't repeat

    } while (checkFile);
    fclose(file); //close file
}

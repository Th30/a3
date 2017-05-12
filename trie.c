/*
 *
 * CCPS305 - Assignment 3 
 * trie.c
 * By: Theo Dule
 *
 */
#include "trie.h"

void inititializeNode(Node *node) {
    node->key = (Node **)malloc(sizeof(Node *) * BUFFER_SIZE);
}

int insertInTrie(Node *rootNode, char *inputWord) {
    int size = strlen(inputWord); // world length
    int characterPosition = 0;    // start position at index 0

    // traverse through all the characters in the inputWord
    for (int i = 0; i < size; i++) {
        characterPosition = getCharacterPosition(inputWord[i]);

        if (characterPosition >= 0) { // insert on valid inputs only
            if (rootNode->key[characterPosition] == NULL) {
                rootNode->key[characterPosition] = (Node *)malloc(sizeof(Node));
                inititializeNode(rootNode->key[characterPosition]);
            }

            rootNode = rootNode->key[characterPosition];
        }
    }

    rootNode->word = (char *)malloc(sizeof(char) * size);
    strcpy(rootNode->word, inputWord); // copy inputword into node

    return 0;
}

int getCharacterPosition(char incomingCharacter) {

    if (incomingCharacter == '\'') // check for '
        return 0;

    int characterPosition = (int)(incomingCharacter - 'A'); // lowest ASCII reference no. in the provided bounds [A-Za-z] is A => ASCII 65

    if ((characterPosition > (int)('Z' - 'A') && characterPosition < (int)('a' - 'A')) || characterPosition > (int)('z' - 'A'))
        return -1;

    if (characterPosition > (int)('Z' - 'A'))
        characterPosition -= 6; // to account for ASCII 91 - ASCII 96, i.e. '[' - '`' | ASCII 97 < 'a'

    return characterPosition + 1; //position 0 is for '
}
// Print all the matches
void printTrie(Node *rootNode, char *inputWord) {
    Node *autoCompleteList = (Node *)malloc(sizeof(Node) * MAX_INPUT_SIZE);
    Node *temp = rootNode;
    int i = 0;

    while (inputWord[0]){
        i = getCharacterPosition(inputWord[0]);

        // XXX: Skip invalid character positions 
        if (i >= 0) {
            temp = temp->key[i]; 

            // End loop on null key nodes 
            if (temp == NULL)
                break;

            inputWord++;
        }
    }

    i = 0;
    autoCompleteList[i].node = temp;
    autoCompleteList[i].index = 0;

    printWords(temp, autoCompleteList, i);

    free(autoCompleteList);
}

// Continue Traversal - modulating program
void printWords(Node *rootNode, Node *autoCompleteList, int i){
    while (1) { // traverse throughout nodes and print accordingly

        if (autoCompleteList[i].index < BUFFER_SIZE) { 

            // XXX: Make sure the node exists. Otherwise, skip it. 
            if(autoCompleteList[i].node != NULL) {

                rootNode = (autoCompleteList[i].node)->key[autoCompleteList[i].index++];

                if (rootNode) {

                    if (rootNode->word) {
                        printf(" %s", rootNode->word);
                    }

                    autoCompleteList[++i].node = rootNode; // push to the autoCompleteList
                    autoCompleteList[i].index = 0;
                }
            } else {
                i--;
            }
        } else {
            i--;

            if (i < 0)
                break;
        }
    
    }
}
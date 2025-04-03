/*
* Author: Peter Thomsen
* Course: CS1
* Assignment: Assignment 3
* Date: Spring 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_COUNT 100

// Trie node structure
typedef struct TrieNode{

    struct TrieNode* children[ALPHABET_SIZE];

    bool isEndOfWord;
    int frequency;

    int highestFrequency;
    char* commonWord;

} TrieNode;

// Function Prototypes
TrieNode* createNode();
void insertWord(TrieNode* root, const char* word, int frequency);
char* completeWord(TrieNode* root, const char* prefix);

void readCommands(TrieNode* head);


int main(int argc, char** argv){

    // Create Root Node
    TrieNode* root = createNode();

    readCommands(root);
}

TrieNode* createNode(){
    TrieNode* newNode = (TrieNode*) malloc(sizeof(TrieNode));

    newNode->isEndOfWord = false;
    newNode->frequency = 0;
    newNode->highestFrequency = 0;

    newNode->commonWord = (char*) malloc(sizeof(char) * MAX_WORD_COUNT);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

void insertWord(TrieNode* root, const char* word, int frequency){
    TrieNode* currentNode = root;
    
    // Goes through each character of the word, updating data and creating Trie nodes when needed
    for(int x = 0; word[x] != '\0'; x++){

        // Converts the character of the letter to an int to be used by the array
        int index = tolower(word[x]) - 'a';

        // Creates a new node if there isn't one already
        if(currentNode->children[index] == NULL){
            currentNode->children[index] = createNode();
        }

        // Moves currentNode to the next node in the trie
        currentNode = currentNode->children[index];

        // Updates data depending on the frequency of the inputted word
        if(currentNode->highestFrequency < frequency){
            currentNode->highestFrequency = frequency;
            strcpy(currentNode->commonWord, word);
        }
    }

    // Assigns variables at the end of the word
    currentNode->isEndOfWord = true;
    currentNode->frequency = frequency;
}

char* completeWord(TrieNode* root, const char* prefix){
    TrieNode* currentNode = root;

    for(int x = 0; prefix[x] != '\0'; x++){

        // Converts the character of the letter to an int to be used by the array
        int index = tolower(prefix[x]) - 'a';

        // Returns an error if the Trie doesn't contain the prefix
        if(currentNode->children[index] == NULL){
            printf("UNKNOWN WORD\n");
            return "unkown word";
        }

        // Moves currentNode to the next node in the trie
        currentNode = currentNode->children[index];
    }

    // Returns the most likely word from the prefix
    return currentNode->commonWord;
}

void readCommands(TrieNode* root){

    // Gets the first character in the input
    int numOfCommands;
    scanf("%d", &numOfCommands);

    // Does a number of commands equal to the first number in the file
    for(int x = 0; x < numOfCommands; x++){

        // Create temporary variables to place from scanf
        char* inputWord = (char*) malloc(sizeof(char) * MAX_WORD_COUNT);
        int inputFrequency;

        getchar(); // Ignore the next newline or space character

        // Gets the first number in the line to determine which command to execute
        switch(getchar()){
            case '1':
            scanf("%s %d", inputWord, &inputFrequency);
            // Inserts the word into the Trie
            insertWord(root, inputWord, inputFrequency);
            break;
            
            case '2':
            scanf("%s", inputWord);
            // Prints the guessed word
            printf("%s\n", completeWord(root, inputWord));
            break;
        }

        // Frees inputWord after use
        free(inputWord);
        printf("X = %d\n", x);
    }
}
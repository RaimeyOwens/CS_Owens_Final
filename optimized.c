//OPTIMIZED VERSION OF THE WORD COUNT PROGRAM 

//Header files and definitions for the baseline word count program
#include <stdio.h> //Gives you input/output functions like printf, fopen, fgets, etc.
#include <string.h> //String functions like strcmp, strcpy, etc.
#include <ctype.h> //Character handling functions like tolower.
#include <time.h> //For finding performance speed
#include <stdlib.h> //For dynamic memory allocation (malloc, free)

#define TABLE_SIZE 10000 //Size of the hash table
#define MAX_WORD_LEN 100 //Max length of a single word
#define MAX_NODES 100000 //Max number of nodes in the memory pool


typedef struct Node {
    char word[MAX_WORD_LEN];
    int count;
    struct Node *next;
} Node;

Node *hash_table[TABLE_SIZE];

// heap-based memory pool
Node *nodes_pool = NULL;
int pool_index = 0;

int word_count = 0;

// Initialize hash table
void init_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

unsigned int hash(const char *str) { //Simple hash function 
    unsigned int h = 0;
    while (*str) { //Hashing the string by iterating through each character, converting to lowercase, and combining it into a hash value
        h = (h * 31) + tolower(*str++);
    }
    return h % TABLE_SIZE;
}

Node* new_node(const char *word) {
    // safety check
    if (pool_index >= MAX_NODES) {
        printf("Error: Memory pool exhausted\n");
        exit(1);
    }


    Node *n = &nodes_pool[pool_index++];
    strcpy(n->word, word);
    n->count = 1;
    n->next = NULL;
    return n;
}

void add_word(const char *word) {
    unsigned int index = hash(word);

    Node *current = hash_table[index];

    // search only within bucket (much smaller than full list)
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }

    // not found → insert new node
    Node *n = new_node(word);
    n->next = hash_table[index];
    hash_table[index] = n;

    word_count++;
}
//Like basleine, but we convert to lowercase in-place to save memory and time
void to_lowercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}
//Process text line by line, tokenizing and adding words to the hash table
void process_text(char *text) {
    char *token = strtok(text, " \t\n\r,.!?;:\"()[]{}<>");

    while (token != NULL) { //Tokenize the input text using delimiters (space, punctuation, etc.)
        to_lowercase(token);
        add_word(token);
        token = strtok(NULL, " \t\n\r,.!?;:\"()[]{}<>");
    }
}
//Main function to read input, process text, and print results
int main() {
    char input[5000]; //Buffer to hold input lines

    // allocate memory pool (only once)
    nodes_pool = malloc(sizeof(Node) * MAX_NODES);
    if (nodes_pool == NULL) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }

    init_table();

    printf("Enter text (press Ctrl+D when done):\n");

    clock_t start = clock(); //Start timing the execution

    while (fgets(input, sizeof(input), stdin)) {
        process_text(input);
    }

    clock_t end = clock(); //End timing the execution

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC; //Calculate the time taken for execution

    printf("\nWord Frequencies (Hash Table Version):\n");

    for (int i = 0; i < TABLE_SIZE; i++) { //Iterate through the hash table and print each word and its count
        Node *current = hash_table[i];
        while (current != NULL) {
            printf("%s: %d\n", current->word, current->count);
            current = current->next;
        }
    }

    printf("\nTotal unique words: %d\n", word_count);
    printf("Execution time: %f seconds\n", time_taken);

    // free memory pool 
    free(nodes_pool);

    return 0;
}
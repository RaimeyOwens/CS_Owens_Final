//OPTIMIZED VERSION OF THE WORD COUNT PROGRAM 

//Header files and definitions for the baseline word count program
#include <stdio.h> //Gives you input/output functions like printf, fopen, fgets, etc.
#include <string.h> //String functions like strcmp, strcpy, etc.
#include <ctype.h> //Character handling functions like tolower.
#include <time.h> //For finding performance speed

#define TABLE_SIZE 10000 //Size of the hash table
#define MAX_WORD_LEN 100 //Max length of a single word
#define MAX_NODES 100000 //Max number of nodes in the memory pool


typedef struct Node {
    char word[MAX_WORD_LEN];
    int count;
    struct Node *next;
} Node;

Node *hash_table[TABLE_SIZE];

// memory pool (avoids malloc = faster)
Node nodes_pool[MAX_NODES];
int pool_index = 0;

int word_count = 0;

unsigned int hash(const char *str) {
    unsigned int h = 0;
    while (*str) {
        h = (h * 31) + tolower(*str++);
    }
    return h % TABLE_SIZE;
}

Node* new_node(const char *word) {
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

void to_lowercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

void process_text(char *text) {
    char *token = strtok(text, " \t\n\r,.!?;:\"()[]{}<>");

    while (token != NULL) {
        to_lowercase(token);
        add_word(token);
        token = strtok(NULL, " \t\n\r,.!?;:\"()[]{}<>");
    }
}

int main() {
    char input[5000];

    printf("Enter text (press Ctrl+D when done):\n");

    clock_t start = clock();

    while (fgets(input, sizeof(input), stdin)) {
        process_text(input);
    }

    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nWord Frequencies (Hash Table Version):\n");

    // print results from hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = hash_table[i];
        while (current != NULL) {
            printf("%s: %d\n", current->word, current->count);
            current = current->next;
        }
    }

    printf("\nTotal unique words: %d\n", word_count);
    printf("Execution time: %f seconds\n", time_taken);

    return 0;
}
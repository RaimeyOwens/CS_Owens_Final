//Header files and definitions for the baseline word count program
#include <stdio.h> //Gives you input/output functions like printf, fopen, fgets, etc.
#include <stdlib.h> //General utilities 
#include <string.h> //String functions like strcmp, strcpy, etc.
#include <ctype.h> //Character handling functions like tolower.

#define MAX_WORDS 1000 //Max number of unique words we can store 
#define MAX_WORD_LEN 100 //Max length of a single word


typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

WordEntry word_list[MAX_WORDS];
int word_count = 0;

void to_lowercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

// Add or update word
void add_word(const char *word) {
    // Linear search
    for (int i = 0; i < word_count; i++) {
        if (strcmp(word_list[i].word, word) == 0) {
            word_list[i].count++;
            return;
        }
    }

    // Add new word
    if (word_count < MAX_WORDS) {
        strcpy(word_list[word_count].word, word);
        word_list[word_count].count = 1;
        word_count++;
    }
}
// Process a line of text
void process_line(char *line) {
    char *token = strtok(line, " \t\n\r,.!?;:\"()[]{}<>");

    while (token != NULL) {
        to_lowercase(token);
        add_word(token);
        token = strtok(NULL, " \t\n\r,.!?;:\"()[]{}<>");
    }
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file)) {
        process_line(buffer);
    }

    fclose(file);

    // Print results
    for (int i = 0; i < word_count; i++) {
        printf("%s: %d\n", word_list[i].word, word_list[i].count);
    }

    printf("\nTotal unique words: %d\n", word_count);

    return 0;
}

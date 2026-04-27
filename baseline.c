//Header files and definitions for the baseline word count program
#include <stdio.h> //Gives you input/output functions like printf, fopen, fgets, etc.
#include <string.h> //String functions like strcmp, strcpy, etc.
#include <ctype.h> //Character handling functions like tolower.
#include <time.h> //For finding performance speed

#define MAX_WORDS 1000 //Max number of unique words we can store 
#define MAX_WORD_LEN 100 //Max length of a single word


typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

WordEntry word_list[MAX_WORDS];
int word_count = 0;

// Convert word to lowercase
void to_lowercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

// Add or update word 
//linear search)
void add_word(const char *word) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(word_list[i].word, word) == 0) {
            word_list[i].count++;
            return;
        }
    }

    if (word_count < MAX_WORDS) {
        strcpy(word_list[word_count].word, word);
        word_list[word_count].count = 1;
        word_count++;
    }
}

// Process input text
void process_text(char *text) {
    char *token = strtok(text, " \t\n\r,.!?;:\"()[]{}<>"); //strtok splits the text into tokens based on the specified delimiters (spaces, punctuation, etc.)

    while (token != NULL) {
        to_lowercase(token);
        add_word(token);
        token = strtok(NULL, " \t\n\r,.!?;:\"()[]{}<>");
    }
}

int main() {
    char input[5000];

    printf("Enter text (press Ctrl+D when done):\n");
    clock_t start = clock();   // START TIMER
    //allows the user to input multiple lines of text. The fgets function reads a line of input from stdin and stores it in the input buffer. The loop continues until there are no more lines to read.
    while (fgets(input, sizeof(input), stdin)) {
    process_text(input);
}
    clock_t end = clock();     // END TIMER

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nWord Frequencies:\n");
    for (int i = 0; i < word_count; i++) {
        printf("%s: %d\n", word_list[i].word, word_list[i].count);
    }

    printf("\nTotal unique words: %d\n", word_count);
    printf("Execution time: %f seconds\n", time_taken);

    return 0;
}


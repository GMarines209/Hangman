#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 256

// Function declarations
int menu();
char *choose_Word();
char *setup(char *wordLen);
void correct_Guess(char *chosen_word, char *wordLen, char guess);

char full_Hangman[][50] = {
    {"   r----------      \n"}, // layer 0
    {"   |         |      \n"}, // layer 1
    {"   |         O      \n"}, // Head layer 2
    {"   |        /|      \n"}, // Arm 1 layer 3
    {"   |        /|\\    \n"}, // Arm 1 & 2 layer 4
    {"   |          \\    \n"}, // Leg 1 layer 5
    {"   |        / \\    \n"}, // Leg 1 & 2 layer 6
    {" __|__              \n"}  // toes
};

char base_Hangman[][50] = {
{"   r----------    \n"}, 
{"   |         |    \n"},                           
{"   |              \n"}, 
{"   |              \n"},                          
{"   |              \n"}, 
{" __|__            \n"} };

int menu() {
  int choice;
  printf("\nWelcome to hangman!\n");
  printf("Choose your gamemode: \n");
  printf("1. Easy\n");
  printf("2. Medium\n");
  printf("3. Hard\n");
  printf("4. Quit\n");
  scanf("%d", &choice);
  return choice;
}

char *setup(char *wordLen) {
  // Chooses the starting word
  char *chosen_Word = choose_Word();
  printf("The chosen word is: %s", chosen_Word);

  int len = strlen(chosen_Word) - 1;

  // Loads the hangman base
  for (int i = 0; i < 6; i++) {
    printf("%s", base_Hangman[i]);
  }

  printf("\n\n");

  // Initialize the wordLen array with underscores
  for (int i = 0; i < len; i++) {
    wordLen[i] = '_';
  }
  wordLen[len] = '\0'; // Null-terminate the string

  // Print the initial underscores
  printf("%s", wordLen);

  return chosen_Word; // Return the chosen word
}

char *choose_Word() {
  FILE *file;
  file = fopen("words.txt", "r");

  if (file == NULL) {
    printf("Error opening file!");
    exit(1); // Exit if file cant open
  }

  int wordCount = 0;
  char buffer[256];

  // Count the number of words in file
  while (fgets(buffer, sizeof(buffer), file)) {
    wordCount++;
  }

  rewind(file);

  int current_Line = 0;
  int rand_Word_Index = rand() % wordCount;

  char *chosenWord = malloc(sizeof(buffer));

  // get random word from the file
  while (fgets(buffer, sizeof(buffer), file)) {
    if (current_Line == rand_Word_Index) {
      strcpy(chosenWord, buffer);
    }
    current_Line++;
  }

  fclose(file);
  return chosenWord;
}

void correct_Guess(char *chosen_word, char *wordLen, char guess) {
  for (int i = 0; i < strlen(chosen_word) - 1; i++) {
    if (chosen_word[i] == guess) {
      wordLen[i] = guess; // Update guessed letter in the word lines
    }
  }

  // Print the updated word lines
  printf("\nCurrent word: %s\n", wordLen);
}

int main() {
  srand(time(0));

  int guessed = 0; // if guessed = 1, word has been guessed...end game
  char guess;
  char *guess_ptr;
  char *chosen_word;
  char wordLen[MAX_LEN]; // Array to store the word spaces

  int option = menu();
  while (option != 4) {
    switch (option) {
    case 1: {
      chosen_word = setup(wordLen); // Setup the game and get the chosen word

      // While the word hasn't been guessed...
      while (guessed == 0) {
        printf("\n\nChoose a letter: ");
        scanf(" %c", &guess);

        // Check if the guess is in the word
        guess_ptr = strchr(chosen_word, guess);

        // If the guessed letter is in the word...
        if (guess_ptr != NULL) {
          correct_Guess(chosen_word, wordLen, guess);

          // Check if the word has been fully guessed
          if (strcmp(chosen_word, wordLen) == 0) {
            printf("Congratulations! You've guessed the word!\n");
            guessed = 1; // End the game loop
          }
        }
      }

      break;
    }

    case 2:
    case 3:
      for (int i = 0; i < 6; i++) {
        printf("%s", base_Hangman[i]);
      }
      break;

    case 4:
      printf("Goodbye!");
      break;

    default:
      break;
    }

    option = menu();
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 256

// Function declarations
int menu();
char *setup(char *wordLen);
char *choose_Word();
void correct_Guess(char *chosen_word, char *wordLen, char guess);
void incorrect_Guess(char guess, int incorrect_Guess);

char full_Hangman[][50] = {
{"   r----------      \n"}, // layer 0
{"   |         |      \n"}, // layer 1
{"   |         O      \n"}, // Head layer 2
//===========================================
{"   |         |      \n"}, //  torso layer 3
{"   |        /|      \n"}, //  Arm 1 layer 4
{"   |        /|\\    \n"}, //  Arm 1 & 2 layer 5
//================================================
{"   |          \\    \n"}, //  Leg 1 layer 6
{"   |        / \\    \n"}, //  Leg 1 & 2 layer 7
//================================================
{" __|__              \n"}  // toes layer 8

};

char base_Hangman[][50] = {
{"   r----------    \n"},  //Layer 0
{"   |         |    \n"},  //Layer 1                 
{"   |              \n"},  //Layer 2
{"   |              \n"},  //Layer 3                
{"   |              \n"},  //Layer 4
{" __|__            \n"}}; //Layer 5

char blank_Hangman[][50] = {
{"   r----------    \n"},  //Layer 0
{"   |         |    \n"},  //Layer 1                 
{"   |              \n"},  //Layer 2
{"   |              \n"},  //Layer 3                
{"   |              \n"},  //Layer 4
{" __|__            \n"}}; //Layer 5

int menu() {
  int choice;
  printf("\nWelcome to hangman!\n");
  printf("What do you want to do? \n");
  printf("1. Play\n");
  printf("2. Quit\n");
  scanf("%d", &choice);
  while (getchar() != '\n');
  while (choice !=1 && choice != 2)
  {
    printf("Invalid choice. Try again:");
    scanf("%d", &choice);
    while (getchar() != '\n');
  }
  
  return choice;
}

char *setup(char *wordLen) {

  for(int i = 0; i < 6; i++){
    strcpy(base_Hangman[i],blank_Hangman[i]);
  }


  // Chooses the starting word
  char *chosen_Word = choose_Word();
  // printf("The chosen word is: %s\n", chosen_Word); // Only for testing :)

  int len = strlen(chosen_Word);

  // Loads the hangman base
  for (int i = 0; i < 6; i++) {
    printf("%s", base_Hangman[i]);
  }

  printf("\n\n");

  // Initialize the wordLen array with underscores
  for (int i = 0; i < len; i++) {
    wordLen[i] = '_';
  }
  wordLen[len] = '\0';

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
      chosenWord[strcspn(chosenWord, "\n")] = '\0';  // Remove newline character
    }

    current_Line++;
  }

  fclose(file);
  return chosenWord;
}

void correct_Guess(char *chosen_word, char *wordLen, char guess) {

  int updated = 0;

  for (int i = 0; i < strlen(chosen_word); i++) {

    if (chosen_word[i] == guess && wordLen[i] != guess) {
      wordLen[i] = guess; // Update guessed letter in the word lines
      updated = 1;
    }

  }
  // If the word was updated, print the updated word lines
    if (updated) {
        printf("\nCurrent word: %s\n", wordLen);
    } else {
        printf("You already guessed that letter correctly!\n");
    }

}

void incorrect_Guess(char guess, int inc_Guess){
  

  if (inc_Guess >= 1) strcpy(base_Hangman[2], full_Hangman[2]);  // Head
  if (inc_Guess >= 2) strcpy(base_Hangman[3], full_Hangman[3]);  // torso
  if (inc_Guess >= 3) strcpy(base_Hangman[3], full_Hangman[4]);  // Arm 1
  if (inc_Guess >= 4) strcpy(base_Hangman[3], full_Hangman[5]);  // Arm 1 & 2
  if (inc_Guess >= 5) strcpy(base_Hangman[4], full_Hangman[6]);  // Leg 1
  if (inc_Guess >= 6) strcpy(base_Hangman[4], full_Hangman[7]);  // Leg 1 & 2

  for (int i = 0; i < 6; i++) {
    printf("%s", base_Hangman[i]);
  }

}

int main() {

  srand(time(0));

    int guessed = 0; // if guessed = 1, word has been guessed...end game
    int dead = 0; // if hangman is alive game keeps going
    char guess; //stores player guess
    char *guess_ptr; //ptr stores strchr result
    char *chosen_word;
    char wordLen[MAX_LEN]; // Array to store the word spaces
    int inc_Guess = 0;
    int corr_Guess = 0;
    char prev_Guess[MAX_LEN];
    int count;



  int option = menu();
  while (option != 2) {

    switch (option) {

    case 1: {
      inc_Guess = 0;
      corr_Guess = 0;
      guessed = 0;
      dead = 0;
      count = 0;

      prev_Guess[0] = '\0';

      chosen_word = setup(wordLen); // Setup the game and get the chosen word

      // While the word hasn't been guessed...
      while (guessed != 1 ||  dead != 1) {

        printf("\n\nChoose a letter: ");
        scanf(" %c", &guess);

        // Check if the guess has been made 
        if (strchr(prev_Guess, guess) != NULL) {
          printf("You've already guessed '%c'. Try a different letter.\n", guess);
          continue;
        } 

        prev_Guess[count] = guess;
        prev_Guess[count + 1] = '\0'; // Null-terminate string
        count++;

        // Check if the guess is in the word
        guess_ptr = strchr(chosen_word, guess);

        if(guess_ptr == NULL){

          ++inc_Guess;
          incorrect_Guess(guess,inc_Guess);

          if(inc_Guess >=6 ){

            printf("The word was: %s\nGame Over!\n",chosen_word);
            dead = 1;
            break;

          }

        }// end of if incorrect
        else if(guess_ptr != NULL){ // If the guessed letter is in the word...

          correct_Guess(chosen_word, wordLen, guess);

          if (strcmp(chosen_word, wordLen) == 0) {
            printf("\nCongratulations! The word was %s", chosen_word);
            guessed = 1;
            break;

          }

        }

        // printf("player guesses are: %s", prev_Guess); // Only for testing :)

      }
      break;



    }
    case 2:
      printf("Goodbye!");
      break;

    default:
      printf("Incorrect entry. Try again");
      break;
    }



    option = menu();
  }

  return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// int build_Base();
int menu();
int main();
char *choose_Word();
char word_Guess(char word[], char *ptr, char guess);


char full_Hangman[][50] = {
    {"   r----------      \n"}, //layer 0
    {"   |         |      \n"}, // layer 1
    {"   |         O      \n"}, // Head layer 2
    {"   |        /|      \n"}, // Arm 1 layer 3
    {"   |        /|\\    \n"}, // Arm 1 &2 layer 4
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
    {" __|__            \n"}
};


int menu(){

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

char word_Guess(char word[], char *ptr, char guess){

    int firstTime = 1;
    int word_pos = ptr-word+1;


   int len = strlen(word) -1;
   char wordLen[256];

   printf("\n");


        if(firstTime == 1){
            
            for(int i = 0; i < len; i++){

                wordLen[i] =  '_';
                printf("%c",wordLen[i]);

            }

            
            firstTime = 0;
        }
        else{

            for (int i = 0; i < len; i++)
            {
                wordLen[word_pos - 1] = guess;
                printf("%c",wordLen[i]);
            }
        }


}


char *choose_Word(){
    FILE * file;
    file = fopen("words.txt", "r");

    if(file == NULL)
    printf("Error opeining file!");

    int wordCount = 0;
    char buffer[256];
    

    while(fgets(buffer,sizeof(buffer), file)){
        wordCount++;
    }

    rewind(file);
    
    int current_Line = 0;
    int rand_Word_Index = rand() % wordCount;

    // printf("WORD INDEX IS: %d", rand_Word_Index);
    char *chosenWord = malloc( (sizeof(buffer)));
    
    while(fgets(buffer,sizeof(buffer), file)){

        if(current_Line == rand_Word_Index){
            strcpy(chosenWord,buffer);
        }
        current_Line++;
    }
    


    fclose(file);

    return chosenWord;
}


int main(){

    srand(time(0));

    char guess;
    int guessed = 0;
    char *ptr;

    int option = menu();
    while(option != 4){

        switch (option){
            case 1:

           
            // Declare the starting word
                char *word = choose_Word();
                printf("Word is %s\n", word);


            //starting by loading the base 
                for(int i = 0; i < 6; i++){
                    printf("%s", base_Hangman[i]);
                }
                
                word_Guess(word,ptr,guess);//loads the length of word for guesses to fill

                

                //while the word hasnt been guessed...
                while(guessed == 0){

                    printf("\n\nChoose a letter: ");
                    scanf(" %c", &guess);

                    //check if guess in word
                    ptr = strchr(word,guess);


                    if(ptr == NULL){
                        
                    }

                    // if guess in word.. 
                    while (ptr != NULL){

                        printf ("found at %d\n",ptr-word+1);
                        ptr = strchr(ptr+1,guess);
                        word_Guess(word,ptr,guess);
                    }

                    


                }
                

                



        
                break;

            case 2:

                for(int i = 0; i < 6; i++){
                    printf("%s", base_Hangman[i]);
                }
                break;

            case 3:

                for(int i = 0; i < 6; i++){
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
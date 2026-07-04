#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


const char* choose_word() //Function for random word generating
{
    const char* words[]={"messi", "mafia", "statistics", "ronaldo", "penalty", "argentina"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int random_index = rand() % word_count;
    return words[random_index];
}

const char* giving_hint(const char* word) //Function to give hints
{
    if (strcmp(word, "messi") == 0)
    return "Literally the GOAT.";
    if (strcmp(word, "mafia") == 0)
    return "An organized crime syndicate.";
    if (strcmp(word, "statistics") == 0)
    return "The math of collecting and analyzing data.";
    if (strcmp(word, "ronaldo") == 0)
    return "Famous Portuguese football player.";
    if (strcmp(word, "penalty") == 0)
    return "A free shot at the goal in football.";
    if (strcmp(word, "argentina") == 0)
    return "The country with the GOAT.";

    return "No hint available.";
}

void print_hangman(int wrong_guesses)
{
    printf("\n");
    if (wrong_guesses == 0) {
        printf("  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n");
    } else if (wrong_guesses == 1) {
        printf("  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n");
    } else if (wrong_guesses == 2) {
        printf("  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n");
    } else if (wrong_guesses == 3) {
        printf("  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n");
    } else if (wrong_guesses == 4) {
        printf("  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n");
    } else if (wrong_guesses == 5) {
        printf("  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n");
    } else if (wrong_guesses == 6) {
        printf("  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n");
    }
}

char* word_display(const char* word, const char* guesses) //Function to display word with blanks and guessed characters
{
    static char display[100];
    int word_siz = strlen(word);
    int index = 0;

    for (int i = 0; i < word_siz; i++)
    {
        if (strchr(guesses, word[i]) != NULL)
        {
            display[index++] = word[i];
        }
        else
        {
            display[index++] = '_';
        }
        display[index++] = ' ';
    }
    display[index - 1] = '\0'; //terminating the string
    return display;
}

int player_cooked(int turns, const char* word, const char* guesses) //Function to check if the player has lost the game
{
    char* display_word = word_display(word, guesses);
    if (turns == 0 && strchr(display_word, '_') != NULL) //check if there is turns left
    {
        return 1; //Player lost
    }
    return 0; //Player won
}

int main ()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //for colors
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    srand(time(0)); //random time generator
    char name[150];

    printf("\033[1;32m+----------------------------------------------------------------------+\n");
    printf("\033[1;32m|\033[1;36m  _______                                                             \033[1;32m|\n");
    printf("\033[1;32m|\033[1;36m |/      |        \033[1;36m _   _    _    _   _  ____ __  __    _    _   _     \033[1;32m|\n");
    printf("\033[1;32m|\033[1;36m |      \033[1;33m(_)\033[1;36m       \033[1;36m| | | |  / \\  | \\ | |/ ___|  \\/  |  / \\  | \\ | |    \033[1;32m|\n");
    printf("\033[1;32m|\033[1;36m |      \033[1;33m\\|/\033[1;36m       \033[1;36m| |_| | / _ \\ |  \\| | |  _| |\\/| | / _ \\ |  \\| |    \033[1;32m|\n");
    printf("\033[1;32m|\033[1;36m |       \033[1;33m|\033[1;36m        \033[1;36m|  _  |/ ___ \\| |\\  | |_| | |  | |/ ___ \\| |\\  |    \033[1;32m|\n");
    printf("\033[1;32m|\033[1;36m |      \033[1;33m/ \\\033[1;36m       \033[1;36m|_| |_/_/   \\_\\_| \\_|\\____|_|  |_/_/   \\_\\_| \\_|    \033[1;32m|\n");
    printf("\033[1;32m|\033[1;36m |                                                                    \033[1;32m|\n");
    printf("\033[1;32m|\033[1;36m_|___                                                                 \033[1;32m|\n");
    printf("\033[1;32m+----------------------------------------------------------------------+\033[0m\n\n");

    printf("\nGive us your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; //trick to remove the hidden enter key press
    printf("Hello, %s, time to play the game\n", name);

    printf("\n----------------------------------------\n");
    printf("          CHOOSE GAME MODE              \n");
    printf("----------------------------------------\n");
    printf("1. Host Mode (Type your own word & hint)\n");
    printf("2. Player Mode (Play with pre-generated words)\n");
    printf("Choose an option (1 or 2): ");

    int choice;
    scanf("%d", &choice);

    while (getchar() != '\n'); ////trick to remove the hidden enter key press

    char custom_word[100];
    char custom_hint[250];
    const char* active_word;
    const char* active_hint;

    if (choice == 1)
    {
        printf("\n--- HOST MODE ---\n");
        printf("Host, enter the secret word: ");
        fgets(custom_word, sizeof(custom_word), stdin);
        custom_word[strcspn(custom_word, "\n")] = '\0';

        printf("Host, enter a hint for the guesser: ");
        fgets(custom_hint, sizeof(custom_hint), stdin);
        custom_hint[strcspn(custom_hint, "\n")] = '\0';

        active_word = custom_word;
        active_hint = custom_hint;

        for (int i = 0; i < 50; i++) {
            printf("\n");
        }
        printf("Screen is ready! Bring in the player.\n");
    }
    else
    {
        active_word = choose_word();
        active_hint = giving_hint(active_word);
    }

    int turns = 6;
    char guesses[100] = "";
    int hint_used = 0;

    while(turns > 0)
    {
        int wrong_guesses_made = 6 - turns;
        print_hangman(wrong_guesses_made);
        char* display = word_display(active_word, guesses);
        printf("You have %d guesses remaining.\n", turns);
        printf("%s\n", display);

        if (strchr(display, '_') == NULL)
        {
            printf("\n====================================\n");
            printf("              YOU WON              \n");
            printf("====================================\n");
            break;
        }

        printf("\nGuess a character (or type '?' for a hint): ");
        char guess;
        scanf(" %c", &guess);

        if (guess == '?')
        {
            if (hint_used == 0)
            {
                printf("\n*** HINT: %s ***\n\n", active_hint);
                hint_used = 1; //so player can use the hint only 1 time
            }
            else
            {
                printf("\nYou have already used your hint for this round!\n\n");
            }
            continue;
        }

        if (strchr(guesses, guess) != NULL) //Check if the character is repeated
            {
                printf("\nYou have already tried this letter\n");
                continue;
            }

       int len = strlen(guesses);
       guesses[len] = guess;
       guesses[len + 1] = '\0';

        if (strchr(active_word, guess) == NULL) //reducing turns
        {
            printf("\nWrong guess, try again!\n");
            turns--;
        }

        if (player_cooked(turns, active_word, guesses)) //check if the player has won or lost
        {
            print_hangman(6);
            printf("\n=====================================\n");
            printf("  YOU LOSE! The word was: %s\n", active_word);
            printf("=====================================\n");
            break;
        }
        }

    return 0;

}

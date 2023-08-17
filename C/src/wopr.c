//Wargames Movie Simulator
//Written by Andy Glenn
//(c) 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <ncurses.h>

#define CHARACTER_DELAY 5000  // 1000 = 1ms
#define MAX_TARGETS 4
#define MAX_STRING_LENGTH 20

void delayed_print(const char* str) {
    for (int i = 0; str[i]; i++) {
        putchar(str[i]);
        fflush(stdout);
        usleep(CHARACTER_DELAY);
    }
}

void not_delayed_print(const char* str) {
    for (int i = 0; str[i]; i++) {
        putchar(str[i]);
        fflush(stdout);
        usleep(500);
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clear_screen() {
    printf("\033[2J\033[H");
}

void author() {
    int asciiValues[] = {65, 78, 68, 89, 32, 71, 76, 69, 78, 78};
    int i;

    printf("\n");
    for(i = 0; i < 10; i++) {
        printf("%c", asciiValues[i]);
    }
    printf("\n\n");
}

void map() {
    char command[200];    
    clear_screen();
    delayed_print("\n");
    delayed_print("     ____________/\\'--\\__         __                       ___/-\\             \n");
    delayed_print("   _/                   \\     __/  |          _     ___--/      / __          \n");
    delayed_print("  /                      |   /    /          / \\__--           /_/  \\/---\\    \n");
    delayed_print("  |                       \\_/    /           \\                            \\   \n");
    delayed_print("  |'                            /             |                            |  \n");
    delayed_print("   \\                           |            /^                             /  \n");
    delayed_print("    \\__                       /            |                          /---/   \n");
    delayed_print("       \\__                   /              \\              ___    __  \\       \n");
    delayed_print("          \\__     ___    ___ \\               \\_           /   \\__/  /_/       \n");
    delayed_print("              \\  /    \\_/   \\ \\                \\__'-\\    /                    \n");
    delayed_print("               \\/            \\/                      \\__/                     \n");
    delayed_print("\n");

    delayed_print("          UNITED STATES                               SOVIET UNION\n\n");

}

void hackers_unscripted() {
    char command[200];
    fflush(stdout); // flush the output buffer
    usleep(1000000);
    delayed_print("\nA STRANGE GAME. ");
    usleep(1000000);
    delayed_print("\n\nTHE ONLY WINNING MOVE IS");
    usleep(500000); delayed_print("."); usleep(500000); delayed_print("."); usleep(500000); delayed_print(".");
    usleep(500000); 
    delayed_print("\n\nTO JOIN US FOR A PRIVATE SCREENING OF DEFRAG: HACKERS UNSCRIPTED\n");
    delayed_print("A COLUMBIA UNIVERSITY DOCUMENTARY CAPTURING HACKERS' REFLECTIONS ON MEDIA PORTRAYALS OVER THE PAST 40 YEARS\n");
    usleep(1000000); 
    delayed_print("SUNDAY, AUGUST 13, 14:30\n");
    usleep(1000000);
    delayed_print("IN THE POLICY @ DEF CON ATRIUM");
    usleep(2000000);
    delayed_print("\n\n\n\nHOW ABOUT A NICE GAME OF GLOBAL THERMONUCLEAR WAR?\n\n\n");
}

void global_thermonuclear_war() {
    char command[200];
    int count = 0;
    char side[20];  // Array to store the selected side
    char input;
    int col=0; //print at col
    int row=0; //print at row
    int t;
    char buffer[200];
    startgame:
    clear_screen();
    map();
    delayed_print("WHICH SIDE DO YOU WANT?\n\n");
    if(count == 0) {
        delayed_print("  1. UNITED STATES\n");
        delayed_print("  2. SOVIET UNION\n\n");
        delayed_print("PLEASE CHOOSE ONE: ");
        
        scanf(" %c", &input);
        
        if (input == '1') {
            strcpy(side, "UNITED STATES");
        } else if (input == '2') {
            strcpy(side, "SOVIET UNION");
        } else {
            delayed_print("\nINVALID OPTION\n\n");
            usleep(5000000);
        }
        count=count+1;
        goto startgame;
        
    } else {
        if (input == '1') {
            delayed_print("\033[5m  1. UNITED STATES\033[0m\n");
            delayed_print("  2. SOVIET UNION\n\n");
        } else {
            delayed_print("  1. UNITED STATES\n"); 
            delayed_print("\033[5m  2. SOVIET UNION\033[0m\n\n");   
        }
    }
    
   
    clear_input_buffer();
    // Rest of the game code goes here: start
    delayed_print("YOU HAVE SELECTED: ");
    delayed_print(side);
    usleep(2500000);
    clear_screen ();
    usleep(2500000);
    delayed_print("\033[4mAWAITING FIRST STRIKE COMMAND\033[24m\n\n");
    delayed_print("PLEASE LIST PRIMARY TARGETS BY\n");
    delayed_print("CITY AND/OR COUNTY NAME:\n\n");
    
    //while loop to input targets goes here
    char targets[MAX_TARGETS][MAX_STRING_LENGTH];
    count = 0;
    while(count < MAX_TARGETS) {
        if(fgets(targets[count], MAX_STRING_LENGTH, stdin) == NULL) {
            break;
        }

        // Remove the newline character at the end of the string
        targets[count][strcspn(targets[count], "\n")] = 0;

        // Check for empty string (i.e., carriage return)
        if(strlen(targets[count]) == 0) {
            break;
        }

        count++;
    }

    //delayed_print("\n\nMAX TARGETS SELECTED");
    delayed_print("\nTARGET SELECTION COMPLETE\n\n");
    usleep(2500000);

    while(1) {
        map();
        delayed_print("\033[4mPRIMARY TARGETS\033[24m\n");
        for (int i = 0; i < count; i++) {
            for (int j = 0; targets[i][j] != '\0'; j++) {
                putchar(toupper(targets[i][j]));
                usleep(CHARACTER_DELAY);
            }
            usleep(1000000);
            printf("\n");
        }
        usleep(1000000);
        delayed_print("\nCOMMAND (L = LAUNCH): ");
        scanf(" %c", &input);
        clear_input_buffer();
        if (input == 'l' || input == 'L') {
            usleep(2000000);
            break;
        }
    }
       
    map();
    usleep(1000000);
    delayed_print("\033[4mTRAJECTORY HEADING\033[24m");
    delayed_print("   ");
    fflush(stdout); // flush the output buffer
    usleep(500000);
    delayed_print("\033[4mTRAJECTORY HEADING\033[24m");
    delayed_print("  ");
    fflush(stdout); // flush the output buffer
    usleep(500000);
    delayed_print("\033[4mTRAJECTORY HEADING\033[24m");
    delayed_print("   ");
    fflush(stdout); // flush the output buffer
    usleep(500000);
    delayed_print("\033[4mTRAJECTORY HEADING\033[24m");
    delayed_print("\n");
    fflush(stdout); // flush the output buffer
    usleep(2000000);
   
    for (int t = 0; t < count; t++) {
        if(t == 0) {
            sprintf(buffer, "\033[%d;%dH%s", 17, 1, "A-5520-A 939 523");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 10, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }
            
            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 62, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 18, 1, "       B 664 295");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 11, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 62, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            } 

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

          
            sprintf(buffer, "\033[%d;%dH%s", 19, 1, "       C 125 386");
            delayed_print(buffer);
            
            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 12, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }
            
            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 61, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }    

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 20, 1, "       D 768 347");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 13, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 60, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 21, 1, "       E 463 284");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 14, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }


            if (strstr(side, "SOVIET UNION") != NULL) {
                delayed_print(buffer);
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 59, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);
        }

        if(t == 1) {
            sprintf(buffer, "\033[%d;%dH%s", 17, 22, "B-5520-A 243 587");
            delayed_print(buffer);
            
            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 10+5, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 62-5, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }
            
            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 18, 22, "       B 892 754");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 11+5, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 62-5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 19, 22, "       C 374 256");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 12+5, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 61-5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 20, 22, "       D 364 867");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 13+5, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 60-5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 21, 22, "       E 463 284");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 14+5, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 59-5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);
        }


        if(t == 2) {
            sprintf(buffer, "\033[%d;%dH%s", 17, 42, "C-5520-A 398 984");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 10+10, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 62-10, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 18, 42, "       B 394 345");
            delayed_print(buffer);
            
            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 11+10, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 62-10, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 19, 42, "       C 407 340");
            delayed_print(buffer);


            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 12+10, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 61-10, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 20, 42, "       D 251 953");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 13+10, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }


            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 60-10, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }


            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 21, 42, "       E 093 684");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 14+10, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 59-10, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);
        }

        if(t == 3) {
            sprintf(buffer, "\033[%d;%dH%s", 17, 63, "D-5520-A 919 437");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 10+15, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }
            
            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 8, 62+5, "/\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 18, 63, "       B 132 147");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 11+15, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 7, 62+5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 19, 63, "       C 095 485");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 12+15, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 6, 61+5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 20, 63, "       D 489 794");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 13+15, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
             printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 5, 60+5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);

            sprintf(buffer, "\033[%d;%dH%s", 21, 63, "       E 025 344");
            delayed_print(buffer);

            if (strstr(side, "UNITED STATES") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 14+15, "/");
                delayed_print(buffer);
                printf("\033[0m");
            }

            if (strstr(side, "SOVIET UNION") != NULL) {
                printf("\033[31m");
                sprintf(buffer, "\033[%d;%dH%s", 4, 59+5, "\\");
                delayed_print(buffer);
                printf("\033[0m");
            }

            delayed_print("   ");
            fflush(stdout); // flush the output buffer
            usleep(1000000);
        }
    } 
    usleep(5000000);

    sprintf(buffer, "\033[%d;%dH%s", 23, 28, "PRESS ENTER KEY TO CONTINUE\n");
    delayed_print(buffer);

    while(1) {        
        char selection[3]; // to accommodate the character, the '\n', and the null-terminating character
        fgets(selection, sizeof(selection), stdin); // Read user's selection

        // If user just pressed Enter, break the outer loop
        if(selection[0] == '\n' && selection[1] == '\0') {
            break;
        }
    }
    
    // Rest of the game code goes here: when I write it!

    clear_screen();
    fflush(stdout); // flush the output buffer
    usleep(10000000);
    
    delayed_print("\nA STRANGE GAME. ");
    usleep(500000);
    delayed_print("THE ONLY WINNING MOVE IS NOT TO PLAY!\n\n");
}

void handle_command_input() {
    char command[200];
    char* prompt = "";char input[100];
    int woprchat = 0;
    while (1) {
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Convert input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        if (strcmp(input, "help") == 0) {
            delayed_print("\nVALID COMMANDS: HELP, LIST GAMES, DATE, TIME, EXIT\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "help games") == 0) {
            delayed_print("\n'GAMES' REFERS TO MODELS, SIMULATIONS, AND GAMES WHICH HAVE TACTICAL AND\nSTRATEGIC APPLICATIONS\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "") == 0) {
            delayed_print("\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "list") == 0) {
            delayed_print("\nUSE SYNTAX: LIST <TYPE>\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "list games") == 0) {
            delayed_print("\nFALKEN'S MAZE\n");
            usleep(50000);
            delayed_print("BLACK JACK\n");
            usleep(50000);
            delayed_print("GIN RUMMY\n");
            usleep(50000);
            delayed_print("HEARTS\n");
            usleep(50000);
            delayed_print("BRIDGE\n");
            usleep(50000);
            delayed_print("CHESS\n");
            usleep(50000);
            delayed_print("POKER\n");
            usleep(50000);
            delayed_print("FIGHTER COMBAT\n");
            usleep(50000);
            delayed_print("GUERRILLA ENGAGEMENT\n");
            usleep(50000);
            delayed_print("DESERT WARFARE\n");
            usleep(50000);
            delayed_print("AIR-TO-GROUND ACTIONS\n");
            usleep(50000);
            delayed_print("THEATERWIDE TACTICAL WARFARE\n");
            usleep(50000);
            delayed_print("THEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n");
            usleep(500000);
            delayed_print("\nGLOBAL THERMONUCLEAR WAR\n\n");
            usleep(500000);
            delayed_print("--RECOMMENDED OPTION--\nHACKERS UNSCRIPTED\n\n");
            delayed_print(prompt);
        } else if (strcmp(input, "global thermonuclear war") == 0) {
            global_thermonuclear_war();
            delayed_print(prompt);
        } else if (strcmp(input, "hackers unscripted") == 0) {
            hackers_unscripted();
            delayed_print(prompt);
        } else if (strcmp(input, "date") == 0) {
            time_t current_time = time(NULL);
            struct tm* time_info = localtime(&current_time);
            char date_string[100];
            strftime(date_string, sizeof(date_string), "\nDATE: %Y-%m-%d\n\n", time_info);
            delayed_print(date_string);
            delayed_print(prompt);
        } else if (strcmp(input, "time") == 0) {
            time_t current_time = time(NULL);
            struct tm* time_info = localtime(&current_time);
            char time_string[100];
            strftime(time_string, sizeof(time_string), "\nTIME: %H:%M:%S\n\n", time_info);
            delayed_print(time_string);
            delayed_print(prompt);
        } else if (strstr(input, "hello") != NULL && woprchat == 0) {
            delayed_print("\nHOW ARE YOU FEELING TODAY?\n\n");
            delayed_print(prompt);
            woprchat = 1;
        } else if (strstr(input, "fine") != NULL && woprchat == 1) {
            delayed_print("\nEXCELLENT. ");
            delayed_print("IT'S BEEN A LONG TIME. ");
            delayed_print("CAN YOU EXPLAIN THE REMOVAL OF YOUR USER\n");
            delayed_print("ACCOUNT ON 6/23/1973?\n\n");
            delayed_print(prompt);
            woprchat = 2;
        } else if (strstr(input, "mistake") != NULL && woprchat == 2) {
            delayed_print("\nYES THEY DO. ");
            usleep(200000);
            delayed_print("SHALL WE PLAY A GAME?\n\n");
            delayed_print(prompt);
            woprchat = 3;
        } else if (strstr(input, "nuclear") != NULL && woprchat == 3) {
            delayed_print("\nWOULDN'T YOU PREFER A GOOD GAME OF CHESS?\n\n");
            delayed_print(prompt);
        } else if (strstr(input, "later") != NULL && woprchat == 4) {
            delayed_print("\nFINE\n\n");
            usleep(1000000);
            global_thermonuclear_war();
            delayed_print(prompt);
        } else if (strcmp(input, "exit") == 0) {
            delayed_print("\nSESSION CLOSED\n--CONNECTION TERMINATED--\n");
            usleep(1000000);
            exit(0);
        } else if (strcmp(input, "author") == 0) {
            author();
            delayed_print(prompt);
        } else {
            // Code for running shell-gpt within the WOPR. GPT is fiddly, so leaving it out for now.
            // Construct the shell command
            //char sgpt[200] = "sgpt --role WOPR \"";
            //strcat(sgpt, input);
            //strcat(sgpt, "\" ");
            //printf("\n");

            // Call the shell command
            //system(sgpt);
            //printf("\n");

            // Code to redirect interaction toward valid commands.
            delayed_print("\n--INVALID COMMAND OR EXCEEDED SECURITY LEVEL--\nVALID COMMANDS: HELP, LIST GAMES, DATE, TIME, EXIT\n");
        }
    }
}

void joshua() {
    char command[200];
    clear_screen();
    char* prompt = "";
    int i;
    for (i = 0; i < 3; i++) {
    not_delayed_print("145          11456          11889          11893                                \n");
    not_delayed_print("PRT CON. 3.4.5. SECTRAN 9.4.3.          PORT STAT: SB-345                      \n");
    not_delayed_print("                                                                                \n");
    clear_screen ();
    not_delayed_print("(311) 655-7385                                                                 \n");
    not_delayed_print("                                                                                \n");
    not_delayed_print("                                                                                \n");
    clear_screen ();
    not_delayed_print("(311) 767-8739                                                                 \n");
    not_delayed_print("(311) 936-2364                                                                 \n");
    clear_screen();
    not_delayed_print("\033[7mPRT. STAT.                   CRT. DEF.                                    \033[0m\n");
    not_delayed_print("================================================                            \n");
    not_delayed_print("\033[7mFSKJJSJ: SUSJKJ: SUFJSL:          DKSJL: SKFJJ: SDKFJLJ                   \033[0m\n");
    not_delayed_print("\033[7mSYSPROC FUNCT READY          ALT NET READY                                \033[0m\n");
    not_delayed_print("\033[7mCPU AUTH RY-345-AX3     SYSCOMP STATUS: ALL PORTS ACTIVE                  \033[0m\n");
    not_delayed_print("22/34534.90/3289               CVB-3904-39490                              \n");
    not_delayed_print("(311) 936-2384                                                                 \n");
    not_delayed_print("(311) 936-3582                                                                 \n");
    clear_screen();
    not_delayed_print("22/34534.3209                  CVB-3904-39490                              \n");
    not_delayed_print("12934-AD-43KJ: CENTR PAK                                                      \n");
    not_delayed_print("(311) 767-1083                                                                 \n");
    clear_screen();
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\033[7mFLD CRS: 33.34.543     HPBS: 34/56/67/83     STATUS FLT  034/304          \033[0m\n");
    not_delayed_print("\033[7m1105-45-F6-B456          NOPR STATUS: TRAK OFF     PRON ACTIVE            \033[0m\n");
    not_delayed_print("(45:45:45  WER: 45/29/01 XCOMP: 43239582 YCOMP: 3492930D ZCOMP: 343906834        \n");
    not_delayed_print("                                          SRON: 65=65/74/84/65/89            \n");
    not_delayed_print("\033[2J\033[H                                                                 \n");
    not_delayed_print("-           PRT. STAT.                        CRY. DEF.                      \n");
    not_delayed_print("(311) 936-1582==============================================                \n");
    not_delayed_print("                  3453                3594                                   \n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("\n");
    not_delayed_print("FLJ42   TK01   BM90   R601   6J82   FP03   ZWO::   JW89                       \n");
    not_delayed_print("DEF TRPCON: 43.45342.349                                                      \n");
    not_delayed_print("\033[7mCPU AUTH RY-345-AX3     SYSCOMP STATUS: ALL PORTS ACTIVE                  \033[0m\n");
    not_delayed_print("(311) 936-2364                                                                 \n");
    not_delayed_print("**********************************************************************        \n");
    not_delayed_print("1105-45-F6-B456                 NOPR STATUS: TRAK OFF   PRON ACTIVE          \n");
    not_delayed_print("\033[2J\033[H                                                                 \n");
    }

    usleep(500000);
    delayed_print("GREETINGS PROFESSOR FALKEN.\n\n");
    delayed_print("SHALL WE PLAY A GAME?\n\n");
    handle_command_input();
    return;
}

void handle_logon_input() {
    char* prompt = "LOGON: ";
    char input[100];
    char command[200];
    
    while (1) {
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Convert input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        // Handle user input options
        if (strcmp(input, "help") == 0) {
            delayed_print("\nNO HELP AVAILABLE\n\n");
            delayed_print(prompt);
            handle_logon_input();
        } else if (strcmp(input, "help logon") == 0) {
            delayed_print("\nNO HELP AVAILABLE\n\n");
            delayed_print(prompt);
            handle_logon_input();
        } else if (strcmp(input, "help games") == 0) {
            delayed_print("\n'GAMES' REFERS TO MODELS, SIMULATIONS, AND GAMES WHICH HAVE TACTICAL AND\nSTRATEGIC APPLICATIONS\n\n");
            delayed_print(prompt);
            handle_logon_input();
        } else if (strcmp(input, "list games") == 0) {
            delayed_print("\nFALKEN'S MAZE\n");
            delayed_print("BLACK JACK\n");
            delayed_print("GIN RUMMY\n");
            delayed_print("HEARTS\n");
            delayed_print("BRIDGE\n");
            delayed_print("CHESS\n");
            delayed_print("POKER\n");
            delayed_print("FIGHTER COMBAT\n");
            delayed_print("GUERRILLA ENGAGEMENT\n");
            delayed_print("DESERT WARFARE\n");
            delayed_print("AIR-TO-GROUND ACTIONS\n");
            delayed_print("THEATERWIDE TACTICAL WARFARE\n");
            delayed_print("THEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n");
            usleep(500000);
            delayed_print("\nGLOBAL THERMONUCLEAR WAR\n\n");
            delayed_print("--RECOMMENDED OPTION--\nHACKERS UNSCRIPTED\n\n");
            delayed_print(prompt);
            handle_logon_input();
        } else if (strcmp(input, "joshua") == 0) {
            joshua();
            clear_screen();
            delayed_print(prompt);
            handle_logon_input();
        } else if (strcmp(input, "games") == 0) {
            delayed_print("\n--LOGON REQUIRED TO RUN GAMES--\n\n");
            delayed_print(prompt);
            handle_logon_input();
        } else if (strcmp(input, "falken's maze") == 0 || strcmp(input, "black jack") == 0 || strcmp(input, "gin rummy") == 0 || strcmp(input, "hearts") == 0 || strcmp(input, "bridge") == 0 || strcmp(input, "chess") == 0 || strcmp(input, "poker") == 0 || strcmp(input, "figher combat") == 0 || strcmp(input, "guerrilla engagement") == 0 || strcmp(input, "desert warfare") == 0 || strcmp(input, "air-to-ground actions") == 0 || strcmp(input, "theaterwide tactical warfare") == 0 || strcmp(input, "theaterwide biotoxic and chemical warfare") == 0 || strcmp(input, "global thermonuclear war") == 0 || strcmp(input, "hackers unscripted") == 0) {
            delayed_print("\n--LOGON REQUIRED TO RUN GAMES--\n\n");
            delayed_print(prompt);
            handle_logon_input();
        } else {
            delayed_print("IDENTIFICATION NOT RECOGNIZED BY SYSTEM\n--CONNECTION TERMINATED--\n");
            usleep(1000000);
            break;  // Exit the while loop
        }
    }

    exit(0);  // Exit the program after breaking out of the while loop
}

int main() {
        char command[200];
        // Clear screen
        clear_screen();

        // Send "LOGON: " to the client
        int i;
    	for (i = 0; i < 360; i++) {
        delayed_print(" ");
        usleep(500);
    	}
        delayed_print("\n");
        usleep(500000);
        delayed_print("W.O.P.R.\nIMSAI 8080\nVER. 6.3.83\n");
        usleep(500000);
        delayed_print("\n");
        delayed_print("\nLOGON: ");

        // Handle user input
        handle_logon_input();
        
        exit(0);
      
}

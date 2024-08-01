#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "auxiliary.h"
#include <stdio.h>
#include "sounds.h"
#define CYAN "\033[0;36m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

void intro(){
    gotoxy(10, 10);
    printf(CYAN);
    printf("A long time ago in a galaxy far,");
    gotoxy(10, 11);
    printf("far away....");
    Sleep(5000);
    system("cls");
}

void p_options(int i){
    if(i == 0)
        printf(GREEN);
    else
        printf(RESET);
    printf("Easy\n");
    if(i == 1)
        printf(GREEN);
    else
        printf(RESET);
    printf("Medium\n");
    if(i == 2)
        printf(GREEN);
    else
        printf(RESET);
    printf("Hard\n");
    if(i == 3)
        printf(GREEN);
    else
        printf(RESET);
    printf("Very Hard");
    printf(RESET);
}

void options(int i){
    gotoxy(0, 21);
    if(i == 0){
        printf(GREEN);
    }
    printf("Play\n");
    if(i == 1)
        printf(GREEN);
    else
        printf(RESET);
    printf("Records\n");
    if(i == 2)
        printf(GREEN);
    else
        printf(RESET);
    printf("Credits\n");
    if(i == 3)
        printf(GREEN);
    else
        printf(RESET);
    printf("Exit\n");
    printf(RESET);
}

int play(){
    system("cls");
    printf("Choose difficulty :\n");
    char ch;
    int j = 0;
    while(1){
        if(kbhit()){
            ch = getch();
            switch (ch) {
                case 'w':
                    if(j == 0)
                        break;
                    else
                        j--;
                    break;
                case 's':
                    if(j == 3)
                        break;
                    else
                        j++;
                    break;
                case 'd':
                    if(j == 0)
                        return 30;
                    else if(j == 1)
                        return 20;
                    else if(j == 2)
                        return 14;
                    else
                        return 6;
                case 'a':
                    return 0;
                default:
                    break;
            }
        }
        gotoxy(0, 1);
        p_options(j);
    }
}

void records(){
    system("cls");
    FILE *fp = fopen("records.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }
    char string[100];
    char strings[100][100];
    int i, count = 0;
    while (fgets(string, 100, fp))
    {
        string[strcspn(string, "\n")] = 0;
        strcpy(strings[count], string);
        count++;
    }
    fclose(fp);
    printf("Recent Records :\n");
    for (i = count - 1; i >= 0; i--)
    {
        printf("%s\n", strings[i]);
    }
    char ch;
    while(ch != 'a'){
        ch = getch();
    }
}

void credits(){
    system("cls");
    char strings[10][150];
    char string[150];
    int count = 0;
    FILE * fp = fopen("credits.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }
    while (fgets(string, 150, fp))
    {
        string[strcspn(string, "\n")] = 0;
        strcpy(strings[count], string);
        count++;
    }
    fclose(fp);
    printf("Credits :\n");
    for(int i = 0; i < count; i++){
        printf("%s\n", strings[i]);
    }
    char ch;
    while(ch != 'a'){
        ch = getch();
    }
}


int menu(){
    intro();
    theme_sound();
    char ch;
    int i = 0;
    while(1){
        gotoxy(0, 0);
        printf(YELLOW);
        printf("                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@       @@@@@@@@@@@@@@@                 \n"
               "                    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@      @@@@@@@@@@@@@@@@                \n"
               "                    @@@@@@@@       @@@@@@@        @@@@@@ @@@@@      @@@@@@     @@@@@                \n"
               "                     @@@@@@@        @@@@@         @@@@@@ @@@@@@     @@@@@@    @@@@@@                \n"
               "                      @@@@@@@@      @@@@@        @@@@@@   @@@@@     @@@@@@@@@@@@@@@                 \n"
               "                       @@@@@@@      @@@@@        @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@                  \n"
               "         @@@@@@@@@@@@@@@@@@@@@      @@@@@       @@@@@@@@@@@@@@@@    @@@@@@ @@@@@@@@@@@@@@@@         \n"
               "         @@@@@@@@@@@@@@@@@@@@@      @@@@@       @@@@@@@@@@@@@@@@@   @@@@@@  @@@@@@@@@@@@@@@         \n"
               "          @@@@@@@@@@@@@@@@@@        @@@@@      @@@@@@       @@@@@   @@@@@@    @@@@@@@@@@@@@         \n"
               "                                                                                                    \n"
               "          @@@@@@   @@@@@@@  @@@@@@    @@@@@@@@@       @@@@@@@@@@@@@@         @@@@@@@@@@@@@@         \n"
               "          @@@@@@@ @@@@@@@@  @@@@@    @@@@@@@@@@@      @@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@@@         \n"
               "           @@@@@@@@@@@@@@@@@@@@@@    @@@@@@@@@@@      @@@@@@     @@@@@@    @@@@@@@@@@@@@@@@         \n"
               "           @@@@@@@@@@@@@@@@@@@@@    @@@@@@ @@@@@@     @@@@@@     @@@@@@    @@@@@@@                  \n"
               "            @@@@@@@@@@@@@@@@@@@@    @@@@@@  @@@@@     @@@@@@@@@@@@@@@@@     @@@@@@@@                \n"
               "             @@@@@@@@@@@@@@@@@@    @@@@@@   @@@@@@    @@@@@@@@@@@@@@@         @@@@@@@               \n"
               "             @@@@@@@@  @@@@@@@@    @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              \n"
               "              @@@@@@@  @@@@@@@    @@@@@@@@@@@@@@@@@   @@@@@@  @@@@@@@@@@@@@@@@@@@@@@@               \n"
               "              @@@@@@    @@@@@@    @@@@@       @@@@@   @@@@@@    @@@@@@@@@@@@@@@@@@@@                \n");
        printf(RESET);
        if(kbhit()){
            ch = getch();
            switch (ch) {
                case 'w':
                    if(i == 0)
                        break;
                    else
                        i--;
                    break;
                case 's':
                    if(i == 4)
                        break;
                    else
                        i++;
                    break;
                case 'a':
                    break;
                case 'd':
                    if(i == 0){
                        int k = play();
                        if(k){
                            bonus_sound();
                            return k;
                        }
                    }
                    if(i == 1) {
                        records();
                        break;
                    }
                    if(i == 2){
                        credits();
                        break;
                    }
                    if(i == 3)
                        return 0;
                    break;
            }
        }
        options(i);
    }
}

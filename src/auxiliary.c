#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "sounds.h"

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

int gscore;

void write_record(){
    SYSTEMTIME t;
    GetLocalTime(&t);
    char name[50];
    scanf("%[^\n]s", name);
    FILE * fp = fopen("records.txt", "a+");
    fprintf(fp, "Score: %d ", gscore);
    fprintf(fp, "Name: %s Date: %d/%d/%d Time: %.2d:%.2d", name, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute);
    fprintf(fp,"\n");
    fclose(fp);
}

int restart(){
    int i = 0;
    char ch;
    printf("Enter your name : ");
    write_record();
    while(1){
        if(kbhit()){
            ch = getch();
            switch (ch){
                case 'a':
                    i++;
                    break;
                case 'd':
                    i++;
                    break;
                case 32:
                    if(i % 2 == 0)
                        return 1;
                    else
                        return 0;
                default:
                    break;
            }
        }
        gotoxy(0, 21);
        printf("Do you want to restart ?\n");
        if(i % 2 == 0){
            printf("\033[0;32m");
            printf("YES\t");
            printf("\033[0m");
            printf("NO");
        }
        else{
            printf("YES\t");
            printf("\033[0;32m");
            printf("NO");
            printf("\033[0m");
        }
    }
}


int game_over(int score){
    system("cls");
    go_sound();
    gotoxy(0, 10);
    printf("\033[0;31m");
    printf("  ____    _    __  __ _____ \n"
           " / ___|  / \\  |  \\/  | ____|\n"
           "| |  _  / _ \\ | |\\/| |  _|  \n"
           "| |_| |/ ___ \\| |  | | |___ \n"
           " \\____/_/   \\_\\_|__|_|_____|\n"
           " / _ \\ \\   / / ____|  _ \\| |\n"
           "| | | \\ \\ / /|  _| | |_) | |\n"
           "| |_| |\\ V / | |___|  _ <|_|\n"
           " \\___/  \\_/  |_____|_| \\_(_)\n");
    printf("\033[0m");
    printf("Your Score : %d\n", score);
    gscore = score;
    return restart();
}

int pause(){
    int i = 0;
    char ch;
    while(1){
        if(kbhit()){
            ch = getch();
            switch (ch){
                case 'a':
                    i++;
                    break;
                case 'd':
                    i++;
                    break;
                case 32:
                    if (i % 2 == 0) {
                        system("cls");
                        return 1;
                    } else
                        return 0;
                default:
                    break;
            }
        }
        gotoxy(0, 42);
        printf("Game Paused !\n");
        if(i % 2 == 0){
            printf("\033[0;32m");
            printf("Continue\t");
            printf("\033[0m");
            printf("Give up");
        }
        else{
            printf("Continue\t");
            printf("\033[0;32m");
            printf("Give up");
            printf("\033[0m");
        }
    }
}


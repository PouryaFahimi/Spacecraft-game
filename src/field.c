#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "linklist.h"
//#include "linklist.c"
#include "auxiliary.h"
#include "menu.h"
#include "sounds.h"

void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

char field[40][40];

int x = 35, y = 16;

int frame = 0;
int speed = 0;
int sh_health = 10;
int double_shot = 0;
int level;

void move() {
    for (int i = 0; i < 3; ++i) {
        if (i == 0) {
            field[x][y + 1] = '/';
            field[x][y + 2] = 'T';
            field[x][y + 3] = '\\';
        } else if (i == 1) {
            field[x + 1][y] = '/';
            field[x + 1][y + 1] = field[x + 1][y + 2] = field[x + 1][y + 3] = '|';
            field[x + 1][y + 4] = '\\';
        } else {
            field[x + 2][y + 1] = field[x + 2][y + 2] = field[x + 2][y + 3] = 'Y';
        }
    }
}

void boundaries() {
    for (int i = 0; i < 40; ++i) {
        field[0][i] = field[39][i] = field[i][0] = field[i][39] = '#';
    }
}

void Print() {
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 40; ++j) {
            gotoxy(j, i + 1);
            printf("%c", field[i][j]);
        }
    }
    printf("\n");
}

void clear() {
    for (int i = 1; i < 39; ++i) {
        for (int j = 1; j < 39; ++j) {
            field[i][j] = 32;
        }
    }
}

int random_num() {
    srand(time(NULL));
    return rand() % 36 + 1;
}

void mine() {
    add_end(new_node(1, random_num(), 'm'));
}

void equipment() {
    add_end(new_node(1, random_num(), 'e'));
}

void bomber(int i) {
    if (i)
        add_end(new_node(1, 2, 'c'));
    else
        add_end(new_node(1, 35, 'g'));
}

void fighter() {
    add_end(new_node(1, random_num(), 'f'));
}

void stalker() {
    add_end(new_node(1, random_num(), 's'));
}

void shot() {
    if(double_shot != 0){
        add_end(new_node(x, y + 1, 't'));
        add_end(new_node(x, y + 3, 't'));
        double_shot--;
    }
    else
        add_end(new_node(x, y + 2, 't'));
    //shot_sound();
}

void update() {
    int i = 1;
    for (node *ptr = head; ptr != NULL; ptr = ptr->next) {
        switch (ptr->type) {
            case 't':
                if (ptr->x != 1)
                    ptr->x -= 2;
                else {
                    delete_index(i);
                    break;
                }
                if (field[ptr->x][ptr->y] != 32 || field[ptr->x - 1][ptr->y] != 32) {
                    delete_index(i);
                    if (delete_index(find(ptr->x - 2, ptr->y, '~')) == 0)
                        break;
                    if (delete_index(find(ptr->x - 2, ptr->y - 1, '~')) == 0)
                        break;
                    delete_index(find(ptr->x - 2, ptr->y - 2, '~'));
                } else
                    field[ptr->x][ptr->y] = 'A';
                break;
            case 'm':
                if (ptr->x == 36) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 6 == 0)
                        ptr->x++;
                }
                if (ptr->x == x - 2) {
                    if (ptr->y - y >= -2 && ptr->y - y <= 4) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                }
                field[ptr->x][ptr->y] = field[ptr->x][ptr->y + 1] = field[ptr->x][ptr->y + 2] = field[ptr->x + 1][ptr->y] = field[ptr->x + 1][ptr->y + 2] = field[ptr->x + 2][ptr->y] = field[ptr->x + 2][ptr->y + 1] = field[ptr->x + 2][ptr->y + 2] = '-';
                field[ptr->x + 1][ptr->y + 1] = 'X';
                break;
            case 'e':
                if (ptr->x == 36) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 4 == 0)
                        ptr->x++;
                }
                if (ptr->x == x - 2) {
                    if (ptr->y - y >= -2 && ptr->y - y <= 4) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                }
                field[ptr->x][ptr->y] = field[ptr->x + 2][ptr->y + 2] = '/';
                field[ptr->x][ptr->y + 2] = field[ptr->x + 2][ptr->y] = '\\';
                field[ptr->x + 1][ptr->y] = field[ptr->x + 1][ptr->y + 2] = '|';
                field[ptr->x][ptr->y + 1] = field[ptr->x + 2][ptr->y + 1] = '-';
                field[ptr->x + 1][ptr->y + 1] = '?';
                break;
            case 'h':
                if (ptr->x == 36) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 6 == 0)
                        ptr->x++;
                }
                if (ptr->x == x - 2) {
                    if (ptr->y - y >= -2 && ptr->y - y <= 4) {
                        delete_index(i);
                        bonus_sound();
                        if (sh_health != 10)
                            sh_health++;
                        break;
                    }
                }
                field[ptr->x][ptr->y] = field[ptr->x][ptr->y + 1] = field[ptr->x][ptr->y + 2] = field[ptr->x + 1][ptr->y] = field[ptr->x + 1][ptr->y + 2] = field[ptr->x + 2][ptr->y] = field[ptr->x + 2][ptr->y + 1] = field[ptr->x + 2][ptr->y + 2] = '=';
                field[ptr->x + 1][ptr->y + 1] = '+';
                break;
            case 'd':
                if (ptr->x == 36) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 6 == 0)
                        ptr->x++;
                }
                if (ptr->x == x - 2) {
                    if (ptr->y - y >= -2 && ptr->y - y <= 4) {
                        delete_index(i);
                        bonus_sound();
                        double_shot = 10;
                        break;
                    }
                }
                field[ptr->x][ptr->y] = field[ptr->x][ptr->y + 1] = field[ptr->x][ptr->y + 2] = field[ptr->x + 1][ptr->y] = field[ptr->x + 1][ptr->y + 2] = field[ptr->x + 2][ptr->y] = field[ptr->x + 2][ptr->y + 1] = field[ptr->x + 2][ptr->y + 2] = '=';
                field[ptr->x + 1][ptr->y + 1] = 'A';
                break;
            case 'c':
                if (ptr->y == 36) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 6 == 0) {
                        ptr->x++;
                        ptr->y++;
                    }
                }
                if(speed % 25 == 1){
                    add_end(new_node(ptr->x + 2, ptr->y + 1, 'b'));
                }
                if (ptr->x == x - 2) {
                    if (ptr->y - y >= -2 && ptr->y - y <= 4) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                }
                field[ptr->x + 1][ptr->y] = '(';
                field[ptr->x + 1][ptr->y + 1] = '@';
                field[ptr->x + 1][ptr->y + 2] = ')';
                field[ptr->x + 2][ptr->y] = '\\';
                field[ptr->x + 2][ptr->y + 1] = '_';
                field[ptr->x + 2][ptr->y + 2] = '/';
                break;
            case 'g':
                if (ptr->y == 1) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 6 == 0) {
                        ptr->x++;
                        ptr->y--;
                    }
                }
                if(speed % 25 == 1){
                    add_end(new_node(ptr->x + 2, ptr->y + 1, 'b'));
                }
                if (ptr->x == x - 2) {
                    if (ptr->y - y >= -2 && ptr->y - y <= 4) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                }
                field[ptr->x + 1][ptr->y] = '(';
                field[ptr->x + 1][ptr->y + 1] = '@';
                field[ptr->x + 1][ptr->y + 2] = ')';
                field[ptr->x + 2][ptr->y] = '\\';
                field[ptr->x + 2][ptr->y + 1] = '_';
                field[ptr->x + 2][ptr->y + 2] = '/';
                break;
            case 'f':
                if (ptr->x == 36) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 4 == 0)
                        ptr->x++;
                }
                if (ptr->x == x - 2) {
                    if (ptr->y - y >= -2 && ptr->y - y <= 4) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                }
                if(speed % 25 == 20){
                    add_end(new_node(ptr->x + 2, ptr->y + 1, 'v'));
                }
                field[ptr->x][ptr->y + 1] = field[ptr->x + 1][ptr->y] = field[ptr->x + 1][ptr->y + 2] = '-';
                field[ptr->x + 1][ptr->y + 1] = '#';
                field[ptr->x + 2][ptr->y + 1] = 'V';
                break;
            case 'v':
                if (ptr->x == 36) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 2 == 0)
                        ptr->x++;
                }
                if (ptr->x == x) {
                    if (ptr->y - y >= 1 && ptr->y - y <= 3) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                } else if(ptr->x == x + 1){
                    if (ptr->y - y >= 0 && ptr->y - y <= 4) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                }
                field[ptr->x][ptr->y] = 'V';
                break;
            case 's':
                if (speed % 4 == 0) {
                    if (ptr->x < x)
                        ptr->x++;
                    else if(ptr->x > x)
                        ptr->x--;
                    if(ptr->y < y)
                        ptr->y++;
                    else if(ptr->y > y)
                        ptr->y--;
                }
                if (ptr->x - x >= -2 && ptr->x <= 2) {
                    if (ptr->y - y >= -2 && ptr->y - y <= 4) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                }
                field[ptr->x][ptr->y + 1] = field[ptr->x + 1][ptr->y] = field[ptr->x + 1][ptr->y + 2] = '-';
                field[ptr->x + 1][ptr->y + 1] = 'X';
                field[ptr->x + 2][ptr->y + 1] = 'V';
                break;
            case 'b':
                if (ptr->x == 36) {
                    delete_index(i);
                    break;
                } else {
                    if (speed % 2 == 0)
                        ptr->x++;
                }
                if (ptr->x == x) {
                    if (ptr->y - y >= 1 && ptr->y - y <= 3) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                } else if(ptr->x == x + 1){
                    if (ptr->y - y >= 0 && ptr->y - y <= 4) {
                        delete_index(i);
                        sh_health--;
                        break;
                    }
                }
                field[ptr->x][ptr->y] = '@';
                break;
        }
        i++;
    }
    speed++;
}


void health() {
    printf("HEALTH : ");
    if (sh_health > 3)
        printf(GREEN);
    else
        printf("\033[0;31m");
    for (int i = 0; i < 10; ++i) {
        //gotoxy(10 + i, 41);
        if (i < sh_health)
            printf("=");
        else
            printf(" ");
    }
    printf(RESET);
    if(double_shot){
        printf(" POWER : ");
        printf(YELLOW);
        for (int i = 0; i < 10; ++i) {
            if (i < double_shot)
                printf("=");
            else
                printf(" ");
        }
        printf(RESET);
    } else
        printf("          ");
}

void enemy() {
    if (frame % level != 0)
        return;
    int r = rand() % 8;
    if (r == 0 || r == 1 || r == 6)
        mine();
    else if (r == 2 || r == 3)
        equipment();
    else if (r == 4)
        bomber(rand() % 2);
    else if (r == 5)
        fighter();
    else
        stalker();

}

int main() {
    hide_cursor();
    level = menu();
    if (level == 0)
        return 0;
    boundaries();
    move();
    char ch;
    clock_t start = clock();
    clock_t end;
    while (ch != 27) {
        clear();
        if (kbhit()) {
            ch = getch();
            switch (ch) {
                case 'a':
                    if (y == 1)
                        break;
                    --y;
                    break;
                case 's':
                    if (x == 36)
                        break;
                    ++x;
                    break;
                case 'd':
                    if (y == 34)
                        break;
                    ++y;
                    break;
                case 'w':
                    if (x == 1)
                        break;
                    --x;
                    break;
                case 32:
                    shot();
                    break;
                case 'p':
                    if(pause())
                        break;
                    else
                        return 0;
                default:
                    break;
            }
        }
        fflush(stdin);
        move();
        enemy();
        //system("cls");
        end = clock();
        gotoxy(0, 0);
        printf("SCORE : %.3ld items : %.3d\n", (end - start) / 1000, len());
        //boundaries();
        update();
        Print();
        if (sh_health == 0) {
            if (game_over((end - start) / 1000)) {
                sh_health = 10;
            } else {
                system("cls");
                level = menu();
                if (level == 0)
                    return 0;
            }
            system("cls");
            free_list();
            start = clock();
            x = 35;
            y = 16;
        }
        frame++;
        health();
    }
    system("pause");
    return 0;
}

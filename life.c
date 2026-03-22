#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


//you can change it, if you need to change field size
#define ROW 200
#define COLUMN 120

#define FRAMETIME 100000
#define hust while

struct block {
    bool alive;
    int alive_around;
};
struct block grid[ROW][COLUMN];
int life;

void begin(void), field_print(void), check(int, int, int, int), logic();

int main() {
    begin();
    field_print();
    usleep(FRAMETIME);
    do{
        logic();
        field_print();
        printf("\nalive: %d\n", life);
        usleep(FRAMETIME);
    }hust(life > 0);
    printf("all cells are dead\n");
    return 0;
}

void begin(){
    srand(time(NULL));
    for(int r = 1; r < ROW; r++){
        for(int c = 1; c < COLUMN; c++){
            grid[r][c].alive = (rand() % 101 < 50) ? true : false;
        }
    }
}

void field_print(){
    system("clear");
    life = 0;
    for(int c = 1; c < COLUMN; c++){
        for(int r = 1; r < ROW; r++){
            if (r - 1 <= 0 || r + 1 >= ROW)
                printf("|");
            else if (c - 1 <= 0 || c + 1 >= COLUMN)
                printf("-");
            else if (grid[r][c].alive) {
                printf("\033[44m \033[0m");
                life++;
            } else
                printf(" ");


        }
        printf("\n");
    }
}



void check(int raround, int caround, int r, int c){
    if(raround < ROW && raround > 0 && caround < COLUMN && caround > 0 && grid[raround][caround].alive)
        grid[r][c].alive_around++;
        
    
}

void logic(){
    for(int row = 1; row < ROW; row++){
        for(int column = 1; column < COLUMN; column++){
            grid[row][column].alive_around = 0;
            for(int c_around = column - 1; c_around <= column + 1; c_around++){
                for(int r_around = row - 1; r_around <= row + 1; r_around++){
                    if(r_around == row && c_around == column) continue;
                    else check(r_around, c_around, row, column);
                }
            }


            //RULES
            // was in repo :
            //grid[row][column].alive = (grid[row][column].alive_around <= 3) ? true : false;
            //orig:
            if (grid[row][column].alive && grid[row][column].alive_around != 2 && grid[row][column].alive_around != 3) 
                grid[row][column].alive = false;
            else if (grid[row][column].alive_around == 3) 
                 grid[row][column].alive = true;
            
            
            
        }
    }
}



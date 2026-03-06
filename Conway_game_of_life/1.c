#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 40
#define GENERATIONS 50

int field[SIZE][SIZE];
int next[SIZE][SIZE];

int count_neighbors(int x, int y) {
    int count = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE)
                count += field[nx][ny];
        }
    }

    return count;
}

void next_generation() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            int neighbors = count_neighbors(i, j);

            if (field[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3)
                    next[i][j] = 0;
                else
                    next[i][j] = 1;
            } else {
                if (neighbors == 3)
                    next[i][j] = 1;
                else
                    next[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            field[i][j] = next[i][j];
}

void print_field(int gen) {

    printf("Generation %d\n", gen);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (field[i][j])
                printf("O");
            else
                printf(".");
        }
        printf("\n");
    }

    printf("\n");
}

int main() {

    /* пример начальной конфигурации */

    field[1][2] = 1;
    field[2][3] = 1;
    field[3][1] = 1;
    field[3][2] = 1;
    field[3][3] = 1;

    for (int g = 0; g < GENERATIONS; g++) {

        print_field(g);
        next_generation();

        usleep(200000);
    }

    return 0;
}

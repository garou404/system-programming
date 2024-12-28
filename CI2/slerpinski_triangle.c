#include <stdlib.h>
#include <stdio.h>

int sort_get_index(float tab[], int top, float val) {
    for (int i = 0; i < top; i++) {
        if (val < tab[i]){
            return i;
        }
    }
    return top;
}

void sort_insert_at(float tab[], int i, int top, float val) {
    for (int u = top; u > i; --u) {
        tab[u] = tab[u-1];
    }
    tab[i] = val;
}

void sort_insert(float tab[], int top, float val) {
    int i = sort_get_index(tab, top, val);
    sort_insert_at(tab, i, top, val);
}

int nb_columns() {
    return 32;
}

int nb_lines() {
    return 16;
}

void grid_init(char grid[], char pixel) {
    for (int i = 0; i < nb_columns()*nb_lines(); i++) {
        grid[i] = pixel;
    }
}

void grid_display(char grid[]) {
    for (int i = 0; i < nb_columns()*nb_lines(); i++) {
        printf("%c", grid[i]);
        if ((i+1) % nb_columns() == 0) {
            printf("\n");
        }
    }
}

void plot_point(char grid[], int x, int y, char iv) {
    if (x > nb_columns()-1) {
        printf("%d OUT\n", x);
        exit(EXIT_FAILURE);
    }else if (y > nb_lines()-1)
    {
        printf("%d OUT\n", y);
        exit(EXIT_FAILURE);
    }
    
    grid[nb_columns()*(nb_lines()-1-y) + x] = iv;
}

int main(int argc, char** argv){
    char grid[nb_columns() * nb_lines()];
    grid_init(grid, '*');
    plot_point(grid, 3, 1, ' ');
    // plot_point(grid, 3, 100, ' ');
    grid_display(grid);
    return EXIT_SUCCESS;
}
#include <stdlib.h>
#include <stdio.h>

struct point {
    float x;
    float y;
};

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

void plot_vline(char grid[], int x, float fy0, float fy1, char pixel) {
    int y0 = (int) (fy0+0.5);
    if ((y0-0.5) == fy0) {
        y0 = y0 - 1;
    }
    int y1 = (int) (fy1+0.5);
    for (int i = y0; i <= y1; i++) {
        plot_point(grid, x, i, pixel);
    }
}

void plot_poly_sweep(char grid[], struct point p[], int tab_length, int x, char pixel) {
    printf("sweep: %d", x);
    int j = tab_length - 1;
    for (int i = 0; i < tab_length; i++) {
        // printf(" (%d, %d)", j, i);
        if (((p[i].x <= x) & (x <= p[j].x)) | ((p[j].x <= x) & (x <= p[i].x))) {
            printf(" %f", p[i].y + (x - p[i].x) * (p[j].y - p[i].y) / (p[j].x - p[i].x));
        }
        j = i;
    }
    // for(int i = axis; i < (nb_columns()*nb_lines()); (i = i +nb_columns())) {
    //     printf("%c", grid[i]);
    // }
    printf("\n");
}

void plot_poly(char grid[], struct point p[], int tab_length, char pixel) {
    for (int o = 0; o < nb_columns(); o++) {
        plot_poly_sweep(grid, p, tab_length, o, pixel);
    }
}

int main(int argc, char** argv){
    char grid[nb_columns() * nb_lines()];
    
    grid_init(grid, ' ');
    plot_point(grid, 3, 1, ' ');
    int tab_length = 6;
    struct point p[] = {{ 2, 13 }, { 10, 13 }, { 30, 7 }, { 10, 1 }, { 2, 1 }, { 18, 7 }};
    plot_poly(grid, p, tab_length, '*');
    // grid_display(grid);
    return EXIT_SUCCESS;
}
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
    return 129;
}

int nb_lines() {
    return 65;
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
    float vlines[tab_length*4];
    int top = 0;
    int j = tab_length - 1;
    for (int i = 0; i < tab_length; i++) {
        if (p[i].x == x) {
            if(p[j].x == x) {
                if (p[i].y < p[j].y) {
                    plot_vline(grid, x, p[i].y, p[j].y, pixel);
                }else {
                    plot_vline(grid, x, p[j].y, p[i].y, pixel);
                }
            } else {
                plot_vline(grid, x, p[i].y, p[i].y, pixel);
            }
        } {
            if(p[i].x <= p[j].x) {
                if((p[i].x <= x) & (x < p[j].x)) {
                    sort_insert(vlines, top, p[i].y + (x - p[i].x) * (p[j].y - p[i].y) / (p[j].x - p[i].x));
                    top += 1;
                }
            }
            if (p[i].x >= p[j].x ){
                if((p[i].x > x) & (x >= p[j].x)) {
                    sort_insert(vlines, top, p[i].y + (x - p[i].x) * (p[j].y - p[i].y) / (p[j].x - p[i].x));
                    top += 1;
                }
            }
        }
        j = i;
    }

    for (int i = 0; i < top; i+=2) {
        plot_vline(grid, x, vlines[i], vlines[i+1], pixel);
    }
    printf("\n");
}

void plot_poly(char grid[], struct point p[], int tab_length, char pixel) {
    for (int o = 0; o < nb_columns(); o++) {
        plot_poly_sweep(grid, p, tab_length, o, pixel);
    }
}

void plot_triangle(char grid[], struct point p1, struct point p2, struct point p3, char pixel) {
    struct point points_triangle[3] = {p1, p2, p3};
    plot_poly(grid, points_triangle, 3, '-');
}


struct point line_middle(struct point p1, struct point p2) {
    struct point middle = {(p1.x+p2.x)/2, (p1.y+p2.y)/2};
    return middle;
}

void sierpinski(char grid[], struct point p1, struct point p2, struct point p3, int n, char pixel){
    if (n == 1) {
        plot_triangle(grid, p1, p2, p3, pixel);
    }else {
        sierpinski(grid, p1, line_middle(p1, p2), line_middle(p1, p3), n-1, pixel);
        sierpinski(grid, p2, line_middle(p2, p1), line_middle(p2, p3), n-1, pixel);
        sierpinski(grid, p3, line_middle(p3, p1), line_middle(p3, p2), n-1, pixel);
    }
}

int main(int argc, char** argv){
    char grid[nb_columns() * nb_lines()];
    
    grid_init(grid, ' ');
    struct point p1 = {0, 0};
    struct point p2 = {64, 64};
    struct point p3 = {128, 0};
    sierpinski(grid, p1, p2, p3, 6, '-');
    grid_display(grid);
    return EXIT_SUCCESS;
}
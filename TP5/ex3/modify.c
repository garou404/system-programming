#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "student.h"
#include <assert.h>


int main(int argc, char** argv) {
    if(argc != 4) {
        printf("Usage: ./modify grade_file student_name grade\n");
        return EXIT_FAILURE;
    }

    FILE* grade_file = fopen(argv[1], "r+");
    if (grade_file == NULL) {
        printf("fopen %s: %s", argv[1], strerror(errno));
    }
    fseek(grade_file, 0, SEEK_END);
    long size = ftell(grade_file);
    printf("grade file size: %ld\n", size);
    long student_nb = size/sizeof(struct student);
    printf("number of students: %ld\n", student_nb);

    struct student* stdts = malloc(sizeof(struct student)*student_nb);
    assert(stdts);
    printf("supposed size : %lu\n", student_nb*sizeof(struct student));
    printf("size of struct : %lu\n\n", sizeof(struct student));
    fseek(grade_file, 0, SEEK_SET);
    int elemnt_nb_read = fread(stdts, sizeof(struct student), student_nb, grade_file);
    printf("%d\n", elemnt_nb_read);

    for (int i = 0; i < student_nb; i++) {
        printf("%s with grade %d\n", (stdts+i)->name, (stdts+i)->rank);
    }
    int cursor = 0;
    for (cursor; cursor < student_nb; cursor++) {
        if(strcmp(argv[2], (stdts+cursor)->name) == 0){
            break;
        }
    }
    if(cursor == student_nb){
        printf("%s is not in the student list\n", argv[2]);
        return EXIT_FAILURE;
    }else{
        int new_grade = atoi(argv[3]);
        printf("\n%s old grade: %d, new grade: %d\n", (stdts+cursor)->name, (stdts+cursor)->rank, new_grade);
        (stdts+cursor)->rank = new_grade;
    }
    fseek(grade_file, cursor*sizeof(struct student), SEEK_SET);
    if(fwrite((stdts+cursor), sizeof(struct student), 1, grade_file) == 0) {
        printf("fwrite error\n");
        return EXIT_FAILURE;
    }

    free(stdts);
    return EXIT_SUCCESS;
}

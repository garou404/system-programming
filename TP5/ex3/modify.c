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
    // printf("%s\n", (stdts+50)->name);
    // printf("student %s with grade %d\n", (stdts+sizeof(struct student)*0)->name, (stdts+sizeof(struct student)*0)->rank);
    // printf("student %s with grade %d\n", (stdts+1)->name, (stdts+sizeof(struct student)*1)->rank);
    // printf("student %s with grade %d\n", (stdts+sizeof(struct student)*3)->name, (stdts+sizeof(struct student)*3)->rank);

    for (int i = 0; i < student_nb; i++) {
    //     // printf("%d\n", (stdts+i*sizeof(struct student))->rank);
        printf("student %s with grade %d\n", (stdts+i)->name, (stdts+i)->rank);
    }
    free(stdts);
    return EXIT_SUCCESS;
}

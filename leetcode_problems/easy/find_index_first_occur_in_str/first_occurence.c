#include <stdio.h>
#include <stdlib.h>


int strStr(char* haystack, char* needle) { // O(N+2M)
    
    // KPM alogrithm
    int needle_len = 0;
    while(needle[needle_len] != '\0') { // O(M)
        needle_len++;
    }
    int*lps = malloc(sizeof(int)*needle_len);
    lps[0] = 0;
    for(int i = 1; i < needle_len; i++) { // O(M)
        int val = 0;
        for(int o = i; o >0; o--){
            val = o;
            for(int u = 0; u < o; u++) {
                if(needle[u] != needle[u+i+1-o]) {
                    val = 0;
                    break;
                }
            }
            if (val != 0){
                break;
            }
        }
        lps[i] = val;
    }
    int i = 0;
    int j = 0;
    while(haystack[i] != '\0') { // O(N)
        if(needle[j] == '\0'){
            printf("here j %d - needle_len %d =  %d\n", j, needle_len, j-needle_len);
            return i - needle_len;
        }
        printf("haystack[i] %c != needle[j] %c\n", haystack[i], needle[j]);
        if(haystack[i] != needle[j]){
            i = i-j;
            j = lps[j];
        }else{
            j++;
        }
        i++;
    }
    printf("needle[j+1=%d]=%c \n", j, needle[j]);
    if(needle[j] == '\0') {
        return i-j;
    }else{
        return -1;
    }
}

int strStr2(char* haystack, char* needle) { //best solution I proposed
    int output = -1;
    int index_haystack = 0;
    int index_needle = 0;
    while(haystack[index_haystack] != '\0') {
        if(needle[index_needle] == '\0') {
            return output;
        }
        if(haystack[index_haystack] == needle[index_needle]) {
            if(output == -1){
                output = index_haystack;
            }
            index_needle++;
        }else{
            if(output != -1){
                index_haystack = output;
            }
            index_needle = 0;
            output = -1;
        }
        index_haystack++;
    }
    if(needle[index_needle] == '\0') {
        return output;
    }
    return -1;
}

int kpm_algo(char* haystack, char* needle) {// Knuth Maurice Pratt
    // LPS computation
    int needle_len = 0;
    while(needle[needle_len] != '\0') { // O(M)
        needle_len++;
    }
    int*lps = malloc(sizeof(int)*needle_len);
    lps[0] = 0;
    int len = 0;
    for (int i = 1; i < needle_len; i++) { // O(M)
        if(needle[len] == needle[i]){
            len++;
            lps[i] = len;
        }else{
            if(len > 0) {
                len = lps[len-1];
                i--;
            }else{
                len = 0;
                lps[i] = len;
            }
        }
    }
    for (int i = 0; i < needle_len; i++)
    {
        printf("lps[%d] = %d\n", i, lps[i]);
    }
    
    int i = 0;
    int j = 0;
    while(haystack[i] != '\0') { // O(N)
        if(needle[j] == '\0'){
            return i - needle_len;
        }
        if(haystack[i] != needle[j]){
            if(j > 0) {
                j = lps[j-1];
            }else{
                i++;
            }
        }else{
            j++;
            i++;
        }
    }
    if(needle[j] == '\0') {
        return i-j;
    }else{
        return -1;
    }
}

int assert_int_equal(int a, int b) {
    if(a == b) {
        printf("true\n");
        return 1;
    }else{
        printf("false\n");
        return -1;
    }
}


int main(int argc, char** argv) {

    // char* haystack = "ababababac";
    // char* needle = "ababac";
    // printf("strStr(haystack, needle) = %d\n", kpm_algo(haystack, needle));
    // assert_int_equal(4, kpm_algo(haystack, needle));

    // char* haystack2 = "hello";
    // char* needle2 = "ll";
    // printf("strStr(haystack, needle) = %d\n", kpm_algo(haystack2, needle2));
    // assert_int_equal(2, kpm_algo(haystack2, needle2));

    // char* haystack3 = "a";
    // char* needle3 = "a";
    // printf("strStr(haystack, needle) = %d\n", kpm_algo(haystack3, needle3));
    // assert_int_equal(0, kpm_algo(haystack3, needle3));

    // char* haystack4 = "leetcode";
    // char* needle4 = "leeto";
    // printf("strStr(haystack, needle) = %d\n", kpm_algo(haystack4, needle4));
    // assert_int_equal(0, kpm_algo(haystack4, needle4));
    assert_int_equal(-1, kpm_algo("adcadcaddcadde", "adcadde"));

    return EXIT_SUCCESS;
}



#pragma once

#include <stdlib.h>

// String helpers

char** splitstr(const char* s, const char* delim) {
    // Count the number of tokens
    int count = 0;
    const char* tmp = s;
    while (*tmp) {
        if (strchr(delim, *tmp)) {
            count++;
        }
        tmp++;
    }
    count++; // For the last token

    // Allocate memory for the array of strings
    char** result = malloc((count + 1) * sizeof(char*));
    if (!result) {
        return NULL; // Allocation failed
    }

    // Tokenize the string
    int index = 0;
    const char* start = s;
    tmp = s;
    while (*tmp) {
        if (strchr(delim, *tmp)) {
            size_t len = tmp - start;
            result[index] = malloc(len + 1);
            if (!result[index]) {
                // Free previously allocated memory on failure
                for (int i = 0; i < index; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[index], start, len);
            result[index][len] = '\0';
            index++;
            start = tmp + 1; // Move past the delimiter
        }
        tmp++;
    }

    // Handle the last token
    size_t len = tmp - start;
    result[index] = malloc(len + 1);
    if (!result[index]) {
        for (int i = 0; i < index; i++) {
            free(result[i]);
        }
        free(result);
        return NULL;
    }
    strncpy(result[index], start, len);
    result[index][len] = '\0';
    index++;

    result[index] = NULL; // Null-terminate the array

    return result;
}

void printstrarray(char** arr) {
    if (!arr) return;
    for (int i = 0; arr[i] != NULL; i++) {
        puts(arr[i]);
        putchar('\n');
    }
}

char *itoa(long n) {
    static char buf[32];
    int i = 0;
    int neg = 0;

    if (n == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
    if (n < 0) {
        neg = 1;
        n = -n;
    }
    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }
    if (neg)
        buf[i++] = '-';
    buf[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char t = buf[j];
        buf[j] = buf[i - j - 1];
        buf[i - j - 1] = t;
    }
    return buf;
}
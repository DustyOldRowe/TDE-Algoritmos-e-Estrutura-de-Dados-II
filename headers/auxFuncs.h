#include "StructVendas.h"
#include <stdio.h>
#include <stdbool.h>
#ifndef _AUX_FUNCS
#define _AUX_FUNCS

char *strsep(char **stringp, const char *delim);

void seekBinary(char key[24], long str, long end, int* comp, bool* find, FILE *file);

int binarySearchCleaner(cleaner array[], char x[24], int low, int high);

void insertSortedCleaner(cleaner array[], int *size, const char *newKey);

void quickSortData(dataOrd array[], int low, int high);

void quickSortIndex(index array[], int low, int high);

#endif

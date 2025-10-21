#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "headers/auxFuncs.h"

char *strsep(char **stringp, const char *delim) {
    if (*stringp == NULL) return NULL;

    char *start = *stringp;
    char *p = start;

    // percorre até encontrar um delimitador ou fim da string
    while (*p) {
        if (strchr(delim, *p)) {
            *p = '\0';         // substitui delimitador por terminador '\0'
            *stringp = p + 1;  // avança o ponteiro original
            return start;      // retorna o token
        }
        p++;
    }

    // não encontrou delimitador: último token
    *stringp = NULL;
    return start;
}

void seekBinary(char key[24], long str, long end, int* comp, bool* find, FILE *file) {

  long mid;
  char buffer[24];
    
  if (*find || str > end) return;

  mid = str + (end - str) / 2;
  
  fseek(file, (mid*48), SEEK_SET);
  fread(buffer, sizeof(buffer), 1, file);
  (*comp)++;
  
  if (strcmp(buffer, key) == 0) {
    *find = true;
    return;
  } else if (strcmp(buffer, key) > 0) {
    seekBinary(key, str, mid - 1, comp, find, file);
  } else {
    seekBinary(key, mid + 1, end, comp, find, file);
  }

  return;
}

int binarySearchCleaner(cleaner array[], char x[24], int low, int high) {
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (strcmp(x, array[mid].key) == 0)
      return mid;

    if (strcmp(x, array[mid].key) > 0)
      low = mid + 1;

    else
      high = mid - 1;
  }

  return -1;
}

void insertSortedCleaner(cleaner array[], int *size, const char *newKey) {

  if (*size >= 40000) {
    printf ("Erro: vetor cheio ao inserir %s\n", newKey);
    return;
  }
  
  int i = *size - 1;

  while (i >= 0 && strcmp(array[i].key, newKey) > 0) {
      strncpy(array[i + 1].key, array[i].key, sizeof(array[i + 1].key));
      i--;
  }

  strncpy(array[i + 1].key, newKey, sizeof(array[i + 1].key));
  
  array[i + 1].key[sizeof(array[i + 1].key) - 1] = '\0';
  (*size)++;
}

void swapD(dataOrd *a, dataOrd *b) {
  dataOrd t = *a;
  *a = *b;
  *b = t;
}

int partitionD(dataOrd array[], int low, int high) {

  char pivot[24];
  strncpy(pivot, array[high].key, sizeof(pivot)-1);

  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (strncmp(array[j].key, pivot, sizeof(array[j].key)) == -1) {
      i++;

      swapD(&array[i], &array[j]);
    }
  }

  swapD(&array[i + 1], &array[high]);
  
  return (i + 1);  
}

void quickSortData(dataOrd array[], int low, int high) {

  if (low < high) {

    int pi = partitionD(array, low, high);

    quickSortData(array, low, pi - 1);

    quickSortData(array, pi + 1, high);
  }
}

void swapI(index *a, index *b) {
  index t = *a;
  *a = *b;
  *b = t;
}

int partitionI(index array[], int low, int high) {

  char pivot[24];
  strncpy(pivot, array[high].key, sizeof(pivot)-1);

  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (strncmp(array[j].key, pivot, sizeof(array[j].key)) == -1) {
      i++;

      swapI(&array[i], &array[j]);
    }
  }

  swapI(&array[i + 1], &array[high]);
  
  return (i + 1);  
}

void quickSortIndex(index array[], int low, int high) {

  if (low < high) {

    int pi = partitionI(array, low, high);

    quickSortIndex(array, low, pi - 1);

    quickSortIndex(array, pi + 1, high);
  }
}

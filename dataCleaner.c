#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/auxFuncs.h"
#include "headers/dataCleaner.h"

void treatBJoias() {
  FILE* csvf = fopen("data/jewelry.csv", "r");
  FILE* auxcsvf = fopen("data/jewelry_treated.csv", "w");
 
  if (!csvf) {
    perror ("Falha ao abrir o arquivo(csvf joias)");
    return;
  }
  
  if (!auxcsvf) {
    perror ("Falha ao abrir o arquivo(auxcsvf joias)");
    return;
  }
  
  char control[180];
  cleaner *cleanList = malloc(40000 * sizeof(cleaner));
  int pos = 0;
  
  while (fgets(control, sizeof(control), csvf)) {
    control[strcspn(control, "\n")] = '\0';

    char aux[180];
    strncpy(aux, control, sizeof(aux));
    char *p = control;
    char *token;

    for (int i = 0; i < 3; i++) token = strsep(&p, ",");
    
    if ((binarySearchCleaner(cleanList, token, 0, pos-1))== -1) {
      insertSortedCleaner(cleanList, &pos, token);
      fprintf(auxcsvf, "%s\n", aux);
    }
  }

  free(cleanList);
  fclose(csvf);
  fclose(auxcsvf);
}

void treatBCompras() {
  FILE* csvf = fopen("data/jewelry.csv", "r");
  FILE* auxcsvf = fopen("data/purchases_treated.csv", "w");

  if (!csvf) {
    perror("Falha ao abrir o arquivo(csvf compras)");
    return;
  }
  
  if (!auxcsvf) {
    perror("Falha ao abrir o arquivo(auxcsvf compras)");
    return;
  }
  
  char control[180];
  cleaner *cleanList = malloc(40000 * sizeof(cleaner));
  int pos = 0;
  
  while (fgets(control, sizeof(control), csvf)) {
    control[strcspn(control, "\n")] = '\0';

    char aux[180];
    strncpy(aux, control, sizeof(aux));
    char *p = control;
    char *token;

    for (int i = 0; i < 2; i++) token = strsep(&p, ",");
    
    if ((binarySearchCleaner(cleanList, token, 0, pos)) == -1) {
      insertSortedCleaner(cleanList, &pos, token);
      fprintf(auxcsvf, "%s\n", aux);
    }
  }

  free(cleanList);
  fclose(csvf);
  fclose(auxcsvf);
}

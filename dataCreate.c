#include <stdio.h>
#include <string.h>
#include "headers/auxFuncs.h"
#include "headers/dataCreate.h"
#include "headers/dataOrdena.h"

void createBJoias() { 
  FILE* csvf = fopen("data/jewelry_treated.csv", "r");
  FILE* binfJoias = fopen("data/joias.bin", "w+b");

  if (!csvf) {
    perror ("falha ao abrir o arquivo(csvf joias)");
    return;
  }

  if (!binfJoias) {
    perror ("Falha ao abrir o arquivo(binfJoias joias)");
    return;
  }

  char control[180];
  int counter = 0;

  while (fgets(control, sizeof(control), csvf)) {
    counter = 0;
    control[strcspn(control, "\n")] = '\0';

    char *p = control;
    char buffer[24] = {0};
    strncpy(buffer, control, sizeof(buffer)-1);
    char *token;
    char elo[24] = {0};

    while ((token = strsep(&p, ",")) != NULL) {
      if (counter == 2 || counter == 5 || counter == 7) {
        strncpy(buffer, token, sizeof(buffer)-1);
        if (buffer[0] == '\0') strncpy(buffer, "INDEFINIDO", sizeof(buffer));
        fwrite(buffer, sizeof(buffer), 1, binfJoias);
      }
      counter++;
    }
    fwrite(elo, sizeof(elo), 1, binfJoias);
    fwrite(elo, sizeof(elo), 1, binfJoias);
  }
  fclose(csvf);
  fclose(binfJoias);

  dataOrdena("data/joias.bin");
}

void createBCompras() {
  FILE* csvf = fopen("data/purchases_treated.csv", "r");
  FILE* binfCompras = fopen("data/compras.bin", "w+b");

  if (!csvf) {
    perror ("Falha ao abrir o arquivo(csvf compras)");
    return;
  }

  if (!binfCompras) {
    perror ("Falha ao abrir o arquivo(binfCompras compras)");
    return;
  }

  char control[180];
  int counter = 0;

  while (fgets(control, sizeof(control), csvf)) {
    counter = 0;
    control[strcspn(control, "\n")] = '\0';

    char *p = control;
    char buffer[24] = {0};
    strncpy(buffer, control, sizeof(buffer)-1);
    char *token;
    char elo[24] = {0};

    while ((token = strsep(&p, ",")) != NULL) {
      if (counter == 1 || counter == 2 || counter == 9) {
        strncpy(buffer, token, sizeof(buffer)-1);
        if (buffer[0] == '\0') {
          if (counter == 9) {
            strncpy(buffer, "m", sizeof(buffer));
          } else strncpy(buffer, "INDEFINIDO", sizeof(buffer));
        }  
        fwrite(buffer, sizeof(buffer), 1, binfCompras);
      }
      counter++;
    }
    fwrite(elo, sizeof(elo), 1, binfCompras);
    fwrite(elo, sizeof(elo), 1, binfCompras);
  }
  fclose(csvf);
  fclose(binfCompras);

  dataOrdena("data/compras.bin");
}

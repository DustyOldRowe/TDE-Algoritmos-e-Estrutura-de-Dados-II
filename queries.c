#include "headers/queries.h"
#include "headers/auxFuncs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

long indexSearch(char *key, char *fileChar, char *indexChar1,
                 char *indexChar2, char *indexChar3) {

  FILE *file = fopen(fileChar, "rb");
  FILE *index1 = fopen(indexChar1, "rb");
  FILE *index2 = fopen(indexChar2, "rb");
  FILE *index3 = fopen(indexChar3, "rb");

  if (!file) {
    perror("Erro ao abrir arquivo(main)");
    return -1;
  }
  if (!index1) {
    perror("Erro ao abrir arquivo(indice 1)");
    return -1;
  }
  if (!index2) {
    perror("Erro ao abrir arquivo(indice 2)");
    return -1;
  }
  if (!index3) {
    perror("Erro ao abrir arquivo(indice 3)");
    return -1;
  }
  
  fseek(index1, 0, SEEK_END);
  long size1 = ftell(index1) / 48;
  rewind(index1);

  fseek(index2, 0, SEEK_END);
  long size2 = ftell(index2) / 48;
  rewind(index2);

  fseek(index3, 0, SEEK_END);
  long size3 = ftell(index3) / 48;
  rewind(index3);

  int comp = 0;
  bool find = false;
  char buffer[24];
  char registro[24];
  char end[24];
  char *ptr;
  long pos_inicio;
  long pos_ultimo;


  while (fread(buffer, sizeof(buffer), 1, index3)) {
    if (strcmp(key, buffer) <= 0) {
      fread(end, sizeof(end), 1, index3);
      pos_inicio = strtol(end, &ptr, 10);
      pos_ultimo = (pos_inicio + (10 - 1) * 48);

      fseek(index2, pos_inicio, SEEK_SET);

      while (fread(buffer, sizeof(buffer), 1, index2)) {
        long current = ftell(index2);
        if (strncmp(key, buffer, sizeof(buffer)) <= 0) {
          fread(end, sizeof(end), 1, index2);

          pos_inicio = strtol(end, &ptr, 10);
          pos_ultimo = (pos_inicio + (1000 - 1) * 48)+48;
          pos_inicio = pos_inicio / 48;
          pos_ultimo = pos_ultimo / 48;

          seekBinary(key, pos_inicio, pos_ultimo, &comp, &find, index1);

          printf ("Numero de Comparações: %d\n", comp);
       
          if (find == true) {
            fread(end, sizeof(end), 1, index1);
            long address = strtol(end, &ptr, 10);
            fclose(file);
            fclose(index1);
            fclose(index2);
            fclose(index3);
            printf ("DADO ENCONTRADO.\n");
            return address;
          } else {
           fclose(file);
           fclose(index1);
           fclose(index2);
           fclose(index3);
           printf ("DADO NÃO ENCONTRADO.\n");
           return -1;
          }
          
          break;
        }

      if (current > pos_ultimo) break;

      fseek(index2, 24, SEEK_CUR);
    } 

    break;
  }

  fseek(index2, 24, SEEK_CUR);

} 

  fclose(file);
  fclose(index1);
  fclose(index2);
  fclose(index3);

  return -1;
}

void joiasMaisCara() {
  FILE *file = fopen("data/joias.bin", "rb");

  if (!file) {
    perror ("Erro ao abrir o arquivo(joiasMaisCara)");
    return;
  }

  char buffer[24];
  char type[24];
  char dlt[24];
  char *ptr;
  fseek(file, 48, SEEK_SET);
  float highValue;
  float aux;

  while (fread(buffer, sizeof(buffer), 1, file)) {

    fseek(file, 24, SEEK_CUR);
    fread(dlt, sizeof(dlt), 1, file);
    if (strcmp(dlt, "ELIMINADO") != 0) {
      fseek(file, -48, SEEK_CUR);
      
      if (strcmp(buffer, "INDEFINIDO") != 0) aux = strtof(buffer, &ptr);

      if (aux > highValue) {
        highValue = aux;
        fseek(file, -48, SEEK_CUR);
        fread(buffer, sizeof(buffer), 1, file);
        strcpy(type, buffer);
        fseek(file, 24, SEEK_CUR);
      }
    }
    
    fseek(file, 96, SEEK_CUR);
  }

  printf ("A joia mais cara, do tipe %s, custa: R$%.2f\n", type, highValue);
}

void quantType(char *key) {
  FILE *file = fopen("data/joias.bin", "rb");
  
  if (!file) {
    perror ("Erro ao abrir o arquivo(quantType)");
    return;
  }

  char buffer[24];
  fseek(file, 24, SEEK_SET);
  int count = 0;
  char dlt[24];

  while (fread(buffer, sizeof(buffer), 1, file)) {

    fseek(file, 48, SEEK_CUR);
    fread(dlt, sizeof(dlt), 1, file);
    if (strcmp(dlt, "ELIMINADO") != 0) {
      fseek(file, -72, SEEK_CUR);
      
      if (strcmp(key, buffer) == 0) {
        count++;
      }
    }
    fseek(file, 96, SEEK_CUR);
  } 

  printf ("Quantidade de joias do tipo %s: %d\n", key, count); 
}

void demoGenero(char *key) {
  FILE *file = fopen("data/compras.bin", "rb");

  if (!file) {
    perror ("Erro ao abrir o arquivo(demoGenero)");
    return;
  }
  
  char buffer[24];
  char dlt[24];
  fseek(file, 48, SEEK_SET);
  int count = 0;
  
  while (fread(buffer, sizeof(buffer), 1, file)) {

    fseek(file, 24, SEEK_CUR);
    fread(dlt, sizeof(dlt), 1, file);
    if (strcmp(dlt, "ELIMINADO") != 0) {
      fseek(file, -48, SEEK_CUR);
    
      if (strcmp(key, buffer) == 0) {
        count++;
      }
    }
    
    fseek(file, 96, SEEK_CUR);
  } 

  printf ("Quantidade de usuarios do genero %s: %d\n", key, count); 
}

void mostrarDados(char *key) {
  FILE *file = fopen(key, "rb");

  if (!file) {
    perror("Erro ao abrir o arquivo(mostrarDados)");
    return;
  }

  char buffer[120];
  char temp[24];
  char dlt[24];
  int i = 0;
  int t = 0;
  long add = 0;
  char *ptr;

  while (fread(buffer, 24, 5, file)) {

    fseek(file, -24, SEEK_CUR);
    fread(dlt, sizeof(dlt), 1, file);
    if (strcmp(dlt, "ELIMINADO") != 0) {
      
      for (int i = 0; i < 5; i++) {
          printf("%.*s ", 24, buffer + (i * 24));
      }
      printf ("\n");

    }
  }
}

#include <stdio.h>
#include <string.h>
#include "headers/operacoes.h"
#include "headers/queries.h"
#include "headers/indiceStore.h"

void insertData(char *fileName, char *key, char *ele1, char *ele2,  char *indexChar1,
                char *indexChar2, char *indexChar3) {

  FILE *file = fopen(fileName, "r+b");
  
  if (!file) {
    perror("Erro ao abrir o arquivo(insertData)");
    return;
  }
  
  char buffer[24] = {0};
  char extra[24] = {0};
  long address = 0;
  fseek(file, 0, SEEK_END);
  long addLast = ftell(file);
  rewind(file);

  if (indexSearch(key, fileName, indexChar1, indexChar2, indexChar3) == -1) {
    while (fread(buffer, sizeof(buffer), 1, file)) {
      
      if (strncmp(key, buffer, sizeof(buffer)) < 0) {
        address = ftell(file)-24;
        fseek(file, -72, SEEK_CUR);

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%ld", addLast);
        fwrite(buffer, sizeof(buffer), 1, file);

        fclose(file);
        
        break;
      }
      
      fseek(file, 96, SEEK_CUR);
    }

    file = fopen(fileName, "a+b");

    if (!file) {
      perror("Erro ao abrir o arquivo(insertData second)");
      return;
    }
    
    strcpy(buffer, key);
    fwrite(buffer, sizeof(buffer), 1, file);
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, ele1);
    fwrite(buffer, sizeof(buffer), 1, file);
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, ele2);
    fwrite(buffer, sizeof(buffer), 1, file);
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%ld", address);
    fwrite(buffer, sizeof(buffer), 1, file);
    fwrite(extra, sizeof(extra), 1, file);
    
    fclose(file);
    
    if (strcmp(indexChar1, "data/joias_indice.bin") == 0) {
      indiceJoias();
    } else {
      indiceCompras();
    }
  }

  fclose(file);
}

void removeData(char *fileName, char *key, char *indexChar1,
                char *indexChar2, char *indexChar3) {
  
  FILE *file = fopen(fileName, "r+b");

  if (!file) {
    perror("Erro ao abrir o arquivo(removeData)");
    return;
  }
  
  char buffer[24] = {0};
  strcpy(buffer, "ELIMINADO");
  long address = indexSearch(key, fileName, indexChar1, indexChar2, indexChar3);
  
  if (address != -1) {
    fseek(file, (address)+96, SEEK_SET);
    fwrite(buffer, sizeof(buffer), 1, file);

    FILE *index = fopen(indexChar1, "rb");
    FILE *indexNew = fopen("data/temporary.bin", "wb");

    if (!index) {
      perror("Erro ao abrir o arquivo(removeData index)");
      return;
    }

    if (!indexNew) {
      perror("Erro ao abrir o arquivo(removeData indexNew)");
      return;
    }

    while (fread(buffer, sizeof(buffer), 1, index)) {
      if (strcmp(key, buffer) != 0) {
        fwrite(buffer, sizeof(buffer), 1, indexNew);
      } else fseek(index, 24, SEEK_CUR);
    }

    fclose(index);
    fclose(indexNew);
    
    if (remove(indexChar1) == 0) {
      if (rename("data/temporary.bin", indexChar1) != 0) {
        perror("Erro ao renomear arquivo novo.");
        return;
      } 
    } else {
      perror("Erro ao deletar arquivo antigo.");
      return;
    }
    printf ("Valor removido.\n");
  } else printf ("Valor não encontrado.\n");

  fclose(file);
}

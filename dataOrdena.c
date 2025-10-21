#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/dataOrdena.h"
#include "headers/auxFuncs.h"

void dataOrdena(char fileName[]) {
  FILE* binfNew = fopen("data/Auxiliary.bin", "wb");
  FILE* binf = fopen(fileName, "rb");

  if (!binfNew) {
    perror ("Erro na leitura de binfNew(ordenação)");
    return;
  }
  
  if (!binf) {
    perror ("Erro na leitura de binf(ordenação)");
    return;
  }

  fseek(binf, 0, SEEK_END);
  long size = ftell(binf);
  rewind(binf);
  
  size_t total_registros = size / sizeof(dataOrd);
  
  dataOrd *array = malloc(total_registros * sizeof(dataOrd));

  if(!array) {
    perror("Erro ao alocar memoria!");
    return;
  }

  size_t lidos = fread(array, sizeof(dataOrd), total_registros, binf);
  if (lidos != total_registros) {
    fprintf (stderr, "Aviso(data): esperava %zu registros, mas li %zu.\n",
             total_registros, lidos);
  }

  quickSortData(array, 0, total_registros -1);

  char buffer[24] = {0};
 
  for (size_t i = 0; i < lidos; i++) {
    strncpy(buffer, array[i].key, sizeof(buffer)-1);
    fwrite(buffer, sizeof(buffer), 1, binfNew);
    
    strncpy(buffer, array[i].secondCamp, sizeof(buffer)-1);
    fwrite(buffer, sizeof(buffer), 1, binfNew);
    
    strncpy(buffer, array[i].thirdCamp, sizeof(buffer)-1);
    fwrite(buffer, sizeof(buffer), 1, binfNew);
    
    strncpy(buffer, array[i].elo, sizeof(buffer)-1);
    fwrite(buffer, sizeof(buffer), 1, binfNew);
    
    strncpy(buffer, array[i].del, sizeof(buffer)-1);
    fwrite(buffer, sizeof(buffer), 1, binfNew);
  }

  fclose(binf);
  fclose(binfNew);
  
  if (remove(fileName) == 0) {
    if (rename("data/Auxiliary.bin", fileName) != 0) {
      perror("Erro ao renomear arquivo novo");
      return;
    } 
  } else {
    perror("Erro ao deletar arquivo antigo");
    return;
  }
}

void indiceOrdena(char fileName[]) {

  FILE* binfNew = fopen("data/Auxiliary.bin", "wb");
  FILE* binf = fopen(fileName, "rb");
  
  if (!binfNew) {
    perror ("Erro na leitura de binfNew(ordenação)");
    return;
  }
  
  if (!binf) {
    perror ("Erro na leitura de binf(ordenação)");
    return;
  }

  fseek(binf, 0, SEEK_END);
  long size = ftell(binf);
  rewind(binf);
  
  size_t total_registros = size / sizeof(index);
  
  index *array = malloc(total_registros * sizeof(index));

  if(!array) {
    perror("Erro ao alocar memoria!");
    return;
  }

  size_t lidos = fread(array, sizeof(index), total_registros, binf);
  if (lidos != total_registros) {
    fprintf (stderr, "Aviso(index): esperava %zu registros, mas li %zu.\n",
             total_registros, lidos);
  }

  quickSortIndex(array, 0, total_registros-1);

  char buffer[24] = {0};
  
  for (size_t i = 0; i < lidos; i++) {
    strncpy(buffer, array[i].key, sizeof(buffer)-1);
    fwrite(buffer, sizeof(buffer), 1, binfNew);
    
    strncpy(buffer, array[i].address, sizeof(buffer)-1);
    fwrite(buffer, sizeof(buffer), 1, binfNew);
  }

  fclose(binf);
  fclose(binfNew);
  
  if (remove(fileName) == 0) {
    if (rename("data/Auxiliary.bin", fileName) != 0) {
      perror("Erro ao renomear arquivo novo");
      return;
    } 
  } else {
    perror("Erro ao deletar arquivo antigo");
    return;
  }
}

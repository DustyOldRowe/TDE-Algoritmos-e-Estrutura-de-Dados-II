#include <stdio.h>
#include <string.h>
#include "headers/indiceStore.h"
#include "headers/dataOrdena.h"
#include "headers/StructVendas.h"

void indiceLvl2(FILE* file, const char* fileName) { 
  FILE* indexlvl2 = fopen(fileName, "wb");

  if (!indexlvl2) {
    perror("Erro ao abrir o arquivo(indicelvl2)");
    return;
  }

  unsigned long reg_size = 48;
  unsigned long reg_per_block = 1000;
  unsigned long block_size = (reg_size * reg_per_block);
  
  fseek(file, 0, SEEK_END);
  unsigned long size = ftell(file) / block_size;
  fseek(file, 0, SEEK_SET);
 
  char buffer[24] = {0};

  unsigned int end = 0;
  unsigned long pos_inicio, pos_ultimo;

  for (unsigned long i = 0; i <= size; i++) {
    pos_inicio = i * block_size;
    pos_ultimo = pos_inicio + (reg_per_block - 1) * reg_size;

    fseek(file, pos_ultimo, SEEK_SET);
    if (fread(buffer, sizeof(buffer), 1, file) != 1) {
      fseek(file, -48, SEEK_END);
      fread(buffer, sizeof(buffer), 1, file);
     
      fwrite(buffer, sizeof(buffer), 1, indexlvl2);
      memset(buffer, 0, sizeof(buffer));
      snprintf(buffer, sizeof(buffer), "%lu", pos_inicio);
      fwrite(buffer, sizeof(buffer), 1, indexlvl2);
      
      break;
    }
    
    fwrite(buffer, sizeof(buffer), 1, indexlvl2);
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%lu", pos_inicio);
    fwrite(buffer, sizeof(buffer), 1, indexlvl2);
  }

  fclose(indexlvl2);
} 

void indiceLvl3(FILE* file, const char* fileName) { 
  FILE* indexlvl3 = fopen(fileName, "wb");

  if (!indexlvl3) {
    perror("Erro ao abrir o arquivo(indiceLvl3)");
    return;
  }

  unsigned long reg_size = 48;
  unsigned long reg_per_block = 10;
  unsigned long block_size = (reg_size * reg_per_block);
  
  fseek(file, 0, SEEK_END);
  unsigned long size = ftell(file) / block_size;
  fseek(file, 0, SEEK_SET);
 
  char buffer[24] = {0};

  unsigned int end = 0;
  unsigned long pos_inicio, pos_ultimo;

  for (unsigned long i = 0; i <= size; i++) {
    pos_inicio = i * block_size;
    pos_ultimo = pos_inicio + (reg_per_block - 1) * reg_size;

    fseek(file, pos_ultimo, SEEK_SET);
    if (fread(buffer, sizeof(buffer), 1, file) != 1) {
      fseek(file, -48, SEEK_END);
      fread(buffer, sizeof(buffer), 1, file);
     
      fwrite(buffer, sizeof(buffer), 1, indexlvl3);
      memset(buffer, 0, sizeof(buffer));
      snprintf(buffer, sizeof(buffer), "%lu", pos_inicio);
      fwrite(buffer, sizeof(buffer), 1, indexlvl3);
      
      break;
    }
    
    fwrite(buffer, sizeof(buffer), 1, indexlvl3);
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%lu", pos_inicio);
    fwrite(buffer, sizeof(buffer), 1, indexlvl3);
  }

  fclose(indexlvl3);
}
 
void indiceJoias() {
  FILE* binf = fopen("data/joias.bin", "rb");
  FILE* joiasIndice = fopen("data/joias_indice.bin", "w+b");
  
  if (!binf) {
    perror("Erro ao abrir arquivo(indiceJoias, binf)");
    return;
  }
  
  if (!joiasIndice) {
    perror("Erro ao abrir arquivo(indiceJoias, joiasIndice)");
    return;
  }

  char buffer[24] = {0};

  fseek(binf, 0, SEEK_END);
  unsigned int pos;
  rewind(binf);

  while (fread(buffer, sizeof(buffer), 1, binf)) {
    pos = ftell(binf) -24;

    fwrite (buffer, sizeof(buffer), 1, joiasIndice);
    
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%u", pos);
    fwrite(buffer, sizeof(buffer), 1, joiasIndice);

    fseek(binf, 96, SEEK_CUR);
  }
  
  fclose(binf);
  fclose(joiasIndice);

  indiceOrdena("data/joias_indice.bin");

  joiasIndice = fopen("data/joias_indice.bin", "rb");
  
  if (!joiasIndice) {
    perror("Erro ao abrir arquivo(indiceJoias, joiasIndice second)");
    return;
  }
  
  indiceLvl2(joiasIndice, "data/joias_indice_lvl2.bin");

  FILE* indicelvl2 = fopen("data/joias_indice_lvl2.bin", "rb");
  
  if (!indicelvl2) {
    perror("Erro ao abrir arquivo(indiceJoias, indicelvl2)");
    return;
  }

  indiceLvl3(indicelvl2, "data/joias_indice_lvl3.bin");

  fclose(indicelvl2);
  fclose(joiasIndice);
}

void indiceCompras() {
  FILE* binf = fopen("data/compras.bin", "rb");
  FILE* comprasIndice = fopen("data/compras_indice.bin", "w+b");

  if (!binf) {
    perror("Erro ao abrir arquivo(indiceCompras, binf)");
    return;
  }
  
  if (!comprasIndice) {
    perror("Erro ao abrir arquivo(indiceCompras, comprasIndice)");
    return;
  }

  char buffer[24] = {0};

  fseek(binf, 0, SEEK_END);
  unsigned int pos;
  rewind(binf);

  while (fread(buffer, sizeof(buffer), 1, binf)) {
    pos = ftell(binf) -24;

    fwrite (buffer, sizeof(buffer), 1, comprasIndice);
    
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%u", pos);
    fwrite(buffer, sizeof(buffer), 1, comprasIndice);

    fseek(binf, 96, SEEK_CUR);
  }
  fclose(binf);
  fclose(comprasIndice);

  indiceOrdena("data/compras_indice.bin");

  comprasIndice = fopen("data/compras_indice.bin", "rb");
  
  if (!comprasIndice) {
    perror("Erro ao abrir arquivo(indiceCompras, comprasIndice second)");
    return;
  }
  
  indiceLvl2(comprasIndice, "data/compras_indice_lvl2.bin");

  FILE* indicelvl2 = fopen("data/compras_indice_lvl2.bin", "rb");
  
  if (!indicelvl2) {
    perror("Erro ao abrir arquivo(indiceCompras, indicelvl2)");
    return;
  }

  indiceLvl3(indicelvl2, "data/compras_indice_lvl3.bin");
  
  fclose(indicelvl2);
  fclose(comprasIndice);
}

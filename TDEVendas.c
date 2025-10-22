#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "headers/dataCleaner.h"
#include "headers/dataCreate.h"
#include "headers/dataOrdena.h"
#include "headers/indiceStore.h"
#include "headers/operacoes.h"
#include "headers/queries.h"
#include "headers/auxFuncs.h"

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

void loadData() {

  printf ("== INICIALIZANDO ==\n");
  
  if (access("data/jewelry_treated.csv", F_OK) != 0) {
    printf ("ARQUIVO TRATADO DE JOIAS NÃO ENCONTRADO. GERANDO.\n");
    treatBJoias();
  } else {
    printf ("ARQUIVO TRATADO DE JOAIS ENCONTRADO. SEGUINDO.\n");
  }
  
  if (access("data/purchases_treated.csv", F_OK) != 0) {
    printf ("ARQUIVO TRATADO DE COMPRAS NÃO ENCONTRADO. GERANDO.\n");
    treatBCompras();
  } else {
    printf ("ARQUIVO TRATADO DE COMPRAS ENCONTRADO. SEGUINDO.\n");
  }

  if (access("data/joias.bin", F_OK) != 0) {
    printf ("ARQUIVO DE JOIAS NÃO ENCONTRADO. GERANDO.\n");
    createBJoias();
  } else {
    printf ("ARQUIVO DE JOIAS ENCONTRADO. SEGUINDO.\n");
  }
  
  if (access("data/compras.bin", F_OK) != 0) {
    printf ("ARQUIVO DE COMPRAS NÃO ENCONTRADO. GERANDO.\n");
    createBCompras();
  } else {
    printf ("ARQUIVO DE COMPRAS ENCONTRADO. SEGUINDO.\n");
  }

  if (access("data/joias_indice.bin", F_OK) != 0) {
    printf ("ARQUIVO DE INDICE PARA JOIAS NÃO ENCONTRADO. GERANDO\n");
    indiceJoias();
  } else {
    printf ("ARQUIVO INDICE PARA JOIAS ENCONTRADO. SEGUINDO.\n");
  }
  
  if (access("data/compras_indice.bin", F_OK) != 0) {
    printf ("ARQUIVO DE INDICE PARA COMPRAS NÃO ENCONTRADO. GERANDO\n");
    indiceCompras();
  } else {
    printf ("ARQUIVO INDICE PARA COMPRAS ENCONTRADO. SEGUINDO.\n");
    
  }
}

int main() {
  
  loadData();
  
  int option;
  char choice[24];
  char joia[24], preco[24];
  char codOut[24], gnr[24];
  char buffer[120];
  long add = 0;
  FILE *file;

  do {
    printf("\nPROTOTIPO PROJETO DADOS\n");
    printf("1 - MOSTRAR JOIA MAIS CARA\n");
    printf("2 - MOSTRAR QUANTIDADE DE UM TIPO DE JOIA\n");
    printf("3 - MOSTRAR DEMOGRAFIA DE COMPRAS SEGUNDO SEXO\n");
    printf("4 - MOSTRAR TODOS OS DADOS DE JOIAS\n");
    printf("5 - MOSTRAR TODOS OS DADOS DE COMPRAS\n");
    printf("6 - PESQUISAR ENTRADA EM JOIAS\n");
    printf("7 - PESQUISAR ENTRADA EM COMPRAS\n");
    printf("8 - INSERIR DADOS EM JOIAS\n");
    printf("9 - INSERIR DADOS EM COMPRAS\n");
    printf("10 - REMOVER DADOS DE JOIAS\n");
    printf("11 - REMOVER DADOS DE COMPRAS\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &option);
    getchar();

    switch(option) {
      case 1:
        joiasMaisCara();

      break;
      case 2:
        printf ("Insira tipo de joias que estas buscando: \n" 
                "(opções: electronics.clocks, jewelry.pendant,\n"
                "jewelry.necklace, jewelry.earring,\n"
                "jewelry.ring, jewelry.bracelet,\n"
                "jewelry.souvenir, jewelry.brooch)\n");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        quantType(choice);

      break;
      case 3:
        printf("Insira o genero que estar buscando: \n"
               "(opções: f, m)\n");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';

        demoGenero(choice);

      break;
      case 4:
        mostrarDados("data/joias.bin");

      break;
      case 5:
        mostrarDados("data/compras.bin");

      break;
      case 6:
        printf ("Insira codigo da entrada que queres buscar: \n"
                "(modelo: 1839772374128394799)\n");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        
        add = indexSearch(choice, "data/joias.bin", "data/joias_indice.bin", 
         "data/joias_indice_lvl2.bin", "data/joias_indice_lvl3.bin");

        if (add != -1) {
          file = fopen("data/joias.bin", "rb");
          fseek(file, add, SEEK_SET);
          fread(buffer, 24, 5, file);
          
          for (int i = 0; i < 5; i++) {
              printf("%.*s ", 24, buffer + (i * 24));
          }
        }
        fclose(file);

      break;
      case 7:
        printf ("Insira codigo da entrada que queres buscar: \n"
                "(modelo: 1839772374128394799)\n");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        
        add = indexSearch(choice, "data/compras.bin", "data/compras_indice.bin", 
         "data/compras_indice_lvl2.bin", "data/compras_indice_lvl3.bin");
        
        if (add != -1) {
          file = fopen("data/compras.bin", "rb");
          fseek(file, add, SEEK_SET);
          fread(buffer, 24, 5, file);
          
          for (int i = 0; i < 5; i++) {
              printf("%.*s ", 24, buffer + (i * 24));
          }
        }
        fclose(file);

      break;
      case 8:
        printf ("Insira codigo da nova entrada: \n"
                "(modelo: 1839772374128394799)\n");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        
        printf ("Insira o tipo de joia da nova entrada: \n"
                "(modelo: electronics.clocks, jewelry.pendant)\n");
        fgets(joia, sizeof(joia), stdin);
        joia[strcspn(joia, "\n")] = '\0';
        
        printf ("Insira o preço da nova entrada: \n"
                "(modelo: 1000.99)\n");
        fgets(preco, sizeof(preco), stdin);
        preco[strcspn(preco, "\n")] = '\0';
        
        insertData("data/joias.bin", choice, joia, preco, 
                   "data/joias_indice.bin", "data/joias_indice_lvl2.bin", 
                   "data/joias_indice_lvl3.bin");

      break;
      case 9:
        printf ("Insira codigo da nova entrada: \n"
                "(modelo: 1839772374128394799)\n");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        
        printf ("Insira o codigo externo da nova entrada: \n"
                "(modelo: 1839772374128394799)\n");
        fgets(codOut, sizeof(codOut), stdin);
        codOut[strcspn(codOut, "\n")] = '\0';
        
        printf ("Insira o genero do comprador da nova entrada: \n"
                "(modelo: f ou m)\n");
        fgets(gnr, sizeof(gnr), stdin);
        gnr[strcspn(gnr, "\n")] = '\0';
        
        insertData("data/compras.bin", choice, codOut, gnr, 
                   "data/compras_indice.bin", "data/compras_indice_lvl2.bin", 
                   "data/compras_indice_lvl3.bin");

      break;
      case 10:
        printf ("Insira codigo da entrada que deseja remover: \n"
                "(modelo: 1839772374128394799)\n");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        
        removeData("data/joias.bin", choice, "data/joias_indice.bin", 
                   "data/joias_indice_lvl2.bin", "data/joias_indice_lvl3.bin");

      break;
      case 11:
        printf ("Insira codigo da entrada que deseja remover: \n"
                "(modelo: 1839772374128394799)\n");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        
        removeData("data/compras.bin", choice, "data/compras_indice.bin", 
                   "data/compras_indice_lvl2.bin", "data/compras_indice_lvl3.bin");

      break;
      case 0:
        option = 0;

      break;
    }
  } while (option != 0);
  
  return 1;
}

# TDE-Algoritmos-e-Estrutura-de-Dados-II
Trabalho 1 para a materia de Algoritmos e Estrutura de Dados II.

## loadData()
```
Arquivo TDEVendas.c (main)
```
A função loadData() testa a existencia dos arquivos necessarios para a operação do codigo, e se não existem chama as funções para criação destes

## treatBJoias() e treatBCompras
```
Arquivo dataCleaner.c
```
Ambas funções recebem o arquivo .csv base e tratam ele, removendo chaves repetidas para cada conjunto de dados desejado, para isso eles guardam a chave de cada entrada inserida no arquivo tratado em um array ordenaod em memoria, conferindo a existencia da nova chave por meio de pesquisa binaria, se não existe, ela é gravada no arquivo de saída e guardada no array em memoria para conferir na proxima iteração.

## createBJoias() e createBCompras()
```
Arquivo dataCreate.c
```
Funções para criar os arquivos binaarios de dados. Chama diretamente a função dataOrdena().

## indiceJoias() e indiceCompras()
```
Arquivo indiceStore.c
```
Funções para criar os indices extensivos de ambos os arquivos de dados. Chama diretamente a função indiceOrdena().
### indiceLvl2() e indiceLvl3()
Funções para criar os indices parciais sobre o indice extensivo de cada arquivo de dados.

Indice de nivel 2 guarda blocos de 1000 entradas do indice extensivo, já o indice de nivel 3 guarda blocos de 10 entradas do indice de nivel 2.

## dataOrdena() e indiceOrdena()
```
Arquivo dataOrdena.c
```
Funções para ordenar os arquivos de dados e indices, respectivamente. Lêem todo o conteudo dos arquivos binarios e os guardam em um array em memoria, para então realizar um quick sort sobre esse array atráves da função quickSortIndex() (`Arquivo auxFuncs.c`), então escreve esse array ordenado em um arquivo auxiliar, terminando por excluir o arquivo de dados/indice original e renomeando esse novo ordenado para o mesmo nome do arquivo original.

##joiasMaisCara()
```
Arquivo queries.c
```
Faz a leitura extensido do arquivo de dados `joias.c` procurando pela joia de valor mais caro, escrevendo seu tipo e valor no fim da função.

## quantType()
```
Arquivo queries.c
```
Lê do usuario um tipo de joia, faz a leitura extensido do arquivo de dados `joias.c`, incrementando um contador sempre que encontra um registro daquele tipo de joia, escrevendo o numero final no fim da função.

## demoGenero()
```
Arquivo queries.c
```
Lê do usuario um tipo um caractere representante dos generos registrados, faz a leitura extensido do arquivo de dados `compras.c`, incrementando um contador sempre que encontra um registro daquele genero, escrevendo o numero final no fim da função.

## mostrarDados()
```
Arquivo queries.c
```
Imprime todos os registros de um arquivo de dados em ordem física. Ignora registros considerados deletados.

## indexSearch()
```
Arquivo queries.c
```
Faz a busca de um registro, atráves de um codigo inserido pelo usuario, no arquivo de dados.

Primeiramente busca o arquivo de index de terceiro nivel, procurando o bloco do arquivo de index de segundo nivel que esse registro estaria presente, em seguida faz esse mesmo processo para o arquivo de index de segundo nivel e primeiro nivel, por fim faz a pesquisa binaria no bloco identificado do arquivo de index de primeiro nivel, se o valor for encontrado será feita a leitura do endereço fisico guardado naquela posição do arquivo de index de primeiro nivel, então usando de fseek() para recuperar/encontrar o registro buscado no arquivo de dados.

## insertData()
```
Arquivo operacoes.c
```
Essa função faz a inserção de novas entradas nos arquivos de dados.

O usuario deve inserir as informações pertinentes para cada arquivo de dados antes da função ser chamada.
Primeiramente ela chama a função indexSearch() para saber se a chave inserida pelo usuario já existe no arquivo de dados. Confirmada sua inexistencia ele vai percorrer o arquivo de dados extensivamente para conferir se a nova chave deve ser inserida no meio do arquivo, caso seja o caso, na porção de bytes reservada para elo se insere a posição fisica para o fim do arquivo, após isso é feita a acrescentação da nova entrada no final do arquivo.
Os arquivos de indice são refeitos por completo em cada adição de um novo registro.

- Funcionalidade para atualizar elo em caso de novas adições, infelizmente, não foi implementada(eu não soube como).

## removeData()
```
Arquivo operacoes.c
```
Essa função faz a remoção lógica de registros dos arquivos de dados.

O usuario deve inserir a chave do registro que deseja deletar.
Primeiramente é procurado o endereço do registro que se deseje deletar, isto é feito através da função indexSearch(), caso o registro seja encontrado, é escrito na porção de bytes reservado para a remoção logica a palavra "ELIMINADO", registrando que aquele registro é para ser ignorado. Após isso, o registro é removido dos arquivos de indice, realizando isso após cada operação de remoção.

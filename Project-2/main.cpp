// "Copyright [2016] <Gustavo Olegário>"
// "Copyright [2016] <Otto Pires>"

#include <stdio.h>
#include <cstring>
#include "Word_Index.h"
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>

void generate_dat(int argc, char* argv[]);
ListaDupla<int> man_pages_positions(char* palavra);
void search_by_one_word();
void search_by_two_words();
void search_by_command();

static const int size_max_word = 100;
static const int size_max_command = 100;
static const int size_max_content = 149900;
static const int amount_connectives = 25;
static const char* connectives[] = {
    "a","the","and","or","if","of","to","into","by","for","on","at","in","next",
    "then","than","more","only","always","never","all","off","with","that",
    "this",""
};

// Menu de opções

int main(int argc, char* argv[]) {
    int input;
    //INICIA MENU
    do {
        printf("\n");
        printf("Please, type an option: \n");
        printf("(1) - Generate .dat\n");
        printf("(2) - Search by commnad\n");
        printf("(3) - Search by one word\n");
        printf("(4) - Search by two words\n");
        printf("(0) - Exit\n");
        scanf("%d",&input);
        switch (input) {
            case 1: generate_dat(argc, argv); break;
            case 2: search_by_command(); break;
            case 3: search_by_one_word(); break;
            case 4: search_by_two_words(); break;
        }
    } while(input != 0);
}

/**
 * Recebe os argumentos da execução do programa, que devem ter a quantidade de
 * argumentos e o nome dos arquivos a serem processados.
 * Gera o arquivo "manpages.dat" que contém os nomes dos arquivos originais
 * e seus conteúdos, formatados com um tamanho máximo padrão para facilitar
 * a busca utilizando um índice
 * Durante a geração de "manpages.dat":
 *      é criada duas Listas do tipo Word_Index, onde serão guardadas
 as palavras e os indices onde mais tarde faremos as buscas.
 * Gera o "indices.dat" que é a lista de "Index"s organizada em níveis,
 * que facilitará a busca
 * Gera o "words.dat" que é lista de "Words"s organizada em níveis.
 *
 * As palavras são obtidas separando o texto original pelos seguintes
 * caracteres: " \n.,|`´^~<>:;_-+=()[]\"!@#"
 * Os conectivos são retirados utilizando o array de palavras "connectives"
 */
void generate_dat(int argc1, char* argv[]) {
    ListaDupla<Word_Index> indices;
    ListaDupla<Word_Index> palavras;
    char command[size_max_command];
    printf("----%d------", argc1);

    //-----------Começa MANPAGES.DAT----------------//
    FILE *manPagesDat;
    manPagesDat = fopen("..\\manpages.dat", "wb");
    printf("Generating manpages.dat ...\n");

    for(int i = 1; i < argc1; i++) {
        //Abre e le cada arquivo de manpage
        FILE *manPageF;
        manPageF = fopen(argv[i], "r");
        if (manPageF == NULL) perror ("Error open file");

        printf("%d - Openned %s\n", i, argv[i]);

        /* Gera o nome do comando a partir do nome do arquivo, tirando
         * tirando a extensão .txt, e coloca em "command" */

        std::string name = argv[i];
        int init = name.find_last_of('/')+1;
        int end = name.find_last_of('.');
        std::string commandName = name.substr(init, end-init);

        strcpy(command, commandName.c_str());

        //Lê o conteudo do arquivo e coloca em "content"
        char content[size_max_content];

        int j;
        for(j = 0; !feof(manPageF); j++) {
            content[j] = fgetc(manPageF);
        }

        content[j-1] = '\0';
        //Fecha o arquivo atual
        fclose(manPageF);

        bool final_char = false;
        //Escreve comando em manpages.dat
        for(j = 0; j < size_max_command; j++) {
            if(final_char)
                fputc(' ', manPagesDat);
            else {
                if(command[j] == '\0') {
                    final_char = true;
                    fputc('\0', manPagesDat);
                } else
                    fputc(command[j], manPagesDat);
            }
        }

        //Escreve conteúdo em manpages.dat
        for(j = 0; j < size_max_content; j++) {
            fputc(content[j], manPagesDat);
        }

        //---------Montagem da lista de palavras-----------//
        char *word = strtok(content, " \n.,|`´^~<>:;_-+=()[]\"'/*!@#");
        while(word != 0) {
            Word_Index current(word, i-1);
            palavras.adicionaNoInicioDuplo(current);
            word = strtok(0," \n.,|`´^~<>:;_-+=()[]\"'/*!@#");
        }

        /* Adiciona o arquivo e seu indice na lista de indice principal
         * "i=1" corresponde a posição que foi salvo o registro do comando
         * em manpages.dat */
        Word_Index manPage;
        strcpy(manPage.word, command);
        manPage.positions.adicionaNoInicioDuplo(i-1);
        indices.adicionaNoInicioDuplo(manPage);
    }
    //Fecha manPagesDat
    fclose(manPagesDat);
    printf("Finalizing manpages.dat\n");

    ///////////////////////////////////
    ///// TERMINOU A MANPAGES.DAT
    ///////////////////////////////////
    ///// COMEÇA A INDICES.DAT
    ///////////////////////////////////

    Word_Index* indicesOrdenados = nullptr;
    for (int i = 0; i < indices.verUltimo(); ++i) {
      indicesOrdenados[i] = indices.retiraDoInicioDuplo();
    }
    printf("Organizing by level\n");

    //Cria o arquivo indices.dat para escrita
    FILE* indicesDat;
    indicesDat = fopen("..\\indices.dat", "wb");

    printf("Starting to generate indices.dat ...\n");

    //Percorre cada indice do array
    for(int i = 0; i < indices.verUltimo(); i++) {
        //coloca os valores que serão passados para o arquirvo em comando

        //indicesOrdenados[i] = indices.retiraDoInicioDuplo();
        strcpy(command, indicesOrdenados[i].word);

        printf("%d - %s\n",(i+1), command);
        //int position = indicesOrdenados[i].positions.retiraDoInicioDuplo();
        //troca os 4 ultimos bytes de comando, guardando a posição
        //*((int*)&command[96]) = position;

        for(int j = 0; j < size_max_command; j++) {
            fputc(command[j], indicesDat);
        }
    }
    delete indicesOrdenados;
    fclose(indicesDat);
    printf("Finalizado a geração de indices.dat\n");

    ///////////////////////////////////
    ///// TERMINA A INDICES.DAT
    ///////////////////////////////////
    ///// COMEÇA O PALAVRAS.DAT
    ///////////////////////////////////

    FILE* palavrasDat;
    palavrasDat = fopen("..\\palavras.dat", "wb");
    printf("Starting to genrate palavras.dat\n");

    //Exclui connectives da lista para agilizar processo de busca
    for(int i = 0; i < amount_connectives; i++) {
        char connective[100];
        strcpy(connective, connectives[i]);
        palavras.retiraEspecificoDuplo(Word_Index(connective, 0));
    }

    //Gera array de palavras para inserção
    Word_Index* palavrasOrdenadas = nullptr;
    for (int i = 0; i < palavras.verUltimo(); ++i) {
      palavrasOrdenadas[i] = palavras.retiraDuplo();
    }
    printf("Gerou palavras ordenadas\n");

    //Escreve quantidade de palavras
    int maxSize = palavras.verUltimo();
    char maxSizeW[4];
    *((int*)&maxSizeW[0]) = maxSize;
    for(int i = 0; i < 4; i++) {
        fputc(maxSizeW[i], palavrasDat);
    }

    /* Escreve palavras seguidas do inicio de local das posicoes, e a
     * quantidade de posiçoes */
    int position = 0;
    for(int i = 0; i < maxSize; i++) {
        Word_Index current = palavrasOrdenadas[i];
        printf("%d - %s\n",i, current.word);
        *((int*)&current.word[92]) = position;
        int qtd = current.positions.verUltimo();
        *((int*)&current.word[96]) = qtd;
        for(int i = 0; i < 100; i++) {
            fputc(current.word[i], palavrasDat);
        }
    }
    //Escreve as posições das manpages que contem as palavras
    char pos[4];
    for(int i = 0; i < maxSize; i++) {
        Word_Index current = palavrasOrdenadas[i];
        while(!current.positions.listaVazia()) {
            *((int*)&pos[0]) = current.positions.primeiro();
            current.positions.retiraDoInicioDuplo();
            for(int i = 0; i < 4; i++) {
                fputc(pos[i], palavrasDat);
            }
        }
    }

    fclose(palavrasDat);

    printf("Finalizado a geração de palavras.dat\n");

    ///////////////////////////////////
    ///// TERMINOU A PALAVRAS.DAT
    ///////////////////////////////////
}

/**
 * Pede o nome do comando/manpage a ser procurado
 * Percorre o arquivo "indices.dat" que está organizado como uma árvore
 * níveis procurando pelo texto informado.
 *
 * O percorrimento por níveis é feito do seguinte modo:
 *  Estando em uma posição "x" e
 *      verificando que aquilo que é procurado é menor que atual, vá para
 *      o nodo da esquerda, no caso a posição "2(x+1)-1"
 *
 *      verificando que aquilo que é procurado é maior que atual, vá para
 *      o nodo da direita, no caso posição "2(x+1)"
 */
 void search_by_command() {
     //Array onde será salvo o comando a ser pesquisado
     char comandoBusca[100];

     //Recebe o comando
     scanf("%s",comandoBusca);
     //Abre arquivo indices.dat
     FILE* indicesDat = fopen("..\\indices.dat", "rb");

     //calcula a quantidade de itens na arvore e armazena em "tamanho"
     std::ifstream in("..\\indices.dat", std::ifstream::ate | std::ifstream::binary);
     int tamanho = in.tellg();
     tamanho /= size_max_command;

     //Percorrimento da lista em arquivo, buscando pelo item pedido
     int pos = 0;
     bool achou = false;
     char comandoAtual[100];
     while(!achou && pos<tamanho) {
         //Posiciona o leitor no começo do registro
         fseek(indicesDat, pos*size_max_command, SEEK_SET);
         char comandoAtual[100];
         //le o registro do arquivo
         fgets(comandoAtual, 100, indicesDat);
         int cmpResult = strcmp(comandoBusca, comandoAtual);
         //Buscando maior que encontrado, pega o ramo da direita
         if(cmpResult < 0) {
             pos++;
             pos = (2*pos)-1;
         //Buscando menor que encontrado, pega o ramo da esquerda
         } else if(cmpResult > 0) {
             pos++;
             pos = (2*pos);
         //Encontrou
         } else {
             achou = true;
         }
     }
     //fecha indices.dat, mas deixa salvo o conteúdo pedido em "comandoAtual"
     fclose(indicesDat);

     if(achou) {
         //Retira a posição dos ultimos 4 bytes de comando
         int posicao;
         posicao = *((int*)&comandoAtual[96]);

         //Abre a manpages.dat para pegar o conteúdo pedido

         FILE* manPagesDat;
         manPagesDat = fopen("..\\manpages.dat", "rb");
         //Posiciona o leitor no começo do conteudo do registro
         posicao = posicao * (size_max_command+size_max_content) + size_max_command;
         fseek(manPagesDat, posicao, SEEK_SET);

         char lido = ' ';
         while(lido != '\0') {
             printf("%c",lido=fgetc(manPagesDat));
         }

         fclose(manPagesDat);
     } else {
         printf("\nManPage não encontrada\n");
     }
 }

 /**
  * Pede uma palavra e pega a man_pages_positions(palavra) a lista de
  * de índices que possuem a palavra pesquisada.
  * Traduz os índices para o nome das manpages acessando "manpages.dat" e
  * pegando o nome dos registros de índice respectivos.
  */
void search_by_one_word(){
    //Pede a palavra a ser pesquisada
    char palavra[100];
    scanf("%s",palavra);
    //Pega a lista de índices que possuem a palavra
    ListaDupla<int> indices = man_pages_positions(palavra);
    FILE* manPagesDat;
    manPagesDat = fopen("..\\manpages.dat", "rb");

    printf("\n\n");
    //Pega o nome dos registros a partir dos índices
    while (!indices.listaVazia()) {
        fseek(manPagesDat, indices.primeiro()*(size_max_command+size_max_content), SEEK_SET);
        char comando[100];
        fgets(comando, 100, manPagesDat);
        printf("%d - %s\n",indices.primeiro(), comando);
        indices.retiraDoInicioDuplo();
    }
    fclose(manPagesDat);
}
/**
 * Pede as duas palavras, e obtem os indices de modo semelhante a
 * search_by_one_word, realiza as intersecção entre as listas de índices
 * Traduz os índices para o nome das manpages consultando "manpages.dat"
 */
void search_by_two_words() {
    //Pede a primeira palavra
    char palavra1[100];
    scanf("%s", palavra1);
    //Pega a lista de índices que possuem a primeira palavra
    ListaDupla<int> indices1 = man_pages_positions(palavra1);
    //Pede a segunda palavra
    char palavra2[100];
    scanf("%s", palavra2);
    //Pega índices da segunda palavra
    ListaDupla<int> indices2 = man_pages_positions(palavra2);

    //Intersecção de indices1 e indices2
    ListaDupla<int> indices;
    while (!indices2.listaVazia()) {
        int atual = indices2.primeiro();
        bool achou = false;
        for(int i = 0; i < indices1.verUltimo() && !achou; i++) {
            if(indices1.mostra(i) == atual) achou = true;
        }
        if(achou) indices.adicionaDuplo(atual);
        indices2.retiraDoInicioDuplo();
    }

    FILE* manPagesDat;
    manPagesDat = fopen("..\\manpages.dat", "rb");
    printf("\n\n");

    while (!indices.listaVazia()) {
        fseek(manPagesDat, indices.primeiro()*(size_max_command+size_max_content), SEEK_SET);
        char comando[100];
        fgets(comando, 100, manPagesDat);
        printf("%d - %s\n", indices.primeiro(), comando);
        indices.retiraDoInicioDuplo();
    }

    fclose(manPagesDat);
}

/**
 * Recebe a palavra a ser procurada
 * Consulta o "palavras.dat", que é uma lista, procurando pela
 * palavra pedida
 * Retorna a lista de índices que possuem a palavra pedida
 */
ListaDupla<int> man_pages_positions(char* palavra) {
    FILE* palavrasDat;
    palavrasDat = fopen("..\\palavras.dat", "rb");

    //Lê a quantidade de palavras dos 4 bytes e guarda em "tamanho"
    char tamanhoC[4];
    for(int i = 0; i < 4; i++) {
        tamanhoC[i] = fgetc(palavrasDat);
    }

    int tamanho = *((int*)&tamanhoC[0]);
    int pos = 0;
    bool achou = false;
    char palavraAtual[100];
    while (!achou && pos < tamanho) {
        //Posiciona o leitor no inicio do registro da palavra
        fseek(palavrasDat, 4+(pos*size_max_word), SEEK_SET);
        //Pega palavra do registro
        fgets(palavraAtual, 100, palavrasDat);

        int cmpResult = strcmp(palavra, palavraAtual);
        //Buscando maior que encontrado, pega o ramo da esquerda
        if(cmpResult < 0) {
            pos++;
            pos = (2*pos)-1;
        //Buscando menor que encontrado, pega o ramo da direita
        } else if(cmpResult > 0) {
            pos++;
            pos = (2*pos);
        //Encontrado
        } else {
            achou = true;
        }
    }

    ListaDupla<int> indices;
    if(achou) {
        pos = *((int*)&palavraAtual[92]);
        int qtd = *((int*)&palavraAtual[96]);
        fseek(palavrasDat, 4+(tamanho*size_max_word)+pos*4, SEEK_SET);
        for(int i = 0; i < qtd; i++) {
            char indiceC[4];
            for(int j = 0; j < 4; ++j){
                indiceC[j] = fgetc(palavrasDat);
            }
            int indice = *((int*)&indiceC[0]);
            indices.adicionaDuplo(indice);
        }
    } else {
        printf("Nenhum arquivo encontrado com a palavra '%s'\n", palavra);
    }

    fclose(palavrasDat);

    return indices;
}
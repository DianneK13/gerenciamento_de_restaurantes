#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    italiana = 1,
    japonesa,
    brasileira,
    mexicana,
    vegana,
    fastFood,
    outros,
    numTiposCozinha,
} TipoCozinha;

typedef struct {
    char nome[100];
    char descricao[100];
    float preco;
} Prato;

typedef struct{
    char nome[50];
    char descricao[100];
    int codigo;
    TipoCozinha tipo;
    Prato* menu;
    int qtdMenu;
}Restaurante;

void novoRestaurante(Restaurante** restaurantes, int* qtdRestaurantes) {

    int codigo, existe = 0;
    char nome[50];
    char descricao[100];
    TipoCozinha tipo;

    printf("Digite o codigo do restaurante: ");
    scanf("%d", &codigo);

    //Verificar se o codigo ja existe
    int i = 0;
    while (existe == 0 && i < *qtdRestaurantes) {
        if (restaurantes[i]->codigo == codigo) {
            existe = 1;}
        i++;
    }

    if (existe) {
        printf("Codigo ja cadastrado. Nao foi possivel adicionar o restaurante.\n");
    } else {
        printf("Digite o nome do restaurante: \n");
        scanf("%[^\n]", nome);

        printf("Digite a descricao do restaurante: \n");
        scanf("%[^\n]", descricao);

        printf("Escolha o tipo de cozinha: \n");
        printf("1 - Italiana\n2 - Japonesa\n3 - Brasileira\n4 - Mexicana\n5 - Vegana\n6 - FastFood\n7 - Outros\n");
        scanf("%d", &tipo);


        // Alocar espaco extra
        Restaurante* tmp = realloc(*restaurantes, (*qtdRestaurantes + 1) * sizeof(Restaurante));
        if (tmp == NULL) {
            printf("Erro ao alocar espaco extra.\n");
            exit(1);
        }
        *restaurantes = tmp;

        // Preencher campos no novo restaurante
        Restaurante* novo = &(*restaurantes)[*qtdRestaurantes];
        strcpy(novo->nome, nome);
        strcpy(novo->descricao, descricao);
        novo->codigo = codigo;
        novo->tipo = tipo;
        novo->menu = NULL;
        novo->qtdMenu = 0;

        (*qtdRestaurantes)++;

        printf("Restaurante cadastrado com sucesso!");
    }
}


void listarRestaurantes(Restaurante** restaurantes, int qtdRestaurantes) {

}


Restaurante* buscarRestaurante(Restaurante* restaurantes, int qtdRestaurantes, int codigoRestaurante) {

}


void atualizarRestaurante(Restaurante* restaurantes, int qtdRestaurantes) {

}


void adicionarPrato(Restaurante* restaurantes, int qtdRestaurantes) {

}


void listarMenu(Restaurante* restaurantes, int qtdRestaurantes) {

}


void removerPrato(Restaurante* restaurantes, int qtdRestaurantes) {

}


void desaloca(Restaurante* restaurantes, int qtdRestaurantes) {

}

int main () {

    return 0;
}

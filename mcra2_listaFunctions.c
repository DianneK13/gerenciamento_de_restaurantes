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

void listarRestaurantes(Restaurante** restaurantes, const int qtdRestaurantes) {
    if (qtdRestaurantes == 0) {
        printf("Nenhum restaurante cadastrado no sistema. \n");

    } else {
        int filtrar;
        printf("Deseja filtrar por tipo de cozinha? (1 - SIM, 0 - NAO): ");
        scanf("%d\n", &filtrar);

        int tipoFiltro = -1;
        if (filtrar == 1) {
            printf("Escolha o tipo de cozinha: \n");
            printf("1 - Italiana\n2 - Japonesa\n3 - Brasileira\n4 - Mexicana\n"
                   "5 - Vegana\n6 - FastFood\n7 - Outros\n");
            printf("Digite o numero correspondente: \n");
            scanf("%d", &tipoFiltro);
        }

        int encontrados = 0;
        int i = 0;
        while (i < qtdRestaurantes) {
            // se for para filtrar, so mostre se o tipo bater
            if (filtrar == 1 && restaurantes[i]->tipo != tipoFiltro) {
                i++;
            } else {
                
                printf("\nRestaurante: %s\n", restaurantes[i]->nome);
                printf("Descricao: %s\n", restaurantes[i]->descricao);
                printf("Codigo: %d\n", restaurantes[i]->codigo);
                printf("Tipo: ");
                
                if (restaurantes[i]->tipo == italiana) {
                    printf("italiana\n");
                } else if (restaurantes[i]->tipo == japonesa) {
                    printf("japonesa\n");
                } else if (restaurantes[i]->tipo == brasileira) {
                    printf("brasileira\n");
                } else if (restaurantes[i]->tipo == mexicana) {
                    printf("mexicana\n");
                } else if (restaurantes[i]->tipo == vegana) {
                    printf("vegana\n");
                } else if (restaurantes[i]->tipo == fastFood) {
                    printf("fastFood\n");
                } else if (restaurantes[i]->tipo == outros) {
                    printf("outros\n");
                } else printf("tipo desconhecido.\n");

                printf("---\n");

                encontrados++;
            }

            if (encontrados == 0) {
                printf("\nNenhum restaurante encontrado com os filtros selecionados.");
            } else {
                printf("\nTotal de restaurantes encontrados: %d\n", encontrados);
            }
        }
    }
}

Restaurante* buscarRestaurante(Restaurante* restaurantes, const int qtdRestaurantes, const int codigoRestaurante) {
    Restaurante *restEncontrado = NULL;  // Variável de controle
    int i = 0;   // Percorre a lista enquanto não encontrar
    while (i < qtdRestaurantes && restEncontrado == NULL) {
        if (restaurantes[i].codigo == codigoRestaurante) {
            restEncontrado = &restaurantes[i];
        }
        i++;
    }
    return restEncontrado;  // Retorna NULL, se não achar

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
    int i = 0;
    while (i < qtdRestaurantes) {
        // Libera pratos do menu
        for (int j = 0; j < restaurantes[i].qtdMenu; j++) {
            free(restaurantes[i].menu[j].nome);
            free(restaurantes[i].menu[j].descricao);
        }
        // Libera vetor de pratos
        free(restaurantes[i].menu);
        //Libera nome e descrição do restaurante
        free(restaurantes[i].nome);
        free(restaurantes[i].descricao);
        i++;
    }
    // Libera vetor de restaurantes
    free(restaurantes);
}

int main () {

    return 0;
}

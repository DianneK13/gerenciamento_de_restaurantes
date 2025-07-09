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
    char *nome;
    char *descricao;
    float preco;
} Prato;

typedef struct{
    char *nome;
    char *descricao;
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
        scanf(" %49[^\n]", nome);

        printf("Digite a descricao do restaurante: \n");
        scanf(" %99[^\n]", descricao);

        printf("Escolha o tipo de cozinha: \n");
        printf("1 - Italiana\n2 - Japonesa\n3 - Brasileira\n4 - Mexicana\n5 - Vegana\n6 - FastFood\n7 - Outros\n");
        scanf("%u", &tipo);


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

void atualizarRestaurante(Restaurante* restaurantes, const int qtdRestaurantes) {

    printf("Digite o codigo do restaurante que deseja atualizar: ");
    int codigo;
    scanf("%d", &codigo);

    Restaurante *r = buscarRestaurante(restaurantes, qtdRestaurantes, codigo);

    if (r == NULL) {
            printf("Restaurante nao encontrado.\n");
        } else {
            char escolha;
            char novoTexto[100];

            // Atualizar nome
            printf("Deseja alterar o nome? (S/N)");
            scanf(" %c\n", &escolha);
            if (escolha == 'S' || escolha == 's') {
                printf("Digite o novo nome: \n");
                scanf(" %49[^\n]", novoTexto);

                // Liberar antigo
                free(r->nome);
                r->nome = strdup(novoTexto);
                if (r->nome == NULL) {
                    printf("Problema de alocacao na troca de nome!\n");
                    exit(1);
                }
            }

            // Atualizar descricao
            printf("Deseja alterar a descrição? (S/N)");
            scanf(" %c", escolha);
            if (escolha == 'S' || escolha == 's'){
                printf("Digite nova descricao: ");
                scanf(" %[^\n]", novoTexto);

                // Liberar antigo
                free(r->descricao);
                r->descricao = strdup(novoTexto);
                if (r->descricao == NULL){
                    printf("Problema de alocacao na troca de descricao!\n");
                    exit(1);
                }
            }

            // Atualizar tipo
            printf("Deseja atualizar o tipo de cozinha? (S/N)");
            scanf(" %c", escolha);
            if (escolha == 'S' || escolha == 's') {
                int novoTipo;
                printf("Escolha um novo tipo de cozinha: ");
                printf("1 - Italiana\n2 - Japonesa\n3 - Brasileira\n4 - Mexicana\n5 - Vegana\n6 - FastFood\n7 - Outros\n");
                scanf(" %d", &novoTipo);

                r->tipo = novoTipo;
            }
            printf("Restaurante atualizado com sucesso!\n");
        }

}

void adicionarPrato(Restaurante* restaurantes, const int qtdRestaurantes) {

    printf("Digite o codigo do restaurante que deseja adicionar um prato: ");
    int codigo;
    scanf("%d", &codigo);

    Restaurante *r = buscarRestaurante(restaurantes, qtdRestaurantes, codigo);
    if (r == NULL) {
        printf("Restaurante nao encontrado.\n");
    } else {
        Prato novoPrato;
        char nomePrato[100];
        char descPrato[100];

        printf("Digite o nome do prato: \n");
        scanf(" %[^\n]", nomePrato);

        printf("Digite a descricao do prato: \n");
        scanf(" %[^\n]", descPrato);

        printf("E qual o preco? \n");
        scanf(" %f", &novoPrato.preco);

        novoPrato.nome = strdup(nomePrato);
        if (novoPrato.nome == NULL) {
            printf("Erro de alocacao no nome.\n");
            exit(1);
        }

        novoPrato.descricao = strdup(descPrato);
        if (novoPrato.descricao == NULL) {
            printf("Erro de alocacao na descricao.\n");
            exit(1);
        }

        // Realocar espaco extra
        Prato *tmp = realloc(r->menu, (r->qtdMenu + 1) * sizeof(Prato));
        if (tmp == NULL) {
            printf("Erro de alocacao no menu\n");
            exit(1);
        }
        r->menu = tmp;

        r->menu[r->qtdMenu] = novoPrato;
        r->qtdMenu++;

        printf("Prato adicionado ao menu do Restaurante %s com sucesso!\n", r->nome);
    }

}

void listarMenu(Restaurante* restaurantes, int qtdRestaurantes) {

    printf("Digite  o codigo do restaurante que deseja ver o menu: ");
    int codigo;
    scanf("%d", &codigo);

    Restaurante *r = buscarRestaurante(restaurantes, qtdRestaurantes, codigo);
    if (r == NULL) {
        printf("Restaurante nao encontrado.\n");
    } else if (r->qtdMenu == 0) {
        printf("Nenhum prato cadastrado no menu do restaurante.\n");
    } else {
        printf("\n===== Menu do restaurante %s =====\n", r->nome);

        int i = 0;
        while (i < r->qtdMenu) {
            printf("\nPrato %d:\n", i);
            printf("Nome: %s\n", r->menu[i].nome);
            printf("Descricao: %s\n", r->menu[i].descricao);
            printf("Preco: R$%.2f\n", r->menu[i].preco);
            printf("---");
            i++;
        }
        printf("\n");
    }

}

void removerPrato(Restaurante* restaurantes, int qtdRestaurantes) {
    printf("Digite o codigo do restaurante que deseja remover um prato: ");
    int codigo;
    scanf("%d", &codigo);

    Restaurante *r = buscarRestaurante(restaurantes, qtdRestaurantes, codigo);
    if (r == NULL) {
        printf("Restaurante nao encontrado.\n");
    } else if (r->qtdMenu == 0) {
        printf("Nenhum prato cadastrado no menu do restaurante.\n");
    } else {
        listarMenu(restaurantes, qtdRestaurantes);
        // Solicitar indice
        int indice;
        printf("Digite o indice do prato que deseja remover: ");
        scanf("%d", &indice);

        // Validar indice
        if (indice < 0 || indice >= r->qtdMenu) {
            printf("Indice invalido.\n");
        } else {
            // Liberar prato
            free(r->menu[indice].nome);
            free(r->menu[indice].descricao);
            // Deslocar os pratos seguintes para a esquerda
            for (int i = indice; i < r->qtdMenu - 1; i++) {
                r->menu[i] = r->menu[i + 1];
            }
            // Reduzir contador
            r->qtdMenu--;
            // Realocar vetor
            Prato *tmp = realloc(r->menu, r->qtdMenu * sizeof(Prato));
            if (tmp == NULL) {
                printf("Erro de alocacao no menu\n");
                exit(1);
            }
            r->menu = tmp;
            printf("Prato removido com sucesso!\n");
        }
    }
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


int main() {
    Restaurante *restaurantes = NULL;
    int qtdRestaurantes = 0;
    int opcao = 0;

    do {
        printf("\n=================================\n");
        printf("      🍽️  GO Food - Sistema      \n");
        printf("=================================\n");
        printf("1️⃣  - Cadastrar restaurante\n");
        printf("2️⃣  - Listar restaurantes\n");
        printf("3️⃣  - Atualizar restaurante\n");
        printf("4️⃣  - Adicionar prato\n");
        printf("5️⃣  - Listar menu\n");
        printf("6️⃣  - Remover prato\n");
        printf("7️⃣  - Sair\n");
        printf("=================================\n");
        printf("Digite sua opcao: ");
        scanf(" %d", &opcao);

        if (opcao == 1) {
            novoRestaurante(&restaurantes, &qtdRestaurantes);
        } else if (opcao == 2) {
            listarRestaurantes(&restaurantes, qtdRestaurantes);
        } else if (opcao == 3) {
            atualizarRestaurante(restaurantes, qtdRestaurantes);
        } else if (opcao == 4) {
            adicionarPrato(restaurantes, qtdRestaurantes);
        } else if (opcao == 5) {
            listarMenu(restaurantes, qtdRestaurantes);
        } else if (opcao == 6) {
            removerPrato(restaurantes, qtdRestaurantes);
        } else if (opcao == 7) {
            printf("\nEncerrando sistema GO Food...\n");
            desaloca(restaurantes, qtdRestaurantes);
        }
        else {
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 3);

    return 0;
}

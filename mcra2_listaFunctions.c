#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_DESC 100

// STRUCTS E ENUM

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

// FUNCOES UTILITARIAS

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

void printRestaurante(const Restaurante * r) {
    printf("\n📍 Restaurante\n");
    printf("🧾 Nome:        %s\n", r->nome);
    printf("📝 Descrição:   %s\n", r->descricao);
    printf("🏷️ Código:       %d\n", r->codigo);
    printf("🍽️ Tipo:         ");
    switch (r->tipo) {
        case italiana:   printf("italiana\n"); break;
        case japonesa:   printf("japonesa\n"); break;
        case brasileira: printf("brasileira\n"); break;
        case mexicana:   printf("mexicana\n"); break;
        case vegana:     printf("vegana\n"); break;
        case fastFood:   printf("fastFood\n"); break;
        case outros:     printf("outros\n"); break;
        default:         printf("tipo desconhecido\n");
    }
    printf("-------------------------------------------\n");
}

int escolherTipoCozinha() {
    int tipo;
    printf("Tipos de cozinha: \n");
    printf("1 - Italiana\n2 - Japonesa\n3 - Brasileira\n4 - Mexicana\n5 - Vegana\n6 - FastFood\n7 - Outros\n");
    do {
        printf("Digite o numero correspondente (1-7): ");
        scanf("%d", &tipo);

        if (tipo < 1 || tipo >= numTiposCozinha) {
            printf("❌ Tipo inválido! Tente novamente.\n\n");
        }
    } while (tipo < 1 || tipo >= numTiposCozinha);
    return tipo;
}

int validarCodigo() {
    char entrada[100];
    int codigo;
    int valido = 0;
    while (!valido) {
        scanf("%s", entrada);
        if (sscanf(entrada, "%d", &codigo) == 1) {
            valido = 1;
        } else {
            printf("❌ Por favor, digite apenas numeros inteiros: ");
        }
    }
    return codigo;
}

// FUNCOES DO MENU

void novoRestaurante(Restaurante** restaurantes, int* qtdRestaurantes) {

    int existe = 0;
    char nome[MAX_NOME];
    char descricao[MAX_DESC];

    printf("Digite o codigo do restaurante: ");
    const int codigo = validarCodigo();

    //Verificar se o codigo ja existe
    int i = 0;
    while (existe == 0 && i < *qtdRestaurantes) {
        if ((*restaurantes)[i].codigo == codigo) {
            existe = 1;}
        i++;
    }

    if (existe) {
        printf("\n❌ Codigo ja cadastrado. Nao foi possivel adicionar o restaurante.\n");
    } else {
        printf("Digite o nome do restaurante: ");
        scanf(" %49[^\n]", nome);

        printf("Digite a descricao do restaurante: ");
        scanf(" %99[^\n]", descricao);

        const TipoCozinha tipo = escolherTipoCozinha();

        // Alocar espaco extra
        Restaurante* tmp = realloc(*restaurantes, (*qtdRestaurantes + 1) * sizeof(Restaurante));
        if (tmp == NULL) {
            printf("⚠️ Erro ao alocar espaco extra.\n");
            exit(1);
        }
        *restaurantes = tmp;

        // Preencher campos no novo restaurante
        Restaurante* novo = &(*restaurantes)[*qtdRestaurantes];
        novo->nome      = strdup(nome);
        novo->descricao = strdup(descricao);
        novo->codigo    = codigo;
        novo->tipo      = tipo;
        novo->menu      = NULL;
        novo->qtdMenu   = 0;
        if (!novo->nome || !novo->descricao) {
            printf("⚠️ Erro de alocacao de string");
            exit(1);
        }
        (*qtdRestaurantes)++;

        printf("\n✅ Restaurante \"%s\" cadastrado com sucesso! 🎉\n", novo->nome);
        printf("\nVoltando ao menu principal... 🍽️\n");
    }
}

void listarRestaurantes(Restaurante** restaurantes, const int qtdRestaurantes) {
    if (qtdRestaurantes == 0) {
        printf("Nenhum restaurante cadastrado no sistema.\n");

    } else {
        int filtrar = -1;
        printf("Deseja filtrar por tipo de cozinha? (1 - SIM, 0 - NAO): ");
        scanf("%d", &filtrar);

        int tipoFiltro = -1;
        if (filtrar == 1) {
            tipoFiltro = escolherTipoCozinha();
        }

        printf("\n==🍽️  Listando restaurantes cadastrados...==\n");
        printf("-------------------------------------------\n");

        int encontrados = 0;
        for (int i = 0; i < qtdRestaurantes; i++) {
            const Restaurante *r = &(*restaurantes)[i];
            // se for para filtrar, so mostre se o tipo bater
            if (!filtrar || r->tipo == tipoFiltro) {
                printRestaurante(r);
                encontrados++;
            }
        }

        if (encontrados == 0) {
            printf("\n⚠️ Nenhum restaurante encontrado com o filtro selecionado.\n");
        } else {
            printf("\nTotal de restaurantes encontrados: %d\n", encontrados);
        }
    }
    printf("\nVoltando ao menu principal... 🍽️\n");
}

void atualizarRestaurante(Restaurante* restaurantes, const int qtdRestaurantes) {

    printf("Digite o codigo do restaurante que deseja atualizar: ");
    const int codigo = validarCodigo();

    Restaurante *r = buscarRestaurante(restaurantes, qtdRestaurantes, codigo);

    if (r == NULL) {
            printf("Restaurante nao encontrado.\n");
        } else {
            char escolha;
            char novoTexto[100];

            // Atualizar nome
            printf("Deseja alterar o nome? (S/N) ");
            scanf(" %c", &escolha);
            if (escolha == 'S' || escolha == 's') {
                printf("Digite o novo nome: ");
                scanf(" %99[^\n]", novoTexto);

                // Liberar antigo
                free(r->nome);
                r->nome = strdup(novoTexto);
                if (r->nome == NULL) {
                    printf("⚠️ Erro de alocacao na troca de nome!\n");
                    exit(1);
                }
            }

            // Atualizar descricao
            printf("Deseja alterar a descricao? (S/N) ");
            scanf(" %c", &escolha);
            if (escolha == 'S' || escolha == 's'){
                printf("Digite nova descricao: ");
                scanf(" %99[^\n]", novoTexto);

                // Liberar antigo
                free(r->descricao);
                r->descricao = strdup(novoTexto);
                if (r->descricao == NULL){
                    printf("⚠️ Erro de alocacao na troca de descricao!\n");
                    exit(1);
                }
            }

            // Atualizar tipo
            printf("Deseja atualizar o tipo de cozinha? (S/N) ");
            scanf(" %c", &escolha);
            if (escolha == 'S' || escolha == 's') {
                const int novoTipo = escolherTipoCozinha();
                r->tipo = novoTipo;
            }
            printf("\n✅ Restaurante \"%s\" atualizado com sucesso! 🎉\n", r->nome);
        }
    printf("\nVoltando ao menu principal... 🍽️\n");

}

void adicionarPrato(Restaurante* restaurantes, const int qtdRestaurantes) {

    printf("Digite o codigo do restaurante que deseja adicionar um prato: ");

    const int codigo = validarCodigo();

    Restaurante *r = buscarRestaurante(restaurantes, qtdRestaurantes, codigo);
    if (r == NULL) {
        printf("Restaurante nao encontrado.\n");
    } else {
        Prato novoPrato;
        char nomePrato[MAX_NOME];
        char descPrato[MAX_DESC];

        printf("Digite o nome do prato: ");
        scanf(" %49[^\n]", nomePrato);

        printf("Digite a descricao do prato: ");
        scanf(" %99[^\n]", descPrato);

        printf("E qual o preco? ");
        scanf("%f", &novoPrato.preco);

        novoPrato.nome = strdup(nomePrato);
        if (novoPrato.nome == NULL) {
            printf("⚠️ Erro de alocacao no nome.\n");
            exit(1);
        }

        novoPrato.descricao = strdup(descPrato);
        if (novoPrato.descricao == NULL) {
            printf("⚠️ Erro de alocacao na descricao.\n");
            exit(1);
        }

        // Realocar espaco extra
        Prato *tmp = realloc(r->menu, (r->qtdMenu + 1) * sizeof(Prato));
        if (tmp == NULL) {
            printf("⚠️ Erro de alocacao no menu\n");
            exit(1);
        }
        r->menu = tmp;

        r->menu[r->qtdMenu] = novoPrato;
        r->qtdMenu++;

        printf("\n✅ Prato \"%s\" adicionado ao menu do restaurante \"%s\" com sucesso! 🎉\n",
               novoPrato.nome, r->nome);
    }
    printf("\nVoltando ao menu principal... 🍽️\n");
}

void listarMenu(Restaurante* restaurantes, const int qtdRestaurantes, const int codigo) {

    const Restaurante *r = buscarRestaurante(restaurantes, qtdRestaurantes, codigo);
    if (r == NULL) {
        printf("Restaurante nao encontrado.\n");
    } else if (r->qtdMenu == 0) {
        printf("Nenhum prato cadastrado no menu do restaurante.\n");
    } else {
        printf("\n===== Menu do restaurante %s =====\n", r->nome);

        int i = 0;
        while (i < r->qtdMenu) {
            printf("\nPrato %d:\n", i + 1);
            printf("Nome: %s\n", r->menu[i].nome);
            printf("Descricao: %s\n", r->menu[i].descricao);
            printf("Preco: R$%.2f\n", r->menu[i].preco);
            printf("---");
            i++;
        }
        // Adiciona extensao dinamica no separador, proporcional ao nome
        printf("\n==========================");
        for (int i = 0; i < strlen(r->nome); i++) printf("=");
        printf("======\n");
    }
}

void removerPrato(Restaurante* restaurantes, const int qtdRestaurantes) {
    printf("Digite o codigo do restaurante que deseja remover um prato: ");
    const int codigo = validarCodigo();

    Restaurante *r = buscarRestaurante(restaurantes, qtdRestaurantes, codigo);
    if (r == NULL) {
        printf("Restaurante nao encontrado.\n");
    } else if (r->qtdMenu == 0) {
        printf("Nenhum prato cadastrado no menu do restaurante.\n");
    } else {
        listarMenu(restaurantes, qtdRestaurantes, codigo);
        // Solicitar indice
        printf("\nDigite o indice do prato que deseja remover: ");
        int indice = validarCodigo();

        // Validar indice (entre 1 e qtdMenu)
        while (indice < 1 || indice > r->qtdMenu){
            printf("\n❌ Indice invalido! Tente novamente.\n");
            printf("\nDigite o indice do prato que deseja remover: ");
            indice = validarCodigo();
        }
        indice--;
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
        Prato* tmp = NULL;
        tmp = realloc(r->menu, r->qtdMenu * sizeof(Prato));
        if (tmp == NULL) {
            printf("⚠️ Erro de alocacao no menu\n");
            exit(1);
        }
        r->menu = tmp;
        printf("\n✅ Prato removido do restaurante \"%s\" com sucesso! 🎉\n", r->nome);

    }
    printf("\nVoltando ao menu principal... 🍽️\n");
}

void desaloca(Restaurante* restaurantes, const int qtdRestaurantes) {
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


// LISTA DE FUNCOES PARA ESCOLHA DO MENU
// Video usado como base https://youtu.be/Lf3ZV0UsnEo?si=6gmjm_Xa5ikqoI-Y :)
// Recomendo dar uma olhada, é ótimo!

void opcaoCadastrar(Restaurante** r, int* qtd) {
    novoRestaurante(r, qtd);
}

void opcaoListarRestaurantes(Restaurante** r, const int * qtd) {
    listarRestaurantes(r, *qtd);
}

void opcaoAtualizar(Restaurante** r, const int * qtd) {
    atualizarRestaurante(*r, *qtd);
}

void opcaoAdicionarPrato(Restaurante** r, const int * qtd) {
    adicionarPrato(*r, *qtd);
}

void opcaoListarMenu(Restaurante** r, const int * qtd) {
    printf("Digite o codigo do restaurante que deseja ver o menu: ");
    const int codigo = validarCodigo();
    listarMenu(*r, *qtd, codigo);
    printf("\nVoltando ao menu principal... 🍽️\n");
}

void opcaoRemoverPrato(Restaurante** r, const int * qtd) {
    removerPrato(*r, *qtd);
}

void opcaoSair(Restaurante** r, int* qtd) {
    printf("\nObrigado por usar o GO Food! Ate a proxima! 🎉👋\n");
    desaloca(*r, *qtd);
    *r = NULL;
    *qtd = 0;
}

typedef void (*FuncaoMenu)(Restaurante**, int*);

int main() {
    Restaurante *restaurantes = NULL;
    int qtdRestaurantes = 0;
    int opcao = 0;

    const FuncaoMenu funcoes[] = {
        opcaoCadastrar,
        opcaoListarRestaurantes,
        opcaoAtualizar,
        opcaoAdicionarPrato,
        opcaoListarMenu,
        opcaoRemoverPrato,
        opcaoSair
    };

    const int numFuncoes = sizeof(funcoes) / sizeof(funcoes[0]);

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

        if (opcao >= 1 && opcao <= numFuncoes) {
            funcoes[opcao - 1](&restaurantes, &qtdRestaurantes);
        } else {
            printf("❌ Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 7);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SAPATOS 100
#define MAX_NUMERACOES 10

typedef struct {
    int numero;
    int quantidade;
} Numeracao;

typedef struct {
    char nome[50];
    Numeracao numeracoes[MAX_NUMERACOES];
    int totalNumeracoes;
} Sapato;

void salvarCatalogo(Sapato sapatos[], int totalSapatos) {
    FILE *file = fopen("catalogo.dat", "wb");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fwrite(&totalSapatos, sizeof(int), 1, file);
    fwrite(sapatos, sizeof(Sapato), totalSapatos, file);
    fclose(file);
}

void carregarCatalogo(Sapato sapatos[], int *totalSapatos) {
    FILE *file = fopen("catalogo.dat", "rb");
    if (!file) {
        printf("Arquivo de catalogo nao encontrado. Criando novo...\n");
        *totalSapatos = 0;
        return;
    }
    fread(totalSapatos, sizeof(int), 1, file);
    fread(sapatos, sizeof(Sapato), *totalSapatos, file);
    fclose(file);
}

void listarSapatos(Sapato sapatos[], int totalSapatos) {
    if (totalSapatos == 0) {
        printf("Nenhum sapato cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalSapatos; i++) {
        printf("%d - %s\n", i + 1, sapatos[i].nome);
        for (int j = 0; j < sapatos[i].totalNumeracoes; j++) {
            printf("   Num: %d, Qtde: %d\n", sapatos[i].numeracoes[j].numero, sapatos[i].numeracoes[j].quantidade);
        }
    }
}

void adicionarSapato(Sapato sapatos[], int *totalSapatos) {
    if (*totalSapatos >= MAX_SAPATOS) {
        printf("Catalogo cheio!\n");
        return;
    }
    printf("Nome do sapato: ");
    scanf(" %49[^\n]", sapatos[*totalSapatos].nome);
    sapatos[*totalSapatos].totalNumeracoes = 0;
    (*totalSapatos)++;
    salvarCatalogo(sapatos, *totalSapatos);
}

void removerSapato(Sapato sapatos[], int *totalSapatos) {
    listarSapatos(sapatos, *totalSapatos);
    printf("Informe o numero do sapato para remover: ");
    int idx;
    scanf("%d", &idx);
    if (idx < 1 || idx > *totalSapatos) {
        printf("Indice invalido!\n");
        return;
    }
    for (int i = idx - 1; i < *totalSapatos - 1; i++) {
        sapatos[i] = sapatos[i + 1];
    }
    (*totalSapatos)--;
    salvarCatalogo(sapatos, *totalSapatos);
}

void removerTodosSapatos(Sapato sapatos[], int *totalSapatos) {
    *totalSapatos = 0;
    salvarCatalogo(sapatos, *totalSapatos);
    printf("Todos os sapatos foram removidos do catalogo.\n");
}

void adicionarNumeracao(Sapato sapatos[], int totalSapatos) {
    listarSapatos(sapatos, totalSapatos);
    printf("Escolha o sapato: ");
    int idx;
    scanf("%d", &idx);
    if (idx < 1 || idx > totalSapatos) {
        printf("Indice invalido!\n");
        return;
    }
    Sapato *s = &sapatos[idx - 1];
    if (s->totalNumeracoes >= MAX_NUMERACOES) {
        printf("Limite de numeracoes atingido!\n");
        return;
    }
    printf("Numero: ");
    scanf("%d", &s->numeracoes[s->totalNumeracoes].numero);
    printf("Quantidade: ");
    scanf("%d", &s->numeracoes[s->totalNumeracoes].quantidade);
    s->totalNumeracoes++;
    salvarCatalogo(sapatos, totalSapatos);
}

void removerNumeracao(Sapato sapatos[], int totalSapatos) {
    listarSapatos(sapatos, totalSapatos);
    printf("Escolha o sapato: ");
    int idx;
    scanf("%d", &idx);
    if (idx < 1 || idx > totalSapatos) {
        printf("Indice invalido!\n");
        return;
    }
    Sapato *s = &sapatos[idx - 1];
    printf("Escolha a numeracao para remover: ");
    int numIdx;
    scanf("%d", &numIdx);
    if (numIdx < 1 || numIdx > s->totalNumeracoes) {
        printf("Indice invalido!\n");
        return;
    }
    for (int i = numIdx - 1; i < s->totalNumeracoes - 1; i++) {
        s->numeracoes[i] = s->numeracoes[i + 1];
    }
    s->totalNumeracoes--;
    salvarCatalogo(sapatos, totalSapatos);
}

int main() {
    Sapato sapatos[MAX_SAPATOS];
    int totalSapatos;
    carregarCatalogo(sapatos, &totalSapatos);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1 - Listar sapatos\n");
        printf("2 - Adicionar sapato\n");
        printf("3 - Remover sapato\n");
        printf("4 - Adicionar numeracao\n");
        printf("5 - Remover numeracao\n");
        printf("6 - Remover todos os sapatos\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: listarSapatos(sapatos, totalSapatos); break;
            case 2: adicionarSapato(sapatos, &totalSapatos); break;
            case 3: removerSapato(sapatos, &totalSapatos); break;
            case 4: adicionarNumeracao(sapatos, totalSapatos); break;
            case 5: removerNumeracao(sapatos, totalSapatos); break;
            case 6: removerTodosSapatos(sapatos, &totalSapatos); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

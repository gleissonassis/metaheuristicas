#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

struct matriz {
    int numero_elementos;
    int** elementos;
};

struct nodo {
    int indice;
    int valor;
};

void ler_arquivo(struct matriz*, char*);
int calcular_custo(struct matriz, int*);
void construir_caminho(struct matriz, int*);
void construir_caminho_aleatorio(struct matriz, int*);

void imprimir_caminho(int, int*);

void imprimir_matriz(struct matriz);
void linha();

int main(int argc, char *argv[]) {
    struct matriz m;

    ler_arquivo(&m, "/Users/gleissonassis/Dropbox/CH/instancias/10_01_25.txt");
    imprimir_matriz(m);

    int *solucao_inicial = malloc((m.numero_elementos + 1) * sizeof(int));
    construir_caminho(m, solucao_inicial);
    printf("Solucao inicial: ");
    imprimir_caminho(m.numero_elementos + 1, solucao_inicial);

    int custo_solucao_inicial = calcular_custo(m, solucao_inicial);
    printf("Custo solução inicial: %d", custo_solucao_inicial);

    srand(1);

    linha();
    int *solucao_aleatoria = malloc((m.numero_elementos + 1) * sizeof(int));
    for(int i = 0; i < 10; i++) {
        construir_caminho_aleatorio(m, solucao_aleatoria);
        int custo_solucao_aleatoria = calcular_custo(m, solucao_aleatoria);
        printf("Solucao aleatória: ");
        imprimir_caminho(m.numero_elementos + 1, solucao_aleatoria);
        printf("Custo solução aleatória: %d\n", custo_solucao_aleatoria);
    }
}
//-----------------------------------------------------------------------------

void ler_arquivo(struct matriz* m, char* arquivo) {
    FILE* fp = fopen(arquivo, "r");

    fscanf(fp, "%d\n", &m->numero_elementos);

    m->elementos = malloc(m->numero_elementos * sizeof(int*));

    for(int i = 0; i < m->numero_elementos; i++) {
        m->elementos[i] = malloc(m->numero_elementos * sizeof(int));
        for(int j = 0; j < m->numero_elementos; j++) {
            fscanf(fp, "%d ", &m->elementos[i][j]);
        }
    }


    fclose(fp);
}

//-----------------------------------------------------------------------------

int calcular_custo(struct matriz m, int* caminho) {
    int custo = 0;

    for(int i = 0; i < m.numero_elementos; i++) {
        custo = custo + m.elementos[caminho[i]][caminho[i + 1]];
    }

    return custo;
}

//-----------------------------------------------------------------------------

void construir_caminho(struct matriz m, int* caminho) {
    int *inseridos = malloc(m.numero_elementos * sizeof(int));

    for(int i = 0; i < m.numero_elementos; i++) {
        inseridos[i] = FALSE;
    }

    caminho[0] = 0;
    inseridos[0] = TRUE;

    for(int i = 0; i < m.numero_elementos; i++) {
        int valor_referencia = INT_MAX;
        int vizinho_selecionado = 0;

        for(int j = 0; j < m.numero_elementos; j++) {
            if(!inseridos[j] && valor_referencia > m.elementos[i][j]) {
                vizinho_selecionado = j;
                valor_referencia = m.elementos[i][j];
            }
        }

        caminho[i + 1] = vizinho_selecionado;
        inseridos[vizinho_selecionado] = TRUE;
    }

    caminho[m.numero_elementos] = 0;

    free(inseridos);
}



//-----------------------------------------------------------------------------

void construir_caminho_aleatorio(struct matriz m, int* caminho) {
    int *inseridos = malloc(m.numero_elementos * sizeof(int));
    struct nodo *vizinhos = malloc(m.numero_elementos * sizeof(struct nodo));

    for(int i = 0; i < m.numero_elementos; i++) {
        inseridos[i] = FALSE;
    }

    caminho[0] = 0;
    inseridos[0] = TRUE;

    for(int i = 0; i < m.numero_elementos; i++) {
        int iv = 0;

        for(int j = 0; j < m.numero_elementos; j++) {
            if(!inseridos[j]) {
                vizinhos[iv].indice = j;
                vizinhos[iv].valor = m.elementos[i][j];
                iv++;
            }
        }

        if(iv == 0) {
            caminho[i + 1] = 0;
        } else {
            int vizinho_selecionado = rand() % iv;
            caminho[i + 1] = vizinhos[vizinho_selecionado].indice;
            inseridos[vizinhos[vizinho_selecionado].indice] = TRUE;
        }
    }

    free(inseridos);
    free(vizinhos);
}

//-----------------------------------------------------------------------------

void imprimir_matriz(struct matriz m) {
    linha();
    printf("Matriz\n\n");

    for(int i = 0; i < m.numero_elementos; i++) {
        for(int j = 0; j < m.numero_elementos; j++) {
            printf("%d ", m.elementos[i][j]);
        }

        printf("\n");
    }

    linha();
}

//-----------------------------------------------------------------------------

void imprimir_caminho(int n, int* caminho) {
    int i;

    for(i = 0; i < n; i++) {
        printf("%d ", caminho[i]);
    }
    printf("\n");
}

//-----------------------------------------------------------------------------

void linha() {
    int i;
    printf("\n");
    for(i = 0; i < 80; i++) printf("_");
    printf("\n");
}
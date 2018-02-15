
# Metaheurísticas #04 - Caixeiro Viajante passo a passo

Nessa etapa do curso, é demonstrado o passo a passo para gerar uma solução para o problema do Caixeiro Viajante. Usando a heurística do vizinho mais próximo é apresentada uma forma de gerar uma solução gulosa e também uma solução totalmente aleatória para o problema. As técnicas demonstradas serão base para os nossos próximos vídeos aprofundando mais sobre o assunto. Os códigos apresentados tem cunho didático e prezam pelo esclarecimento dos conceitos teóricos e não são referências como as melhores práticas em programação da linguagem C.

Veja o vídeo completo em:
https://youtu.be/QTMo_El_tMU

# Explicações sobre o código

O algoritmo deve seguir as seguintes etapas:

* Ler um arquivo de dados contendo os detalhes do problema teste;
* Gerar uma solução gulosa/aleatória para o problema;
* Avaliar o custo da solução gerada;
* Imprimir na tela a solução e o custo associado à solução.

## Principais funções

A seguir é detalhado as principais funções utilizadas no programa.

### Leitura do arquivo

Essa função é responsável por ler o arquivo de dados e mapear em memória o conteúdo da matriz de adjacência. É importante ressaltar nesse bloco de código a forma como a alocação dinâmica de memória é feita, pois uma matriz bidimensional nada mais é do que um vetor de vetores.

```c
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
```

### Construção de uma solução inicial gulosa

Utilizando a heurística do vizinho mais próximo esse bloco de código gera uma solução inicial gulosa para o problema. É importante ressaltar a forma como a lista de vizinhos inseridos no caminho é gerenciada e também a decisão de seleção do vizinho, que é baseada no custo de utilização da aresta.

```c
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
```


}

### Construção de uma solução aleatória

Esse bloco de código gera uma solução inicial aleatória para o problema. É importante ressaltar a forma como a lista de vizinhos inseridos no caminho é gerenciada e também a decisão de seleção do vizinho, que é baseada no sorteio de um elemento disponível na lista de vizinhos possíveis de serem vizitados a partir do nodo atual.

```c
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
```

# Considerações

Fique a vontade para entrar em contato caso tenha dúvidas ou encontre algum problema no código.

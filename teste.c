#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó em uma lista de adjacência
struct Node {
    int data;
    struct Node* next;
};

// Estrutura para representar a lista de adjacência
struct AdjList {
    struct Node* head;
};

// Estrutura para representar o grafo
struct Graph {
    int V; // Número de vértices
    struct AdjList* array;
};

// Função para criar um novo nó
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo com V vértices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Crie uma matriz de listas de adjacência. O tamanho da matriz é V.
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Inicialize todas as listas de adjacência como vazias (NULL)
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Função para adicionar uma aresta ao grafo não direcionado
void addEdge(struct Graph* graph, int src, int dest) {
    // Adicione uma aresta de src para dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Como o grafo é não direcionado, também deve-se adicionar uma aresta de dest para src
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Função para imprimir o grafo
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        struct Node* temp = graph->array[v].head;
        printf("Lista de adjacência do vértice %d\n", v);
        while (temp) {
            printf(" -> %d", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int V = 5; // Número de vértices

    struct Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    return 0;
}

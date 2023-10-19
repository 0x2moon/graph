#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um vértice
struct Vertex {
    char name;
    int visited;
    struct Vertex* next;
};

// Estrutura para representar a lista de adjacência
struct AdjList {
    struct Vertex* head;
};

// Estrutura para representar o grafo
struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Função para criar um novo vértice
struct Vertex* createVertex(char name) {
    struct Vertex* newVertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    newVertex->name = name;
    newVertex->visited = 0;
    newVertex->next = NULL;
    return newVertex;
}

// Função para criar um grafo com um número específico de vértices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));

    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Função para adicionar uma aresta entre dois vértices
void addEdge(struct Graph* graph, char src, char dest) {
    struct Vertex* newVertex = createVertex(dest);
    int index = src - 'a';
    newVertex->next = graph->array[index].head;
    graph->array[index].head = newVertex;
}

// Função de busca em profundidade recursiva
void depthFirstSearch(struct Graph* graph, char vertex) {
    int index = vertex - 'a';
    struct Vertex* current = graph->array[index].head;

    // Marcar o vértice como visitado
    graph->array[index].head->visited = 1;
    printf("%c ", vertex);

    while (current != NULL) {
        index = current->name - 'a';
        if (graph->array[index].head->visited == 0) {
            depthFirstSearch(graph, current->name);
        }
        current = current->next;
    }
}

// Função para verificar se o grafo é conexo
int isGraphConnected(struct Graph* graph) {
    // Executa busca em profundidade a partir do primeiro vértice
    depthFirstSearch(graph, 'a');

    // Verifica se todos os vértices foram visitados
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->array[i].head != NULL && graph->array[i].head->visited == 0) {
            return 0; // O grafo não é conexo
        }
    }

    return 1; // O grafo é conexo
}

// Função para imprimir a estrutura do grafo
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Vertex* current = graph->array[i].head;
        printf("Adjacências do vértice %c: ", i + 'a');
        while (current != NULL) {
            printf("%c -> ", current->name);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    struct Graph* graph = createGraph(3);

    addEdge(graph, 'a', 'b');
    addEdge(graph, 'a', 'b');
    addEdge(graph, 'b', 'a');
    addEdge(graph, 'b', 'a');
    addEdge(graph, 'b', 'c');
    addEdge(graph, 'c', 'b');
    addEdge(graph, 'x', 'y');
    addEdge(graph, 'y', 'x');

    printf("Estrutura do Grafo:\n");
    printGraph(graph);

    printf("Busca em Profundidade a partir do vértice 'a':\n");
    depthFirstSearch(graph, 'a');
    printf("\n");

    if (isGraphConnected(graph)) {
        printf("O grafo é conexo.\n");
    } else {
        printf("O grafo não é conexo.\n");
    }

    return 0;
}

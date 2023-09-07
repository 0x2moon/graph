#include <stdio.h>
#include <stdlib.h>

struct relationship
{
    char name, infection;
    struct relationship *next;
};

struct vertex
{
    char name, infection;
    struct vertex *down;
    struct relationship *next;
};

struct graph
{
    int vertexSize;
    struct vertex *vertexStart;
};

struct vertex *createVertex(char name, char infection)
{
    struct vertex *newvertex = (struct vertex *)calloc(1, sizeof(struct vertex));
    newvertex->down = NULL;
    newvertex->next = NULL;
    newvertex->name = name;
    newvertex->infection = infection;
    return newvertex;
}

struct relationship *createRelationship(char name, char infection)
{
    struct relationship *newrelationship = (struct relationship *)calloc(1, sizeof(struct relationship));
    newrelationship->infection = infection;
    newrelationship->name = name;
    newrelationship->next = NULL;
    return newrelationship;
}

struct graph *createGraph()
{
    struct graph *newgraph = (struct graph *)calloc(1, sizeof(struct graph));
    newgraph->vertexStart = NULL;
    newgraph->vertexSize = 0;
    return newgraph;
}

struct vertex *searchVertexInGraph(struct vertex *vertex, char vertexName)
{
    if (vertex == NULL)
    {
        return NULL;
    }

    if (vertex->name == vertexName)
    {
        return vertex;
    }

    searchVertexInGraph(vertex->down, vertexName);
}

struct vertex *addvertexInGraph(struct graph *graph, struct vertex *vertex, char name, char infec)
{
    if (graph->vertexStart == NULL)
    {
        graph->vertexStart = createVertex(name, infec);
        graph->vertexSize++;
        return graph->vertexStart;
    }
    else
    {
        struct vertex *auxVertex = graph->vertexStart;
        while (1)
        {
            if (auxVertex->down == NULL)
            {
                auxVertex->down = createVertex(name, infec);
                graph->vertexSize++;
                return auxVertex;
            }
            auxVertex = auxVertex->down;
        }
    }
}

struct relationship *addRelationshipInGraph(struct vertex *vertexRelationship, char name, char infec)
{
    struct relationship *aux = vertexRelationship->next;

    if (vertexRelationship->next == NULL)
    {
        vertexRelationship->next = createRelationship(name, infec);
        return vertexRelationship->next;
    }
    else
    {
        while (1)
        {
            if (aux->next == NULL)
            {
                aux->next = createRelationship(name, infec);
                return aux;
            }
            aux = aux->next;
        }
    }
}

void printGraph(struct graph *graph)
{
    struct vertex *vertex = graph->vertexStart;
    while (vertex != NULL)
    {
        struct relationship *relationship = vertex->next;
        printf("Vertex [ %c%c ]-> ", vertex->name, vertex->infection);
        while (relationship != NULL)
        {
            printf(" [%c%c] :", relationship->name, relationship->infection);
            relationship = relationship->next;
        }
        puts("\n");
        vertex = vertex->down;
    }
}

struct graph *readFile(char *pathfile)
{
    struct graph *graph = createGraph();
    if (graph == NULL)
    {
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(pathfile, "r");
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    char buffer[3];
    struct vertex *vertexPresente = NULL;
    while (fread(&buffer, sizeof(char), 3, file))
    {
        if (buffer[2] == ',')
        {
            vertexPresente = searchVertexInGraph(graph->vertexStart, buffer[0]);
            if (vertexPresente == NULL)
            {
                vertexPresente = addvertexInGraph(graph, graph->vertexStart, buffer[0], buffer[1]);
                vertexPresente = searchVertexInGraph(graph->vertexStart, buffer[0]);
            }
        }

        if (buffer[2] == '\n')
        {
            addRelationshipInGraph(vertexPresente, buffer[0], buffer[1]);
        }
    }
    return graph;
}

int main()
{
    struct graph *g = readFile("pablo.csv");
    puts("inseriu");
    printGraph(g);
    return 0;
}
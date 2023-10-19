#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DOT "small.dot"
#define BRANCO 0
#define PRETO 1

// Estrutura do grafo
struct corresponding
{
    char name;
    int check;
    struct corresponding *next;
};

struct vertex
{
    char name;
    int check;
    struct vertex *down;
    struct corresponding *next;
};

struct graph
{
    int vertexSize;
    char *nameGraph;
    int connection;
    struct vertex *vertexStart;
};

// funções de criação do grafo
struct corresponding *createCorresponding(char name)
{
    struct corresponding *newCor = (struct corresponding *)malloc(sizeof(struct corresponding));
    newCor->next = NULL;
    newCor->name = name;
    newCor->check = BRANCO;
    return newCor;
}

struct vertex *createVertex(char name)
{
    struct vertex *newVertex = (struct vertex *)malloc(sizeof(struct vertex));
    newVertex->down = NULL;
    newVertex->next = NULL;
    newVertex->name = name;
    newVertex->check = BRANCO;
    return newVertex;
}

struct graph *createGraph()
{
    struct graph *newGraph = (struct graph *)malloc(sizeof(struct graph));
    newGraph->vertexStart = NULL;
    newGraph->vertexSize = 0;
    newGraph->nameGraph = NULL;
    newGraph->connection = BRANCO;
    return newGraph;
}

// Operações no graafo
struct vertex *addvertexInGraph(struct graph *graph, char name)
{
    if (graph->vertexStart == NULL)
    {
        graph->vertexStart = createVertex(name);
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
                auxVertex->down = createVertex(name);
                graph->vertexSize++;
                return auxVertex;
            }
            auxVertex = auxVertex->down;
        }
    }
}

struct corresponding *addCorrespondingInGraph(struct vertex *vertexCorresponding, char name)
{

    if (vertexCorresponding->next == NULL)
    {
        vertexCorresponding->next = createCorresponding(name);
        return vertexCorresponding->next;
    }
    else
    {
        struct corresponding *aux = vertexCorresponding->next;
        while (1)
        {
            if (aux->next == NULL)
            {
                aux->next = createCorresponding(name);
                return aux;
            }
            aux = aux->next;
        }
    }
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

void readNameGraphDot(struct graph *graph, FILE *file)
{
    char allocaName, *name = NULL;
    while (fread(&allocaName, sizeof(char), 1, file))
    {
        int crtlName = 0;
        if (allocaName != '\n')
        {
            crtlName++;
            char temp[2] = {allocaName, '\0'};
            if (name == NULL)
            {
                name = strdup(temp);
            }
            else
            {
                char *new = (char *)malloc(strlen(name) + 2);
                strcpy(new, name);
                strcat(new, temp);
                free(name);
                name = new;
            }
        }
        else
        {
            graph->nameGraph = name;
            break;
        }
    }
}

struct graph *fillGraphFile(char *pathfile)
{
    int crtl = 0;
    char buffer, duploBuffer[2];
    struct vertex *existingVertex = NULL;
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

    readNameGraphDot(graph, file);

    while (fread(&buffer, sizeof(char), 1, file))
    {
        if (buffer == '{')
        {
            continue;
        }

        if (buffer == '}')
        {
            break;
        }

        if (buffer == '\n')
        {
            continue;
        }

        if (buffer == ';')
        {
            crtl = 0;
            continue;
        }

        if (buffer == ' ')
        {
            continue;
        }

        if (buffer == '-')
        {
            crtl++;
            continue;
        }

        if (crtl == 0)
        {
            duploBuffer[crtl] = buffer;
        }
        else if (crtl == 2)
        {
            duploBuffer[crtl - 1] = buffer;
            existingVertex = searchVertexInGraph(graph->vertexStart, duploBuffer[0]);
            if (existingVertex == NULL)
            {
                addvertexInGraph(graph, duploBuffer[0]);
                existingVertex = searchVertexInGraph(graph->vertexStart, duploBuffer[0]);
                
            }
            addCorrespondingInGraph(existingVertex, duploBuffer[1]);
            existingVertex = searchVertexInGraph(graph->vertexStart, duploBuffer[1]);
            if (existingVertex == NULL)
            {
                addvertexInGraph(graph, duploBuffer[1]);
                existingVertex = searchVertexInGraph(graph->vertexStart, duploBuffer[1]);
                
            }
            addCorrespondingInGraph(existingVertex, duploBuffer[0]);
        }
        
    }
    fclose(file);
    return graph;
}

// Operações de fundamentos do grafo

void searchCorrespondingOfVertex(struct vertex *vertex, char vertexName)
{
    struct corresponding *corresponding = vertex->next;
    while (corresponding != NULL)
    {
        if (corresponding->name == vertexName)
        {
            corresponding->check = true;
            vertex->check = true;
            return;
        }
        corresponding = corresponding->next;
    }
}

// Desalocar o grafo
void freeCorrespondingAllocationStructure(struct corresponding *corresponding)
{
    if (corresponding == NULL)
    {
       return;
    }
    freeCorrespondingAllocationStructure(corresponding->next);
    free(corresponding);
}

void freeVertexAllocationStructure(struct vertex *vertex)
{
    if (vertex == NULL)
    {
        return;
    }
    freeCorrespondingAllocationStructure(vertex->next);
    freeVertexAllocationStructure(vertex->down);
    free(vertex);
}

void freeGraphAllocationStructure(struct graph *graph)
{
    if (graph == NULL)
    {
        return;
    }  
   freeVertexAllocationStructure(graph->vertexStart);
   free(graph);
}

// printar a estrutura do grafo
void printGraphAllocationStructure(struct graph *graph)
{
    printf("Nome: %s\n\n", graph->nameGraph);
    struct vertex *vertex = graph->vertexStart;
    while (vertex != NULL)
    {
        struct corresponding *corresponding = vertex->next;
        printf("Vertex [ %c - [%d]]-> ", vertex->name,vertex->check);
        while (corresponding != NULL)
        {
            printf(" [ %c - [%d] ] :", corresponding->name, corresponding->check);
            corresponding = corresponding->next;
        }
        puts("\n");
        vertex = vertex->down;
    }
}












void dps(struct graph *graph, char visitados[], char stack[], int i, int j)
{
    while (vs != NULL)
    {
        vs->check = 1;
        visitados[i] = vs->name;
        struct corresponding *aux = vs->next;
        while (aux != NULL)
        {
            stack[j] = aux->name;
            aux = aux->next;
            j++;
            
        }
        if (stack[j] != '0')
        {
            vs = searchVertexInGraph(graph->vertexStart, stack[j]);
        }
        
    }
    
}

void t(struct graph *graph){

    char visitados[graph->vertexSize], stack[graph->vertexSize];
    struct vertex *vs = graph->vertexStart;
    for (int h = 0; h < graph->vertexSize; h++)
        {
            visitados[h] = '0';
            stack[h] = '0';
        }


    int i = 0, j = 0;
}




int main()
{
    struct graph *g = fillGraphFile(DOT);
    printGraphAllocationStructure(g);
    dps(g);
    puts("\n\n\n");
    printGraphAllocationStructure(g);
    // printf("vertex size %d", g->vertexSize);
    freeGraphAllocationStructure(g);
}
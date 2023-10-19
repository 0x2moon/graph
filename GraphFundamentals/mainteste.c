#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Definição das estruturas*/
struct corresponding
{
    char name;
    struct corresponding *next;
};

struct vertex
{
    char name;
    struct vertex *down;
    struct corresponding *next;
};

struct graph
{
    int vertexSize;
    char *nameGraph;
    struct vertex *vertexStart;
};

/*Função de criação das estruturas*/
struct corresponding *createCorresponding(char name)
{
    struct corresponding *newCor = (struct corresponding *)malloc(sizeof(struct corresponding));
    newCor->next = NULL;
    newCor->name = name;
    return newCor;
}

struct vertex *createVertex(char name)
{
    struct vertex *newVertex = (struct vertex *)malloc(sizeof(struct vertex));
    newVertex->down = NULL;
    newVertex->next = NULL;
    newVertex->name = name;
    return newVertex;
}

struct graph *createGraph()
{
    struct graph *newGraph = (struct graph *)malloc(sizeof(struct graph));
    newGraph->vertexStart = NULL;
    newGraph->vertexSize = 0;
    newGraph->nameGraph = NULL;
    return newGraph;
}

/*aaa*/
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

void searchAndAddCorrespondingOfVertex(struct vertex *vertex, struct vertex *vertexPresenteAdd, char vertexName)
{
    struct vertex *currentVertex = vertex;
    while (currentVertex != NULL)
    {
        struct corresponding *aux = vertex->next;
        while (aux != NULL)
        {
            if (aux->name == vertexName)
            {
                addCorrespondingInGraph(vertexPresenteAdd, currentVertex->name);
            }

            aux = aux->next;
        }

        currentVertex = currentVertex->down;
    }
}

void searchAndAddCorrespondingWITHVertex(struct graph *graph, struct vertex *vertexPresenteAdd, char correspName, char buffer)
{
    struct vertex *v = searchVertexInGraph(graph->vertexStart, correspName);

    if (v != NULL)
    {
        struct corresponding *aux = v->next;

        while (aux != NULL)
        {
            if (aux->name == buffer)
            {
                addCorrespondingInGraph(vertexPresenteAdd, aux->name);
            }

            aux = aux->next;
        }
    }
}

struct graph *fillGraphFile(char *pathfile)
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

    char buffer, allocaName, primaryBuffer, secondBuffer, *name = NULL;
    int ctrlIntoGraph = 0, ctrlConnectionGraph = 0;
    struct vertex *existingVertex = NULL;

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

    while (fread(&buffer, sizeof(char), 1, file))
    {
        if (buffer == '{')
        {
            continue;
        }

        if (buffer == '}')
        {
            ctrlIntoGraph = 0;
            break;
        }

        if (buffer == '\n')
        {
            continue;
        }

        if (buffer == ';')
        {
            ctrlConnectionGraph = 0;
            continue;
        }

        if (buffer == ' ')
        {
            continue;
        }

        if (buffer == '-')
        {
            continue;
        }
    
        primaryBuffer = buffer;
        existingVertex = searchVertexInGraph(graph->vertexStart, primaryBuffer);
        secondBuffer  = primaryBuffer;
        
            if (existingVertex == NULL)
            {   
                addvertexInGraph(graph, primaryBuffer);
                existingVertex = searchVertexInGraph(graph->vertexStart,primaryBuffer);
                ctrlConnectionGraph = 1;
            }
        
      
          
            addCorrespondingInGraph(existingVertex, primaryBuffer);
            existingVertex = searchVertexInGraph(graph->vertexStart, buffer);
        
            if (existingVertex == NULL)
            {   
                primaryBuffer = buffer;
                addvertexInGraph(graph, buffer);
                existingVertex = searchVertexInGraph(graph->vertexStart,primaryBuffer);

            }
        
        
        
        
        
        
        
    }
    fclose(file);
    return graph;
}

/*Imprime a estrutura do grafo*/
void printGraphAllocationStructure(struct graph *graph)
{
    struct vertex *vertex = graph->vertexStart;
    while (vertex != NULL)
    {
        struct corresponding *corresponding = vertex->next;
        printf("Vertex [ %c ]-> ", vertex->name);
        while (corresponding != NULL)
        {
            printf(" [ %c ] :", corresponding->name);
            corresponding = corresponding->next;
        }
        puts("\n");
        vertex = vertex->down;
    }
}

int main()
{
    struct graph *g = fillGraphFile("text.dot");
    printGraphAllocationStructure(g);
    return 0;
}
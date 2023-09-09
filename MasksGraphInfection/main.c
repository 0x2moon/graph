/*
Disciplina:
┌┬┐┌─┐┌─┐┬┌─┌─┐  ┌─┐┬─┐┌─┐┌─┐┬ ┬  ┬┌┐┌┌─┐┌─┐┌─┐┌┬┐┬┌─┐┌┐┌
│││├─┤└─┐├┴┐└─┐  │ ┬├┬┘├─┤├─┘├─┤  ││││├┤ ├┤ │   │ ││ ││││
┴ ┴┴ ┴└─┘┴ ┴└─┘  └─┘┴└─┴ ┴┴  ┴ ┴  ┴┘└┘└  └─┘└─┘ ┴ ┴└─┘┘└┘
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Definição das estruturas*/
struct AnalyzeInfection
{
    char *infectionDescrition[4],
    *probability[4][4], *probabilityColors[4][4], *infectionNumber[4];
};

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

/*Funções de criação para cada estrutura*/
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

struct AnalyzeInfection *createAnalyze()
{
    struct AnalyzeInfection *analyze = (struct AnalyzeInfection *)malloc(sizeof(struct AnalyzeInfection));
    analyze->infectionDescrition[0] = "0 -> Sem máscara, sem infecção da COVID-19";
    analyze->infectionDescrition[1] = "1 -> Com máscara, sem infecção da COVID-19";
    analyze->infectionDescrition[2] = "2 -> Com máscara, com infecção da COVID-19";
    analyze->infectionDescrition[3] = "3 -> Sem máscara, com infecção da COVID-19";

    analyze->infectionNumber[0] = "0";
    analyze->infectionNumber[1] = "1";
    analyze->infectionNumber[2] = "2";
    analyze->infectionNumber[3] = "3";

    char *vectorAux[16] = 
    {"0%","0%","50%","100%","0%","0%","25%","50%","100%","100%","100%","100%","100%","100%","100%","100%",};

    char *vectorAuxColors[16] =
        {
            "\033[42;1;37m     0%       \033[m",
            "\033[42;1;37m     0%       \033[m",
            "\033[44;1;37m     50%      \033[m",
            "\033[41;1;37m     100%     \033[m",
            "\033[42;1;37m     0%       \033[m",
            "\033[42;1;37m     0%       \033[m",
            "\033[43;1;37m     25%      \033[m",
            "\033[44;1;37m     50%      \033[m",
            "\033[41;1;37m     100%     \033[m",
            "\033[41;1;37m     100%     \033[m",
            "\033[41;1;37m     100%     \033[m", 
            "\033[41;1;37m     100%     \033[m",
            "\033[41;1;37m     100%     \033[m",
            "\033[41;1;37m     100%     \033[m",
            "\033[41;1;37m     100%     \033[m",
            "\033[41;1;37m     100%     \033[m"};

    int aux = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            analyze->probability[i][j] = vectorAux[aux];
            analyze->probabilityColors[i][j] = vectorAuxColors[aux];
            aux++;
        }
    }
    return analyze;
}

/*Desalocar grafo*/
void freeRelationshipAllocationStructure(struct relationship *relationship)
{
    if (relationship == NULL)
    {
       return;
    }
    freeRelationshipAllocationStructure(relationship->next);
    free(relationship);
}

void freeVertexAllocationStructure(struct vertex *vertex)
{
    if (vertex == NULL)
    {
        return;
    }
    freeRelationshipAllocationStructure(vertex->next);
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

void freeAnalyze(struct AnalyzeInfection *analyse)
{
    free(analyse);
    return;
}

/*Funções de funcionalidade do grafo*/
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
    fclose(file);
    return graph;
}

/*Funções de analize do grafo*/
char *probality(struct AnalyzeInfection *analyze, char *firstPeople, char *secondPeople)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((strcmp(analyze->infectionNumber[i], firstPeople) == 0) && (strcmp(analyze->infectionNumber[j], secondPeople) == 0))
            {
                return analyze->probability[i][j];
            }
        }
    }
}

char *probalityColors(struct AnalyzeInfection *analyze, char *firstPeople, char *secondPeople)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((strcmp(analyze->infectionNumber[i], firstPeople) == 0) && (strcmp(analyze->infectionNumber[j], secondPeople) == 0))
            {
                return analyze->probabilityColors[i][j];
            }
        }
    }
}

void analyzeGraph(struct graph *graph)
{
    FILE *analyzeWriteFile = fopen("graph_analysis.txt", "w+");

    if (analyzeWriteFile != NULL)
    {
        struct AnalyzeInfection *analyze = createAnalyze();
        struct vertex *vertex = graph->vertexStart;
        fprintf(analyzeWriteFile, "------------------------------------------------------------------------------------------------------------------------");
        fprintf(analyzeWriteFile, "\nLegenda:\n");
        printf("------------------------------------------------------------------------------------------------------------------------");
        printf("\nLegenda:\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%s\n", analyze->infectionDescrition[i]);
            fprintf(analyzeWriteFile, "%s\n", analyze->infectionDescrition[i]);
        }

        printf("------------------------------------------------------------------------------------------------------------------------");
        printf("\n\n[ID] [NumberState] <-|[probability]|-> [ID] [NumberState]\n\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n\n");

        fprintf(analyzeWriteFile, "------------------------------------------------------------------------------------------------------------------------");
        fprintf(analyzeWriteFile, "\n\n[ID] [NumberState] <-|[probability]|-> [ID] [NumberState]\n\n");
        fprintf(analyzeWriteFile, "------------------------------------------------------------------------------------------------------------------------\n\n");

        while (vertex != NULL)
        {
            struct relationship *relationship = vertex->next;
            while (relationship != NULL)
            {
                fprintf(analyzeWriteFile, "[%c][%s] <-|[\t|%s|\t]|-> [%s][%s]\n", vertex->name, analyze->infectionDescrition[(int)(vertex->infection) - 48], probality(analyze, &vertex->infection, &relationship->infection), &relationship->name, analyze->infectionDescrition[(int)(relationship->infection) - 48]);
                printf("[%c][%s] <-|[%s]|-> [%s][%s]\n", vertex->name, analyze->infectionDescrition[(int)(vertex->infection) - 48], probalityColors(analyze, &vertex->infection, &relationship->infection), &relationship->name, analyze->infectionDescrition[(int)(relationship->infection) - 48]);
                relationship = relationship->next;
            }
            vertex = vertex->down;
        }
        fprintf(analyzeWriteFile, "------------------------------------------------------------------------------------------------------------------------");
        printf("------------------------------------------------------------------------------------------------------------------------");
        freeAnalyze(analyze);
    }
    fclose(analyzeWriteFile);
}

/*Imprime a estrutura do grafo*/
void printGraphAllocationStructure(struct graph *graph)
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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso incorreto. Por favor, forneça o path do arquivo CSV como argumento.\n");
        printf("Exemplo:\n\tcsv/small.csv\n\tcsv/big.csv\n");
        return 1;
    }

    char *pathname = argv[1];
    if (strstr(pathname, ".csv") != NULL) {
        struct graph *MasksGraphInfection = fillGraphFile(pathname); //Cria e preenche o grafo;
        analyzeGraph(MasksGraphInfection); //Escreve no arquivo txt e na tela as analizes;
        // printGraphAllocationStructure(MasksGraphInfection); //Printa a estrutura da lista alocada teorico;
        freeGraphAllocationStructure(MasksGraphInfection); // Desaloca a estrutra inteira;
        return 0;
    } 
    printf("Arquivo PRESCISA ser '.csv', tente novamente!"); 
}
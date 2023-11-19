#include <stdio.h>
#include <stdlib.h>

struct individuals
{
    char name, numberInfected;
};

struct nodeList
{
    int idNode;
    struct individuals *dataPeople;
    struct nodeList *prev, *next;
};

struct listAdj
{
    int id;
    struct nodeList *start;
    struct listAdj *down, *top;
};

struct graph
{
    struct listAdj *vectorListAdj;
};

struct graph *createGraph();
struct listAdj *createListAdj(struct graph *, struct listAdj *);
struct nodeList *createNodeList(struct graph *, struct listAdj *, struct nodeList *, char, char);
struct individuals *createIndividuals(struct graph *, struct listAdj *, struct nodeList *, char, char);

void createVertex_Adjlist(struct graph *, struct listAdj *, struct nodeList *, char, char)

// struct 
// int add(struct graph *, struct listAdj *, struct nodeList *, char, char);

// int idVerifyListAdj(char, struct listAdj *);
// int idVerifyNodeList(char, struct nodeList *);
// void readfile(char *);



int main()
{

    return 0;
}

struct graph *createGraph()
{
    struct graph *newgraph = (struct graph *) malloc (sizeof(struct graph));
    newgraph->vectorListAdj = NULL;
    return newgraph;
}

struct listAdj *createListAdj(struct graph *graph, struct listAdj *adjlist)
{
    struct listAdj *newlist = (struct listAdj *) malloc (sizeof(struct listAdj));

    if (graph->vectorListAdj == NULL)
    {
        graph->vectorListAdj = newlist;
        newlist->down = NULL;
        newlist->top = NULL;
        newlist->start = NULL;
        newlist->id = 0;
        return newlist;
    }

    if (adjlist->down == NULL)
    {
        adjlist->down = newlist;
        adjlist->down->top  = adjlist;
        adjlist->down->down = NULL;
        adjlist->down->id++;
        return newlist;

    }

    createListAdj(graph, adjlist->down);    
}

struct nodeList *createNodeList(struct graph *graph, struct listAdj *adjlist, struct nodeList *node, char name, char numberInfected)
{
    if (adjlist->start == NULL)
    {
        adjlist->start = (struct nodeList *) malloc (sizeof(struct nodeList));
        adjlist->start->idNode = 0;
        adjlist->start->prev = NULL;
        adjlist->start->next = NULL;
        adjlist->start->dataPeople = createIndividuals(graph,adjlist,adjlist->start, name, numberInfected);
        return adjlist->start;
    }
    
    if (node->next = NULL)
    {
        node->next = (struct nodeList *) malloc (sizeof(struct nodeList));
        node->next->idNode = node->idNode + 1;
        node->next = NULL;
        node->prev = node;
        node->dataPeople = createIndividuals(graph, adjlist, node->next, name, numberInfected);
        return node->next;
    }
    
    createNodeList(graph, adjlist, node->next,name, numberInfected);
}

struct individuals *createIndividuals(struct graph *graph, struct listAdj *adjlist, struct nodeList *node, char name, char numberInfected)
{
    struct individuals *newdata = (struct individuals *) malloc (sizeof(struct individuals));
    newdata->numberInfected = numberInfected;
    newdata->name = name;
    return newdata;
}

int add(struct graph *graph, struct listAdj *adjlist, struct nodeList * node, char name, char numberInfected);
{
    
}

void readfile(char *pathfile, struct graph *graph, struct listAdj *adjlist, struct nodeList *node)
{
    FILE *file = fopen(pathfile, "r");
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    char buffer;
    int controlState = 0, controlRelationship = 0;
    while (fread(&buffer, sizeof(char), 1, file))
    {   
        if (buffer == '#')
        {
            printf("\nFINAL\n");
            return;
        }

        if (buffer == '\n')
        {
            controlRelationship = 0;
            printf("\n");
        }

        if (controlRelationship == 1)
        {
            if (controlState == 0)
            {   controlState++;
                // name 
                printf("%c", buffer);
            }
            else
            {
                if (controlState == 1)
                {
                    controlState = 0;
                    // numbero de infecção
                    printf("%c", buffer);
                }
            }
            continue;
        }
       
        if (buffer == ',')
        {  
            // relacionamento contole 
            controlRelationship++;
            printf(", ");
            continue;
        }
       
        if (controlState == 0)
        {   controlState++;
             // node
            printf("%c", buffer);
        }
        else
        {
            if (controlState == 1)
            {
                controlState = 0;
                // numbero de infecção
                printf("%c", buffer);
            }
     
        }

    }
      
}

struct listAdj *idVerifyListAdj(char bufferChar, struct listAdj *Adljlist)
{   int auxnumber = 0;
    if (bufferChar == Adljlist->start->dataPeople->name)
    {
        auxnumber = Adljlist->id;
    }
    idVerifyListAdj(bufferChar, Adljlist->down);
    
}

int idVerifyNodeList(char, struct nodeList *);
#include <stdio.h>
#include <stdlib.h>

// • Sem m´ascara, sem infec¸c˜ao da COVID-19
//  0 para sem e 1 para com 
struct individuals
{
    int maskUse, infected;
};

struct nodeList
{
    struct individuals *dataPeople;
    struct nodeList *prev, *next;
};

struct listAdj
{
    struct nodeList *start;
    struct listAdj *down, *top;
};

struct graph
{
    struct listAdj *vectorListAdj;
};

struct graph *createGraph();
struct listAdj *createListAdj(struct graph *, struct listAdj *);
struct nodeList *createNodeList(struct graph *, struct listAdj *, struct nodeList *);
struct individuals *createIndividuals(struct nodeList *);


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

struct listAdj *createListAdj(struct graph *graph, struct listAdj *GraphVectorListAdj )
{
    struct listAdj *newList = (struct listAdj *) malloc (sizeof(struct listAdj));
    
    if (GraphVectorListAdj == NULL)
    { 
        newList->start = NULL;
        newList->down = NULL;
        newList->top = NULL;
        graph->vectorListAdj = newList;
        return newList;
    }

    if (GraphVectorListAdj->down == NULL)
    {
        GraphVectorListAdj->down = (struct listAdj *) malloc (sizeof(struct listAdj));
        GraphVectorListAdj->down->top = GraphVectorListAdj;
        return GraphVectorListAdj->down;
    }
    createListAdj(graph, GraphVectorListAdj->down);
}

struct nodeList *createNodeList(struct graph *graph, struct listAdj *listAdj, struct nodeList *node)
{
   if (listAdj->start == NULL)
   {
        listAdj->start =  (struct nodeList *) malloc (sizeof(struct nodeList));
        listAdj->start->prev = NULL;
        listAdj->start->next = NULL;
        return listAdj->start;
   }
   
   if (node->next == NULL)
   {
        node->next = (struct  nodeList *) malloc (sizeof(struct nodeList));
        node->next->prev = node;
        node->next->next = NULL;
        return node->next;
   }
   
    createNodeList(graph,listAdj,node->next);
}


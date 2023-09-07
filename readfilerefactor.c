
struct graph * readFile(char *pathfile)
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

    char buffer;
    char auxVertex[2];
    char auxRelationship[2];
    int controlState = 0, controlRelationship = 0, controlBuff[2];
    
    struct vertex *vertexPresente = NULL;
    struct relationship *relationshipPresente = NULL;
    
    controlBuff[1] = 0;    
    controlBuff[0] = 0;
    auxVertex[0] = '*';
    auxVertex[1] = '*';
    
    auxRelationship[0] = '*';
    auxRelationship[1] = '*';

    while (fread(&buffer, sizeof(char), 1, file))
    {   
        if (controlBuff[0] == 2)
        {
            struct vertex *searchVertex = searchVertexInGraph(graph->vertexStart,auxVertex[0]);
            if(searchVertex == NULL)
            {
                vertexPresente = addvertexInGraph(graph,graph->vertexStart, auxVertex[0],auxVertex[1]);
                controlBuff[0] = 0;
                auxVertex[0] = '*';
                auxVertex[1] = '*';
            }

        }
            if (controlBuff[1] == 2)
            {
                relationshipPresente = addRelationshipInGraph(vertexPresente, auxRelationship[0],auxRelationship[1]);
                controlBuff[1] = 0;
                auxRelationship[0] = '*';
                auxRelationship[1] = '*';
            }
       
        
        if (buffer == '#')
        {
            printf("\nFINAL\n");
            return graph;
        }

        if (buffer == '\n')
        {
            controlRelationship = 0;
            continue; 
        }

        if (controlRelationship == 1)
        {
            if (controlState == 0)
            {
                controlState++;
                // name relacionamenoto
                auxRelationship[0] = buffer;
                controlBuff[1]++;


            }
            else
            {
                if (controlState == 1)
                {
                    controlState = 0;
                    // numbero de infecção relacionamento
                    auxRelationship[1] = buffer;
                    controlBuff[1]++;
                }
            }
            continue;
        }

        if (buffer == ',')
        {
            // relacionamento contole
            controlRelationship++;
            continue;
        }

        if (controlState == 0)
        {
            controlState++;
            // vertex nome
            auxVertex[0] = buffer; 
            controlBuff[0]++;
        }
        else
        {
            if (controlState == 1)
            {
                controlState = 0;
                // numbero de infecção vertex
                auxVertex[1] = buffer;
               controlBuff[0]++;
            }
        }
    }
}

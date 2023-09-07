#include <stdio.h>
#include <stdlib.h>

void readfile(char *pathfile);
int main()
{
    readfile("teste.csv");
    return 0;
}

void readfile(char *pathfile)
{
    FILE *file = fopen(pathfile, "r");
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

 char buffer[3], auxVertex[2],auxRelationship[2];
    int controlState = 0, controlRelationship = 0;
    
    auxVertex[0] = '*';
    auxVertex[1] = '*';
    
    auxRelationship[0] = '*';
    auxRelationship[1] = '*';
    while (fread(&buffer, sizeof(char), 3, file))
    {   
        if(buffer[2] == ',')
        {
            struct vertex *searchVertex = searchVertexInGraph(graph->vertexStart,auxVertex[0]);
            if(searchVertex == NULL)
            {
                vertexPresente = addvertexInGraph(graph,graph->vertexStart, buffer[0],buffer[1]);
             
            }
            continue;
        }

        if (buffer[2] == '\n')
        {
           relationshipPresente = addRelationshipInGraph(vertexPresente, buffer[0],buffer[1]);
        }
        
       
        
    }
}

// funciona 
// void readfile(char *pathfile)
// {
//     FILE *file = fopen(pathfile, "r");
//     if (file == NULL)
//     {
//         exit(EXIT_FAILURE);
//     }

//     char buffer;
//     int controlState = 0, controlRelationship = 0;
//     while (fread(&buffer, sizeof(char), 1, file))
//     {   
//         if (buffer == '#')
//         {
//             printf("\nFINAL\n");
//             return;
//         }

//         if (buffer == '\n')
//         {
//             controlRelationship = 0;
//             printf("\n");
//         }

//         if (controlRelationship == 1)
//         {
//             if (controlState == 0)
//             {   controlState++;
//                 // name relacionamenoto
//                 printf("%c", buffer);
//             }
//             else
//             {
//                 if (controlState == 1)
//                 {
//                     controlState = 0;
//                     // numbero de infecção relacionamento
//                     printf("%c", buffer);
//                 }
//             }
//             continue;
//         }
       
//         if (buffer == ',')
//         {  
//             // relacionamento contole 
//             controlRelationship++;
//             printf(", ");
//             continue;
//         }
       
//         if (controlState == 0)
//         {   controlState++;
//              // vertex nome
//             printf("%c", buffer);
//         }
//         else
//         {
//             if (controlState == 1)
//             {
//                 controlState = 0;
//                 // numbero de infecção vertex
//                 printf("%c", buffer);
//             }
     
//         }

//     }
      
// }
// void readfile(char *pathfile)
// {
//     char byte, buffer[2];
//     int controlState = 0, controlRelationship = 0;
//     while (fread(&byte, sizeof(char), 1, file))
//     {   
//         if (buffer == '#')
//         {
//             printf("\nFINAL\n");
//             return;
//         }

//         if (buffer == '\n')
//         {
//             controlRelationship = 0;
//             printf("\n");
//         }

//         if (controlRelationship == 1)
//         {
//             if (controlState == 0)
//             {   controlState++;
//                 // name 
//                 printf("%c", buffer);
//             }
//             else
//             {
//                 if (controlState == 1)
//                 {
//                     controlState = 0;
//                     // numbero de infecção
//                     printf("%c", buffer);
//                 }
//             }
//             continue;
//         }
       
//         if (buffer == ',')
//         {  
//             // relacionamento contole 
//             controlRelationship++;
//             printf(", ");
//             continue;
//         }
       
//         if (controlState == 0)
//         {   controlState++;
//              // name 
//             printf("%c", buffer);
//         }
//         else
//         {
//             if (controlState == 1)
//             {
//                 controlState = 0;
//                 // numbero de infecção
//                 printf("%c", buffer);
//             }
     
//         }

//     }
      
// }
#include <stdio.h>
#include <stdlib.h>

struct individuals
{
    char maskUse, infected;
};

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

    }
      
}
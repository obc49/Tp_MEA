#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static void sorter(void *array, unsigned n);

static int comparer(const void *a, const void *b);
int main(void)
{   
    static const char test_reads[] = "test_reads.txt";
    char *line_array[20000];
    char line[101];
    int i = 0;
    int j = 0;
    //int k = 0;
    //int cpt = 0;

    //Ouverture du fichier reads.fasta en lecture
    FILE *file = fopen(test_reads, "r");
    //Ouverture du fichier trié en lecture & Ecriture
    FILE *sorted_test_reads = fopen("sorted_test_reads.txt","w+");

    if (file != NULL)
    {
        //Lecture ligne par ligne du fichier reads.fasta
        while (fgets(line, sizeof line, file) != NULL)
        {
           //On récupère le premier caractere de la ligne
           //char c = (char) line[0];

            // Trim the newline character
            line[strcspn(line, "\n")] = '\0';

            // Stop processing if line_array is full
            if (i < sizeof line_array / sizeof *line_array)
            {
                line_array[i++] = strdup(line);
            }
            else
            {
                break;
            }
       }
       //Fermeture du fichier reads.fasta
        fclose(file);
 
        //Tri du tableau contenant toutes les lignes du fichier sans les commentaires
        sorter(line_array, i);

        //Filtre du tableau trié en conservant une seule occurrence d'une lecture se apparaissant au moins deux fois
        for (j = 0; j < i; j++)
        {
            if(strlen(line_array[j])>1)
            {
                fprintf (sorted_test_reads,"%s\n",line_array[j]);
            }
        }
        
        // liberation de la memory
        for (j = 0; j < i; j++)
        {
            free(line_array[j]);
        }

    }
    // Error si le fichier n'a pas être ouvert
    else
    {
        perror(test_reads);
    }
    
    return 0;
}

//Fonction de comparaison
int comparer(const void *a, const void *b)
{
    return (strcmp(*(char **)a, *(char **)b));
}

//Fonction de tri
void sorter(void *array, unsigned n)
{
    qsort(array, n, sizeof(const char *), comparer);
}
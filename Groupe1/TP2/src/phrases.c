#include <stdio.h>
#include <string.h>

int main(void) {
    char filename[32]; 
    char extension[3] = "txt";
    char file[50];
    printf("Le nom du fichier à ouvrir: ");
    scanf("%s",filename);
    FILE *fp;
    strcpy(file, filename);
    file[strlen(filename)] = (char)'t';
    file[strlen(filename)+1] = (char)'x';
    file[strlen(filename)+2] = (char)'t';
    fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    char text[30];
    char pattern[50];
    int nbOcc[40];
    int lineNumber = 1;
    int countOnLine;
    int TAILLE_MAX_LIGNE = 50;

    printf("Phrase/expression a chercher : \n");
    scanf(" %49[^\n]", pattern);
    while((fgetc(fp)) != EOF){
        countOnLine = 0;
        while((fgetc(fp)) != '\n'){
            if((fgetc(fp)) == *pattern){
                if(strcmp(pattern, fgets(file, sizeof(pattern), fp)) == 1){
                    countOnLine++;
                }
            }  
        }
        nbOcc[lineNumber] = nbOcc[nbOcc[lineNumber]] +1;
        lineNumber++;
    }
    fclose(fp);
    printf("\n");
    return 0;
}
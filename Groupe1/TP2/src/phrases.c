#include <stdio.h>
#include <string.h>

int main(void) {
    char filename[32]; 
    char extension[3] = "txt";
    char file[50];
    printf("Le nom du fichier à ouvrir: ");
    scanf("%31s",filename);
    FILE *fp;
    int size = 1;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    int temp = ' ';
    while((temp = fgetc(fp)) != EOF){
        if(temp == '\n'){
            size++;
        }
    }
    rewind(fp);
    char pattern[50];
    int nbOcc[size+1];
    for(int i = 0; i <= size; i++) {
        nbOcc[i] = 0;
    }
    int lineNumber = 1;
    int TAILLE_MAX_LIGNE = 50;
    char current = ' ';
    printf("Phrase/expression a chercher : \n");
    scanf(" %49[^\n]", pattern);
    while(current != EOF){
        while(current != pattern[0] && current != '\n' && current != EOF){
            current = fgetc(fp);
        }
        if(current == '\n'){
            lineNumber++;
            current = fgetc(fp);
            continue;
        }
        if(current == pattern[0]){
            long offset = ftell(fp);
            int match = 1;
            for(int i = 1; i < strlen(pattern); i++){
                int nextChar = fgetc(fp);
                if(nextChar == EOF || nextChar != pattern[i]){
                    match = 0;
                    break;
                }
                else if(nextChar == '\n'){
                    match = 0;
                    break;
                }
            }
            if(match){
                nbOcc[lineNumber]++;
            }
            fseek(fp, offset, SEEK_SET);
            current = fgetc(fp);
        }
        current = fgetc(fp);
    }
    fclose(fp);
    for(int i = 1; i <= size; i++){
        printf("Nombre d'occurrences de \"%s\" à la ligne %d : %d \n", pattern, i, nbOcc[i]);
    }
    return 0;
}
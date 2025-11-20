#include <stdio.h>

char* phrases[10] = {
    "Bonjour, comment ça va ?",
    "Le temps est magnifique aujourd'hui.",
    "C'est une belle journée.",
    "La programmation en C est amusante.",
    "Les tableaux en C sont puissants.",
    "Les pointeurs en C peuvent être déroutants.",
    "Il fait beau dehors.",
    "La recherche dans un tableau est intéressante.",
    "Les structures de données sont importantes.",
    "Programmer en C, c'est génial.",

};

int len(char* s){
    int offset = 0;
    while(s[offset] != '\0'){
        offset++;
    }
    return offset; 
}

int main(void) {
    char pattern[100];    
    int position = 69;
    int found = 0;
    printf("Phrase/expression a chercher : \n");
    fgets(pattern, 100, stdin);
    if (pattern[len(pattern) - 1] == '\n') {
        pattern[len(pattern) - 1] = '\0'; 
    }
    int size = len(pattern);
    for(int i=0;i< 10;i++){
        if(len(phrases[i]) == size){
            int correct = 1;
            char* element = phrases[i];
            for(int j=0;j<len(element);j++){
                if(element[j] != pattern[j]){
                    correct = 0;
                    break;
                }
                else if (j == len(element)-1 && correct == 1){
                    position = i+1;
                    printf("Phrase trouvee en position : %d \n", position);
                    found = 1;
                }
            }
        }
    }
    if (found == 0){
        printf("Phrase non-trouvee \n");
    }
    return 0;
}
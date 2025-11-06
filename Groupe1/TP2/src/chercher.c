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
    int l = 0;
    while(s[offset] != '\0'){
        offset++;
    }
    return l;
    
}

int main(void) {
    char pattern[100];    
    int exist = 0;
    int position = 69;
    printf("Phrase/expression a chercher : \n");
    fgets(pattern, 100, stdin);
    for(int i=0;i< 10;i++){
        if(len(phrases[i]) == len(pattern)){
            int correct = 0;
            char* element = phrases[i];
            for(int j=0;j<len(element);j++){
                if(element[j] != pattern[j] && correct == len(element)-2){
                    printf("Phrase trouvee en position : %d ", position);
                    position = j+1;
                }
            }
        }
    }
    printf("Phrase non-trouvee \n");
    return 0;
}
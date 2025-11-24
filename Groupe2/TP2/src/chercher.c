/*
Author : Blaise Barriquand
Goal : Take a string in input and search it among a string array (tableau_phrases), without using standard C libraries
outside of stdio.
Notes : all the research of the strings are doing mannually, comparing each char after char.
*/

#include <stdio.h>

int main(){

    char tableau_phrases[10][100] = {
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
    char phrase_recherchee[100];

    //query de la phrase à chercher
    printf("Saisir une phrase à chercher : \n");
    scanf("%[^\n]",phrase_recherchee);
    printf("phrase cherchee : %s\n",phrase_recherchee);

    //calcul de la taille de la phrase (utile pour la recherche)
    int taille_phrase = 0;
    while(phrase_recherchee[taille_phrase] != '\0'){
        taille_phrase++;
    }

    //recherche de la phrase 
    int phrase_trouvee = 0; // si la phrase est trouvée, phrase_trouvee sera égal à taille_phrase
    for(int i=0 ; i<10 ; i++){ //pour chaque phrase
        for(int j=0 ; j<100 ; j++){ //et pour chaque caractères jusqu'a taille_phrase (nécessité d'aller jusqu'au bout)
            if(phrase_recherchee[j] == tableau_phrases[i][j]) //si caractère j correspond
                phrase_trouvee++; // on incrémente "phrase_trouvee"
        }
        if(phrase_trouvee == taille_phrase){ //si phrase_trouvee == taille_phrase, c'est que tous les caractères correspondent
            printf("Phrase trouvée ! Index %d\n", i);
            return 0;
        }else{
            phrase_trouvee = 0; //sinon on remet à 0 pour 
        }
    }
    printf("Phrase non trouvée !\n"); // on arrive ici uniquement si la phrase n'est pas trouvée

    return 0;
}
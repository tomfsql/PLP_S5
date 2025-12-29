/* ========= EXPLANATIONS ========= */
/* Programme principal pour tester la conversion postfixée et l'évaluation */

/* ========= INCLUDES ========= */
#include <stdio.h>
#include "postfix.h"
#include "lexer.h"
#include "evaluateur.h"

/* ========= MACROS ========= */

/* ========= GLOBAL VARIABLES ========= */

/* ========= FUNCTIONS ========= */

int main(){

    char commande[1024];
    while(1){
        printf("> "); // Affiche le prompt de commande
        // Lit la commande utilisateur et la stocke dans le buffer
        if(fgets(commande, sizeof(commande), stdin) != NULL) {
            double resultat = evaluateur(postfix(commande));
            
            printf("\nRésultat final du calcul : %.2f\n", resultat);
        }
        else{
            printf("Mauvaise utilisation\n");
        }
    }

    return 0;
}

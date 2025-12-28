#include <stdio.h>
#include <math.h>
#include "evaluation.h"


double evaluateur(Calcultab tab){

    double res = tab.calcul_i[0].operande1;
    //premier calcul réalisé d'office
    switch (tab.calcul_i[0].operateur)
        {
        case '/':
            if (tab.calcul_i[0].operande2 == 0) {
                printf("Erreur : Division par zéro !\n");
                return 0.0; // Ou une valeur d'erreur spécifique
            }
            res = res / tab.calcul_i[0].operande2;
            break;
        case '*':
            res = res * tab.calcul_i[0].operande2;
            break;
        case '+':
            res = res + tab.calcul_i[0].operande2;
            break;
        case '-':
            res = res - tab.calcul_i[0].operande2;
            break;
        default:
            break;
        }
    //et on continue s'il y en a d'autres
    if(tab.Calcultab_size > 1){
        for(int i=1 ; i<=tab.Calcultab_size ; i++){
            switch (tab.calcul_i[i].operateur){
            case '/':
                if (tab.calcul_i[i].operande2 == 0) {
                    printf("Erreur : Division par zéro !\n");
                    return 0.0; // Ou une valeur d'erreur spécifique
                }
                res = res / tab.calcul_i[i].operande2;
                break;
            case '*':
                res = res * tab.calcul_i[i].operande2;
                break;
            case '+':
                res = res + tab.calcul_i[i].operande2;
                break;
            case '-':
                res = res - tab.calcul_i[i].operande2;
                break;
            default:
                break;
            }
        }
    }
    return res;
}
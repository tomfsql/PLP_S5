#include <stdio.h>
#include "evaluation.h"


double evaluateur(Calcultab tab){

    double res = tab.calcul_i[0].operande1;
    for(int i=0 ; i<=tab.Calcultab_size ; i++){
        switch (tab.calcul_i[i].operateur1)
        {
        case '/':
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
        if(tab.calcul_i[i].operateur2 != '\0'){
            switch (tab.calcul_i[i].operateur2)
            {
            case '/':
                res = res / tab.calcul_i[i+1].operande1;
                break;
            case '*':
                res = res * tab.calcul_i[i+1].operande1;
                break;
            case '+':
                res = res + tab.calcul_i[i+1].operande1;
                break;
            case '-':
                res = res - tab.calcul_i[i+1].operande1;
                break; 
            default:
                break;
            }

        }
    }
    return res;

}
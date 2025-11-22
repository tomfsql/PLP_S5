#include <stdio.h>
#include <stdlib.h> // nécessaire pour la génération aléatoire des couleurs
#include <time.h> // idem


// variable pour sélectionner un remplissage aléatoire des valeurs (1 = oui, 0 = non). Remplissage prédéfini sinon
#define REMPLISSAGE_RANDOM 1

// disclaimer : pour faciliter la lecture des résultats, les composantes ARGB des couleurs sont capées par la valeur 
// MAX_ARGB_VALEUR et le nombre de couleurs est réduit à NOMBRE_COULEURS. Changer les paramètres ici si nécessaire

#define MAX_ARGB_VALEUR 2
#define NOMBRE_COULEURS 10


typedef struct {
    int R;
    int G;
    int B;
    int A;
}couleur;

int main(){

    couleur couleur_tab[NOMBRE_COULEURS]; //tableau de couleurs
    if(REMPLISSAGE_RANDOM){
        // replissage aléatoire des structures couleur
        srand(time(NULL)); // pour avoir une génération différente à chaque exec
        for(int i=0; i<NOMBRE_COULEURS; i++){
            int r = rand() % MAX_ARGB_VALEUR; //sélection d'un entier "aléatoire" entre 0 et MAX_ARGB_VALUE
            int g = rand() % MAX_ARGB_VALEUR; //idem
            int b = rand() % MAX_ARGB_VALEUR;
            int a = rand() % MAX_ARGB_VALEUR;
            couleur_tab[i].R=r;
            couleur_tab[i].G=g;
            couleur_tab[i].B=b;
            couleur_tab[i].A=a;
        }
    }else{ //remplissage prédéfini pour tests unitaires, 10 couleurs
        couleur_tab[0].R=7;couleur_tab[0].G=4;couleur_tab[0].B=2;couleur_tab[0].A=9;
        couleur_tab[1].R=3;couleur_tab[1].G=1;couleur_tab[1].B=8;couleur_tab[1].A=5;
        couleur_tab[2].R=7;couleur_tab[2].G=4;couleur_tab[2].B=2;couleur_tab[2].A=9;  // comme la 0
        couleur_tab[3].R=5;couleur_tab[3].G=8;couleur_tab[3].B=1;couleur_tab[3].A=6;
        couleur_tab[4].R=5;couleur_tab[4].G=8;couleur_tab[4].B=1;couleur_tab[4].A=6;  // comme la 3
        couleur_tab[5].R=1;couleur_tab[5].G=3;couleur_tab[5].B=6;couleur_tab[5].A=2;
        couleur_tab[6].R=8;couleur_tab[6].G=9;couleur_tab[6].B=4;couleur_tab[6].A=3;
        couleur_tab[7].R=2;couleur_tab[7].G=7;couleur_tab[7].B=5;couleur_tab[7].A=8;
        couleur_tab[8].R=7;couleur_tab[8].G=4;couleur_tab[8].B=2;couleur_tab[8].A=9;  // comme la 0
        couleur_tab[9].R=6;couleur_tab[9].G=5;couleur_tab[9].B=7;couleur_tab[9].A=1;           
    }
    // résultat attendu : couleur 7 4 2 9 : 3 fois , couleur 5 8 1 6 : 2 fois

    //int select = rand() % NOMBRE_COULEURS;
    //printf("Couleur n° %d , R : %d G : %d B : %d A : %d\n",select,couleur_tab[select].R,couleur_tab[select].G,couleur_tab[select].B,couleur_tab[select].A);
    
    //test pour voir si la couleur est unique :

    int occurence_couleur[NOMBRE_COULEURS]; // si la couleur n apparait k fois, occurence_couleur[n]==k
    int couleur_deja_trouvee[NOMBRE_COULEURS]; //si la couleur a deja été matchée avec une autre =1, 0 sinon
    for(int i = 0; i<NOMBRE_COULEURS;i++){
        occurence_couleur[i] = 1; //init à 1 
        couleur_deja_trouvee[i] = 0;
    }

        //comparaison des 4 composantes de la couleur à chaque autre couleur
    for(int i=0 ; i<NOMBRE_COULEURS ; i++){
        for(int j=0 ; j<NOMBRE_COULEURS ; j++){
            if(couleur_tab[j].R == couleur_tab[i].R &&
               couleur_tab[j].G == couleur_tab[i].G &&
               couleur_tab[j].B == couleur_tab[i].B &&
               couleur_tab[j].A == couleur_tab[i].A &&
               j!=i){
                if(couleur_deja_trouvee[i]==0){ //si couleur numéro i pas encore matchée avec une autre
                    occurence_couleur[i]++;
                    couleur_deja_trouvee[j] = 1;
                }
            }
        }             
    }

    //affichage du nombre d'occurence de chaque couleur
    for(int i=0 ; i<NOMBRE_COULEURS ; i++){
        if(couleur_deja_trouvee[i]==0)
        printf("Couleur R:%d G:%d B:%d A:%d occurences %d fois\n",
            couleur_tab[i].R,couleur_tab[i].G,couleur_tab[i].B,couleur_tab[i].A, occurence_couleur[i]);
    }


    return 0;
}
#include <stdio.h>
#include <math.h>

int main(){
    int rayon;
    printf("Saisir le rayon : ");
    scanf("%i",&rayon);
    float aire = rayon * M_PI * rayon;
    float perim = 2 * M_PI * rayon;
    printf("Aire : %.3f , perimètre : %.3f\n", aire,perim);

}
#include <stdio.h> 
#include <FL/math.h>
int main() {  
    float rayon;
    printf("Entrez le rayon : \n");
    scanf("%f", &rayon);
    float aire = M_PI * rayon * rayon;
    float perimetre = 2 * M_PI * rayon;
    printf("Area of the circle: %.4f\n", aire);
    printf("Perimeter of the circle: %.4f\n", aire);
    return 0;
}

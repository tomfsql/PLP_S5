#include <stdio.h>
#include <string.h>
struct couleur{
 char* nom;
};

int main() {
   struct couleur red = { "R"};

   struct couleur blue = { "B"};

   struct  couleur green = {"G"};

   struct couleur all = {"A"};

   struct couleur tab[100];

   for(int i=0;i<100;i++){
        if(i%4==0){
            tab[i]=red;
        }
        else if(i%5==0){
            tab[i]=blue;
        }
        else if(i%6==2){
            tab[i]=green;
        }
        else{
            tab[i]=all;
        }
    }

    int r=0;
    int b=0;
    int g=0;
    int a=0;

    for(int j=0;j<100;j++){
        if(tab[j].nom =="R"){
            r++;
        }
        else if(tab[j].nom =="B"){
            b++;
        }
        else if(tab[j].nom=="G"){
            g++;
        }
        else{
            a++;
        }
    }

    printf("Rouge : %d, Bleu : %d, Vert : %d, Autre : %d\n", r, b, g, a);
    return (0);
}
#include <stdio.h>
#include <string.h>

int main() {

   char chaine1[100];
   char chaine2[100];

   printf("Saisissez la premiere chaine : \n");
   scanf("%s", chaine1);

   printf("Saisissez la deuxieme chaine : \n");
   scanf("%s", chaine2);

   int len1 = strlen(chaine1);
   int len2 = strlen(chaine2);

   printf("Longueur de la premiere chaine avec strlen : %d \n", len1);
   printf("Longueur de la deuxieme chaine avec strlen : %d \n", len2);

   char* chaine3 = strcpy(chaine3, chaine2);
   printf("Affichage de chaine3 après strcpy(chaine3, chaine2) : %s \n", chaine3);

   char* chaine4 = strcat(chaine1, chaine2);
   printf("Affichage de chaine1 après strconcat(chaine1, chaine2) : %s \n", chaine4);

   return (0);

}
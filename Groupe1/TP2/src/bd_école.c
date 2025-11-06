#include <stdio.h>
#include <string.h>
struct etudiant{
 char prenom[30];
 char nom[30];
 char adresse[30];
 int notes[3];
};

int main() {
   struct etudiant dupont = { "Dupont", "Pierre", "Boulevard du 11 novembre 1918", {10,12,14}};

   struct etudiant sam = {
    .notes = {19, 15, 17}
   };

   strcpy(sam.prenom, "sam");
   strcpy(sam.nom, "Pierre");
   strcpy(sam.adresse, "Boulevard du 11 novembre 1918");

   char prenom3[30];
   char nom3[30];
   char adresse3[30];

   int n1;
   int n2;
   int n3;

   printf("Entre le prénom du 3e etudiant : \n");
   scanf("%s", prenom3);

   printf("Entre le nom du 3e etudiant : \n");
   scanf("%s", nom3);

   printf("Entre l'adresse du 3e etudiant, 30 caractères : \n");
   scanf(" %29[^\n]", adresse3);

   printf("Entre la note 1 du 3e etudiant : \n");
   scanf("%d", &n1);

   printf("Entre la note 2 du 3e etudiant : \n");
   scanf("%d", &n2);

   printf("Entre la note 3 du 3e etudiant : \n");
   scanf("%d", &n3);

   int notes3[3] = {n1, n2, n3};

   struct etudiant tom;

   strcpy(tom.prenom, prenom3);
    strcpy(tom.nom, nom3);
    strcpy(tom.adresse, adresse3);

    // 3. Assigner les notes
    tom.notes[0] = n1;
    tom.notes[1] = n2;
    tom.notes[2] = n3;

   printf("3e etudiant : \n");
   printf("%s ", tom.prenom);
   printf("%s \n", tom.nom);
   printf("Adresse : %s \n", tom.adresse);
   printf("Notes: %d, %d, %d\n", tom.notes[0], tom.notes[1], tom.notes[2]);

      return (0);

}
/*
Author : Blaise Barriquand
Goal : learn how to handle structures, strings, and user input
Notes : the program is just about testing how strucures and string manipulation works. It doesnt have a real purpose
*/

#include <stdio.h>
#include <string.h>

struct adresse{
    char rue[20];
    int numero;
};

struct etudiant{
    char nom[20];
    char prenom[20];
    struct adresse studentadresse;
    int notes[20];
};

struct etudiant etudiant1;
struct etudiant etudiant2 ={
    .nom = "Doe",
    .prenom = "John",
    .studentadresse.rue = "Rue de France",
    .studentadresse.numero = 10,
    .notes = { 12,4,15,12,14}
};
struct etudiant etudiant3;
struct etudiant etudiant4;
struct etudiant etudiant5;


int main(){

    
    printf("Saisir les informations d'etudiant1 : \n");
    printf("Nom : ");
    scanf(" %[^\n]",etudiant1.nom);
    printf("Prenom : ");
    scanf(" %[^\n]",etudiant1.prenom);
    printf("Adresse (rue) : ");
    scanf(" %[^\n]",etudiant1.studentadresse.rue);
    printf("numéro de rue : ");
    scanf(" %d", &etudiant1.studentadresse.numero);
    printf("Note 1 : ");
    scanf(" %d",etudiant1.notes);

    printf("-----Informations saisies etudiant1:----- \n");
    printf("Nom : %s\nPrenom : %s\n", etudiant1.nom,etudiant1.prenom);
    printf("Adresse :%d %s \n",etudiant1.studentadresse.numero,etudiant1.studentadresse.rue);
    for(int i = 0; i<20;i++){
        if(etudiant1.notes[i]){
            printf("Note : %d\n",etudiant1.notes[i]);
        }
    }
    printf("Recopier les données de l'étudiant1 dans le 2 ? (y / n)\n");
    char c;
    scanf(" %c",&c);
    if(c=='y'){
        strcpy(etudiant2.nom,etudiant1.nom);
        strcpy(etudiant2.prenom,etudiant1.prenom);
        etudiant2.studentadresse.numero=etudiant1.studentadresse.numero;
        strcpy(etudiant2.studentadresse.rue,etudiant1.studentadresse.rue);
        for(int i = 0; i<20;i++){
            etudiant2.notes[i] = etudiant1.notes[i];
        }

        printf("-----Informations saisies etudiant2 :----- \n");
        printf("Nom : %s\nPrenom : %s\n", etudiant1.nom,etudiant1.prenom);
        printf("Adresse :%d %s \n",etudiant1.studentadresse.numero,etudiant1.studentadresse.rue);
        for(int i = 0; i<20;i++){
            if(etudiant1.notes[i]){
                printf("Note : %d\n",etudiant1.notes[i]);
            }
        }
    }
    
    return 0;
}
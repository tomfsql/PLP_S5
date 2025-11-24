/*
Author : Blaise Barriquand
Goal : Search a specified string in a specified file.
Notes : Test example file is called "aled", looking for "aled" string in it.
*/

#include <stdio.h>
#include <string.h>


int main(){

    char phrase[200];
    char nom_fichier[200];
    FILE* fichier_ptr;
    printf("Entrer la phrase à chercher :\n");
    scanf(" %[^\n]",phrase);
    printf("Entrer le nom du fichier : ");
    scanf(" %[^\n]",nom_fichier);
    printf("Phrase : %s\n",phrase);
    printf("Fichier : %s\n",nom_fichier);
    fichier_ptr = fopen(nom_fichier,"r");
    if(fichier_ptr == NULL){ //test si le fichier existe
        printf("Erreur : fichier non existant\n");
        return 1;
    }else{
        printf("Ouverture fichier réussie\n");
    }

    //compteur du nombre de lignes du fichier 
    int nombre_lignes = 1;
    char char_temp = ' ';
    while((char_temp=fgetc(fichier_ptr))!=EOF){
        if(char_temp == '\n'){ // si caract. lu = fin de ligne
            nombre_lignes++; //incr. compteur de lignes
        }
    }
    fseek(fichier_ptr,0,SEEK_SET); //remise à 0 de la tete de lecture
    // tableau qui servira à stocker le nombre d'occurences par ligne, init. à 0
    int occurences_par_ligne[nombre_lignes]; 
    for(int i = 0; i<nombre_lignes;i++){
        occurences_par_ligne[i] = 0;
    }

    printf("Nombre de lignes : %d\n", nombre_lignes);

    // recherche de la taille de la chaine (utile pour plus tard)
    printf("Calcul de la taille de la phrase...");

    int taille_phrase = 0;
    while(char_temp!='\0'){
        char_temp = phrase[taille_phrase];
        taille_phrase++;
    }
    printf("%d\n",(taille_phrase-1));

    // recherche de la phrase dans le fichier :
    // on calcule la taille de la string d'entrée. On prend, depuis le premier caractère du fichier, 
    // une chaine de la même taille (fgets), et on la compare (strcmp). On incrémente le compteur 
    // de caractère (qui sert plus tard). Si la chaine correspond, on incrément le compteur d'occurence.
    // On remet le pointeur de texte à 0 (fseek), puis on le redécale (boucle for + fgetc) avec le compt
    // eur de caractère


    //comparaison de la chaine fichier avec celle cherchée. Si mauvais, on déplace les caractères de 1
    printf("Recherche de la phrase\n");
    char chaine_fichier[200];
    int compteur_chaine=0;
    int ligne_actuelle = 0; //ligne traitée actuellement

    do{
        //on copie la chaine du fichier dans chaine_fichier
        fgets(chaine_fichier,taille_phrase,fichier_ptr);
        //debug printf("Chaine %d : %s\n",compteur_chaine,chaine_fichier);
        // et on teste avec la chaîne cherchée
        if(strcmp(chaine_fichier,phrase) == 0){ //si une occurence est trouvée
            occurences_par_ligne[ligne_actuelle]++;
        }
        compteur_chaine++;
        fseek(fichier_ptr,0,SEEK_SET); //remise de la tete de lecture à 0
        for(int i = 1;i<compteur_chaine;i++){ // remise de la tete de lecture au caractère traité précedemment +1
            fgetc(fichier_ptr);
        }
        if(chaine_fichier[taille_phrase-2] == '\n'){ // si on arrive en fin de ligne (-2 car \0 et taille_phrase 
            // comprend \0 aussi donc encore -1)
            ligne_actuelle++; // on incrémente pour savoir qu'on est à la suivante
            //debug printf("ligne suiv !\n");
        }
    }
    while(fgetc(fichier_ptr) != EOF); //tant qu'on est pas arrivé à la fin du fichier, on incrémente le pointeur texte de 1

    //affichage des lignes où des occurences ont été trouvées
    int occurence_trouvee = 0; //savoir si des occurences ont été trouvées
    for(int i = 0; i<nombre_lignes;i++){
        if(occurences_par_ligne[i]!=0){ // on affiche pas les lignes ou il n'y a pas d'occurence
            printf("Occurence trouvée : ligne %d, %d fois\n",i+1,occurences_par_ligne[i]);
            occurence_trouvee++;
        }
    }
    if(occurence_trouvee==0){
        printf("Aucune occurence trouvée !\n");
    }
    return 0;
}
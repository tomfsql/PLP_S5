## Débogage avec GDB 

Sur le programme `erreurs.c`, le plantage venait du fait que la boucle utilisait `sizeof(tableau)` au lieu de la taille logique 100, ce qui faisait écrire bien au-delà des bornes du tableau et provoquait un stack smashing.
En recompilant avec les infos de debug (`gcc -ggdb3 erreurs.c -o erreurs`) puis en lançant le binaire dans le débogueur, il est possible de poser des breakpoints, d’exécuter pas à pas et d’inspecter les variables pour comprendre précisément où et pourquoi le programme explose.
Cette approche oblige à regarder l’état réel de la mémoire plutôt que de « deviner » le bug, ce qui est très formateur pour repérer les dépassements de tableaux et autres erreurs de logique. 

## Chaîne de compilation en C avec gcc 

Avec `aire.c` et le mini‑projet `sphere`, la chaîne complète a été déroulée : prétraitement (`gcc -E`), compilation en assembleur (`-S`), assemblage en `.o` (`-c`) puis édition de liens, parfois avec des bibliothèques comme `-lm` pour `math.h`. 
Travailler en plusieurs fichiers (`main.c`, `surface.c`, `volume.c`, `sphere.h`) montre bien l’intérêt des en-têtes pour partager les prototypes et du lien final qui assemble les différents objets en un seul exécutable. 
En jouant avec les options d’optimisation (`-O2`, `-O3`), on voit aussi que la compilation n’est pas juste une « traduction », mais une phase où le compilateur peut transformer le code pour le rendre plus efficace. 

## Manipulation de chaînes 

Dans `chaine.c`, les fonctions maison pour calculer la longueur et concaténer deux chaînes reproduisent l’idée de `strlen` et `strcat`, mais en manipulant directement les pointeurs et le caractère de fin `'\0'`. 
La lecture des lignes complètes avec `scanf(" %[^\n]", ...)` et l’usage d’un tampon global de 400 caractères obligent à réfléchir aux tailles de buffers pour éviter les débordements. 
Ce travail montre que la manipulation de chaînes en C reste très bas niveau : rien n’est vérifié pour nous, et la moindre erreur d’indice peut casser tout le programme. 

## Structures, données et recherche 

Le fichier `bd_école.c` utilise des `struct` imbriquées (`etudiant` contenant une `adresse` et un tableau de notes), ce qui permet de regrouper proprement toutes les informations d’un étudiant et de les recopier avec `strcpy` et des boucles. 
Les programmes `phrases.c` et `chercher.c` illustrent deux types de recherche de texte : dans un fichier via `fopen`/`fgets` avec comptage d’occurrences par ligne, et dans un tableau de 10 phrases en comparant caractère par caractère sans s’appuyer sur les fonctions de la bibliothèque standard. 
Enfin, `couleurs.c` montre un autre usage des structures avec un tableau de 100 couleurs RGBA et un comptage des occurrences, ce qui oblige à raisonner à la fois sur les données et sur la logique de comparaison pour ne pas compter deux fois la même couleur. 
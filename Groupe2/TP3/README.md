# Bibliothèques
* 
*

# Références
*
*

# Difficulté
* Dans la gestion des nombres négatifs, car '-' peut être interprété comme opérateur. J'ai fini par aboutir à un lexer beaucoup plus efficace que le schéma sur lequel je suis parti à l'origine, en repartant de 0.

# Commentaires
- Qu'est-ce qui se passe lorsque vous tapez une commande inconnue?
=> Le programme compare la chaîne entrée une par une avec les différentes commandes disponibles. S'il n'en trouve aucune, il arrive au dernier else qui contient le message d'erreur.
- Comment l'interpréteur traite les espaces dans les commandes?
=> La comparaison entre la chaine entrée et les commandes disponibles se fait caractère par caractère, et seul la fin de chaîne ou le retour à la ligne permettent de s'arrêter (pour echo par ex.)
- Qu'est-ce qui se passe lorsque vous utilisez la commande echo avec des arguments?
=> La comparaison pour savoir si la commande est bonne se fait donc uniquement sur les 5 (echo + 1 espace) premiers charactères. Si ils correspondent à "echo ", on affiche alors "echo :" et la chaine capturée au début du programme à partir du 6e élement. 
- Comment pourriez-vous modifier le code pour ajouter de nouvelles commandes?
=> ajouter une étape if/else supplémentaire.
* 



## Compilation et execution

Pour compiler le projet, il suffit d'utiliser le `Makefile` fourni (qui gère la compilation de `repl.c`, `lexer.c`, `parseur.c` et `evaluation.c`) :

```bash
make && ./repl
```
## fonctionnalités 

### Commandes multilingues fr/en

L'interpréteur détecte automatiquement la langue en fonction de la commande saisie :

* **Aide** : `help` ou `aide`.
* **Version** : `version`.
* **Date** : `date` (affiche l'heure et la date système).
* **Echo** : `echo <texte>` (répète le texte saisi).
* **Quitter** : `quit`, `exit` ou `quitter`.

### Calculatrice intégrée

Le programme peut évaluer des expressions mathématiques simples.

* **Détection automatique** : On peut taper directement un calcul (ex: `2+3.5`) sans préfixe, ou utiliser la commande `repl`.
* **Opérations** : Addition (`+`), Soustraction (`-`), Multiplication (`*`), Division (`/`).
* **Support** : Nombres décimaux (doubles) et nombres négatifs (ex: `-5 * 2`).
* **Gestion des divisions par 0** qui retourne une erreur

## Notes de développement

* **Priorités opératoires** : Pour l'instant, les calculs sont évalués séquentiellement de gauche à droite (ex: `2 + 3 * 4` donnera `20` et non `14`).

---

**Auteur :** Blaise Barriquand 3IRC CPE Lyon

**Version :** 1.5

---

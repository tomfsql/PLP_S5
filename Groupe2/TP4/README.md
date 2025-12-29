# Références

* Algorithme Shunting-Yard (Gare de triage) pour la conversion infixée vers postfixée.
* Utilisation d'une pile pour l'évaluation des expressions en notation polonaise inverse (RPN).

# Difficultés

* La gestion des priorités dans la pile d'opérateurs, surtout avec les parenthèses. Il a fallu faire attention à ce que la parenthèse ouvrante dans la pile bloque les autres opérateurs sans être dépilée par erreur.
* L'organisation des fichiers pour que le `main` de l'interpréteur (`repl.c`) puisse communiquer avec les variables globales de l'évaluateur (utilisation de `extern int calcul_erreur`).

# Commentaires

* Comment l'interpréteur gère-t-il les priorités opératoires maintenant ?
=> Contrairement au TP3 où le calcul se faisait de gauche à droite, on passe maintenant par une étape de "traduction" en notation postfixée. Cela permet de traiter les multiplications avant les additions et de respecter les parenthèses sans changer l'évaluateur.
* Pourquoi utiliser des Tokens plutôt qu'une simple chaîne de caractères pour le calcul ?
=> C'est beaucoup plus fiable pour gérer les nombres à plusieurs chiffres (ex: 125) ou les nombres négatifs. Le lexer transforme déjà tout en unités logiques, ce qui évite de manipuler des codes ASCII dans la pile.
* Qu'est-ce qui se passe en cas d'erreur de saisie (ex: "2 / 0" ou "1 + + 2") ?
=> J'ai ajouté un flag `calcul_erreur`. Si l'évaluateur manque d'opérandes dans sa pile ou détecte un diviseur nul, il affiche un message d'erreur et arrête le calcul proprement au lieu de faire crash le programme.
* À quoi sert le fichier `main.c` présent dans le dossier ?
=> C'est un fichier de test isolé. Il permet de tester uniquement la chaîne Lexer -> Postfix -> Evaluateur sans lancer toute l'interface de l'interpréteur de commandes.

## Compilation et exécution

Le `Makefile` compile l'ensemble des modules (`repl.c`, `lexer.c`, `postfix.c`, `evaluateur.c`). Pour lancer l'interpréteur complet :

```bash
make && ./repl

```

Warning de compilation sur une variable inutilisée normal (sert de debug).

## Fonctionnalités

### Commandes multilingues fr/en

L'interpréteur reconnaît les commandes de base dans les deux langues :

* **Aide** : `help` ou `aide`.
* **Version** : `version`.
* **Date** : `date`.
* **Echo** : `echo <texte>`.
* **Quitter** : `quit`, `exit` ou `quitter`.

### Calculatrice avancée (TP4)

Le moteur de calcul a été entièrement refait :

* **Notation infixée** : Support des parenthèses, ex : `2 * (3 + 4)`.
* **Notation postfixée** : On peut aussi entrer directement des expressions en postfixé si on veut.
* **Priorités** : Respect des règles mathématiques standard (* et / avant + et -).
* **Gestion d'erreurs** :
* Détection des caractères invalides (ex: `a + 1`).
* Erreur de syntaxe (ex: `1 + * 2`).
* Division par zéro.



## Notes de développement

* **Évaluation** : L'évaluateur utilise une pile de `Tokens` de type nombre. Chaque opérateur dépile les deux derniers nombres pour traiter le calcul et ré-empile le résultat.
* **Scalabilité** : Le passage par un tableau de Tokens entre chaque étape (Lexer -> Postfix -> Eval) rend le code beaucoup plus facile à débugger avec les `printf`.

---

**Auteur :** Blaise Barriquand 3IRC CPE Lyon

**Version :** 2.0 (intégration pile et postfixé, évaluateur 100% opérationnel)

---
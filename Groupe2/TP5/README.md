# Références

* Gestion d'une table de symboles pour la persistence des données.
* Introduction aux expressions Lambda (fonctions anonymes) et mécanisme de substitution de paramètres.

# Difficultés

* **Gestion des types** : La contrainte de ne pas pouvoir changer le type d'une variable une fois définie a demandé d'ajouter une vérification systématique dans la table des symboles avant chaque affectation.
* **Parsing des Lambda** : L'extraction des différentes parties de la commande `(lambda x.expression) valeur` était complexe. Il a fallu isoler proprement le paramètre, le corps de la fonction et l'argument pour effectuer la substitution avant d'envoyer le tout au moteur de calcul.
* **UTF-8** : Pour supporter des variables comme `π`, le Lexer a été modifié pour accepter les caractères dont le code est supérieur à 127, traitant ainsi les séquences d'octets Unicode sans erreur.

# Commentaires

* Comment est gérée la persistance des types pour les variables ?
=> Lors de la première affectation, la fonction `detect_type` identifie s'il s'agit d'un entier, d'un réel ou d'une chaîne. Cette information est stockée dans la structure `Variable`. Si l'utilisateur tente de réaffecter la même variable avec un type différent, le programme compare le nouveau type détecté avec celui en mémoire et bloque l'opération si ils diffèrent.
* Comment l'interpréteur traite-t-il les variables au milieu d'un calcul ?
=> Le Lexer reconnaît désormais les "identifiants". Lors de l'évaluation postfixée, si l'évaluateur tombe sur un jeton de type variable, il va chercher sa valeur numérique dans la `variable_array` avant d'effectuer l'opération.
* Quel est le processus d'évaluation d'une expression Lambda ?
=> Le programme fonctionne en trois étapes : il extrait le nom du paramètre (ex: `x`), il récupère la valeur de l'argument (soit un nombre, soit une variable existante), puis il effectue une substitution textuelle dans le corps de l'expression. La chaîne résultante, redevenue un calcul classique, est alors envoyée aux fonctions `postfix` et `evaluateur`.

## Compilation et exécution

Le `Makefile` a été mis à jour pour inclure le module `variables.c`. La commande reste la même :

```bash
make && ./repl

```

## Fonctionnalités (TP5)

### Gestion des variables

L'interpréteur permet désormais de stocker des données en mémoire :

* **Affectation** : `x = 10` ou `nom = "CPE"`.
* **Consultation** : Taper simplement le nom d'une variable (ex: `> x`) affiche sa valeur actuelle.
* **Types supportés** : Entiers, réels et chaînes de caractères (entre guillemets).
* **Support UTF-8** : Possibilité d'utiliser des caractères spéciaux pour les noms, ex: `π = 3.14`.

### Expressions Lambda

Support des fonctions anonymes avec substitution dynamique :

* **Syntaxe** : `(lambda <paramètre>.<expression>) <argument>`.
* **Exemple** : `(lambda x.x + 2 * x) 3` retourne `9.00`.
* **Arguments variables** : On peut utiliser une variable définie comme argument, ex: `(lambda x.x + 1) y`.

## Notes de développement

* **Ordre de traitement** : La boucle principale du `repl.c` utilise une structure `if / else if` stricte. Cela évite que les expressions Lambda ou les affectations de variables ne soient interprétées par erreur comme des calculs mathématiques simples.
* **Table des symboles** : Elle est limitée à 100 variables (`MAX_VARS`) pour garantir la stabilité de la mémoire statique.

---

## **Auteur :** Blaise Barriquand 3IRC CPE Lyon **Version :** 3.0 (Variables, UTF-8 et Expressions Lambda)

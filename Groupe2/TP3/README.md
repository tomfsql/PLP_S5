# Bibliothèques
* 
*

# Références
*
*

# Difficulté
*

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


# TP1: GeoNames


## Description

Ce travail a été donné dans le cadre du corus INF3135. Ceci est le premier travail pratique. 

Le projet a pour but de passer à travers un document texte (cities15000.txt) et afficher les villes en
ordre décroissant selon leur population.

Aussi, insérer un lien vers le [sujet du travail](https://gitlab.info.uqam.ca/inf3135-sdo/geonames/-/blob/main/sujet.md).

## Auteur
Kareen Gresseau 
GREK03569800



## Fonctionnement

Dans le terminal, écrire la commande : ./geonames "nombre de ville voulue" 

### Validité des arguments 

Le code commence par valider l'argument 

- Si l'utilisateur écrit juste ./geonames ou si il ecrit plusieur mots après, il recevra un message d'erreur disant que 
  le nombre d'argument est invalide
- Si l'utilisateur entre un élément après ./geonames qui n'est pas un chiffre, il receva un message d'erreur disant que 
  le type d'argument est invalide
- Si l,utilisateur entre un nombre qui n'est pas entre 1 et 5000, il recevra un message d'erreur disant que le nombre de ville
  est invalide.
   
### Les structures 
Les structures sont des regroupement d'informations qui contiennent des variables de plusieurs types. C'est un concept qui est
similaire aux constructeurs en JAVA.

Le code contient une structure de type VILLE qui contient:
- un string pour le nom de la ville
- un string pour le nom du pays
- un long int pour la population. 
Quand l'utilisateur entre le nombre de ville qu'il veut, cela crée un tableau de type ville de longueu du nombre de villes.  

Le code contien aussi une structure de type PAYS qui contient:
- un string pour le code ASCII d'un pays
- Le nom complet du pays associé.
Dans le document countryInfo.txt, il y a 252 pays mentionné. J'ai alors créé un tableau de structure PAYS qui contient 252 cellules.  

### Chercher les pays

Le code va ensuite passer à travers le fichier countryInfo.txt pour récupérer les codes ASCII et les nom des pays. 
Ces données seront enregistrées dans le tableau de structure PAYS. 

### Rechercher les villes. 

Chaque ligne du fichier cities15000.txt contient les information d'une ville qui a au moins 15000 habitants. L'information qu'on recherche 
est le nom de la ville, le code ASCII et la population.
- Ce document ne contient pas le noms de pays, alors il faudra aller les cherches avec les code ASCII. On prend le code ASCII et on le compare 
  à chaque code ASCII qui est dans le tableau PAYS. Lorsqu'on trouve la bonne réponse, on récupère le pays. 


### Trier les villes. 

Si le nombre de ville récupéré est plus petit que le nombre de ville voulue, les information sur une ville sera enregistré dans la première cellule
disponible dans le tableau de structure VILLE. Sinon, la population sera comparé avec les populations enregistrées dans le tableau pour positionner
la nouvelle à la bonne place. 


### Afffichage

Lorsqu'on a terminé de passé à travers le fichier cities15000, Le code va afficher le contenu du tableau de structure VILLE.



## Tests

Pour lancer les tests, écrire sur le terminal la commande "make test"
Le document check.bats vérifie l'argument entré dans le terminal et l'affichage
à la fin du code. S'assure de sortir le résultat attendu. 
Les tests 1 a 8 fonctionnent sur le terminal
les tests 9 et 10 ne fonctionnent pas. 
J'ai laissé les tests 6 à 10 en mode skip parce que j'avais des problèmes dans mon pipeline lorsque je déposait mon travail sur Gitlab

## Dépendances
- Bats pour les test [Bats](https://github.com/bats-core/bats-core)
- GCC (gnu c compiler) pour compiler le projet sans avoir recours à un IDE 
- Pandoc
- unzip
- curl

## Références
Pour completer le travail, j'ai dû faire de la recherche externe pour régler des problèmes.

1. J'ai utilisé la méthode strtok() pour récupéré les informations dans le fichier textes. voici le [lien](https://www.educative.io/answers/splitting-a-string-using-strtok-in-c)
2. J'ai voulu créer des pointeurs pour un tableau de string. Pour savoir commenta faire, je trouvé de l'information sur un chaîne de discussion sur [StackOverflow](https://stackoverflow.com/questions/33968018/how-to-assign-2d-string-array-to-char-pointer-array)
3. J'ai voulu faire des pointeurs pour mes structures. j'ai trouvé comment faire avec ce [lien](https://overiq.com/c-programming-101/pointer-to-a-structure-in-c/)

## État du projet

Indiquez toutes les tâches qui ont été complétés en insérant un `X` entre les
crochets. Si une tâche n'a pas été complétée, expliquez pourquoi (lors de la
remise, vous pouvez supprimer ce paragraphe).

* [X] Le nom du dépôt GitLab est exactement `inf3135-tp1-a22` (Pénalité de
  **50%**).
* [X] L'URL du dépôt GitLab est exactement (remplacer `utilisateur` par votre
  nom identifiant GitLab) `https://gitlab.info.uqam.ca/utilisateur/inf3135-tp1-a22`
  (Pénalité de **50%**).
* [X] Les usagers `dogny_g` et `correcteurs` a accès au projet en mode *Developer*
  (Pénalité de **50%**).
* [X] Le dépôt GitLab est un *fork* de [ce
  dépôt](https://gitlab.info.uqam.ca/inf3135-sdo/geonames)
  (Pénalité de **50%**).
* [X] Le dépôt GitLab est privé (Pénalité de **50%**).
* [X] Le dépôt contient au moins un fichier `.gitignore`.
* [X] Le fichier `Makefile` permet de compiler le projet lorsqu'on entre
  `make`. Il supporte les cibles `html`, `test`, `database` et `clean`.
* [X] Le nombre de tests qui réussissent/échouent avec la `make test` est
  indiqué quelque part dans le fichier `README.md`.
* [X] Les sections incomplètes de ce fichier (`README.md`) ont été complétées.
* [X] L'en-tête du fichier est documentée.
* [X] L'en-tête des déclarations des fonctions est documentée (*docstring*).
* [X] Le programme ne contient pas de valeurs magiques.

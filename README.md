# Micro-projet µ-shell

## Informations
* Executer la commande `make` pour compiler le projet.
* Executer la commande `make clean` pour supprimer les .o .txt et executable.

## Partie 1 : Fonctions de bases

L'affichage de la ligne d'entrée se fait comme ci-dessous:
```
/home/username/Documents: $
```

Utilisation de la commande `exit` pour quitter le programme.

Appel de la fonction `fork` afin de réaliser chaque exécution dans un processus enfant. Ce qui permet alors de continuer à entrer d'autres commandes.

Exécution de la commande rentrée sans arguments avec la fonction `execvp`.
Exemple :
```
ls
who
ps
```


Par la suite, afin d'exécuter des programmes avec des arguments, nous avons utilisé la fonction `strtok` qui permet de récupérer chaque terme entré. En incluant les séparateurs de notre choix, ici '\n '.
Exemple :
```
ls -l -a
who -a
ps faux
```

Enfin, nous avons implémenté deux builtins, qui sont `cd` et `pwd`. Ces derniers ne nécessite pas l'utilisation d'un fork car ce sont des fonctions appelées directement par le programme, et non via des appels `execv`.
Exemples :
```
cd ./directory/
cd ..
pwd
```


## Partie 2 : Fonctions avancées
Pour toutes les fonctions suivantes la chaîne de caractères en entrée est lue.

### Commande en arrière plan
Si le caractère `&` est détectée alors le programme réalise l'exécution dans un processus enfant.

lorsque l’exécution du processus enfant est terminée, il faut fermer ce processus à l'aide de `kill`, pour cela nous enregistrons les PID des enfant pour les détruire plus tard lors de la fermeture du µ-shell.

Ne fonctionne que si `&` est le dernier terme même collé au dernier argument.
Exemples :
```
gedit &
emacs &
```

### Tuyaux
Si le caractère `|` est détecté alors le programme se sépare en deux enfants qui exécutent chacun une partie de la commande.

Pour faire circuler les informations entre les enfants on utilise la fonction `pipe`.

La fonction ne fonctionne que si il n'y a qu'un seul `|`.

Exemples :
```
ls -l | wc
```

### Redirection de stdout
Si le caractère `>` est détecté alors le programme enregistre la sortie dans un fichier. Si ce dernier existe déjà, il sera alors remplacé.

Pour changer la sortie on utilise la fonction `dup2`.

Le nom du fichier doit être spécifié après le `>`.

Exemples :
```
pwd > test.txt
ps faux > texte.txt
```

## Partie 3 : Bonus
Cette partie n'a pas été réalisée par manque de temps, qui en outre, est un bonus.

## Remarques
* Nous avons constaté qu'une fois le signal activé, ce dernier s'effectue également dans la fonction `execPipe` mais nous ne savons pas pourquoi...
* Nous savons que l'utilisation de la fonction `signal` n'est pas très approprié dans le cas de notre shell, mais elle nous permet d'assurer la mort des enfants sans à avoir attendre dans le parent.



### Auteurs : Léo LAVAL & Lucas RIBEIRO
### Date : 12-2021

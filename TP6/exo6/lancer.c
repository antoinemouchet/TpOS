#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 
//#include <sys/wait.h>


/*Exercice 6* Écrivez un programme lancer qui crée un processus ﬁls.
Le processus ﬁls exécute le programme qui est passé en argument au programme lancer.
Le résultat de l’exécution du programme ou commande est stocké dans un ﬁchier qui est aussi passé en argument.
Pour des erreurs de l’exécution, il faut qu’elles soit aﬃchées sur l’écran
Le programme lancer a un format suivant : lancer commande [arg1, arg2, ...] fichier_sortie

Exemple: $ ./lancer ls . /etc resultat 
$ ./lancer cp resultat resultat2 sortie

$ ./lancer toto resultat
Program or command toto is not found*/
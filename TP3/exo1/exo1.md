
# TP 3 

## Exercice 1

### Partie 1

Dans ce programme, on déclare une ``` array ```(=tableau) de taille 5.

Ensuite, on va lancer une boucle (un maximum de 5 fois car ```n``` est incrémenté de 1 à chaque tour et ne peut dépasser ```SIZE``` qui a été défini comme valant 5) pour charger dans le tableau des caractères avec le format d'un entier.

!!! note

    getchar() lit le standard input (ce qui est tapé dans la ligne de commande)

Dans la fonction ```getint``` on boucle tant que le caractère (```c```) est un espace. 
Ensuite, si ```c``` n'est pas un nombre, un caractère de fin de ligne (```EOF = End Of File```) ni un + ou un -, alors on le "supprime" et on renvoie 0, ce qui nous ramène dans ```main``` et arrête donc le programme.

Après, on regarde si le caractère entré est un + ou un -. Si c'est le cas, on le stocke dans la variable ```sign``` et on va chercher le nombre suivant (la boucle ```for``` continue jusqu'à avoir un chiffre) et on calcule l'expression et son signe comme ceci:
```c
*pn = 10 * *pn + (c - '0'); //expression même
*pn *= sign; //signe
```
Le résultat est stocké à l'endroit du tableau indiqué par ```*pn```
Une fois qu'on arrive à ```EOF```, le programme se termine correctement et le tableau ```array``` est complété.

### Partie 2

# Random notes on C

L'utilisation de gdb quand on utilise le signal SIGRTMIN est à **PROSCRIRE** car il remplace sa valeur créant un conflit et cassant tout.

## _*Les librairies*_

Un truc super important qu'il faut pas oublier, ce sont les librairies//headers.
Voici une liste (non-exhaustive et qui sera mise à jour au fur et à mesure) des librairies utilisées en permanence actuellement:
```C
// Librairie générale
#include <stdlib.h>
// Input et Output en C (printf inclus ici)
#include <stdio.h>
// Manipulations de chaines de caractères
#include <string.h>
// Processus et threads principalement
#include <sys/types.h>
// Faciliter l'accès aux informations sur les fichiers
#include <sys/stat.h>
// Processus et diverses fonctions & constantes
#include <unistd.h>
// Manipulations de fichiers
#include <fcntl.h>
// Pour rapporter les codes d'erreurs de certaines librairies
#include <errno.h>
// Processus
#include <sys/wait.h>
// Récupération et gestion de signaux
#include <signal.h>
```


## _*Un peu de syntaxe*_

Le ```;``` est nécessaire après chaque déclaration et assignation et à la majorité des fins de lignes. Le seul moment où il n'est pas nécessaire est au moment de la déclaration d'une fonction.

### _Assignation et déclaration de variable_
Lorsqu'on connaît la valeur de départ d'une variable, on peut la déclarer et lui assigner directement cette valeur.
```C
int amount, result = 0;
```
Dans l'exemple ci-dessus, on ne connait pas la valeur de départ d'```amount``` mais bien celle de ```result``` qui est de 0.

### _Définition et appel de fonction_
Lorsque l'on définit une fonction en C, il est important de préciser son type de retour avant son nom et de préciser le type des paramètres demandés.
```C
int sum(int firstNumber, int secondNumber)
{
    return firstNumber + secondNumber;
}
```
Par contre, lors de l'appel de la fonction, il n'est plus nécessaire de préciser le type passé en argument.
```C
int main(void)
{
    // Déclaration de 2 variables qui sont de types entiers
    int x = 5;
    int y = 6;
    // Déclaration de la variable qui va stocker le résultat de la fonction somme
    // Type entier comme mis devant la définition
    int result;

    // Appel de la fonction et récupération du résultat.
    result = sum(x, y);

    // Par convention, un programme C qui se termine sans erreur renvoie la valeur 0.
    return 0;
}
```


### Static
#### Pour une fonction ou une variable globale

L'utilisation du mot clé ```static``` devant la déclaration d'une fonction ou d'une variable globale (définie en dehors de toute fonction) permet de limiter l'usage de celle-ci uniquement au fichier dans lequel elle se trouve.
```C 
// Variable globale accessible uniquement dans ce fichier.
static int first;

// Fonction accessible uniquement dans ce fichier.
static void display(void)
{
    printf("Hello World!");
}
```
#### Avec les variables dans une fonction
Une variable déclarée dans une fonction sera supprimée de la mémoire à la fin de son exécution **SAUF** si la déclaration de la variable est précédée du mot ```static```.

```C 
int test(void)
{
    // Je déclare ma variable pour la conserver
    static int number = 0;

    // J'incrémente ma variable de 1
    // Équivalent à number += 1 en Python
    number ++;
    return number;
}
int main(void)
{
    printf("%d", test()) // Le résultat de ce print sera 1
    printf("%d", test())
    // Le résultat du second print sera 2
    // car la variable number a gardé la valeur 1 après
    // le premier appel à test().

    return 0;
}
```

### _Nommage des variables_
\
Il faut utiliser le moins possible le ```_``` dans le nom des variables.

!!!warning
    Apparemment, il n'y a pas de convention de nommage officielle en C.

```C 
int NbEnfants;
```

est **mieux** que

```C 
int nombre_enfants;
```
De manière générale:
* camelCase pour les variables/fonctions
* PascalCase pour les structs
* JE_SUIS_PAS_CONTENT_CASE pour les constantes

### _Variable compteur dans une boucle for_
\
Lors de l'utilisation d'une boucle ```for```, si l'on a besoin d'une variable compteur, il n'est pas nécessaire de la déclarer avant la boucle même. En effet, l'écriture suivante est tout à fait acceptable.
```C
for (int i = 0; i < 5; i++)
{
    // Instructions de la boucle ici
}
```

### _Les commentaires_

Les commentaires sont **EXTRÊMEMENT** importants, ils permettent aux autres personnes travaillant sur votre code de comprendre votre raisonnement et pourquoi vous faites les choses d'une façon plutôt que d'une autre. Il faut toujours laisser un espace entre les signes annonçant le début du commentaire et mettre une majuscule (*en vrai c'est pas obligatoire mais c'est mieux et ça rend le code plus lisible*). En C on distingue 2 manières de les faire.

#### Version 1: multi-lignes
```C
/* Ceci
est un commentaire
sur plusieurs lignes.
*/
```
#### Version 2: mono-ligne
```C
// Ici c'est ligne
// Par ligne
// Qu'il faut le faire.
```


### _scanf()_

Lors d'un ```scanf```, on doit désigner l'adresse de l'endroit où la valeur va être stockée. C'est pour cela que l'on différencie un ```scanf``` avec un string d'un ```scanf``` avec un int.

Il est important de noter que ```scanf``` ne fait que récupérer la valeur introduite par l'utilisateur, elle n'affiche rien. Dès lors, il est intéressant de montrer à l'utiliser avec un ```printf``` ce qu'on veut qu'il mette.
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
char sentence[20];

// Ici je veux le nombre
printf("Insert a number.\n");
scanf("%d", &n);

// Par contre là c'est la chaîne de caractères
// Attention qu'une chaîne de caractères demandée comme suit sera arrêtée au premier espace
printf("Insert a string.\n");
scanf("%s", sentence);
```

### _Utilisation des conditions_

En c, on a à notre disposition ```if```, ```else if``` et ```else```.

Rien de mieux qu'un exemple pour montrer leur utilisation:
```C
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    // On déclare juste un nombre ici.
    int number;

    // On récupère le chiffre tapé par l'utilisateur.
    printf("Give me a number!\n");
    scanf("%d", &number);

    // Première condition
    if (number == 0)
    {
        printf("Ton nombre il est nul.\n");
    }
    // On ne vérifiera cette condition que si la première n'est pas vraie.
    else if (number < 0)
    {
        printf("Il faut arrêter d'être négatif maintenant.\n");
    }
    // On passe ici que si aucune autre condition est vrai.
    else
    {
        printf("Tu es positif malgré que tu as déjà raté 2 tests?!\n");
    }
    return 0;
}

```

### _Valeurs de vérités et opérateurs_

En C,  la valeur ```False``` est représentée par le ```0``` (```True``` par ```1``` du coup (*bah oui logique*)).

| Opérateur | Symbole  |
| :-------: | :------: |
|    AND    | ```&&``` |
|    OR     | ```||``` |
|    NOT    | ```!```  |

L'opérateur ```NOT``` permet de vérifier qu'une valeur est fausse.\
Ainsi, dans l'exemple conditionnel ci-dessus les notations suivantes sont équivalentes:
```C
if (number == 0)
```

```C
if (!number)
```
### _switch()_
```switch``` est une sorte de fonction de gestion de cas en fonction des différentes valeurs que peut prendre une variable.

Voici un exemple:
```C
#include <stdio.h>

int main (void)
{
    switch (choix) 
    {
        // Quand choix vaut 1, on passe ici
        case 1:
            printf("Ton choix est le nombre 1.\n");
            
            // Le break est important pour éviter que l'on passe
            // Dans default.
            break;

        // Quand il vaut 2 c'est par ici plutôt
        case 2:
            printf("Ton choix est le nombre 2.\n");

            // Même utilité que case 1
            break;

        // Le reste vient ici
        default:
            printf("Le reste passe par ici.\n");
    }
    return 0;
}
```

## _*Pointeurs*_

### _Valeurs fixes_
```C
int A;
int *P;
P = &A;
```
* ```A```   : le contenu de A.
* ```&A```  : l'adresse de A.
* ```P```   : l'adresse de A.
* ```*P```  : le contenu de A.

```C
int note = 9;
int *p;

p = &note;  // 1
*p = 25     // 2
```
| Identificateur | Adresse |    Valeur     |
| :------------: | :-----: | :-----------: |
|      note      |  5643   |  9 (après **2**: 25)  |
|       p        |  23967  | / (après **1**: 5643) |

### _Tableaux_

A est un tableau
i est l'indice

* ```A``` : l'adresse de A[0]
* ```A+i``` : l'adresse de A[i]
* ```*(A+i)``` : le contenu de A[i]

```P = A```
* ```P``` pointe sur A[0]
* ```(P+i)``` pointe sur A[i]
* ```*(P+i)``` donne le contenu de A[i]

### _Allocation dynamique_
Pour allouer de la mémoire de manière dynamique  (typiquement à un pointeur), on utilise ```malloc``` et ```sizeof```. Il ne faut pas oublier de libérer cet espace à la fin avec ```free```.

```C
int *p;
// Attribution de mémoire dynamique au pointeur d'entier
p = malloc(sizeof(int));

// Libération de la mémoire réservée.
free(p);
```

## _*Structures*_
Il est possible de créer ses propres structures de données avec des caractéristiques différentes en fonction de chaque structure (*on peut le voir comme une classe en python un peu*).

### _Code pour une structure_

Voici le code d'initialisation des structures date, étudiant et année d'étude. 
```C 
// Structure date
struct date
{
    int day;    // Jour
    int month;  // Mois
    int year;   // Année
}

// Structure étudiant
struct student
{
    char name[20]; // Le nom de l'étudiant est de 20 caractères maximum.
    struct date birthDate; // La date de naissance de l'étudiant.
};

// Structure année d'étude
struct studyYear
{
    char code[10];  // Code de l'année et des études
    struct student listStudent[25];
    // On déclare une liste de structures étudiants.
    // Chaque élément de cette liste est un étudiant.
}
```


Maintenant que tous les types sont déclarés, on peut créer des variables de chaque type et modifier leurs valeurs avec l'accès par caractéristique.

```C 
// Déclaration d'une variable classe de type studyYear.
struct studyYear classe;

// Je change la caractéristique "code" de cette classe
// pour la mettre à la valeur voulue.
classe.code = "Bac2-Info";

// Ici je modifie le nom du 3ème étudiant (on commence avec index 0)
classe.listStudent[2].name = "Dupont";

// Ici je modifie le jour d'anniversaire du 3ème étudiant
classe.listStudent[2].birthDate.day = 21;

// Je déclare le délégué entièrement.
// Nom = Dupont
// Date de naissance = 12/05/1992
struct student delegue = {"Dupont", {12, 05, 1992}};

// Il est possible de copier une autre structure
struct student representant;
representant = delegue
```
Une fois qu'un type est déclaré, on peut l'utiliser pour tout. Ainsi, il est possible d'avoir une fonction qui renvoie une valeur d'un type personnalisé.
```C
struct student resultVote(char code[15])
{
    // La variable qui récupère le vainqueur
    struct student winner;

    // Faire des trucs ici

    return winner
}

struct student delegue = resultVote("2e-Bac-Info")
```
### _Listes chaînées_
Il s'agit d'un assemblage de cellues liées par des pointeurs.

```C
struct element
{
    // Caractéristiques de l'élément
    type valeur;

    // Pointeur vers l'élément suivant
    struct element *next;
}
// Je déclare un pointeur sur la variable liste qui est
// une structure d'élément avec un pointeur sur l'élément suivant.
struct element *list;
```

### _Listes doublement chaînées_
Il s'agit d'un assemblage de cellues liées par des pointeurs avec un chaînage dans les 2 sens.

```C
struct element
{
    // Caractéristiques de l'élément
    type valeur;

    // Pointeur vers l'élément précédent
    struct element *previous;

    // Pointeur vers l'élément suivant
    struct element *next;
}
// Je déclare un pointeur sur la variable liste qui est
// une structure d'élément avec un pointeur sur l'élément suivant.
struct element *list;
```
### _Arbres binaires_
On a un chaînage bi-dimensionnel

```C
struct node
{
    // Caractéristique de l'élément
    type valeur;

    // Pointeur sur l'élément à gauche
    struct node *left;

    // Pointeur sur l'élément à droite
    struct node *right;
}
// Déclaration du pointeur sur l'arbre
struct node tree;
```

!!! danger
    L'opérateur ```.``` est prioritaire sur ```*```. Dès lors, il ne faut pas hésiter à utiliser les parenthèses.\
    Il est également bon de noter ceci:
    
    pointeur -> champ $\equiv$ (*pointeur).champ



Voici différents exemples
```C
// Déclaration du type liste chainée
struct element
{
    int value;
    struct element *next;
}
// Déclaration d'un pointeur sur une variable qui est une liste chainée.
struct element *liste;

// Je change la valeur de l'élément sur lequel la liste pointe.
(*liste).value = 5;

// Je mets le pointeur sur l'élément suivant (aucun ici)
liste -> next = NULL;
 
```

Avec des fonctions
```C
// Déclaration du type
struct cellule
{
    int value;
    struct cellule *next;
}

// Déclaration d'une fonction qui renvoie une liste chainée
struct cellule *create(int n)
{
    // Déclaration variable compteur
    int counter;
    // Déclaration de listes chainées
    struct cellule *p, *q;

    compteur = n + 1;
    // La valeur de p est NULL
    p = NULL;

    while(compteur > 1)
    {
        // Attribution de la mémoire
        q = malloc(sizeof(struct cellule));

        // Change la valeur de q
        q -> value  = i -1;

        // Change le pointeur de q
        // L'élément suivant de la liste devient p
        q -> next = p;

        // En faisant ceci, la valeur de p devient celle de q actuellement
        // On crée ainsi une chaine en partant du dernier élément.
        p = q;

        // Décrémente i pour éviter la boucle infinie
        i = i - 1;

    }

    // On retourne la liste chainée complète
    return p
}

// Insertion à la fin de la liste
void insertEnd(int n, struct cellule *p)
{
    struct cellule *q, *r;

    // r sera la dernière cellule de notre liste
    r = malloc(sizeof(struct cellule));
    r -> value = n;
    r -> next = NULL;

    // Si la liste est vide
    if (p == NULL)
    {
        // La liste devient le nouvel élément
        p = r;
    }
    else
    {
        // On fait une copie de p pour ne pas modifier la valeur
        // sur laquelle p pointe.
        q = p;
        // On regarde si l'élément suivant est la fin
        while (q -> next != NULL)
        {
            // On avance de 1 dans la liste
            q = q -> next;
        }
        // On a atteint la fin
        q -> next = r;
    }
}
```

Avec un arbre maintenant
```C
// Déclaration du type
struct node
{
    // Caractéristique du type node
    int value;

    // Pointeurs sur les autres arbres
    struct node *left;
    struct node *right;
}
// Fonction qui fait la somme des éléments de l'arbre.
int sumTree(struct node *tree)
{
    // Si l'arbre est vide, renvoie 0
    if (tree == NULL)
    {
        return 0;
    }
    else
    {
        // Calcul de la somme des arbres gauches et droits
        // et ajout de la valeur de cette node.
        return sumTree(tree -> left) \
        + tree -> value \
        + sumTree(tree -> right);
    }
}
```

## _*Processus*_

Ça sert à quoi ce truc? Et bien c'est pour diviser le travail en quelque sorte.
Le père, qui a la flemme, va faire des gosses (*pas pour les allocs mais pour les mettre au travail ici*) et il va soit travailler de son côté (*Ouais ouais ça lui arrive*), soit attendre que les gosses aient fini leurs tâches respectives.

_Mais comment on fait des gosses me direz-vous?_\
(*Je pourrais répondre demande à tes parents mais pas sûr qu'ils puissent aider*)\
C'est pas très compliqué pour le coup. On peut distinguer plusieurs manières de les faire selon:
* L'arbre familial voulu.
* Le nombre de fils à créer.

Avant de se lancer dans la description des différentes méthodes, il me semble important de parler de la valeur de retour de ```fork()``` ainsi que du ```pid```. 

### _fork()_

```fork()``` est la fonction qui permet la création d'un processus.
Elle renvoie une valeur de type ```pid_t```. Ce type désignant un entier signé, il est tout à fait correct de déclarer la variable dans laquelle est stockée la valeur de retour du fork comme un type ```int```.\
Les valeurs de retour possibles sont:
* 0: on est alors dans le processus fils.
* \> 0: on est dans le processus père.
* -1: il y a eu une erreur lors de la création du processus.

Voici un code C pour créer un processus et définir dans quel processus on est:

```C
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <errno.h>

int main(void)
{
    // Je déclare la variable de retour du fork
    int forkReturn;

    // Ici, on crée le processus fils mais en plus
    // On stocke la valeur de retour dans la variable forkReturn.
    forkReturn = fork();

    // Child case
    if (forkReturn == 0)
    {
        printf("Ici c'est le fils!\n");
    }

    // Parent case
    else if (forkReturn > 0)
    {
        printf("Voilà le père.\n");
        printf("La valeur forkReturn: %d est le pid de mon fils.", forkReturn);
    }

    // Error
    else
    {
        // La fonction perror affiche un message d'erreur à la suite
        // De la chaîne de caractères déjà présente.
        perror("An error occured: ");

        // Cette ligne permet de terminer le programme en montrant 
        // Qu'il y a eu une erreur.
        return 1;
    }

    return 0;
}
```
### _PID_

Le ```pid``` d'un processus est son numéro d'identification. On l'obtient avec la fonction ```getpid()```. Pour obtenir le ```pid``` du père, on utilise la fonction  ```getppid()```.\
(*La réflexion fut intense du côté des développeurs pour le nom de cette dernière.*)

### _2^n - 1 fils_
Dans le cas où l'on veut $2^n-1$ fils, il suffit de mettre $n$ fork() les uns à la suite des autres.

```mermaid
graph TD;
    A[Dad]
    B[Fils 1]
    C[Fils 2]
    D[Fils 3]
    E[Fils 4]
    F[Fils 5]
    G[Fils 6]
    H[Fils 7]
    A-- first fork -->B
    A-- second fork -->C
    B-- second fork -->D
    A-- third fork -->E
    B-- third fork -->F
    C-- third fork -->G
    D-- third fork -->H
```
Le code C qui donne l'arbre ci-dessus est le suivant:

```C
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main(void) 
{ 
    fork();
    fork();
    fork();

    return 0;
}
```

Le problème de ce code est que la structure de l'arbre est définie et qu'en plus, vu qu'on ne récupère par la valeur renvoyée par ```fork```, on ne peut pas savoir dans quel processus on est ou même s'il y a eu un problème lors de la création.

Pour créer des arbres plus spéciaux ou obtenir un nombre de fils différent, il faut donc utiliser une autre méthode. Il en existe plusieurs, encore une fois cela dépend de la structure d'arbre que l'on veut.

### _Plusieurs fils même père_

```mermaid
graph TD;
    A[Dad]
    B[Fils 1]
    C[Fils 2]
    D[Fils 3]
    E[Fils 4]
    F[Fils 5]
    G[Fils 6]
    A-- first fork -->B
    A-- second fork -->C
    A-- third fork -->D
    A-- fourth fork -->E
    A-- fifth fork -->F
    A-- sixth fork -->G

```
(*Oui, une telle productivité est possible...*)

Le code C suivant peut donner ce genre d'arbre

```C
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main(void) 
{
    // On déclare la variable où on va mettre la valeur de retour du fork
    // Et un tableau de 6 entiers (il contiendra les valeurs de forkReturn).
    int forkReturn, ProcessID[6];

    // On boucle tant que les 6 enfants n'ont pas été faits et on ajoute
    // Une condition qui permet de vérifier que seul le père crée des enfants.
    for (int i = 0; i < 6 && id = 0; i++)
    {
        // On stocke la valeur de retour du fork
        // À l'emplacement i du tableau ProcessID
        ProcessID[i] = fork();

        // Ici c'est un enfant, on ne veut pas qu'il ait d'enfant donc
        // On le fait sortir de la boucle en changeant la valeur de id.
        if (ProcessID[i] == 0)
        {
            id = 1;
        }

        // N'oublions pas de gérer le cas potentiel de l'erreur.
        else if (ProcessID[i] < 0)
        {
            perror("An error occured: ");
        }
        // Mettre une condition pour le père n'aurait pas de sens ici car il ne fait
        // Rien.
        // On veut juste qu'il recommence la boucle pour recréer d'autres enfants.
    }

    return 0;
}
    
```

## _*Thread*_
### Différence entre thread et processus

Il y a des accès concurrent à un objet partagé avec:
* **_Les threads:_** Ils ont un espace d’adressage commun, des accès concurrents aux variables globales et aux fichiers ouverts.
* **_Les processus (*parents & enfants*):_** Ils ont un espace d’adressage distincts mais partagent la mémoire et les fichiers ouverts avant le fork.


Le **message passing** c’est le fait d’envoyer des messages entre des entités. Il peut être local (entre threads d’une machine) ou non-local (entre deux machines distantes)

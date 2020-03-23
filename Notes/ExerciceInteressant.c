/* Énoncé - Morceaux de musique

Je joue de la musique irlandaise et j’aimerais pouvoir encoder les morceaux de musique que j’apprends.
Je ne joue, pour le moment, que quatre type de morceaux: des reels, des jigs, des polka et des mazurkas

Une musique a:
    • Un nom
    • Un type (parmi les 4 cités précédemment)
    • Une durée (en secondes).

Écrivez un programme qui me permet d’encoder ces musiques de cette façon:

1) J’indique d’abord le nombre de chansons que je vais encoder, puis je les encode une à une.
2) Affichez ensuite à l'utilisateur:
    a) la durée moyenne d'un morceau
    b) le titre du morceau le plus long
    c) la plus longue suite de morceaux du même type qui ont été encodés, ainsi que les titres de ces morceaux.

    Par exemple, si j'ai encodé 3 jigs, 2 polkas, 1 jig, 4 reels, 1 mazurka
    j'aimerais que le programme m'affiche que j'ai une une séquence de 4 reels, et qu'il m'affiche les noms de ces 4 reels.
*/


#include <stdio.h>
#include <stdlib.h>

enum musique_Type{reels, polka, jigs, mazurkas};

struct Musique
{
    char* titre;
    enum musique_Type genre;
    int duree;

};

typedef struct Musique Musique;

// Ceci doit être mis à jour si musique_Type est changé
static const char *Musique_genre_string[] = {"reel", "polka", "jig", "mazurka"};


// Fonction pour afficher toutes les informations concernant une musique
void display(Musique musique)
{

    printf("Titre: %s\n"
           "Genre: %s\n"
           "Duree: %i:%i (min:sec)\n\n",
           musique.titre, Musique_genre_string[musique.genre], musique.duree/60, musique.duree%60);
}

int main(int argc, char const *argv[])
{
    /* Initialisation */
    int nombre;
    printf("Entrez le nombre de musiques à encoder:\n");
    scanf("%i", &nombre);

    // Tableau de musiques
    Musique portfolio[nombre];

    // Variables pour les scanfs
    int choix;
    int temps;

    // Sauvegarde le choix précédent
    int previous_choix = -1;

    // Tableau divisible en plusieurs sous-variables mais je trouvais ça plus propre et intéressant
    // d'utiliser un tableau. 

    /* Tableau de sauvegarde:
    *  --------------------------
    *  • Taille de la plus longue chaine de meme genre (0)
    *  • Le genre correspondant (1)
    *  • Index du premier titre de la séquence (2)
    *  • Temps de la plus longue musique (3)
    *  • Index de la plus longue musique (4)
    *  • Temps total de toutes les musiques combinées (5)*/
    int save[6];

    // Taille et index de départ de la séquence en cours
    int tmpmax = 1;
    int tmpID = 0;

    // Boucle pour avoir toutes les musiques (while possible, je préfère le for pour pouvoir réutiliser
    // nombre après sans devoir introduire de variable supplémentaire).
    for (int i = 0; i < nombre; i++)
    {
        /* TITRE */
        printf("\nMusique n°%i\n-----------\n", i+1);
        printf("Insérez le titre de la musique: ");
        scanf(" %ms", &portfolio[i].titre);

        /* GENRE */
        printf("• 0 ~ Reel\t| • 2 ~ Jig\n• 1 ~ Polka\t|• 3 ~ Mazurka\nInsérez le numéro correspondant au genre de musique: ");
        scanf("%i", &choix);

        portfolio[i].genre = (enum musique_Type) choix;

        /* Sauvergarde de la plus grande séquence */

        // Si même choix qu'avant, on augmente la durée de la séquence en cours
        if(choix == previous_choix){
            tmpmax++;
        }
        // Sinon on reset la taille et l'index de départ de la séquence en cours
        else
        {
            tmpmax = 1;
            tmpID = i;  
        }
        
        // Vérification de la séquence en cours par rapport à la séquence la plus longue enregistrée (et donc stockée dans save)
        if (tmpmax > save[0]){
            save[0] = tmpmax;
            save[1] = choix;
            save[2] = tmpID;
        }
        // Mise à jour du choix précédent
        previous_choix = choix;

        /* Fin de la gestion de la sauvegarde de séquence*/

        /* DUREE */
        printf("Insérez la durée de la musique en seconde: ");
        scanf("%i", &temps);

        portfolio[i].duree = temps;

        /* Vérification de la musique la plus longue */
        if (temps > save[3])
        {
            save[4] = i;
            save[3] = temps;
        }
        /* Fin de la vérification de la durée */

        // Préparation calcul de la moyenne
        save[5] += temps;
    }

    printf("\nLa durée moyenne d'un morceau est de: %i secondes\n", save[5]/nombre);
    printf("\nTitre du morceau le plus long: %s (duree: %i secondes)\n", portfolio[save[4]].titre, save[3]);
    printf("\nAffichage de la plus longue séquence de titres du même genre (%s)\n", Musique_genre_string[save[1]]);
    for (int i = 0; i < save[0]; i++)
    {
        printf("Musique n°%i\n", i+1);
        display(portfolio[i+save[2]]);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../include/dico.h"

int gagne(int lettreTrouvee[], long tailleMot);
int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[]);
char lireCaractere();

char hint(char z);

int main(int argc, char* argv[])
{
    char lettre = 0; // Stocke la lettre proposée par l'utilisateur (retour du scanf)
    char motSecret[100] = {0}; // Ce sera le mot à trouver
    int *lettreTrouvee = NULL; // Un tableau de booléens. Chaque case correspond à une lettre du mot secret. 0 = lettre non trouvée, 1 = lettre trouvée
    long coupsRestants = 10; // Compteur de coups restants (0 = mort)
    long i = 0; // Une petite variable pour parcourir les tableaux
    long tailleMot = 0;
    char z;

    printf("Bienvenue dans le Pendu !\n\n");

    if (!piocherMot(motSecret))
        exit(0);

    tailleMot = strlen(motSecret);

    lettreTrouvee = malloc(tailleMot * sizeof(int)); // On alloue dynamiquement le tableau lettreTrouvee (dont on ne connaissait pas la taille au départ)
    if (lettreTrouvee == NULL)
        exit(0);

    for (i = 0 ; i < tailleMot ; i++)
        lettreTrouvee[i] = 0;

    // On continue à jouer tant qu'il reste au moins un coup à jouer ou qu'on
    // n'a pas gagné
    while (coupsRestants > 0 && !gagne(lettreTrouvee, tailleMot))
    {
        printf("\n\nIl vous reste %ld coups a jouer", coupsRestants);
        printf("\nQuel est le mot secret ? ");

        /* On affiche le mot secret en masquant les lettres non trouvées
        Exemple : *A**ON */
        for (i = 0 ; i < tailleMot ; i++)
        {
            if (lettreTrouvee[i]) // Si on a trouvé la lettre n°i
                printf("%c", motSecret[i]); // On l'affiche
            else
                printf("_"); // Sinon, on affiche under score pour les lettres non trouvées
        }

        char indice[50];

            

                                printf("\nUn indice ?? [y/n] : ");
                                scanf("%s",indice);

                                if(strcmp(indice,"y") == 0)
                                {
                                    z = motSecret[rand()% tailleMot];
                                    //printf("Hint : %c \n", z);
                                    //on revoie la valeur de z a lettre
                                    lettre = hint(z);
                                   // printf("%c\n", lettre);

                                }

                                else if(strcmp(indice,"n") == 0)
                                {
                                        do 
                                        {
                                            printf("Entrez un alphabet : ");
                                            lettre = lireCaractere();
                                        }while((isalpha(lettre) == 0));
                                    
                                }

        // Si ce n'était PAS la bonne lettre
        if (!rechercheLettre(lettre, motSecret, lettreTrouvee))
        {
            coupsRestants--; // On enlève un coup au joueur
        }
    }


    if (gagne(lettreTrouvee, tailleMot))
        printf("\n\nGagne ! Le mot secret etait bien : %s\n\n", motSecret);
    else
        printf("\n\nPerdu ! Le mot secret etait : %s\n\n", motSecret);

    free(lettreTrouvee); // On libère la mémoire allouée manuellement (par malloc)

        return 0;
}


char lireCaractere()
{
    char caractere = 0;
    while (getchar() != '\n') ;

    caractere = getchar(); // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà

    // On lit les autres caractères mémorisés un à un jusqu'à l'\n
    

    return caractere; // On retourne le premier caractère qu'on a lu
}

char hint(char z)
{
    char caractere = 0;

    caractere = z;
    caractere = toupper(caractere);


    while (getchar() != '\n') ;

    return caractere;
}


int gagne(int lettreTrouvee[], long tailleMot)
{
    long i = 0;
    int joueurGagne = 1;

    for (i = 0 ; i < tailleMot ; i++)
    {
        if (lettreTrouvee[i] == 0)
            joueurGagne = 0;
    }

    return joueurGagne;
}

int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[])
{
    long i = 0;
    int bonneLettre = 0;

    // On parcourt motSecret pour vérifier si la lettre proposée y est
    for (i = 0 ; motSecret[i] != '\0' ; i++)
    {
        if (lettre == motSecret[i]) // Si la lettre y est
        {
            bonneLettre = 1; // On mémorise que c'était une bonne lettre
            lettreTrouvee[i] = 1; // On met à 1 le case du tableau de booléens correspondant à la lettre actuelle
        }
    }

    return bonneLettre;
}

# pendu_AdrienEsther
# Project Title
Jeu du pendu
## _Achievement_
The main goals of this project is to realise a game where a user should be able to think about a letter and propose it. Regardless, he will get a limited chance of 8 times to propose a letter or otherwise he will loose the game after the 8 inputs, beside he will get a hint in order to help the user in this game.

## Author
- Adrien Esther


## _Getting started_
Before we started, we cloned the project work to local in our terminal.
```sh
git clone https://github.com/Adrien2305/pendu_AdrienEsther.git
```
Now , i have created a branch name dev 
```sh
git branch dev
```
Now i need to switch to the branch dev
```sh
git checkout dev
```

## How to execute the program first
```sh
gcc -I include/ -o bin/main src/dico.c src/main.c
cd bin
./main
```
## Step1: The main.c 
```sh
char lireCaractere() 
{ 
    char caractere = 0;
 
    caractere = getchar(); // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà
 
    // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer) 
    while (getchar() != '\n') ;
 
    return caractere; // On retourne le premier caractère qu'on a lu 
}
```
Cette fonction utilise ```getchar() ```qui est une fonction de ```stdio ``` qui revient exactement à écrire ```scanf("%c", &lettre) ```;. La fonction ```getchar``` renvoie le caractère que le joueur a tapé.

## step2
```sh
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
    char lettre = 0; 
    char motSecret[100] = {0}; 
    int *lettreTrouvee = NULL; 
    long coupsRestants = 10; 
    long i = 0; 
    long tailleMot = 0;
    char z;
}
```
Notre main va gérer la plupart du jeu et faire appel à quelques-unes de nos fonctions quand il en aura besoin.
## Step3: Le debut du jeu
```sh
printf("Bienvenue dans le Pendu !\n\n");

    if (!piocherMot(motSecret))
        exit(0);

    tailleMot = strlen(motSecret);

    lettreTrouvee = malloc(tailleMot * sizeof(int)); 
    if (lettreTrouvee == NULL)
        exit(0);

    for (i = 0 ; i < tailleMot ; i++)
        lettreTrouvee[i] = 0;

    
    while (coupsRestants > 0 && !gagne(lettreTrouvee, tailleMot))
    {
        printf("\n\nIl vous reste %ld coups a jouer", coupsRestants);
        printf("\nQuel est le mot secret ? ");

        
        for (i = 0 ; i < tailleMot ; i++)
        {
            if (lettreTrouvee[i]) // Si on a trouvé la lettre n°i
                printf("%c", motSecret[i]); 
            else
                printf("_"); 
        }
```
- Le jeu continue tant qu'il reste des coups ```(coupsRestants > 0)``` et tant qu'on n'a pas gagné.

```Si on n'a plus de coups à jouer, c'est qu'on a perdu. 
printf("\n\nIl vous reste %d coups a jouer", coupsRestants);
printf("\nQuel est le mot secret ? ");

        for (i = 0 ; i < 6 ; i++)
        {
            if (lettreTrouvee[i]) // Si on a trouvé la lettre n° i
                printf("%c", motSecret[i]); // On l'affiche
            else
                printf("_"); // Sinon, on affiche un underscorte pour les lettres non trouvées
        }
```
On affiche à chaque coup le nombre de coups restants ainsi que le mot secret (masqué par des * pour les lettres non trouvées).
L'affichage du mot secret masqué par des * se fait grâce à une boucle for. On analyse chaque lettre pour savoir si elle a été trouvée ```if (lettreTrouvee[i])```. Si c'est le cas, on affiche la lettre. Sinon, on affiche une * de remplacement pour masquer la lettre.

## Step4: Le hint
```
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
```
La fonction ``` char indice[50]``` va donner a l'utilisateur un indice a propos du mot secret.
## Step5: Dico.c/Mode de difficulte
```
int piocherMot(char *motPioche)
{
    FILE* dico = NULL; // Le pointeur de fichier qui va contenir notre fichier
    int nombreMots = 0, numMotChoisi = 0, i = 0;
    int caractereLu = 0;
    char ans[10];

    printf("Choisissez votre mode de difficulte [facile,moyen,difficile]\n");
    scanf("%s", ans);

    if(strcmp(ans, "facile") == 0){
        dico = fopen("../ressource/dico.txt", "r"); // On ouvre le dictionnaire en les 
    }
    else if (strcmp(ans, "moyen") == 0){
        dico = fopen("../ressource/dico1.txt", "r");
    }
    else if (strcmp(ans, "difficile") == 0){
        dico = fopen("../ressource/dico2.txt", "r");
    }

    else {printf("Erreur\n");
}
```
-  On a notre pointeur sur fichier ```dico``` qui va se servir pour lire les fichiers ```dico.txt```.
 

## Step6: Le chemin d'acces vers les fichiers dico.txt
```
dico = fopen("../ressource/dico.txt", "r"); // On ouvre le dictionnaire en lecture seule
```
- si on vers faire directement des modifications dans les fichiers dico.txt , il suffira de mette la fonction du fichier en ``` "r+"```

## Step7: Le dico.h

```
#ifndef DEF_DICO
#define DEF_DICO

int piocherMot(char *motPioche);
int nombreAleatoire(int nombreMax);

#endif
```
ll s'agit juste des prototypes des fonctions. Il faut inclure le```ifndef``` dans tous les ```fichiers.h```


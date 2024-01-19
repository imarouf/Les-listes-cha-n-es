// pointeur = passage par paramètres
// Double pointeur = passe par valeur

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct maillon
{
    char nom[30];
    int nombre;
    struct maillon *suiv;
} MAIL;

MAIL *CreerMaillon();
// Fonctions insertions
MAIL *InsererMaillonEnTete(MAIL *pt_tete, MAIL *nouveau_maillon);
MAIL *InsererMaillonEnQueue(MAIL *pt_tete, MAIL *nouveau_maillon);
MAIL *InsererMaillonBonnePlace(MAIL *pt_tete, MAIL *nouveau_maillon);
// Fonctions Afficher
void AfficherListe(MAIL *pt_tete);
// Divers fonctions
void RechercherElement(MAIL *pt_tete);
void SupprimerElement(MAIL **pt_tete);
// Fonctions relatives aux fichiers
void LireFichier(FILE *fichier);
void EcrireFichier(FILE *fichier, MAIL *pt_tete);

int main()
{
    system("chcp 65001"); // Cette instruction permet d'afficher les caractères spéciaux sur le terminal
    FILE *fichier;
    fichier = fopen("liste_chaine.bin", "a+");

    MAIL *pt_tete = NULL;
    MAIL *nouveau_maillon = NULL;
    // Choix menu
    int choix;

    do
    {
        printf("\n== Menu programme liste chaînée == \n");
        printf("0 - Quitter\n");
        printf("1 - Créer maillon\n");
        printf("2 - Insérer maillon en tête\n");
        printf("3 - Insérer maillon en queue\n");
        printf("4 - Insérer maillon à la bonne place ( liste triée au préalable)\n");
        printf("5 - Rechercher un élément\n");
        printf("6 - Afficher la liste chaînée\n");
        printf("7 - Supprimer un maillon \n");
        printf("8 - Ecrire dans un fichier la liste chaînée\n");
        printf("9 - Lire le fichier contenant les listes chaînées\n");
        printf("== Fin Menu ==\n");

        printf("\nEntrez votre choix :");
        scanf("%d", &choix);

        switch (choix)
        {
        case 0:
            return 0;
            break;
        case 1:
            nouveau_maillon = CreerMaillon();
            break;
        case 2:
            pt_tete = InsererMaillonEnTete(pt_tete, nouveau_maillon);
            break;
        case 3:
            pt_tete = InsererMaillonEnQueue(pt_tete, nouveau_maillon);
            break;
        case 4:
            pt_tete = InsererMaillonBonnePlace(pt_tete, nouveau_maillon);
            break;
        case 5:
            RechercherElement(pt_tete);
            break;
        case 6:
            AfficherListe(pt_tete);
            break;
        case 7:
            SupprimerElement(&pt_tete);
            break;
        default:
            break;
        case 8:
            EcrireFichier(fichier, pt_tete);
            break;
        case 9 : 
            LireFichier(fichier);
        }
    } while (choix != 0);
    fclose(fichier);
}

MAIL *CreerMaillon()
{
    // déclaration du pointeur qui contiendra l'adresse du maillon
    MAIL *pt_maillon = NULL;

    // Allocation de la taille mémoire pour un maillon et récupération de l'adresse
    pt_maillon = (MAIL *)malloc(sizeof(MAIL));

    printf("\n1 - Entrez le nom : ");
    scanf("%s", pt_maillon->nom);
    printf("2 - Entrez le nombre : ");
    scanf("%d", &(pt_maillon)->nombre);

    pt_maillon->suiv = NULL;

    return pt_maillon;
}

MAIL *InsererMaillonEnTete(MAIL *pt_tete, MAIL *nouveau_maillon)
{
    if (pt_tete == NULL)
    {
        printf("\n == Le maillon <%s> à bien été inséré en tête ! ==\n", nouveau_maillon->nom);
        return nouveau_maillon;
    }
    else
    {
        nouveau_maillon->suiv = pt_tete;
        printf("\n == Le maillon <%s> à bien été inséré en tête ! ==\n", nouveau_maillon->nom);
        return nouveau_maillon;
    }
}

MAIL *InsererMaillonEnQueue(MAIL *pt_tete, MAIL *nouveau_maillon)
{
    if (pt_tete == NULL) // Vérifie que la liste est vide
    {
        printf("\n == Le maillon <%s> à bien été inséré à la fin ! ==\n", nouveau_maillon->nom);
        return nouveau_maillon;
    }
    MAIL *temp = pt_tete;
    while (temp->suiv != NULL)
    {
        temp = temp->suiv;
    }
    temp->suiv = nouveau_maillon;
    printf("\n == Le maillon <%s> à bien été inséré à la fin ! ==\n", nouveau_maillon->nom);
    return pt_tete;
}

MAIL *InsererMaillonBonnePlace(MAIL *pt_tete, MAIL *nouveau_maillon)
{
    MAIL *pt_prec, *pt_courant = pt_tete;
    if (pt_tete == NULL)
    {
        printf("\n == Maillon <%s> inséré en tête car la liste est vide ! ==  ", nouveau_maillon->nom);
        return nouveau_maillon;
    }
    while ((pt_prec != NULL) && (strcmp(pt_courant->nom, nouveau_maillon->nom) <= 0))
    {
        pt_prec = pt_courant;
        pt_courant = pt_tete->suiv;
    }
    pt_prec->suiv = nouveau_maillon;
    nouveau_maillon->suiv = pt_courant;
    printf("\n == Le maillon <%s> à bien été inséré à la bonne place ! ==  ", nouveau_maillon->nom);
    return pt_tete;
}

void AfficherListe(MAIL *pt_tete)
{
    if (pt_tete == NULL)
    {
        printf("\n== La liste est vide ! ==\n");
        return;
    }
    MAIL *temp = pt_tete;
    printf("\n== Voici votre magnifique liste chainee ==\n");
    while (temp != NULL)
    {
        printf("nom :%s\n", temp->nom);
        printf("nombre %d\n", temp->nombre);
        temp = temp->suiv; // l'adresse de temp est égale à l'adresse du suivant
    }
}

void RechercherElement(MAIL *pt_tete)
{
    char personne_a_trouver[30];

    printf("\n== Menu recherche de personne == \n");

    printf("\nEntrez La personne que vous voulez chercher : ");
    scanf("%s", personne_a_trouver);
    if (pt_tete == NULL)
    {
        printf("La liste est vide !");
        return;
    }
    else
    {
        while ((pt_tete != NULL) && (strcmp(personne_a_trouver, pt_tete->nom) != 0))
        {
            pt_tete = pt_tete->suiv;
        }
        if (pt_tete == NULL)
        {
            printf("L'élément recherché <%s> est introuvable", personne_a_trouver);
        }
        else
        {
            printf("\n== Utilisateur trouve ==\n");
            printf("Nom : %s\n", pt_tete->nom);
            printf("Nombre : %d\n", pt_tete->nombre);
        }
    }
}

void SupprimerElement(MAIL **pt_tete)
{
    char personne_a_supprimer[30];
    MAIL *pt_prec = NULL, *pt_courant = *pt_tete;

    printf("\n== Menu Supprimer une personne == \n");

    printf("\nEntrez La personne que vous voulez chercher : ");
    scanf("%s", personne_a_supprimer);
    if (*pt_tete == NULL)
    {
        printf("La liste est vide donc la personne à supprimer n'existe pas :D\n");
    }
    else
    {
        while (pt_courant != NULL && strcmp(pt_courant->nom, personne_a_supprimer) != 0)
        {
            pt_prec = pt_courant;
            pt_courant = pt_courant->suiv;
        }
        // Cas où la suppression est faite en tête
        if (pt_courant == *pt_tete)
            *pt_tete = pt_courant->suiv;
        // sinon suppression de l'élément
        else
            pt_prec->suiv = pt_courant->suiv;

        free(pt_courant);
        pt_courant = NULL;
    }
}

void LireFichier(FILE *fichier)
{
    if (fichier == NULL)
    {
        
    }
}

void EcrireFichier(FILE *fichier, MAIL *pt_tete)
{
    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir dans le fichier");
    }
    rewind(fichier);
    while (pt_tete != NULL)
    {
        fwrite(pt_tete, sizeof(MAIL), 1, fichier);
        // Passage au maillon suivant
        pt_tete = pt_tete->suiv;
    }
}
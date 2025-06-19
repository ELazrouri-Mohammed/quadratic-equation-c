#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int menu()
{
    int M;
    printf("Appuyer sur 1 pour ajouter les details des livres . \n");
    printf("Appuyer sur 2 pour afficher les details des livres . \n");
    printf("Appuyer sur 3 pour afficher les informations d'un livre . \n");
    printf("Appuyer sur 4 pour afficher les livres de l'auteur donnee . \n");
    printf("Appuyer sur 5 pour sortire . \n");
    printf("Enter votre choix : ");
    scanf("%d", &M);
    return M;
}
typedef struct
{
    char title[50], author[30];
    int pagesnmbr;
    float price;

} Library;
void affiche(FILE *Pfile)
{
    rewind(Pfile);
    Library Book;
    int i = 1;
    while ((fread(&Book, sizeof(Library), 1, Pfile)) == 1)
    {
        printf("Book %i ", i);
        printf("Titre : %s \n ", Book.title);
        printf("Autheur : %s \n ", Book.author);
        printf("Nombre de pages : %i \n ", Book.pagesnmbr);
        printf("Prix : %.2f \n ", Book.price);
        i++;
    }
}
int main()
{
    Library *Book = NULL;
    FILE *Pfile;
    Library tmpbook;
    char Stitle[40];
    int M, Totalbooks, start = 0;
    int addetlivre = 0;
    M = menu();
    int firstbyte;
    Pfile = fopen("Library.bin", "ab+");
    if (Pfile == NULL)
    {
        printf("ERROR");
        return 1;
    }
    rewind(Pfile);
    firstbyte = fgetc(Pfile);
    while (firstbyte == EOF && M != 1)
    {
        printf("Le fichier est vide .\n");
        M = menu();
    }
    while (M >= 1 && M <= 4)
    {
        switch (M)
        {
        case 1:
            printf("Enter le nombre de livres que vous voulez ajouter : ");
            scanf("%i", &addetlivre);
            Totalbooks = start + addetlivre;
            Book = realloc(Book, Totalbooks * sizeof(Library));
            for (int i = start; i < Totalbooks; i++)
            {
                printf("Enter le titre de livre %i : ", i + 1);
                scanf(" %[^\n]", Book[i].title);
                printf("Enter le nom de l'autheur : ");
                scanf(" %[^\n]", Book[i].author);
                printf("Enter le nombre de pages : ");
                scanf("%i", &Book[i].pagesnmbr);
                printf("Enter le prix : ");
                scanf("%f", &Book[i].price);
                fwrite(&Book[i], sizeof(Library), 1, Pfile);
                fflush(Pfile);
            }

            start += addetlivre;
            M = menu();
            break;
        case 2:
            rewind(Pfile);
            affiche(Pfile);
            M = menu();

            break;
        case 3:
            rewind(Pfile);
            printf("Enter le titre de livre : ");
            scanf(" %[^\n]", Stitle);
            int found = 0;
            while (fread(&tmpbook, sizeof(Library), 1, Pfile) == 1)
            {
                if (strcmp(tmpbook.title, Stitle) == 0)
                {
                    printf("Book :\n");
                    printf("Titre : %s\n", tmpbook.title);
                    printf("Auteur : %s\n", tmpbook.author);
                    printf("Nombre de pages : %i\n", tmpbook.pagesnmbr);
                    printf("Prix : %.2f\n", tmpbook.price);
                    found++;
                }
            }
            if (found == 0)
            {
                printf("No book found with that title :");
            }

            M = menu();
            break;
        case 4:
            rewind(Pfile);
            printf("Enter le nom de l'autheur : ");
            scanf(" %[^\n]", Stitle);
            found = 0;
            while (fread(&tmpbook, sizeof(Library), 1, Pfile) == 1)
            {
                if (strcmp(tmpbook.author, Stitle) == 0)
                {
                    printf("Book :\n");
                    printf("Titre : %s\n", tmpbook.title);
                    printf("Auteur : %s\n", tmpbook.author);
                    printf("Nombre de pages : %i\n", tmpbook.pagesnmbr);
                    printf("Prix : %.2f\n", tmpbook.price);
                    found;
                }
            }
            if (found == 0)
            {
                printf("No book found for this author  : ");
            }
            M = menu();
            break;
        case 5:
            printf("Exiting...\n");
            fclose(Pfile);
            return 0;
            break;
        default:
            return 0;
            break;
        }
    }
}

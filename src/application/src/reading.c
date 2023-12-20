// Files in the application/include folder
#include "reading.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  Partie Lecture des images  //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void read_pic(int n_image, int *tab_size, int *tab_width, int *tab_length, uint8_t *global_tab)
{

  FIL fil;    // File object
  FRESULT fr; // FatFs return code

  TCHAR *plop;
  TCHAR chaine[512];
  char *strToken = calloc(100, sizeof(*strToken));
  char *text = calloc(10000, sizeof(*text));

  int fsize = 0; // file size count
  int br;        // Read count
  int c1 = 0;
  int c2 = 0;
  int i = 0;

  int length = 0;
  int width = 0;
  int size = 0;
  char file_name[30] = {'\0'};                //Nom du fichier a ouvrir
  uint8_t pixels[DISPLAY_IMAGE_SIZE * 3];     //Tableau de pixel pour une image


    //Generation du nom de fichier
    sprintf( ..., "%d.ppm", ... );

    // Open a file
    printf("Loading %s\n", ... );
    fr = f_open( ... , ... , FA_READ);
    if (fr)
    {
      printf("Failed to open %s!\n", ... );
      return 0;
    }

    //Lecture de l'entete
    fr = f_read( ... , &c1, 1, ... );
    fr = f_read( ... , &c2, 1, ... );

    //Si l'entete vaut les caracteres 'P3' alors, on est dans le cas d'un fichier ppm
    if (c1 == 0x50 && c2 == 0x33)
    {
      printf("Le fichier %s est un fichier ppm P3.\n", ... );
      plop = f_gets(text, 10000, ... );
      plop = f_gets(text, 10000, ... );
      if (text[0] == '#')
      { // test ligne de commentaire de openCV
        plop = f_gets(text, 10000, &fil);
      }
      strToken = ...(text, " ");					//Utilisation des fonctions sur les chaînes de caractères décrites plus haut
      length = ...(strToken); //Lecture de la longueur de l'image
      strToken = ...(NULL, "\n");
      width = ...(strToken); //Lecture de la largeur de l'image
      size = length * width;
      tab_width[...] = width;						//Remplissage des tableaux des valeus de longueur, largeur et taille des images lues 
      tab_length[...] = length;
      tab_size[...] = size;
      for (i = 0; i < size; i++)					//initialisation du tableau pixel
      {
        pixels[i] = 0;
      }
      printf("File size: %d and image size : %d * %d = %d\n", ... ,
             tab_length[ ... ],
             tab_width[ ... ],
             tab_size[ ... ]);

      plop = f_gets(text, 10000, ... );
      i = 0;
      plop = calloc(3 * size, sizeof(*plop));
      //Pour toutes les lignes du fichier
      while (&fil != NULL && i < (3 * size))
      {
        plop = f_gets(text, 10000, ... ); //On lit une ligne
        strToken = ...(text, " ");  //On separe les differents chiffres
        //Pour tous les chiffres de la ligne
        while (strToken != NULL && i < (3 * size))
        {
          pixels[i] = ...(strToken); //On remplit le tableau pixel par pixel
          i++;
          strToken = ...(NULL, " "); //On selectionne le token suivant
          if (strToken[0] == '\n')
          { // On enlève les caractère de saut de ligne '\n'
            strToken = NULL;
          }
        }
      }
    }
   
    printf("n_image = %d\n", n_image);
    for (i = 0; i < size * 3; i++)
    {
      global_tab[...] = pixels[i]; //On remplit le tableau global pour pouvoir reutiliser le tableau pixel
    }
    printf("Closing file %s\n", ...);

    // Close the file
    if (f_close(...))
    {
      printf("fail to close file!");
      return 0;
    }

  free(...);
  free(...);
  free(...);

}

void convert_to_greyscale(int n_image, int *tab_size, int *tab_width, int *tab_length, uint8_t *global_tab, uint8_t image[CONV_READ_SIZE_PGM])
{
  printf("Affichage image numero : %d   %d*%d=%d\n", n_image, tab_width[n_image - 1], tab_length[n_image - 1], tab_size[n_image - 1]);
  //Transformation Greyscale
  for (int i = 0; i < tab_size[n_image - 1] * 3; i += 3)
  { //For each pixel on R, G et B                  //On remplit pixel par pixel le tableau image en utilisant 0.3 de la valeur de R, 0.57 de la valeur de G et et 0.11 de la valeur de B par pixels du tableau global_tab
    ... }
}


// Files in the application/include folder
#include "reading.h"
#include "application.h"

// General
#include <stddef.h>
#include <stdint.h>
#include <memory.h>

#include "encoding.h"
#include "mini-printf.h"
#include "diskio.h"
#include "ff.h"
#include "bits.h"
#include "hid.h"
#include "eth.h"
#include "elfriscv.h"
#include "lowrisc_memory_map.h"

// For the CNN application ----
#include "types.h"
#include "top_cnn_mancini.h"
#include "coeffs_cifar.h"
#include "biases_cifar.h"

// Including paramter (sizes, images to read, number of filters ...)
#include "date2020_config.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  Partie Lecture des images  //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void read_pic(int n_image, int *tab_size, int *tab_width, int *tab_length, uint8_t *global_tab) {
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

    // Generation du nom de fichier
    // MODIFIED: sprintf( ..., "%d.ppm", ... );
    sprintf( file_name, "%d.ppm", n_image );

    // Open a file
    // MODIFIED: printf("Loading %s\n", ... );
    printf("Loading %s\n", file_name );
    
    // MODIFIED : fr = f_open( ... , ... , FA_READ);
    fr = f_open(&fil, file_name, FA_READ);
    if (fr) {
        // MODIFIED: printf("Failed to open %s!\n", ... );
        printf("Failed to open %s!\n", file_name );
        return 0;
    }

    //Lecture de l'entete
    // MODIFIED: fr = f_read( ... , &c1, 1, ... );
    // MODIFIED: fr = f_read( ... , &c2, 1, ... ); 
    fr = f_read( &fil, &c1, 1, &br);
    fr = f_read( &fil, &c2, 1, &br);

    // Si l'entete vaut les caracteres 'P3' alors, on est dans le cas d'un fichier ppm
    // OMG that's just horrible coding
    if (c1 == 0x50 && c2 == 0x33) {
        // MODIFIED: printf("Le fichier %s est un fichier ppm P3.\n", ... );
        printf("Le fichier %s est un fichier ppm P3.\n", file_name);
        
        // MODIFIED: plop = f_gets(text, 10000, ... ); 
        // MODIFIED: plop = f_gets(text, 10000, ... );
        plop = f_gets(text, 10000, &fil);
        plop = f_gets(text, 10000, &fil);
        
        if (text[0] == '#')
        { // test ligne de commentaire de openCV
            plop = f_gets(text, 10000, &fil);
        }
        
        // MODIFIED: strToken = ...(text, " "); //Utilisation des fonctions sur les chaînes de caractères décrites plus haut
        strToken = strtok(text, " "); //Utilisation des fonctions sur les chaînes de caractères décrites plus haut
        
        // MODIFIED: length = ...(strToken); //Lecture de la longueur de l'image 
        length = atoi(strToken); //Lecture de la longueur de l'image
        
        // MODIFIED: strToken = ...(NULL, "\n"); 
        strToken = strtok(NULL, "\n");
        
        // MODIFIED: width = ...(strToken); //Lecture de la largeur de l'image
        width = atoi(strToken); //Lecture de la largeur de l'image

        size = length * width;
        
        // MODIFIED:
        /*
            tab_width[...] = width;						//Remplissage des tableaux des valeus de longueur, largeur et taille des images lues 
            tab_length[...] = length;
            tab_size[...] = size;        
        */
        tab_width[n_image - 1] = width;						//Remplissage des tableaux des valeus de longueur, largeur et taille des images lues 
        tab_length[n_image - 1] = length;
        tab_size[n_image - 1] = size;
        
        for (i = 0; i < size; i++)					//initialisation du tableau pixel
        {
            pixels[i] = 0;
        }
        
        // MODIFIED:
        /*
            printf("File size: %d and image size : %d * %d = %d\n", ... ,
                    tab_length[ ... ],
                    tab_width[ ... ],
                    tab_size[ ... ]);
        */
        printf("File size: %d and image size : %d * %d = %d\n", size ,
                tab_length[n_image - 1],
                tab_width[n_image - 1],
                tab_size[n_image - 1]);
        
        // MODIFIED: plop = f_gets(text, 10000, ... );
        plop = f_gets(text, 10000, &fil );
        
        i = 0;
        
        plop = calloc(3 * size, sizeof(*plop));
        //Pour toutes les lignes du fichier
        while (&fil != NULL && i < (3 * size))
        {
            // MODIFIED: plop = f_gets(text, 10000, ... ); //On lit une ligne 
            plop = f_gets(text, 10000, &fil ); //On lit une ligne

            // MODIFIED: strToken = ...(text, " ");  //On separe les differents chiffres 
            strToken = strtok(text, " ");  //On separe les differents chiffres

            //Pour tous les chiffres de la ligne
            while (strToken != NULL && i < (3 * size))
            {
                // MODIFIED: pixels[i] = ...(strToken); //On remplit le tableau pixel par pixel 
                pixels[i] = atoi(strToken); //On remplit le tableau pixel par pixel

                i++;

                // MODIFIED: strToken = ...(NULL, " "); //On selectionne le token suivant
                strToken = strtok(NULL, " "); //On selectionne le token suivant

                if (strToken[0] == '\n')
                { // On enlève les caractère de saut de ligne '\n'
                    strToken = NULL;
                }
            }
        }
    }

    printf("n_image = %d\n", n_image);
    
    for (i = 0; i < size * 3; i++) {
        // MODIFIED: global_tab[...] = pixels[i]; //On remplit le tableau global pour pouvoir reutiliser le tableau pixel 
        global_tab[n_image*size*3 + i] = pixels[i]; //On remplit le tableau global pour pouvoir reutiliser le tableau pixel
    }
    
    // MODIFIED: printf("Closing file %s\n", ...); 
    printf("Closing file %s\n", file_name);

    // Close the file
    // MODIFIED: if (f_close(...))
    if (f_close(&fil))
    {
        printf("fail to close file!");
        return 0;
    }

    // MODIFIED:
    /*
        free(...);
        free(...);
        free(...);
    */
    free(strToken);
    free(text);
    free(plop);
}

void convert_to_greyscale(int n_image, int *tab_size, int *tab_width, int *tab_length, uint8_t *global_tab, uint8_t image[CONV_READ_SIZE_PGM]) {
    printf("Affichage image numero : %d   %d*%d=%d\n", n_image, tab_width[n_image - 1], tab_length[n_image - 1], tab_size[n_image - 1]);
    
    // Size of image - Considering that all images have the same size
    int size = tab_size[n_image - 1] * 3;

    // Each channel of a pixel
    uint8_t R;
    uint8_t G;
    uint8_t B;
    
    //Transformation Greyscale
    for (int i = 0; i < size; i += 3)
    {
        // For each pixel on R, G et B
        // On remplit pixel par pixel le tableau image en utilisant 0.3 de la valeur de R, 0.57 de la valeur de G et et 0.11 de la valeur de B par pixels du tableau global_tab

        // Getting each component
        R = global_tab[n_image*size + i];
        G = global_tab[n_image*size + i + 1];
        B = global_tab[n_image*size + i + 2];

        image[i] = 0.3*R + 0.57*G + 0.11*B;
    }
}


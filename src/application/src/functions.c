// Files in the application/include folder
#include "functions.h"

//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  Fonctions Utiles  /////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
/* Les fonctions suivantes ont ete ajoutees dans ce fichier car nous n'avons pas reussi a les inclures depuis les fichiers du RISC-V */
/* Fonction servant à ajouter une chaine de caractere a une autre */
char *My_strcat(char *dest, const char *src)
{
  char *tmp = dest;

  while (*dest)
    dest++;
  while ((*dest++ = *src++) != '\0')
    ;

  return tmp;
}

/* Fonction servant a transformer un caractere en chiffre (dans les cas ou c'est possible) */
int My_atoi(char *chaine)
{
  int res = 0;
  int i;
  for (i = 0; chaine[i] != '\0'; i++)
  {
    res = res * 10 + chaine[i] - '0';
  }
  return res;
}

/* Fonctions utilisees par My_strtok */
char *My_strpbrk(const char *cs, const char *ct)
{
  const char *sc1, *sc2;

  for (sc1 = cs; *sc1 != '\0'; ++sc1)
  {
    for (sc2 = ct; *sc2 != '\0'; ++sc2)
    {
      if (*sc1 == *sc2)
        return (char *)sc1;
    }
  }
  return NULL;
}

size_t My_strspn(const char *s, const char *accept)
{
  const char *p;
  const char *a;
  size_t count = 0;

  for (p = s; *p != '\0'; ++p)
  {
    for (a = accept; *a != '\0'; ++a)
    {
      if (*p == *a)
        break;
    }
    if (*a == '\0')
      return count;
    ++count;
  }

  return count;
}

/* Variable globale utilisee par My_strtok stockant les token suivants */
char *___mystrtok;

/* Fonction permettant de séparer une chaine de caractere en differents token stockes dans __strtok 
   Utilisation : Token = strtok(chaine de caractere, separateur)
                 Token suivant = strtok(NULL, separateur) */
char *My_strtok(char *s, const char *ct)
{

  char *sbegin, *send;

  sbegin = s ? s : ___mystrtok;
  if (!sbegin)
  {
    return NULL;
  }
  sbegin += My_strspn(sbegin, ct);
  if (*sbegin == '\0')
  {
    ___mystrtok = NULL;
    return (NULL);
  }
  send = My_strpbrk(sbegin, ct);
  if (send && *send != '\0')
    *send++ = '\0';
  ___mystrtok = send;
  return (sbegin);
}

// Cifar Related Results  -------------------------------------

unsigned int cifar_class[1];        // Contains the name of the result class
image_type cifar_probabilities[10]; // Contains the probability of each class
const char Cifar10Base[10][11] = {  // Contains the name of each class
    "Airplane",
    "Automobile",
    "Bird",
    "Cat",
    "Deer",
    "Dog",
    "Frog",
    "Horse",
    "Ship",
    "Truck"};

//--------------------------------------------------------------

extern volatile uint64_t *const hid_new_vga_ptr; // = (volatile uint64_t *)(new_vga_base_addr);

uint8_t TAB_GS[NB_IMAGES_TO_BE_READ][DISPLAY_IMAGE_SIZE] = {0};          //Tableau de pixel de toutes les images rangeais les uns apres les autres
uint8_t TAB_GS_FILTERED[NB_IMAGES_TO_BE_READ][DISPLAY_IMAGE_SIZE] = {0}; //Tableau de pixel de toutes les images rangeais les uns apres les autres

// CNN Stuff --------------------------------------------------------------------
// Tableau de pixel de toutes les images rangés les uns apres les autres
uint8_t global_tab[NB_IMAGES_TO_BE_READ * DISPLAY_IMAGE_SIZE * 3] = {0};

uint8_t resized_img[NN_IN_SIZE * 3] = {0};
float resized_tensor[NN_IN_SIZE * 3] = {0};
float normalized_tensor[NN_IN_SIZE * 3] = {0};
// -------------------------------------------------------------------------------------
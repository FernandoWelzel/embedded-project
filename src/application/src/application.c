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

// Specific for the application
#include "application.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////  Fonction Main //////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
  // Start by initializing everything, just in case.
  init_csrs();

  // SHow about message
  about();

  int x = 0;
  int l = 0;
  int n_image = MIN_IMAGES_TO_READ;
  int tab_size[NB_IMAGES_TO_BE_READ] = {0};   //Tableau de toutes les tailles d'images chargees
  int tab_width[NB_IMAGES_TO_BE_READ] = {0};  //Tableau de toutes les largeur d'images chargees
  int tab_length[NB_IMAGES_TO_BE_READ] = {0}; //Tableau de toutes les longueurs d'images chargees

  // Register work area to the default drive
  if (f_mount(&FatFs, "", 1))
  {
    printf("Fail to mount SD driver!\n");
    return 0;
  }

  printf("Number of images to read : %d,    MIN = %d    MAX = %d\n", NB_IMAGES_TO_BE_READ, MIN_IMAGES_TO_READ, MAX_IMAGES_TO_READ);

  // MIN and MAX are included
  for ( ... )				// Lire chaque image et les stocker dans global_tab
  {
    
    ... ;

  }

  
  if (f_mount(NULL, "", 1))
  { // unmount it
    printf("fail to umount disk!");
    return 0;
  }

  // All images loaded, grayscale conversion now.

  // Start the application: {filtering | no filtering} + on_screen
  for ( ... )				//Pour chaque image de global_tab, appliquer le greyscale et stocker le résultat dans TAB_GS 
  {
    ... ;  
  }

  // FILTERING STUFF
  printf("Starting filtering!\n");
  for ( ... )                           //Pour chaque image de TAB_GS, appliquer la convolution et les stocker dans TAB_GS_FILTERED
  {
    ... ;
  }
  printf("Filtering done !\n");



  // Activate the Button inputs
  init_csrs();
  enable_plic_interrupts();

  extern volatile int imageSel;
  extern volatile int filterSel;
  extern volatile int isBouncing;

  imageSel = 0;
  filterSel = 0;
  uint8_t previous_imageSel = -1;
  uint8_t previous_filterSel = -1;

  uint8_t edgeDetectorDone = 0;
  uint8_t CNNDone = 0;

  volatile unsigned int ii;

  while (1)
  {
    if ( ... )    //Comparaison des valeurs courantes et précédentes des variables de sélection de l'image et du filtre
    {
      if ( ... )
      {
        edgeDetectorDone = 0;
        CNNDone = 0;
      }

      display( ... );		//Si dif_mountfférence, maise à jour de l'affichage

      ... ;						//Mise à jour de des valeurs de previous_imageSel et previous_filterSel en fonction des valeurs courantes
      ... ;
    }

    ii = 10000;
    while (ii--)
    {
      isBouncing = 0;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void about()
{
  printf("----- DEMO DATE 2020 - University Booth --------\n");
  printf(" by Noureddine Ait Said, and the PHELMA students\n");
  printf("          Supervised by Mounir Benabdenbi       \n");
  printf("            AMfoRS Team, TIMA Laboratory        \n");
  printf("------------------------------------------------\n");
  printf("      Version 1.0  Built @" __TIMESTAMP__ "     \n");
  printf("------------------------------------------------\n");
  printf("\n");
  printf("(#################################################\n");
  printf("(#################################################\n");
  printf("(###########,,/((//*,*/.(###((######(#############\n");
  printf("(##########*/((((((((((((((((((*,*/((((,(#########\n");
  printf("(##########,((((((((((((((((((((((((((((.#########\n");
  printf("(#########,/((((((((((((((((((((((((((((*.,,,,,*##\n");
  printf("(#####(**,/(((((((((((((((((((((((((((((((((((((/,\n");
  printf("(###(./(((((((((((((((((((((((((((((((((((((((((((\n");
  printf("(,/((((((((((((((((((((((((((((((((((((((/,       \n");
  printf("/*((((((((((/////((((((((((((((((///(((.  ./(,    \n");
  printf(" /(((((((////////((((((((((((/.      ////,   ,    \n");
  printf("/(/*,     ,//////(((///.      .*,    *.   *(*     \n");
  printf("          ,/(//*/*     .,    ,((*    ,     ./((((/\n");
  printf("   .*((/*./*    /*    /((.   ,((*    /(((((((((((/\n");
  printf("/(((/     /*    /*    /((.   ,(((((((((((((((((((/\n");
  printf("/(((/     /*    /*    /((((((((((((((((((((((((((/\n");
  printf("/(((/     /*    ///((((((((((((((((((((((((((((((/\n");
  printf("/(((/     /((((((((((((((((((((((((((((((((((((((/\n");
  printf("/((((/(((((((((((((((((((((((((((((((((((((((((((/\n\n\n");
}

int lowrisc_init(unsigned long addr, int ch, unsigned long quirks);
void tohost_exit(long code);

unsigned long get_tbclk(void)
{
  unsigned long long tmp = 1000000;
  return tmp;
}

char *env_get(const char *name)
{
  return (char *)0;
}

int init_mmc_standalone(int sd_base_addr);

DSTATUS disk_initialize(uint8_t pdrv)
{
  printf("\nu-boot based first stage boot loader\n");
  init_mmc_standalone(sd_base_addr);
  return 0;
}

int ctrlc(void)
{
  return 0;
}

void *find_cmd_tbl(const char *cmd, void *table, int table_len)
{
  return (void *)0;
}

unsigned long timer_read_counter(void)
{
  return read_csr(0xb00) / 10;
}

void __assert_fail(const char *__assertion, const char *__file,
                   unsigned int __line, const char *__function)
{
  printf("assertion %s failed, file %s, line %d, function %s\n", __assertion, __file, __line, __function);
  tohost_exit(1);
}

void *memalign(size_t alignment, size_t size)
{
  char *ptr = malloc(size + alignment);
  return (void *)((-alignment) & (size_t)(ptr + alignment));
}

int do_load(void *cmdtp, int flag, int argc, char *const argv[], int fstype)
{
  return 1;
}

int do_ls(void *cmdtp, int flag, int argc, char *const argv[], int fstype)
{
  return 1;
}

int do_size(void *cmdtp, int flag, int argc, char *const argv[], int fstype)
{
  return 1;
}

DRESULT disk_read(uint8_t pdrv, uint8_t *buff, uint32_t sector, uint32_t count)
{
  while (count--)
  {
    read_block(buff, sector++);
    buff += 512;
  }
  return FR_OK;
}

DRESULT disk_write(uint8_t pdrv, const uint8_t *buff, uint32_t sector, uint32_t count)
{
  return FR_INT_ERR;
}

DRESULT disk_ioctl(uint8_t pdrv, uint8_t cmd, void *buff)
{
  return FR_INT_ERR;
}

DSTATUS disk_status(uint8_t pdrv)
{
  return FR_INT_ERR;
}

void part_init(void *bdesc)
{
}

void part_print(void *desc)
{
}

void dev_print(void *bdesc)
{
}

unsigned long mmc_berase(void *dev, int start, int blkcnt)
{
  return 0;
}

unsigned long mmc_bwrite(void *dev, int start, int blkcnt, const void *src)
{
  return 0;
}

const char version_string[] = "LowRISC minimised u-boot for SD-Card";

/*
    Description:
        - Put all the MACROS and includes you need to compile the project
        - Put the function definitions here for it to be called by the application
*/

// Informations of the read images
#define CONV_READ_WIDTH 640
#define CONV_READ_HEIGHT 480
#define CONV_READ_SIZE_PPM CONV_READ_WIDTH *CONV_READ_HEIGHT * 3
#define CONV_READ_SIZE_PGM CONV_READ_WIDTH *CONV_READ_HEIGHT
#define CONV_READ_INT_FORMAT float

// TODO : FIX this abomination
extern unsigned char OVERLAYS_LIST[];
//-----------------------------

#define DEBUG 0
#define DEBUG_PRINTF(...)  \
  do                       \
  {                        \
    if (DEBUG)             \
      printf(__VA_ARGS__); \
  } while (0)

//-----------------------------

FATFS FatFs; // Work area (file system object) for logical drive
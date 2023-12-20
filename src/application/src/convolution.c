// Files in the application/include folder
#include "convolution.h"

///////////////////////////////////////////////////////////////////////////////////
///////////////////// CONVOLUTION SIMPLE FIN //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
static KERNEL_CONV_FIXED_FORMAT kernel[] = {-0.125, -0.125, -0.125,
                                            -0.125, 1, -0.125,
                                            -0.125, -0.125, -0.125};

static BIAISES_CONV_FIXED_FORMAT biaises[] = {0};

// filter_nb = soit 0 soit 1
void convolution_filter(uint8_t image[CONV_READ_SIZE_PGM], KERNEL_CONV_FIXED_FORMAT kernel[3 * 3 * 1], BIAISES_CONV_FIXED_FORMAT biaises[1], uint8_t output[CONV_CONV_TOTAL_SIZE])
{
  for (int j = 0; j < CONV_CONV_SIZE_1; j++)
  {
    for (int i = 0; i < CONV_CONV_SIZE_0; i++)
    {
      for (int c = 0; c < CONV_CONV_SIZE_2; c++)
      {
        CONV_CONV_FIXED_FORMAT sum = 0;
        for (int l = 0; l < KERNEL1_CONV_SIZE_L; l++)
        {
          for (int m = 0; m < KERNEL1_CONV_SIZE_M; m++)
          {
          bn:
            for (int n = 0; n < KERNEL1_CONV_SIZE_N; n++)
            {
              if (((j + n) > (CONV_CONV_SIZE_1 - 1)) && ((i + m) < (CONV_CONV_SIZE_0 - 1)))
              {
                sum = sum + 0;
              }
              else if (((i + m) > (CONV_CONV_SIZE_0 - 1)) && ((j + n) < (CONV_CONV_SIZE_1 - 1)))
              {
                sum = sum + 0;
              }
              else if (((i + m) > (CONV_CONV_SIZE_0 - 1)) && ((j + n) > (CONV_CONV_SIZE_1 - 1)))
              {
                sum = sum + 0;
              }
              else if (((i + m) < (CONV_CONV_SIZE_0)) && ((j + n) < (CONV_CONV_SIZE_1)))
              {
                sum = sum + image[indexCalculationCONV((i + m), (j + n), l, (CONV_CONV_SIZE_0), (CONV_CONV_SIZE_1), (CONV_CONV_SIZE_2))] * kernel[m + n * KERNEL1_CONV_SIZE_M + l * KERNEL1_CONV_SIZE_M * KERNEL1_CONV_SIZE_N + c * KERNEL1_CONV_SIZE_M * KERNEL1_CONV_SIZE_N * KERNEL1_CONV_SIZE_L];
              }
            }
          }
        }

        CONV_CONV_FIXED_FORMAT tmp = sum * CONV_CONV_NORMALIZE;

        if (tmp < 0)
        {
          tmp = tmp * (CONV_CONV_FIXED_FORMAT)(-1);
        }

        if (sum < EDGE_DETECTOR_THRESHOLD)
        {
          output[indexCalculationCONV(i, j, c, (CONV_CONV_SIZE_0), (CONV_CONV_SIZE_1), (CONV_CONV_SIZE_2))] = 0;
        }
        else if (sum > 255 || tmp > 255)
        {
          output[indexCalculationCONV(i, j, c, (CONV_CONV_SIZE_0), (CONV_CONV_SIZE_1), (CONV_CONV_SIZE_2))] = 255;
        }
        else
        {
          output[indexCalculationCONV(i, j, c, (CONV_CONV_SIZE_0), (CONV_CONV_SIZE_1), (CONV_CONV_SIZE_2))] = (uint8_t)(tmp + biaises[0]);
        }
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  Partie CNN  ///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//square root function
float __ieee754_sqrtf(float x)
{
  asm("... %0, %1"
      : "=f"(x)
      : "f"(x));
  return x;
}

double __ieee754_sqrt(double x)
{
  asm("... %0, %1"
      : "=f"(x)
      : "f"(x));
  return x;
}

// This use the AREA based resizing method, just like the one used in OpenCV
void my_resizing(uint8_t *target_img, uint8_t *source_img, int source_size, int source_sizeX, int source_sizeY,   //Conversion d'une image 640*480 vers 24*24
                 int target_size, int target_sizeX, int target_sizeY)
{
  double temp = 0.0;
  int w = 0;

	...
}

//
// Normalizing the image 24x24 to be feed to the CNN
//
float *normalizing(float *normalized_img, float *resized_img, int size) // height * width * 3
{
  ...
}

//
// Normalizing the image 24x24 to be feed to the CNN
//
float *normalizing_tensor(float *target_tensor, float *source_tensor, int size) // height * width
{
 ...
}

/*
  Converting an RGB image to a tensor, 
    i.e. R0R1R2......G0G1G2........B0B1B2......
*/
void img_to_tensor(float *target_tensor, uint8_t *source_img, int source_size, int source_sizeX, int source_sizeY)
{
  ...
}

//Cette fonction a été retirée de votre template, mais vous pouvez vous en inspirer pour écrire la votre
/*extern void top_cnn_mancini(coef_type tab_coeffs[NB_COEFFS], coef_type tab_biais[NB_BIAIS], led_type cifar_class[1], image_type image_in[CONV_SIZE_1 * CONV_SIZE_1 * 3], image_type cifar_probabilities[NCAN_OUT_5]);*/  
int perform_cnn(int img_in_number)	//fonction top du CNN
{
  // Source = the 640*480 image
  int source_size = DISPLAY_IMAGE_SIZE; // SOURCE IMG (640*480)
  int source_sizeY = DISPLAY_IMAGE_HEIGHT;
  int source_sizeX = DISPLAY_IMAGE_WIDTH;
  // target is the resized/normalized outputs
  int target_size = NN_IN_SIZE; // RESIZED size
  int target_sizeY = NN_IN_HEIGHT;
  int target_sizeX = NN_IN_WIDTH;

  // Allocate memory for intermediate images/tensors
  uint8_t *source_img;
  
  // Load the 640*480 PPM image
  source_img = ... ;

  // Resize to a 24*24 RGB img.
  DEBUG_PRINTF("Starting resizing");
  my_resizing( ... );

  // Convert to a tensor
  DEBUG_PRINTF("Starting img_to_tensor \n");
  img_to_tensor(...);

  // Normalization
  DEBUG_PRINTF("Starting normalization \n");
  normalizing_tensor(...);

  /*top_cnn_mancini(tab_coeffs, tab_biais, cifar_class, normalized_tensor, cifar_probabilities);*/

  printf("\nairplane :    %d \n", (int)cifar_probabilities[0]);
  printf("automobile :  %d \n", (int)cifar_probabilities[1]);
  printf("bird :        %d \n", (int)cifar_probabilities[2]);
  printf("cat :         %d \n", (int)cifar_probabilities[3]);
  printf("deer :        %d \n", (int)cifar_probabilities[4]);
  printf("dog :         %d \n", (int)cifar_probabilities[5]);
  printf("frog :        %d \n", (int)cifar_probabilities[6]);
  printf("horse :       %d \n", (int)cifar_probabilities[7]);
  printf("ship :        %d \n", (int)cifar_probabilities[8]);
  printf("truck :       %d \n", (int)cifar_probabilities[9]);
  printf("--> The image type is %s with a probability of : %d \n\n", Cifar10Base[cifar_class[0]], (int)cifar_probabilities[cifar_class[0]]);

  return cifar_class[0];
}
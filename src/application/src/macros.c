// Files in the application/include folder
#include "macros.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MACROS
#define indexCalculationCONV(i, j, c, size_i, size_j, size_c) (i + j * size_i + c * size_i * size_j)

// Filter type enum
enum filter_type
{
  BYPASS,
  EDGE_DETECTOR,
  CNN_CLASSIFIER
};
typedef enum filter_type filter_type;

/* CONVOLUTION */
#define CONV_CONV_SIZE_0 640
#define CONV_CONV_SIZE_1 480
#define CONV_CONV_SIZE_2 1
#define CONV_CONV_TOTAL_SIZE CONV_CONV_SIZE_0 *CONV_CONV_SIZE_1
#define CONV_CONV_FIXED_FORMAT float
#define CONV_CONV_NORMALIZE 15

/* CONV KERNEL(S) */
#define KERNEL1_CONV_SIZE_L 1
#define KERNEL1_CONV_SIZE_M 3
#define KERNEL1_CONV_SIZE_N 3

#define KERNEL_CONV_FIXED_FORMAT float

#define EDGE_DETECTOR_NORMALIZE (float)0.00194
#define EDGE_DETECTOR_NORMALIZE2 (float)0.0623
#define EDGE_DETECTOR_THRESHOLD 15

/* CONV BIAISES */
#define BIAISES_CONV_FIXED_FORMAT float
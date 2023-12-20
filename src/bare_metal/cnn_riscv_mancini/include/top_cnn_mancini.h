#ifndef TOP_H
#define TOP_H

#include "types.h"

void top_cnn_mancini(coef_type tab_coeffs[NB_COEFFS], coef_type tab_biais[NB_BIAIS],  led_type cifar_class[1], image_type image_in[CONV_SIZE_1*CONV_SIZE_1*3], image_type cifar_probabilities[NCAN_OUT_5]);

#endif

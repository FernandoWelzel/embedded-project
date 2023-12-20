// Files in the application/include folder
#include "display.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  Partie Display  /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void display(int img_in_number, filter_type filter_nb, uint8_t previous_imageSel, uint8_t previous_filterSel) //, uint8_t *edgeDetectorDone, uint8_t *CNNDone)
{
  volatile uint64_t *display_ptr;
  volatile uint64_t *diplay_ptr_filtered;
  volatile uint8_t *ptr_selected_img;
  volatile uint8_t *ptr_selected_img_filtered;

  // Get the image to print
  display_ptr = (uint64_t *)(TAB_GS[img_in_number - 1]);
  ptr_selected_img = (uint8_t *)(TAB_GS[img_in_number - 1]);
  diplay_ptr_filtered = (uint64_t *)(TAB_GS_FILTERED[img_in_number - 1]);
  ptr_selected_img_filtered = (uint8_t *)(TAB_GS[img_in_number - 1]);

  int x, y;

  switch (filter_nb)				//Disjonction de cas en fonction du filtre sélectionné
  {

  case BYPASS:
    on_screen( ... );
    break;

  case EDGE_DETECTOR:
    on_screen( ... );
    break;

  case CNN_CLASSIFIER:
    // In this case we visualize the image, while computing ...
    display_ptr = (uint64_t *)(TAB_GS[img_in_number - 1]);
    for (y = 0; y < 480; ++y)
    {
      for (x = 0; x < 640 / 8; ++x)
      {
        ... = ... ;
	... ;
      }
    }
    // Launch the CNN
    int result = ... ;
    // When finished, show the LABEL as an overlay.
    on_screen( ... );
    break;
  }
}

void on_screen(int mode, int class, uint8_t *img)
{ //, uint8_t* proc_img){
  //printf("Welcome to on_screen\n");

  int y, x;
  int y_offset, x_offset;
  volatile uint64_t *ptr_image = (uint64_t *)(img);
  volatile uint64_t *ptr_labels_overlay = (uint64_t *)(OVERLAYS_LIST);

  if (mode == BYPASS)										//Sélection de l'étiquette en fonction du filtre choisi
  {
    printf("\nPainting BYPASS overlay.\n");
    //L'image à l'indice 10 correspond à l'overlay du bypass
    ptr_labels_overlay = ... ; // on decale pour sauter les etiquettes des classes du CNN
    y_offset = 0;
    x_offset = 0;
  }
  else if (mode == CNN_CLASSIFIER)
  {
    printf("\nPainting CNN CLASS overlay\n");
    //L'image aux indices 0 à 9 correspondent aux overlays des différentes classes du CNN
    ptr_labels_overlay = ... ;
    y_offset = 0;
    x_offset = 0;
  }
  else if (mode == EDGE_DETECTOR)
  {
    printf("\nPainting the FILTER overlay\n");
    //L'image à l'indice 11 correspond à l'overlay du edge detector
    ptr_labels_overlay = ... ; //apres les etiquettes des classes
    y_offset = 0;
    x_offset = 0;
  }

  for (y = 0; y < 480; ++y)						//Affichage de l'image
  {
    for (x = 0; x < 640 / 8; ++x)
    {
      if ( ...
      { //on verifie si on est dans la zone de l'etiquette
        hid_new_vga_ptr[x + y * 640 / 8] = (*ptr_labels_overlay);
        ptr_labels_overlay++;
      }
      else
      {
        hid_new_vga_ptr[x + y * 640 / 8] = (*ptr_image);
      }
      ptr_image++;
    }
  }
}

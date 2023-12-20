// Files in the application/include folder
#include "interruptions.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////  Partie Interruptions  ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FOR INTERRUTPS  ------------------------------------------

void init_csrs()
{
  ... ;    // init mie
  ... ;    // init sie
  ... ;    // init mip
  ... ;    // init sip
  ... ;    // init mideleg
  ... ;    // init medeleg
}

#define PLIC_BASE_ADDRESS 0x0C000000
#define PLIC_MAX_PRIORITY 7

#define ID_BTNW 1
#define ID_BTNE 2
#define ID_BTNS 3
#define ID_BTNN 4

#define PLIC_PRIORITY_BTNW (PLIC_BASE_ADDRESS + 4 * ID_BTNW)
#define PLIC_PRIORITY_BTNE (PLIC_BASE_ADDRESS + 4 * ID_BTNE)
#define PLIC_PRIORITY_BTNS (PLIC_BASE_ADDRESS + 4 * ID_BTNS)
#define PLIC_PRIORITY_BTNN (PLIC_BASE_ADDRESS + 4 * ID_BTNN)

#define PLIC_INT_PENDING_BASEADDR 0x0C001000
#define PLIC_INT_ENABLE_BASEADDR 0x0C002000

#define PLIC_HART0_PRIO_THRESH_ADDR 0x0C200000
#define PLIC_HART0_CLAIM_COMPLETE_ADDR 0x0C200004

// Masks definition
// Refers to chip_top.sv to know the connections of the buttons
#define PLIC_PENDING_BTNW (1 << 1)
#define PLIC_ENABLE_BTNW (1 << 1)

#define PLIC_PENDING_BTNE (1 << 2)
#define PLIC_ENABLE_BTNE (1 << 2)

#define PLIC_PENDING_BTNS (1 << 3)
#define PLIC_ENABLE_BTNS (1 << 3)

#define PLIC_PENDING_BTNN (1 << 4)
#define PLIC_ENABLE_BTNN (1 << 4)

void enable_plic_interrupts()
{

  // Setting the Priority of the interrupt with ID 1,2,3 and 4 to value 1, so that the interrupts can be fired
  // Recall that an interrupt is fired when its priority is > than the threshold
  *(volatile unsigned int *) ... ;
  *(volatile unsigned int *) ... ;
  *(volatile unsigned int *) ... ;
  *(volatile unsigned int *) ... ;

  // Setting the priority threshold to Zero
  *(volatile unsigned int *) ... ;

  // clear interrupt pending
  *(volatile unsigned int *) ... ;

  // PLIC ENABLE interrupts of ID 1,2,3 and 4
  // (ID 1 and ID 2 are connected to zero)
  *(volatile unsigned int *)(PLIC_INT_ENABLE_BASEADDR) = ... ;

  // Enable MEIP (Machine External Interrupt Pending) bit in MIE register
  ... ;

  // Enable MIE (Machine Interrupt Enable) bit of MSTATUS
  ... ;
}

volatile int imageSel;
volatile int filterSel; 
volatile int isBouncing;

void external_interrupt(void)
{
  int claim = 0;
#ifdef VERBOSE
  //printf("Hello external interrupdet! "__TIMESTAMP__"\n");
#endif  
  
  // Read the ID (the highest priority pending interrupt)
  // If the value we read is zero then no pending interrupt is coming from PLIC 
  claim = plic[ ... ]; 									//consulter le fichier syscall.c
  clear_csr(mie, MIP_MEIP);
  if(isBouncing == 0)
  {
    // printf("Interrupt executed !\n");
  	// If BTNW :									//Si pression du bouton Ouest, décrémentation de la variable de sélection de l'image
  	if (claim == 1)									//Mise à sa valeur max si elle atteint sa valeur min
  	{
  		... ;
  		if( ... ) ... ;
    }
  	// If BTNE :									//Si pression du bouton Est, incrémentation de la variable de sélection de l'image
  	else if (claim == 2)								//Mise à sa valeur min si elle atteint sa valeur max
  	{
      		... ;
      if( ... )
        ... ;
  	}
  	// If BTNS :									//Si pression du bouton Sud, décrémentation de la variable de sélection du filtre
  	else if (claim == 3)								//Mise à sa valeur max si elle atteint sa valeur min
  	{
  		... ;
  		if( ... ) ... ;
  	}
  	// If BTNN :									//Si pression du bouton Nord, incrémentation de la variable de sélection du filtre
  	else if (claim == 4)								//Mise à sa valeur min si elle atteint sa valeur max
  	{
      		...;
  	}
  	isBouncing = 1;
  }
  
  // Write the ID of the interrupt source to the claim/complete register to complete the interrupt
  // The PLIC will clear the pending bit of the corresponding ID 
  // /!\ If the ID don't match the pending ID, the completion is silently ignored
  plic[ ... ] = claim;
  set_csr(mie, MIP_MEIP); 
}

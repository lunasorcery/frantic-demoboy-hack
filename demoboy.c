/*
 * C version of the 'space' assembly demo.
 *
 * Little demo illustrating how to use the graphical possibilities
 *  of the GB (background, window and animated sprite)
 * I have used fixed-point values for both the position and
 *  speed of objects to get smooth movements
 * 
 * OBJ data             : 0x8000 -> 0x8FFF (unsigned)
 * Window data          : 0x8800 -> 0x97FF (unsigned)
 * Background data      : 0x8800 -> 0x97FF (signed)
 * 
 * Tiled 0xFC -> 0xFF are standard tiles (all black -> all white)
 * 
 * Keys:
 * Arrow keys           : Change the speed (and direction) of the sprite
 * Arrow keys + A       : Change the speed (and direction) of the window
 * Arrow keys + B       : Change the speed (and direction) of the background
 * START                : Open/close the door
 * SELECT               : Basic fading effect
 * 
 * Note that the window is kept in the lower right part of the screen
 * since it can't be made transparent
 */

#include <gb/gb.h>

#include "image.h"

const unsigned char bkg_palette_map[]={
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
};



const UINT8 BKG_PALETTES_LEN = 6;

#define color0 RGB(31,15,0)
#define color1 RGB(31,15,23)
#define color2 RGB(23,15,31)
#define color3 RGB(0,31,0)
#define color4 RGB(0,31,15)
#define color5 RGB(0,31,31)
#define color6 RGB(23,31,7)
#define color7 RGB(31,31,15)

#define colorX RGB(31,31,31)

const UINT16 BKG_PALETTES[] = {
	color0, 0, color1, colorX,
	color2, 0, color1, colorX,
	color2, 0, color3, colorX,
	color4, 0, color5, colorX,
	color6, 0, color5, colorX,
	color6, 0, color7, colorX,
};


void main()
{
  disable_interrupts();
  DISPLAY_OFF;
  LCDC_REG = 0x67;
  /*
   * LCD        = Off
   * WindowBank = 0x9C00
   * Window     = On
   * BG Chr     = 0x8800
   * BG Bank    = 0x9800
   * OBJ        = 8x16
   * OBJ        = On
   * BG         = On
   */

  /* Set palettes */
  BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;

  /* Initialize the background */
  set_bkg_data(0x00, bkg_tiles_count, bkg_tiles);

  set_bkg_palette(0, BKG_PALETTES_LEN, BKG_PALETTES);

  VBK_REG = 1;
  set_bkg_tiles(0, 0, 20, 18, bkg_palette_map);

  VBK_REG = 0;
  set_bkg_tiles(0, 0, 20, 18, bkg_index_map);

  SCX_REG = 0;
  SCY_REG = 0;
  WX_REG = MAXWNDPOSX;
  WY_REG = MAXWNDPOSY;
  
  DISPLAY_ON;
  enable_interrupts();

  while(1) {
      wait_vbl_done();
  }
}

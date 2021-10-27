#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

int main()
{
	
	int i = 0;
	int j = 0;
	int z = 0;
	int square_l = 110;
    int square_r = 210;
	int square_t = 70;
	int square_b = 170;
	
	uint16_t colours[9]= {WHITE, BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, PURPLE};
	uint16_t colour[(square_r-square_l)*(square_b-square_t)];
	
	for(j; j<(square_b-square_t);j++){
		for(i; i<(square_r-square_l);i++){
			if(z>8){
					z=0;
					colour[i+(j*(square_r-square_l))] = colours[z];
				}else{
					z++;
					
				}
		}
	}
	
	init_lcd();
	
	clear_screen() ;
	
	set_orientation(West);
	
	rectangle squ = {square_l,square_r,square_t,square_b};
	
	fill_rectangle_indexed(squ, colour);
	
	display_string("Hello world");
}

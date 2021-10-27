#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "lcd.h"

int endGame();

volatile int u = 0;

	int rect1L = 2;
	int rect1R = 5;
	int rect1T = 50;
	int rect1B = 100;
	
rectangle squ2 = {2,5,50,100};
	
ISR(INT1_vect){
	fill_rectangle(squ2, BLACK);
	if(squ2.top>=6){
	squ2.top = squ2.top - 5;
	squ2.bottom = squ2.bottom - 5;
	fill_rectangle(squ2, WHITE);
	}
}

ISR(INT0_vect){
	fill_rectangle(squ2, BLACK);
	if(squ2.bottom<=234){
	squ2.top = squ2.top + 5;
	squ2.bottom = squ2.bottom + 5;
	fill_rectangle(squ2, WHITE);
	}
}

int main()
{
	
	int i = 0;	//for the incremental movement along horizontal
	int j = 0;	//for the incremental movement along vertical
	
	int xD = 0; // This is the direction of the x value changing, 1 is left and 0 is right
	int yD = 0; // This is the direction of the y value changing, 1 is down and 0 is up
	
	int incrementI = 2;
	int incrementJ = 2;
	
	int square_l = 157;
    int square_r = 162;
	int square_t = 137;
	int square_b = 142;
	int cubeHi = square_b - square_t;
	int cubeWi = square_r - square_l;
	
	int rect2L = 300;
	int rect2R = 300;
	int rect2T = 0;
	int rect2B = 240;
	
	uint16_t colour[] =  {0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF,
						  0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF, 0xF81F, 0xFFFF};
	
	init_lcd();
	
	clear_screen();
	
	set_orientation(West);
	
	rectangle squ = {square_l,square_r,square_t,square_b};
		
	rectangle squ3 = {rect2L,rect2R,rect2T,rect2B};
	
	fill_rectangle(squ, PURPLE);
	fill_rectangle(squ2, WHITE);
	fill_rectangle(squ3, WHITE);
	
	
	EICRA |= _BV(ISC01);
	EICRA |= _BV(ISC11);
	
	EIMSK |= _BV(INT0);
	EIMSK |= _BV(INT1);
	sei();
	
	for(;;){
		_delay_ms(10);
		fill_rectangle(squ, BLACK);
		
		if((squ.right>=(squ2.left-(incrementI)))&&(squ.left<=(squ2.right+incrementI))&&(squ.top>=(squ2.top-cubeHi))&&(squ.bottom<=(squ2.bottom+cubeHi))){
			xD = !xD;
		}
		
		if((squ.top<=(squ2.bottom+incrementJ))&&(squ.bottom>=(squ2.top-incrementJ))&&(squ.right<=(squ2.right+cubeWi))&&(squ.left>=(squ2.left-cubeWi))){
			yD = !yD;
		}
		
		if((squ.right>=(squ2.left-(incrementI-1)))&&(squ.left<=(squ2.right+incrementI-1))&&(squ.top>=(squ2.top-cubeHi))&&(squ.bottom<=(squ2.bottom+cubeHi))&&(squ.right>=(squ2.left-(incrementI-1)))&&(squ.left<=(squ2.right+incrementI-1))&&(squ.top>=(squ2.top-cubeHi))&&(squ.bottom<=(squ2.bottom+cubeHi))){
			yD = !yD;
			xD = !xD;
		}
		
		//This will check if the cube is at the border
		if((300-incrementI) <= (squ.right)){xD = 1;}
		if(incrementI >= (squ.left)){
			xD = 0;
			endGame();
			break;
		}
		if((240-incrementJ) <= (squ.bottom)){yD = 1;}
		if((incrementJ) >= (squ.top)){yD = 0;}
		
		if(xD){
			i = i-incrementI;
		}else{
			i = i+incrementI;
		}
		
		if(yD){
			j = j-incrementJ;
		}else{
			j = j+incrementJ;
		}
		
		squ.right = square_r + i;
		squ.left = square_l + i;
		squ.bottom = square_b + j;
		squ.top = square_t + j;
		
		fill_rectangle(squ, PURPLE);
	}	
}

int startGame(){
	int le = 0;
	char str[] = "yo bitch you failed";
	le = sizeof(str);
	cli();
	set_orientation(North);
	display.background = PURPLE;
	clear_screen();
	display.x = (((display.width+1)/2)-(5/2*le));
	display.y = (display.height/2);
	display_string(str);
	display.x = (display.width+1)/2 - 2;
	display.y = display.height/2 + 10;
	display_string("yeet");
}

int endGame(){
	int le = 0;
	char str[] = {"yo bitch you failed"};
	le = sizeof(str);
	cli();
	set_orientation(North);
	display.background = PURPLE;
	clear_screen();
	display.x = (display.width+1)/2-((le*5)/2);
	display.y = (display.height/2);
	display_string(str);
	display.x = (display.width+1)/2 - 3;
	display.y = display.height/2 + 10;
	display_string("yeet");
}

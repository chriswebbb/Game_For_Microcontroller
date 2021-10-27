#include <avr/io.h>
#include "lcd.h"

int main()
{
init_lcd();//intilise LCD
clear_screen() ;	//Sets background to one colour
display_string("Hello world");	//Displays the string
}

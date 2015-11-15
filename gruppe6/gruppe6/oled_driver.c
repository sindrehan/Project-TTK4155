

#include "oled_driver.h"

#include "font_8x8.h"

#include <string.h>

uint8_t current_page, current_column;
uint8_t char_width = 4;
const unsigned char* font = (unsigned char*)font_1;




void OLED_init(){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	OLED_command(0xae);    // display off
	OLED_command(0xa1);    //segment remap
	OLED_command(0xda);    //common pads hardware: alternative
	OLED_command(0x12);
	OLED_command(0xc8);    //common output scan direction:com63~com0
	OLED_command(0xa8);    //multiplex ration mode:63
	OLED_command(0x3f);
	OLED_command(0xd5);    //display divide ratio/osc. freq. mode
	OLED_command(0x80);
	OLED_command(0x81);    //contrast control
	OLED_command(0x50);
	OLED_command(0xd9);    //set pre-charge period
	OLED_command(0x21);
	OLED_command(0x20);    //Set Memory Addressing Mode
	OLED_command(0x02);
	OLED_command(0xdb);    //VCOM deselect level mode
	OLED_command(0x30);
	OLED_command(0xad);    //master configuration
	OLED_command(0x00);
	OLED_command(0xa4);    //out follows RAM content
	OLED_command(0xa6);    //set normal display
	OLED_command(0xaf);    // display on
	OLED_command(0xb0);		//Page start address
	OLED_command(0x00);		//Lower column start address
	OLED_command(0x10);		//Higher column start address.
	OLED_reset();
	OLED_home();
}	

void OLED_command(char c){
	volatile char* OLED_c = (char*) 0x1000;
	*OLED_c = c;
}

void OLED_data(char c){
	volatile char* OLED_c = (char*) 0x1200;
	*OLED_c = c; 
}

void OLED_go_to_page(char page)
{
	OLED_command(0xB0+page);
	current_page = page;
}

void OLED_clear_page(char page){
	OLED_go_to_page(page);
	for(int i = 0; i < 128; i++){
		OLED_data(0x00);
	}
}

void OLED_reset(){
	for (int i = 0; i < 8; i++){
		OLED_clear_page(i);
	}
}

void OLED_home(){
	OLED_go_to_page(0);
	OLED_go_to_col(0);
}

void OLED_pos(char page, char column){
	OLED_go_to_page(page);
	OLED_go_to_col(column);
}

void OLED_go_to_col(char column){
	char msb = column & 0b11110000;
	msb /= 0b10000;
	char lsb = column & 0b00001111;
	OLED_command(msb+0b00010000);
	OLED_command(lsb);
	current_column = column;
}

void OLED_clear_rest_of_line(){
	for (int i = current_column; i < 128; i++ ){
		OLED_data(0);
	}
	current_column = 0;
}

void OLED_print(char character){
	if (character == '\n'){
		OLED_clear_rest_of_line();	
	}
	else{
		for (int i = 0; i < char_width; i++){
			char byte = pgm_read_byte((font + (character-32)*char_width + i));
			OLED_data(byte);
		}
		if ((current_column+char_width)>127){
			current_column = 0;
		}
		else{
			current_column += char_width;
		}
	}
}

void OLED_print_string(char string[]){
	for(int i = 0; i < strlen(string); i++){
		OLED_print(string[i]);
	}
}

void print_singleplayer(){
	OLED_home();
	OLED_print_string("Single player");
	OLED_clear_rest_of_line();
	OLED_print_string("Time: ");

}
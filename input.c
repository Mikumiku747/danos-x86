//Input

/*
A set of functions to provide an input buffer, decode keyboard messages into
characters, and keep track of the state of buttons.
*/

#ifndef INPUT_C
#define INPUT_C

//Conversion between a keycode and character
char keymap_lower[] = "##1234567890-=\b\tqwertyuiop[]\n#asdfghjkl;\'`#\\zxcvbnm,./#*# #1234567890##789-456+1230.###AB";
char keymap_upper[] = "##!@#$%^&*()_+\b\tQWERTYUIOP{}\n#ASDFGHJKL:\"~#|ZXCVBNM<>?#*# #1234567890##789-456+1230.###AB";

//Keep track of input
volatile char input_buffer[20];
volatile char *next_input = input_buffer;



#endif
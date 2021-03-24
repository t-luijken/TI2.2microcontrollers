#ifndef LCD_H
#define LCD_H

void init();
void display_text(char *str);
void set_cursor(int position);
void lcd_clear();
void wait( int ms );

#endif
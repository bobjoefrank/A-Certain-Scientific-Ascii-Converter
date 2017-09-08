/* Phillip Lai */

#ifndef ASCII_H
#define ASCII_H

/* converts image to ascii characters and prints inside a word file */
void AsciiConversion(IMAGE *image);

/* clips value into luminance range */
int clip_letter(int x);

/* converts RBG to YUV, takes luminance Y and matches intensity with ascii character */ 
char Color2Letter(IMAGE *image, unsigned int x, unsigned int y);

#endif

/* Phillip Lai */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "DIPs.h"
#include "Ascii.h"

void AsciiConversion(IMAGE *image){
	assert(image);
	FILE *testdoc;
	testdoc= fopen("testdoc.txt", "a");

	fprintf(testdoc, "%s", "\n\n\n\n\n");

	int x,y;
	char color_to_letter;
	for( y = 0; y < image->Height; y ++ ) {
		for( x = 0; x < image->Width; x ++ ) {
			color_to_letter = Color2Letter(image,x,y);
			fprintf(testdoc, "%c", color_to_letter);
		}
		if(y == 5){
			fprintf(testdoc, "%s", "&");
		}
		fprintf(testdoc, "%s", "\n");
	}
	fprintf(testdoc, "%s", "$\n\n\n\n\n\n\n\n");
	fclose(testdoc);
}

char Color2Letter(IMAGE *image, unsigned int x, unsigned int y){
	unsigned char char_value;
	char c;

	/* takes RGB values and converts to a weighted luminance value */
	char_value = (unsigned char)clip_letter((((66*GetPixelR(image,x,y)+129*GetPixelG(image,x,y)+25*GetPixelB(image,x,y)+128)>>8)+16));

	/*pairing char_value with estimated ascii character luminance*/
	if(char_value >= 232){
		c= ' ';
		return c;
	}
	if(char_value >= 209){
		c= ' ';
		return c;
	}
	if(char_value >= 197){
		c= '\'';
		return c;
	}
	if(char_value >= 186){
		c= '"';
		return c;
	}
	if(char_value >= 174){
		c= '.';
		return c;
	}
	if(char_value >= 163){
		c= '~';
		return c;
	}
	if(char_value >= 151){
		c= '+';
		return c;
	}
	if(char_value >= 139){
		c= '!';
		return c;
	}
	if(char_value >= 127){
		c= '/';
		return c;
	}
	if(char_value >= 116){
		c= 'L';
		return c;
	}
	if(char_value >= 102){
		c= '7';
		return c;
	}
	if(char_value >= 93){
		c= 'Y';
		return c;
	}
	if(char_value >= 81){
		c= 'V';
		return c;
	}
	if(char_value >= 70){
		c= '5';
		return c;
	}
	if(char_value >= 58){
		c= 'E';
		return c;
	}
	if(char_value >= 47){
		c= 'G';
		return c;
	}
	if(char_value >= 35){
		c= '6';
		return c;
	}
	if(char_value >= 24){
		c= 'B';
		return c;
	}
	if(char_value >= 12){
		c= 'W';
		return c;
	}
	if(char_value >= 0){
		c= '@';
		return c;
	}
}

int clip_letter(int x){
	if (x >= 255){
		x = 255;
	}
	else if(x <= 0){
		x = 0;
	}
	return x;
}



/* EOF */


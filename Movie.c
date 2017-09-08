/* Phillip Lai */

#include <stdlib.h>
#include <assert.h>

#include "Movie.h"


/* Allocate the memory space for the movie and the memory space
 * for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void){
	MOVIE *movie;
	movie = malloc(sizeof(MOVIE));
	movie->Frames = CreateImageList();
	return movie;
}

/* Release the memory space for the frame list.
 * Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie){
	assert(movie);
	DeleteImageList(movie->Frames);
	movie->Frames = NULL;
	free(movie);
}

/* Traverse the double linked list, and convert each entry from one format to the other */


/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie){ 
	assert(movie);
	int x, y;
	IENTRY *curr;
	
	int c,d,e;

	curr = movie->Frames->First;
	while (curr != NULL) {
		curr->RGBImage = CreateImage(curr->YUVImage->Width, curr->YUVImage->Height);
		for (y = 0; y < curr->YUVImage->Height; y++) { 
			for (x = 0; x < curr->YUVImage->Width; x++) {
				c = ( GetPixelY(curr->YUVImage, x, y)) - 16;
				d = ( GetPixelU(curr->YUVImage, x, y)) - 128;
				e = ( GetPixelV(curr->YUVImage, x, y)) - 128;
				SetPixelR(curr->RGBImage, x, y, (unsigned char)clip(((298*c+409*e+128)>>8)));
				SetPixelG(curr->RGBImage, x, y, (unsigned char)clip(((298*c-100*d-208*e+128)>>8)));
				SetPixelB(curr->RGBImage, x, y, (unsigned char)clip(((298*c+516*d+128)>>8)));
			}
		}
		assert(curr->YUVImage);
		DeleteYUVImage(curr->YUVImage);
		curr->YUVImage = NULL;
		curr = curr->Next;
	}
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie){
	assert(movie);
	int x, y;
	IENTRY *curr;

	int temp_r,temp_g,temp_b;

	curr = movie->Frames->First;
	while(curr != NULL){
		curr->YUVImage = CreateYUVImage(curr->RGBImage->Width, curr->RGBImage->Height);
		for(y = 0; y < curr->RGBImage->Height; y++){
			for(x = 0; x < curr->RGBImage->Width; x++){
				temp_r = ( GetPixelR(curr->RGBImage, x, y));
				temp_g = ( GetPixelG(curr->RGBImage, x, y));
				temp_b = ( GetPixelB(curr->RGBImage, x, y));
				SetPixelY(curr->YUVImage, x, y,	(unsigned char)clip((((66*temp_r+129*temp_g+25*temp_b+128)>>8)+16)));
				SetPixelU(curr->YUVImage, x, y, (unsigned char)clip((((-38*temp_r-74*temp_g+112*temp_b+128)>>8)+128)));
				SetPixelV(curr->YUVImage, x, y, (unsigned char)clip((((112*temp_r-94*temp_g-18*temp_b+128)>>8)+128)));
			}
		}
		assert(curr->RGBImage);
		DeleteImage(curr->RGBImage);
		curr->RGBImage = NULL;
		curr = curr->Next;
	}
}

int clip(int x){
	if (x >= 255){
		x = 255;
	}
	else if(x <= 0){
		x = 0;
	}
	return x;
}


/* EOF */



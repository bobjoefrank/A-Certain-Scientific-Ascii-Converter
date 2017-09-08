/* Phillip Lai */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "Movie.h"
#include "ImageList.h"
#include "Image.h"
#include "DIPs.h"
#include "Ascii.h"

#define SLEN 80

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n, 
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum, 
                 unsigned int width, unsigned height);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	char *fin = NULL;
	unsigned int finLen = 0;
	char *fout = NULL;
	unsigned int foutLen = 0;
	int frames = 0;
	unsigned int frame_width, frame_height;
	unsigned int crop_start, crop_end;
	/*unsigned int fast_factor;*/

	int  hflip_flag= 0, edge_flag= 0, crop_flag= 0,/* fast_flag= 0*/ rvs_flag= 0, ascii_flag= 0;

	MOVIE *movie = NULL;

	/* the while loop to check options in the command line */
	while (x < argc) {

		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				finLen = strlen(argv[x + 1]) + strlen(".yuv") + 1;
				fin = (char *)malloc(sizeof(char) * finLen);
				if (fin == NULL) {
					printf("Error in memory allocation for the input file name!\n");
					free(fout);
					return 5;
				}
				strcpy(fin, argv[x + 1]);
				strcat(fin, ".yuv");
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				free(fin);
				free(fout);
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				foutLen = strlen(argv[x + 1]) + strlen(".yuv") + 1;
				fout = (char *)malloc(sizeof(char) *foutLen);
				if (fout == NULL) {
					printf("Error in memory allocation for the output file name!\n");
					free(fin);
					return 5;
				}
				strcpy(fout, argv[x + 1]);
				strcat(fout, ".yuv");
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				free(fin);
				free(fout);
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/
	
		/* how many frames are read from input stream */
		if (strcmp(argv[x], "-f") == 0) {
			if (x < argc -1) {
				sscanf(argv[x + 1], "%d", &frames);
			}
			x += 2;
			continue;
		}

		/* resolution of the input stream */
		if (strcmp(argv[x], "-s") == 0) {
			if (x < argc -1) {
				if(sscanf(argv[x + 1], "%ux%u", &frame_width, &frame_height) == 2){
						
				}
				else {
					printf("Missing argument for the resolution!\n");
					free(fin);
					free(fout);
					return 5;
				}
			}
			x += 2;
			continue;
		}

		/*activate ascii flag */
		if (strcmp(argv[x], "-ascii") == 0){
			ascii_flag = 1;
			x++;
			continue;
		}

		/* activate hflip flag */
		if (strcmp(argv[x], "-hflip") == 0){
			hflip_flag = 1;
			x++;
			continue;
		}

		/* activate edge flag */
		if (strcmp(argv[x], "-edge") == 0){
			edge_flag = 1;
			x++;
			continue;
		}

		/* activate crop flag */
		if (strcmp(argv[x], "-crop") == 0){
			if (x < argc -1){
				if(sscanf(argv[x + 1], "%u-%u", &crop_start, &crop_end) == 2){

				}
				else {
					printf("Missing argument for the start and end!\n");
					free(fin);
					free(fout);
					return 5;
				}
			}
			crop_flag = 1;
			x += 2;
			continue;
		}

		/* not done */
		/* activate fast flag */
		/*
		if (strcmp(argv[x], "-fast") == 0){
			if (x < argc -1){
				if(sscanf(argv[x + 1], "%u", &fast_factor) == 1){

				}
				else {
					printf("Missing argument for the fast foward factor!\n");
					free(fin);
					free(fout);
					return 5;
				}
			}
			fast_flag = 1;
			x += 2;
			continue;
		}
		*/

		/* activate reverse flag */
		if (strcmp(argv[x], "-rvs") == 0){
			rvs_flag = 1;
			x++;
			continue;
		}

		/* the help option */
		if (strcmp(argv[x], "-h") == 0) { 
			PrintUsage();
			free(fin);
			free(fout);
			x++;
			return 0;
		} /*fi*/

		x++;
	} /*elihw*/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}


	
	movie = LoadMovie(fin, frames, frame_width, frame_height);
	

	
	
	/* Operations to be done depending on flags activated */

	if (crop_flag == 1){
		CropImageList(movie->Frames, crop_start, crop_end); 	
	}

	if (ascii_flag == 1){
		YUV2RGBMovie(movie);
		
		IENTRY *curr;

		curr = movie->Frames->First;
		while (curr != NULL){	
			AsciiConversion(curr->RGBImage);
			curr = curr->Next;
		}
		RGB2YUVMovie(movie);
		printf("Operation Ascii is done!\n");
	}

	if (hflip_flag == 1){
		YUV2RGBMovie(movie);

		IENTRY *curr;

		curr = movie->Frames->First;
		while (curr != NULL) {
			curr->RGBImage = HFlip(curr->RGBImage); 
			curr = curr->Next;
		}
		RGB2YUVMovie(movie);
		printf("Operation HFlip is done!\n");
	}
	
	if (edge_flag == 1){
		YUV2RGBMovie(movie);

		IENTRY *curr;

		curr = movie->Frames->First;
		while (curr != NULL) {
			curr->RGBImage = Edge(curr->RGBImage); 
			curr = curr->Next;
		}

		RGB2YUVMovie(movie);
		printf("Operation Edge is done!\n");
	}
 
	/*not done */
	/*
	if (fast_flag == 1){
		YUV2RGBMovie(movie);

		IENTRY *curr;

		curr = movie->Frames->First;
		while (curr != NULL) {
			curr->RGBImage = HFlip(curr->RGBImage); 
			curr = curr->Next;
		}

		RGB2YUVMovie(movie);
	}
	*/

	if (rvs_flag == 1){
		ReverseImageList(movie->Frames); 
	}
	
	SaveMovie(fout, movie);
	DeleteMovie(movie);
	
	movie = NULL;

	free(fin);
	free(fout);
	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-ascii 		      Conversion movie-to-ascii, in created file \"testdoc.txt\"\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>      <- not working yet\n"
	       "-rvs                  Reverse the frame order of the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n, 
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int count; 
	int x, y;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}
	 
	count = 0; 
	curr = movie->Frames->First;
	while (curr != NULL) {
		for (y = 0; y < curr->YUVImage->Height; y++) { 
			for (x = 0; x < curr->YUVImage->Width; x++) {
				fputc(GetPixelY(curr->YUVImage, x, y), file);
			}
		}

		for (y = 0; y < curr->YUVImage->Height; y += 2) { 
			for (x = 0; x < curr->YUVImage->Width; x += 2) {
				fputc(GetPixelU(curr->YUVImage, x, y), file);
			}
		}

		for (y = 0; y < curr->YUVImage->Height; y += 2) { 
			for (x = 0; x < curr->YUVImage->Width; x += 2) {
				fputc(GetPixelV(curr->YUVImage, x, y), file);
			}
		}
		
		curr = curr->Next;	 
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname); 
	return 0;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum, 
                 unsigned int width, unsigned height){
	assert(fname);
	int i;
	MOVIE *movie;
	movie  = CreateMovie();
	for(i = 0; i < frameNum; i++){
		AppendYUVImage(movie->Frames,LoadOneFrame(fname, i, width, height));
	}
	printf("The movie file %s had been read successfully!\n", fname);
	return movie;
}



/* EOF */

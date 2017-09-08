/* Phillip Lai */

#ifndef IMAGELIST_H
#define IMAGELIST_H

#include "Image.h"

typedef struct ImageEntry IENTRY;
typedef struct ImageList ILIST;

struct ImageEntry{
	ILIST *List;		/* Pointer to the list which this entry belongs to */
	IENTRY *Next;		/* Pointer to the next entry, or NULL */
	IENTRY *Prev;		/* Pointer to the previous entry, or NULL */
	IMAGE *RGBImage;	/* Pointer to the RGB image, or NULL */
	YUVIMAGE *YUVImage;	/* Pointer to the YUV image, or NULL */
};

struct ImageList{
	unsigned int Length;	/* Length of the list */
	IENTRY *First;		/* Pointer to the first entry, or NULL */
	IENTRY *Last;		/* Pointer to the last entry, or NULL */
};

/* Create a new image list */
ILIST *CreateImageList(void); /* Allocate the memory space for an empty ImageList */

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list); /* Free the memory space for all entries in the double linked list
				      and the memory space for the ImageList */

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage); /* Append a new entry to the double linked list, 
						      w/ RGBimage valid */

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVImage); /* Append a new entry to the double linked list,
							 w/ YUVIamge valid */

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end); /* Crop a sequence of entries
									  in the double linked list */

/* Fast foward an image list */
void FastImageList(ILIST *list, unsigned int factor); /* Remove a fixed number of entries in between
							 any two entries */

/* Reverse an image list */
void ReverseImageList(ILIST *list); /* Reverse the order of the linked list */

#endif








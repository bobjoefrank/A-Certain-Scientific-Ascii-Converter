/* Phillip Lai */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ImageList.h"
#include "Image.h"

/* Create a new image list */
ILIST *CreateImageList(void){ /* Allocate the memory space for an empty ImageList */
	ILIST *list;
	list = malloc(sizeof(ILIST));
	if (! list){
		perror("Out of memory! Aborting... ");
		exit(10);
	}
	list->Length = 0;
	list->First = NULL;
	list->Last = NULL;
	return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list){ /* Free the memory space for all entries in the double linked list
				      and the memory space for the ImageList */
	assert(list);
	IENTRY *e, *n;
	YUVIMAGE *i;

	assert(list);
	e = list->First;
	while(e){
		n = e->Next;
		assert(e);
		i = e->YUVImage;
		free(e);
		DeleteYUVImage(i);
		e = n;
	}
	free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBImage){ /* Append a new entry to the double linked list, 
						      w/ RGBimage valid */
	IENTRY *e = NULL;
	assert(list);
	assert(RGBImage);
	e = malloc(sizeof(IENTRY));
	if (! e){
		perror("Out of memory! Aborting... ");
		exit(10);
	}
	e->RGBImage = RGBImage;
	e->YUVImage = NULL;
	if(list->Last){
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;
	}
	else{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;
	}
	list->Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVImage){ /* Append a new entry to the double linked list,
							 w/ YUVImagge valid */
	IENTRY *e = NULL;
	assert(list);
	assert(YUVImage);
	e = malloc(sizeof(IENTRY));
	if (! e){
		perror("Out of memory! Aborting... ");
		exit(10);
	}
	e->YUVImage = YUVImage;
	e->RGBImage = NULL;
	if(list->Last){
		e->List = list;
		e->Next = NULL;
		e->Prev = list->Last;
		list->Last->Next = e;
		list->Last = e;
	}
	else{
		e->List = list;
		e->Next = NULL;
		e->Prev = NULL;
		list->First = e;
		list->Last = e;
	}
	list->Length++;
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end){ /* Crop a sequence of entries
									  in the double linked list */
	
	assert(list);
	IENTRY *curr, *next;
	int counter;
	curr = list->First;
	int end_counter = list->Length - end;

	for(counter = 0; counter < start; counter ++){
		curr = list->First;
		list->First = curr->Next;

		DeleteYUVImage(curr->YUVImage);
		curr->YUVImage = NULL;
		curr->Next = NULL;
		curr->Prev = NULL;
		curr->List = NULL;
		
		free(curr);
	}

	list->First->Prev = NULL;

	for(counter = 0; counter < end_counter-1; counter++){
		curr = list->Last;
		list->Last = curr->Prev;

		DeleteYUVImage(curr->YUVImage);
		curr->YUVImage = NULL;
		curr->Next = NULL;
		curr->Prev = NULL;
		curr->List = NULL;

		free(curr);
	}

	list->Last->Next = NULL;

	list->Length = end-start+1;
	curr = NULL;
	next = NULL;
	printf("Operation Crop is done! New number of frames is %u.\n", end-start+1 );
}

/* Fast foward an image list */
void FastImageList(ILIST *list, unsigned int factor){ /* Remove a fixed number of entries in between
							 any two entries */

	/* finish later if needed */
}

/* Reverse an image list */
void ReverseImageList(ILIST *list){ /* Reverse the order of the linked list */
	assert(list);
	IENTRY *curr, *next;

	curr = list->First;
	list->First = list->Last;
	list->Last = curr;

	while(curr != NULL){
		next = curr->Next;
		curr->Next = curr->Prev;
		curr->Prev = next;
		curr = next;
	}
	curr = NULL;
	next = NULL;
	printf("Operation Reverse is done!\n");
}


/* EOF */

/* Phillip Lai */

#include <string.h>
#include <assert.h>

#include "DIPs.h"

/* Edge */
IMAGE *Edge(IMAGE *image)
{
	assert(image);
	int x, y, m, n, a, b;
	int tmpR = 0;
	int tmpG = 0;
	int tmpB = 0;

	IMAGE *temp_image = CreateImage(image->Width,image->Height);

	for (y = 0; y < image->Height; y++) {
		for (x = 0; x < image->Width; x++) {
			SetPixelR(temp_image,x,y, GetPixelR(image,x,y));
			SetPixelG(temp_image,x,y, GetPixelG(image,x,y));
			SetPixelB(temp_image,x,y, GetPixelB(image,x,y));
		}
	}

	for (y = 0; y < temp_image->Height; y++) {
		for (x = 0; x < temp_image->Width; x++) {
			for (n = -1; n <= 1; n++) {
				for (m = -1; m <= 1; m++) {
					a = x + m;
					b = y + n;
					if (a > temp_image->Width - 1)
						a = temp_image->Width - 1;
					if (a < 0)
						a = 0;
					if (b > temp_image->Height - 1)
						b = temp_image->Height - 1;
					if (b < 0)
						b = 0;
 
                                        if ((n==0)&&(m==0)) {
						tmpR += 8*GetPixelR(temp_image,a,b) ;
						tmpG += 8*GetPixelG(temp_image,a,b) ;
						tmpB += 8*GetPixelB(temp_image,a,b) ;
					} else {
						tmpR -= GetPixelR(temp_image,a,b) ;
						tmpG -=	GetPixelG(temp_image,a,b) ;
						tmpB -= GetPixelB(temp_image,a,b) ;
					}
				}
			}
			SetPixelR(image,x,y, (tmpR>255)? 255: (tmpR<0)? 0: tmpR) ;
			SetPixelG(image,x,y, (tmpG>255)? 255: (tmpG<0)? 0: tmpG) ;
			SetPixelB(image,x,y, (tmpB>255)? 255: (tmpB<0)? 0: tmpB) ;
			tmpR = tmpG = tmpB = 0;
		}
	}
	DeleteImage(temp_image);
	return image;
}

/* HFlip */
IMAGE *HFlip(IMAGE *image)
{
	assert(image);
	int             x, y;
	unsigned char   r, g, b;

	for (y = 0; y < image->Height; y ++) {
		for (x = 0; x < image->Width / 2; x ++) {
			r = GetPixelR(image, image->Width-1-x,y);
			g = GetPixelG(image, image->Width-1-x,y);
			b = GetPixelB(image, image->Width-1-x,y); 

			SetPixelR(image,image->Width - 1 - x, y, GetPixelR(image,x,y));
			SetPixelG(image,image->Width - 1 - x, y, GetPixelG(image,x,y));
			SetPixelB(image,image->Width - 1 - x, y, GetPixelB(image,x,y));

			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	return image;
}


/* EOF */

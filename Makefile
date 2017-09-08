# Phillip Lai

# Makefile: MovieLab
#

FILE =  DIPs.o Movie.o MovieLab Image.o Ascii.o ImageList.o out.yuv testdoc.txt MovieLab.o

all: MovieLab

clean:
	rm -rf $(FILE) 

OBJS = MovieLab.o Ascii.o Image.o DIPs.o ImageList.o Movie.o
DEPS = Ascii.h Image.h DIPs.h ImageList.h Movie.h

MovieLab: $(OBJS)
	gcc -Wall $(OBJS) -o MovieLab

##### object files ####
MovieLab.o: MovieLab.c $(DEPS)
	gcc -c MovieLab.c -o MovieLab.o -ansi -Wall

Movie.o: Movie.c Movie.h
	gcc -c Movie.c -o Movie.o -ansi -Wall

Ascii.o: Ascii.c Ascii.h
	gcc -c Ascii.c -o Ascii.o -ansi -Wall

Image.o: Image.c Image.h
	gcc -c Image.c -o Image.o -ansi -Wall

DIPs.o: DIPs.c DIPs.h
	gcc -c DIPs.c -o DIPs.o -ansi -Wall

ImageList.o: ImageList.c ImageList.h Image.h
	gcc -c ImageList.c -o ImageList.o -ansi -Wall


# EOF

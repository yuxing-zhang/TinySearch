CFLAGS = -Wall -pedantic -std=c99 -I ../../include
AR = /usr/bin/ar
OBJ = html.o dict.o hash.o
LIB = ../../lib/libtseutils.a
INC = ../../include/

$(LIB) : $(OBJ)
	mkdir -p ../../lib
	$(AR) cvr $(LIB) $(OBJ)

html.o : $(INC)html.h

dict.o : $(INC)dict.h $(INC)hash.h

hash.o :

clean :
	rm $(OBJ) $(LIB)

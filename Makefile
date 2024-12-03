#*******************************************************************************
#   Project: C++ Library for General Galois Field Arithmetic
#
#   Language: C++ 2007	   
#   Author: Saied H. Khayat
#   Date:   Feb 2013
#   URL: https://github.com/saiedhk
#   
#   Copyright Notice: Free use of this library is permitted under the
#   guidelines and in accordance with the MIT License (MIT).
#   http://opensource.org/licenses/MIT
#
#*******************************************************************************

# GNU Makefile to build the "test_gfelement" executable

CC     = g++
CFLAGS = -pedantic -ansi -Wall -O3 -o
LFLAGS = -pedantic -ansi -Wall -O3 -c
OBJS   = gfelement.o  galoisfield.o  polynomial_arith.o  modular_arith.o

test_gfelement: test_gfelement.cpp $(OBJS)
	$(CC) $(CFLAGS) test_gfelement test_gfelement.cpp $(OBJS)

sample_app_1: sample_app_1.cpp $(OBJS)
	$(CC) $(CFLAGS) sample_app_1 sample_app_1.cpp $(OBJS)

gfelement.o: gfelement.h gfelement.cpp typedefs.h
	$(CC) $(LFLAGS) gfelement.cpp

galoisfield.o: galoisfield.h galoisfield.cpp typedefs.h
	$(CC) $(LFLAGS) galoisfield.cpp

polynomial_arith.o: polynomial_arith.h  polynomial_arith.cpp  modular_arith.h typedefs.h
	$(CC) $(LFLAGS) polynomial_arith.cpp

modular_arith.o: modular_arith.h  modular_arith.cpp  typedefs.h
	$(CC) $(LFLAGS) modular_arith.cpp

clean:
	/bin/rm -f *.o


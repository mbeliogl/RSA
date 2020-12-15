OPTS := -Wall

all: decrypt encrypt keygen numberTheory.hpp numberTheory_TEST ReallyLongInt.o ReallyLongInt_TEST 

tests: numberTheory_TEST ReallyLongInt_TEST

encrypt: encrypt.cpp numberTheory.tpp numberTheory.hpp
	g++ ${OPTS} -o encrypt encrypt.cpp ReallyLongInt.o

decrypt: decrypt.cpp numberTheory.tpp numberTheory.hpp
	g++ ${OPTS} -o decrypt decrypt.cpp ReallyLongInt.o

keygen: keygen.cpp numberTheory.tpp numberTheory.hpp
	g++ ${OPTS} -o keygen keygen.cpp ReallyLongInt.o

numberTheory_TEST: numberTheory_TEST.cpp catch.hpp numberTheory.tpp numberTheory.hpp ReallyLongInt.o
	g++ ${OPTS} -o numberTheory_TEST numberTheory_TEST.cpp ReallyLongInt.cpp

ReallyLongInt.o: ReallyLongInt.cpp ReallyLongInt.hpp
	g++ ${OPTS} -c ReallyLongInt.cpp

ReallyLongInt_TEST: ReallyLongInt_TEST.cpp catch.hpp ReallyLongInt.o
	g++ ${OPTS} -o ReallyLongInt_TEST ReallyLongInt_TEST.cpp ReallyLongInt.o

clean:
	rm *.o

cleanemacs:
	rm*~
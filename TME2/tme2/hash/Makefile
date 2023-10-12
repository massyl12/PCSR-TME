CPP = clang++ -std=c++20

main : hashtab.o main.o generic.o
	$(CPP) -o main hashtab.o main.o generic.o

hashtab.o : hashtab.hpp hashtab.cpp
	$(CPP) -Wall -stdlib=libc++ -c hashtab.cpp

main.o : main.cpp hashtab.hpp generic.hpp
	$(CPP) -Wall -c main.cpp

generic.o : generic.hpp generic.cpp
	$(CPP) -Wall -stdlib=libc++ -c generic.cpp

clean :
	rm -f *.o main




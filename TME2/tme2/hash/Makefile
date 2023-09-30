CPP = clang++ -std=c++20

main : hashtab.o main.o
	$(CPP) -o main hashtab.o main.o

hashtab.o : hashtab.hpp hashtab.cpp
	$(CPP) -Wall -stdlib=libc++ -c hashtab.cpp

main.o : main.cpp hashtab.hpp
	$(CPP) -Wall -c main.cpp

clean :
	rm -f *.o main




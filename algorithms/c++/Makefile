CPPFLAGS=-std=c++11 -g -O3


Sort: main_list.o main_stack.o
	g++ main_list.o -o runlist
	g++ main_stack.o -o runstack

main_list.o: main_list.cpp
	g++ $(CPPFLAGS) -c main_list.cpp

main_stack.o: main_stack.cpp
	g++ $(CPPFLAGS) -c main_stack.cpp

clean:
	rm *.o -f

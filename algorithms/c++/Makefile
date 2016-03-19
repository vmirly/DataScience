CPPFLAGS=-std=c++11 -g -O3


Sort: main_list.o main_stack.o main_queue.o main_deque.o
	g++ main_list.o -o runlist
	g++ main_stack.o -o runstack
	g++ main_queue.o -o runqueue
	g++ main_deque.o -o rundeque

main_list.o: main_list.cpp
	g++ $(CPPFLAGS) -c main_list.cpp

main_stack.o: main_stack.cpp
	g++ $(CPPFLAGS) -c main_stack.cpp

main_queue.o: main_queue.cpp
	g++ $(CPPFLAGS) -c main_queue.cpp

main_deque.o: main_deque.cpp
	g++ $(CPPFLAGS) -c main_deque.cpp

clean:
	rm *.o -f

all:
	g++ -std=c++11 -o main main.cpp linked_list.cpp -lpthread -g -Wall -Wextra

clean:
	rm -f main

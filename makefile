all: hw4

hw4: interpreter.o arithmetic.o bool_expression.o command.o
	g++ -g -Wall main.cpp interpreter.o arithmetic.o bool_expression.o command.o -std=c++11 -o hw4

interpreter.o: interpreter.h interpreter.cpp
	g++ -g -Wall -c interpreter.cpp -std=c++11 -o interpreter.o

command.o: command.h command.cpp
	g++ -g -Wall -c command.cpp -std=c++11 -o command.o

arithmetic.o: arithmetic.h arithmetic.cpp
	g++ -g -Wall -c arithmetic.cpp -std=c++11 -o arithmetic.o

bool_expression.o: bool_expression.h bool_expression.cpp
	g++ -g -Wall -c bool_expression.cpp -std=c++11 -o bool_expression.o


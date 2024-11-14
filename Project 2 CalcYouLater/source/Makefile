###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Jack Burton jburto05


MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


CalcYouLater: RPNCalc.o Datum.o DatumStack.o parser.o main.o
	$(CXX) $(LDFLAGS) -o CalcYouLater RPNCalc.o Datum.o DatumStack.o \
	parser.o main.o

parser.o: parser.h
	$(CXX) $(CXXFLAGS) -c parser.cpp

DatumStack.o: Datum.h Datum.o DatumStack.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

RPNCalc.o: Datum.h DatumStack.h parser.h RPNCalc.h RPNCalc.cpp
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

main.o: Datum.h Datum.o DatumStack.h DatumStack.cpp RPNCalc.h RPNCalc.cpp \
	parser.h parser.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

unit_test: unit_test_driver.o DatumStack.o Datum.o parser.o RPNCalc.o
	$(CXX) $(CXXFLAGS) $^

## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm Datum.o DatumStack.o parser.o main.o RPNCalc.o a.out

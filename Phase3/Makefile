###################################################
#
# file: Makefile
#
# @Authors:   Artemisia Stamataki  Georgia Papaioannou Ioannis Mytakis
# @Version:  18-03-2023
# @email:    csd4742@csd.uoc.gr csd4781@csd.uoc.gr csd4257@csd.uoc.gr
#
# Makefile
#
####################################################

all:
	bison --yacc --defines --output=parser.cpp parser.y
	flex --outfile=al.cpp al.l
	g++ al.cpp parser.cpp SymbolTable.cpp quad.cpp expr.cpp

al:
	flex --outfile=al.cpp al.l
	g++ al.cpp

parser:
	bison --yacc --defines --output=parser.cpp parser.y

clean:
	-rm -f *.out parser.cpp parser.hpp al.cpp parser.output

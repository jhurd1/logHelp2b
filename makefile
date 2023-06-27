###############################################################
# Program:
#     Search function in logHelp for C++
# Author:
#     Jamie Hurd
# Summary:
#    et al
###############################################################

a.out	:	search.o	searchLogic.o	searchDriver.o
	g++	search.o	searchLogic.o	searchDriver.o

search.o:	search.cpp	search.h
	g++ -c	search.cpp

searchLogic.o:	searchLogic.cpp	searchLogic.h
	g++	-c	searchLogic.cpp

searchDriver.o:	searchDriver.cpp
	g++	-c	searchDriver.cpp

#Alex Paquette 25/09/2023
#Makefile for Lab One

CC = g++
FILES = Semaphore.cpp rendezvous.cpp
FLAGS = -Wall -o rendezvous

RENDEZVOUS: $(FILES)
	$(CC) $(FILES) $(FLAGS)

CLEAN:
	rm rendezvous a.out *.o
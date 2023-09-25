CC = g++
FILES = Semaphore.cpp rendezvous.cpp
FLAGS = -Wall -o rendezvous

RENDEZVOUS: $(FILES)
	$(CC) $(FILES) $(FLAGS)

CLEAN:
	rm rendezvous a.out *.o
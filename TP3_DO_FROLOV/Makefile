CC=clang -Wall -g
EXEC=ensembles

all: $(EXEC)


%.o: %.c
	$(CC) -c $<


operations_ens.o: operations_ens.c operations_ens.h

sac.o: sac.c sac.h

ensembles.o: ensembles.c operations_ens.h sac.h


ensembles: ensembles.o operations_ens.o sac.o
	$(CC) $^ -o $@


clean: 
	rm -f *.o

clear:
	rm -f ensembles
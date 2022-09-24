CC=clang
CFLAGS=-g -Wall -Wextra -Werror

EXEC=client-introduction client-interactif client-tutoriel1 client-TUTORIEL2 client-projetX client-crypteMove client-BayOfPigs client-crypteSeq client-Northwoods client-planB client-OneMillion client-LostCause

all: $(EXEC)

client-introduction: client-introduction.o client.o

client-interactif: client-interactif.o client.o

client-tutoriel1: client-tutoriel1.o client.o

client-TUTORIEL2: client-TUTORIEL2.o client.o

client-projetX: client-projetX.o client.o

client-crypteMove: client-crypteMove.o client.o crypteOperations.o

client-BayOfPigs: client-BayOfPigs.o client.o crypteOperations.o

client-crypteSeq: client-crypteSeq.o client.o crypteOperations.o

client-planB: client-planB.o client.o crypteOperations.o

client-Northwoods: client-Northwoods.o client.o crypteOperations.o

client-OneMillion: client-OneMillion.o client.o crypteOperations.o

client-LostCause: client-LostCause.o client.o crypteOperations.o

client.o: client.c client.h

crypteOperations.o: crypteOperations.c crypteOperations.h

clean:
	rm -f *.o

clear:
	rm -f $(EXEC)

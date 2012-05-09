#CHARMDIR = /home/t-pc/Downloads/charm-6.2-multicore-linux64
CHARMDIR = /tmp/charm/charm-6.4.0-net/
CHARMC = $(CHARMDIR)/bin/charmc $(OPTS)


default: all
all: multiply


multiply : main.o multiply.o
	$(CHARMC) -language charm++ -o multiply main.o multiply.o

main.o : main.C main.h main.decl.h main.def.h multiply.decl.h
	$(CHARMC) -o main.o main.C

main.decl.h main.def.h : main.ci
	$(CHARMC) main.ci

multiply.o : multiply.C multiply.h multiply.decl.h multiply.def.h main.decl.h
	$(CHARMC) -o multiply.o multiply.C

multiply.decl.h multiply.def.h : multiply.ci
	$(CHARMC) multiply.ci


clean:
	rm -f main.decl.h main.def.h main.o
	rm -f multiply.decl.h multiply.def.h multiply.o
	rm -f multiply charmrun

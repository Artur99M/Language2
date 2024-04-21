CC = g++
D = -DDEBUG
ALLOBJFILES = obj/*.o
ALLCPPFILES = src/*.cpp

all: $(ALLOBJFILES)

obj/*.o: src/*.cpp
	$(CC) -c src/*.cpp -o obj/*.o

run : $(ALLOBJFILES)
	$(CC) $(ALLOBJFILES) -o Language.out

dot:
	dot graphviz/* -O

deb:
	$(CC) $(D) $(ALLCPPFILES)
	# $(CC) SPU/main.cpp

app :
	./Diff.out

clean :
	rm *.out obj/*.o graphviz/*

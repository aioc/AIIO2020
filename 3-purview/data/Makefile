.PHONY: all clean input output

all: input output

input:
	g++ -std=c++14 gen/main.cpp -Igen -o inputs
	./inputs
	cp handmade/* .

output: input
	./make-output.sh


clean:
	-rm *.in *.out
	-rm inputs

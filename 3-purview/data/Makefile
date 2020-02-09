.PHONY: all clean input output

all: input output check

input:
	g++ -std=c++14 gen/main.cpp -Igen -o inputs
	./inputs
	cp handmade/* .

output: input
	./make-output.sh

check: input
	./run-validator.sh

clean:
	-rm *.in *.out
	-rm inputs

.PHONY: all clean input output

all: input output check zip

input:
	g++ -std=c++14 gen/main.cpp -Igen -o inputs
	./inputs
	cp handmade/* .

output: input
	./make-output.sh

check: input
	./run-validator.sh

zip: input output check
	zip data.zip *.in *.out

clean:
	-rm *.in *.out
	-rm inputs
	-rm data.zip
	make -C ../validator clean

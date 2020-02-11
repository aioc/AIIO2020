.PHONY: all clean input output

all: input output check zip

input:
	./make-input.sh

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

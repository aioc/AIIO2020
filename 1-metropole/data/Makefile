
.PHONY: all clean sub1 sub234 output check

all: sub1 sub234 output check

sub1:
	./make-input-sub1.sh

sub234: sub1
	./make-input-sub234.sh

output: sub1 sub234
	./make-output.sh

check: sub1 sub234
	./run-validator.sh


clean:
	-rm *.in *.out gen-dijkstra/*.in

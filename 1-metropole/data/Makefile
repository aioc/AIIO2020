
.PHONY: all clean sub1 sub234 output

all: sub1 sub234 output

sub1:
	./make-input-sub1.sh

sub234: sub1
	./make-input-sub234.sh

output: sub1 sub234
	./make-output.sh

clean:
	-rm *.in *.out gen-dijkstra/*.in

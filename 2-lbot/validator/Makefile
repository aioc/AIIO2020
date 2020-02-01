
.PHONY: clean all

common := common.h bounds.h testlib.h

all: sub1 sub2 sub3 sub4 sub5

sub1: sub1.cpp $(common)
	g++ $< -o  $@

sub2: sub2.cpp $(common)
	g++ $< -o  $@

sub3: sub3.cpp $(common)
	g++ $< -o  $@

sub4: sub4.cpp $(common)
	g++ $< -o  $@

sub5: sub5.cpp $(common)
	g++ $< -o  $@

clean:
	-rm sub1 sub2 sub3 sub4 sub5

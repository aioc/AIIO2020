#!/bin/bash

# Compile generators
cd gen/

g++ -std=c++11 all-same-value.cpp -o ../all-same-value
g++ -std=c++11 random-alternate-row-sign.cpp -o ../random-alternate-row-sign
g++ -std=c++11 random-checkerboard.cpp -o ../random-checkerboard
g++ -std=c++11 random-values.cpp -o ../random-values
g++ -std=c++11 rotate.cpp -o ../rotate
g++ -std=c++11 truncate.cpp -o ../truncate
g++ -std=c++11 stripes.cpp -o ../stripes

cd ../

# Subtask 1 cases
# All max value
./all-same-value 3 3 1000 > 3x3-max.in
# Random positive
./random-values 3 3 1 1000 > 3x3-posrand.in
./random-values 2 3 -1000 -1 > 2x3-posrand.in
./rotate < 2x3-posrand.in > 3x2-posrand.in
# Random negative
./random-values 3 3 -1000 -1 > 3x3-negrand.in
./random-values 2 3 -1000 -1 > 2x3-negrand.in
./rotate < 2x3-negrand.in > 3x2-negrand.in
# Random
./random-values 3 3 -1000 1000 > 3x3-rand.in

# Subtask 4 cases

# Stripe cases
./stripes 1000 1000 > horz-stripes.in
./stripes 999 999 | ./rotate > vert-stripes.in

# Random positive, maxsize-1
./random-values 999 999 1 1000 > posrand.in
./random-values 999 1000 1 10 > rand-1to10-1.in
./random-values 1000 999 1 10 > rand-1to10-2.in
./all-same-value 1000 1000 1000 > fullmax.in

# Subtask 5 cases
# Max size, random
./random-values 1000 1000 -1000 1000 > maxrand.in
# Max size, random negative
./random-values 1000 1000 -1000 -1 > negrand.in
# Alternating rows pos/neg
./random-alternate-row-sign 1000 1000 > alternatingrows.in
# Checkerboard pos/neg
./random-checkerboard 1000 1000 > checkerboard.in

# Truncate for subtask 1
for i in *.in; do
    ./truncate 1 1000 < $i > "sub2-"$i
done
for i in *.in; do
	if ! [[ $i =~ "sub2" ]]
	then
	   ./truncate 2 1000 < $i > "sub3-"$i
	fi
done

# Do this last to avoid truncation
cp handmade/* .

# Delete compiled generators.
rm all-same-value
rm random-alternate-row-sign
rm random-checkerboard
rm random-values
rm rotate
rm truncate
rm stripes

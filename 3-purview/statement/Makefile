all: statement.pdf

sample1.svg sample2.svg: gen_diagrams.py
	python3 gen_diagrams.py

sample1.pdf: sample1.svg
	inkscape --file=$+ --export-area-drawing --without-gui --export-pdf=$@

sample2.pdf: sample2.svg
	inkscape --file=$+ --export-area-drawing --without-gui --export-pdf=$@

statement.pdf: statement.md sample1.pdf sample2.pdf
	pandoc -o statement.pdf --from markdown+raw_tex --latex-engine-opt=--shell-escape < statement.md
	rm sample1* sample2*

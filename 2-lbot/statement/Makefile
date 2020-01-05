all: statement.pdf

fourbots.svg sample1.svg sample2.svg sample3.svg: gen_diagrams.py
	python3 gen_diagrams.py

fourbots.pdf: fourbots.svg
	inkscape --file=$+ --export-area-drawing --without-gui --export-pdf=$@

sample1.pdf: sample1.svg
	inkscape --file=$+ --export-area-drawing --without-gui --export-pdf=$@

sample2.pdf: sample2.svg
	inkscape --file=$+ --export-area-drawing --without-gui --export-pdf=$@

sample3.pdf: sample3.svg
	inkscape --file=$+ --export-area-drawing --without-gui --export-pdf=$@

statement.pdf: statement.md sample1.pdf sample2.pdf sample3.pdf fourbots.pdf
	pandoc -o statement.pdf --from markdown+raw_tex --latex-engine-opt=--shell-escape < statement.md
	rm fourbots* sample1* sample2* sample3*

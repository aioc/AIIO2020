all: statement.pdf

sample.pdf: sample.svg
	inkscape --file=$+ --export-area-drawing --without-gui --export-pdf=$@

statement.pdf: statement.md sample.pdf
	pandoc -o statement.pdf --from markdown+raw_tex --latex-engine-opt=--shell-escape < statement.md
	rm sample.pdf

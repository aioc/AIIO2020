all: sample1.svg sample2.svg statement.pdf

sample1.svg sample2.svg: gen_diagrams.py
	python3 gen_diagrams.py
	rm sample1 sample2

statement.pdf: statement.md
	pandoc -o statement.pdf --from markdown+raw_tex < statement.md

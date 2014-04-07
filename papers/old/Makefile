NAME = spaghetty_chapter_v1

all: $(NAME).pdf

%.pdf: %.tex
	latex $(NAME)
	bibtex $(NAME)
	latex $(NAME)
	pdflatex $(NAME)

clean:
	-rm -f *.log *.bbl *.blg *.aux *.dvi *.bib

realclean: clean
	-rm -f *.pdf

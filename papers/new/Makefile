NAME=spaghetty

all: dorks

rubber:
	rubber --pdf --force $(NAME);

dorks:
	pdflatex $(NAME)
	bibtex $(NAME)
	bibtex $(NAME)
	pdflatex $(NAME)
	bibtex $(NAME)

clean:
	rubber --clean $(NAME)
	rm -f $(NAME).pdf

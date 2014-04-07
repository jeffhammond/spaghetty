NAME = spaghetty

TARGETS: $(NAME).pdf
.PHONY: all clean tags wordcount

tex_files = $(shell find . -name '*.tex' -print)
bib_files = $(shell find . -name '*.bib' -print)
eps_files = $(shell find . -name '*.eps' -print)
epsi_files = $(shell find . -name '*.epsi' -print)
ps_files = $(shell find pics -name '*.ps' -print)

tags: $(tex_files) $(bib_files)
	find . \( -name '*.tex' -print \) -or \( -name '*.bib' -print \) | \
		xargs etags

$(NAME).pdf: $(NAME).tex $(tex_files) $(bib_files)
	@if test "`which rubber `" != "" ; then \
		rubber -d $(NAME) ; \
	else \
		pdflatex $(NAME) | tee latex.out ; \
		if grep -q '^LaTeX Warning: Citation.*undefined' latex.out; then \
			bibtex $(NAME); \
			touch .rebuild; \
		fi ; \
		while [ -f .rebuild -o \
			-n "`grep '^LaTeX Warning:.*Rerun' latex.out`" ]; do \
			rm -f .rebuild; \
			pdflatex $(NAME) | tee latex.out; \
		done ; \
		rm latex.out ; \
	fi

wordcount: $(NAME).pdf
	pdftotext $(NAME).pdf - | wc -w 2> /dev/null || true

clean:
	find . \( -name '*.blg' -print \) -or \( -name '*.aux' -print \) -or \
		\( -name '*.bbl' -print \) -or \( -name '*~' -print \) -or \
		\( -name '*.lof' -print \) -or \( -name '*.lot' -print \) -or \
		\( -name '*.toc' -print \) | xargs rm -f; \
	rm -f $(NAME).dvi $(NAME).log $(NAME).ps $(NAME).pdf $(NAME).out _region_* TAGS

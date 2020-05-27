TEXNBASE= 01_intro 02_signals 03_systems 04_fourierseries
TEXNBASE+= 05_fouriertransform 06_filters 07_laplace
TEXNSBASE= XX_vectorspace XX_fs_rclpf XX_fs_add
TEX= XX_systf
INSTDIR= /home/nicolls/.public_html/lectures/eee2047s/notes

PDFSLIDES= $(patsubst %, %_slides.pdf, $(TEXNSBASE))
PDFNOTES= $(patsubst %, %_notes.pdf, $(TEXNSBASE))
PDFNOTES+= $(patsubst %, %_notes.pdf, $(TEXNBASE))
PDF= $(patsubst %, %.pdf, $(TEX)) 
PDF+= $(PDFSLIDES) $(PDFNOTES)
DVI= $(patsubst %.pdf, %.dvi, $(PDF))
PS= $(patsubst %.pdf, %.ps, $(PDF))
PDFINST= $(patsubst %, $(INSTDIR)/%, $(PDF))
PDF2UP= $(patsubst %.pdf, %_2up.pdf, $(PDF))
PDF2UPINST= $(patsubst %, $(INSTDIR)/%, $(PDF2UP))
DISTFILE= fcn_eee2047snotes.tar.gz
DISTINST= $(INSTDIR)/$(DISTFILE)

# Don't delete intermediate files
.SECONDARY:  $(DVI) $(PS) $(PDF)

all:  $(PDFNOTES) $(PDFSLIDES) $(DISTFILE)

# Implicit rules
%.dvi:  %.tex
	latex $<

%.ps:  %.dvi
	dvips -o $@ $<

%_2up.ps:  %.ps
	psnup -pa4 -2 $< $@

%.pdf:  %.ps
	ps2pdf -sPAPERSIZE=a4 $< $@

%_slides.dvi: %.tex
	latex "\def\UseOption{slides}\input{$<}"; mv $*.dvi $@

%_notes.dvi: %.tex
	latex "\def\UseOption{notslides}\input{$<}"; mv $*.dvi $@

# Install rule
$(INSTDIR)/%.pdf:  %.pdf
	/bin/cp -f $< $@; chmod 644 $@

$(INSTDIR)/$(DISTFILE):  $(DISTFILE)
	/bin/cp -f $< $@; chmod 644 $@

pdf:  $(PDF)

dvi:  $(DVI)

ps:  $(PS)

install:  $(PDFINST) $(PDF2UPINST) $(DISTINST)

$(DISTFILE):  
	tar czf $(DISTFILE) Makefile README.txt \
	*.tex *.jpg *.eps *.fig *.m

clean:
	/bin/rm -f $(DVI) $(PS) $(PDF) $(PDF) $(DISTFILE)


# Dependencies (notes)
#mdsp.dvi:  mdsp.tex mdsp_content.tex
#hvs.dvi:  hvs.tex hvs_content.tex
#imform.dvi:  imform.tex imform_content.tex
#improc.dvi:  improc.tex improc_content.tex

# Dependencies and build (slides)
#hvs_slides.pdf:  hvs_slides.tex hvs_content.tex
#	pdflatex hvs_slides.tex

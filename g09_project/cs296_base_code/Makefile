.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base
INPUTLATEX= Final_Report.tex
INPUTAUX = Final_Report.aux
TARGETDVI = Final_Report.dvi
TARGETPS = Final_Report.ps
TARGETLATEX = Final_Report.pdf

# Project Paths
INSTALL_PATH=$(HOME)/Desktop
PROJECT_ROOT=$(HOME)/Desktop/sem_4/cs296/project/cs296project/g09_project/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -Wall -pg
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib -pg

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


.PHONY: all setup doc clean dist install report plot compbox

all: setup $(BINDIR)/$(TARGET) 
setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin
	@mkdir -p plots
	@mkdir -p profile
	@mkdir -p data
	@ cd $(EXTERNAL_ROOT)/src;tar -xf Box2D.tgz;mkdir -p ./Box2D/build296
	

$(BINDIR)/$(TARGET): setup $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"
	
plot: $(BINDIR)/$(TARGET)
	@cp ./src/extra_main/main1.cpp ./src/main.cpp
	@make -s $(BINDIR)/$(TARGET)
	@chmod 755 ./scripts/*.sh
	@./scripts/gen_data_csv.sh
	@./scripts/gen_data_csv2.sh
	@gnuplot> load './scripts/g09_plot01.p'
	@gnuplot> load './scripts/g09_plot02.p'
	@gnuplot> load './scripts/g09_plot03.p'
	@gnuplot> load './scripts/g09_plot04.p'
	@gnuplot> load './scripts/g09_plot05.p'
	@gnuplot> load './scripts/g09_plot06.p'
	@rm -rf load
	@cp ./src/extra_main/main2.cpp ./src/main.cpp


dist:
	@make -s clean
	@cd ../;tar -czf cs296_g09_project.tar.gz cs296_base_code	


install:
	@if test -d $(EXTERNAL_ROOT)/src/Box2D ;\
	then $(ECHO) "Box2D already compiled";\
	else make -s compbox;\
	fi;
	@make -s setup
	@make -s $(BINDIR)/$(TARGET)
	@make -s doc
	@make -s report
	@cd $(INSTALL_PATH);mkdir -p cs296_base_code;cd cs296_base_code;mkdir -p bin;mkdir -p doc
	@cp -R $(BINDIR)/* $(INSTALL_PATH)/cs296_base_code/bin
	@cp -R $(DOCDIR)/*.pdf $(INSTALL_PATH)/cs296_base_code/doc/
	@cp -R $(DOCDIR)/html $(INSTALL_PATH)/cs296_base_code/doc/
	


clean:
	@$(RM) -rf $(DOCDIR)/*.dvi *.ps *.aux *.bbl *.blg *.log *.pdf
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(BINDIR) $(LIBDIR) $(DOCDIR)/html $(TARGETLATEX) $(DOCDIR)/*.pdf
	@$(RM) -rf bin
	@rm -rf ./gmon.out
	@$(RM) -rf plots
	@$(RM) -rf profile
	@$(RM) -rf obj
	@$(RM) -rf data
	

compbox:
	@cd $(EXTERNAL_ROOT)/src;tar xf $(EXTERNAL_ROOT)/src/Box2D.tgz
	@cd $(EXTERNAL_ROOT)/src/Box2D;mkdir -p build296
	@cd $(EXTERNAL_ROOT)/src/Box2D/build296;cmake ../;make;make install

	
report: $(DOCDIR)/$(INPUTLATEX)
	@latex $(DOCDIR)/$(INPUTLATEX)
	@bibtex $(INPUTAUX)
	@latex $(DOCDIR)/$(INPUTLATEX)
	@latex $(DOCDIR)/$(INPUTLATEX)
	@dvips $(TARGETDVI)
	@ps2pdf $(TARGETPS) $(DOCDIR)/$(TARGETLATEX)
	@rm -rf *.dvi *.ps *.aux *.bbl *.blg *.log	

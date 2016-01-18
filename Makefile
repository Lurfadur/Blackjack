#
#Makefile for CS362 BlackJack
#
#see
#http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables
#for reference information

CXX = g++
CXXFLAGS = --std=c++11 -finput-charset=utf-8 -Wall

SRCEXT := cpp
SRCDIR := src
OBJDIR := bin
BLDDIR := $(OBJDIR)

SRCS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
BIN := cardTest

all: directories $(BIN)

directories: 
	@echo "------------Building directories------------"
	@mkdir -pv $(OBJDIR)
	@echo ""

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "------------Compiling: " $@ "------------"
	$(CXX) -o $@ -c $< $(CXXFLAGS)
	@echo ""

$(BIN): $(OBJS)
	@echo "------------Linking" $@ "------------"
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: all directories clean

clean:
	@echo "------------Cleaning------------"
	@rm -fv $(OBJDIR)/*.o
	@rm -fv $(BIN)
	@rmdir -v $(BLDDIR)

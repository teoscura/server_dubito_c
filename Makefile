# Source directories separated by space
# Example ./ src1/ src2/
SRCDIR   =  src/ src/network/ src/packets/ src/api/network/ src/api/packets/
OBJDIR   = target/objects/
# Include directories separated by space
INCDIR   = 
BINDIR   = target/
TARGET   = main
# Compiler
CXX      = g++
# Retrieve list of the source files
SRC      = $(wildcard $(addsuffix *.cpp,$(SRCDIR)))
# Generate list of the object files
OBJ      = $(addprefix $(OBJDIR), $(patsubst %.cpp, %.o, $(notdir $(SRC))))
VPATH    = $(SRCDIR)
# Compilation flags
CXXFLAGS = -std=c++23 -fsanitize=address -g
$(TARGET) : $(OBJ)
	@echo Linking...
	@mkdir -p $(BINDIR)
	@$(CXX) $(CXXFLAGS) -o $(BINDIR)$@ $(OBJ)
	
$(OBJDIR)%.o : %.cpp
	@echo Compiling $< in $@...
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCDIR)) -c -o $@ $<

clean:
	rm ./target/objects/ -rf
	rm ./logs/ -rf
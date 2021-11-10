CXXFLAGS = $(shell pkg-config --cflags sdl2 SDL2_ttf) -Wall -Wextra -pedantic -Wno-unused-parameter -fsanitize=address
LXXFLAGS = $(shell pkg-config --libs   sdl2 SDL2_ttf) -fsanitize=address

SrcDir = src
BinDir = bin

GraphicsDir           = $(SrcDir)/graphics
MathDir               = $(SrcDir)/math
ContainersDir         = $(SrcDir)/containers
EventDir              = $(SrcDir)/event
AppDir                = $(SrcDir)/app
GUISystemDir          = $(SrcDir)/gui_system
PaintGUISystemDir     = $(SrcDir)/paint_gui_system
PaintGUIComponentsDir = $(SrcDir)/paint_gui_components

CppSrc  = $(notdir $(wildcard $(SrcDir)/*.cpp))                \
          $(notdir $(wildcard $(GraphicsDir)/*.cpp))           \
          $(notdir $(wildcard $(MathDir)/*.cpp))               \
          $(notdir $(wildcard $(ContainersDir)/*.cpp))         \
          $(notdir $(wildcard $(EventDir)/*.cpp))              \
          $(notdir $(wildcard $(GUISystemDir)/*.cpp))          \
          $(notdir $(wildcard $(PaintGUISystemDir)/*.cpp))     \
          $(notdir $(wildcard $(PaintGUIComponentsDir)/*.cpp)) \
          $(notdir $(wildcard $(AppDir)/*.cpp))

Headers = $(wildcard $(SrcDir)/*.hpp)                \
          $(wildcard $(GraphicsDir)/*.hpp)           \
          $(wildcard $(MathDir)/*.hpp)               \
          $(wildcard $(ContainersDir)/*.hpp)         \
          $(wildcard $(EventDir)/*.hpp)              \
          $(wildcard $(GUISystemDir)/*.hpp)          \
          $(wildcard $(PaintGUISystemDir)/*.hpp)     \
          $(wildcard $(PaintGUIComponentsDir)/*.hpp) \
          $(wildcard $(AppDir)/*.hpp)

Intermediates = $(addprefix $(BinDir)/, $(CppSrc:.cpp=.o))

paint: $(Intermediates)
	g++ -o paint $(Intermediates) $(LXXFLAGS)

vpath %.cpp $(SrcDir) $(GraphicsDir) $(MathDir) $(ContainersDir) $(EventDir) $(AppDir) $(GUISystemDir) $(PaintGUIComponentsDir) $(PaintGUISystemDir)
$(BinDir)/%.o: %.cpp $(Headers) makefile
	g++ -c $< $(CXXFLAGS) -o $@

.PHONY: init
init:
	mkdir -p $(BinDir)

.PHONY: clean
clean:
	rm -f $(BinDir)/*.o

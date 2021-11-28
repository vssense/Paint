SANITIZE_FLAGS = -fsanitize=address # -fsanitize=leak -fsanitize=undefined

CXXFLAGS = $(shell pkg-config --cflags sdl2 SDL2_ttf) -Wall -Wextra -pedantic -Wno-unused-parameter $(SANITIZE_FLAGS)
LXXFLAGS = $(shell pkg-config --libs   sdl2 SDL2_ttf) $(SANITIZE_FLAGS) -ldl


SrcDir = src
BinDir = bin

GraphicsDir           = $(SrcDir)/graphics
MathDir               = $(SrcDir)/math
ContainersDir         = $(SrcDir)/containers
EventDir              = $(SrcDir)/event
AppDir                = $(SrcDir)/app
ApiDir                = $(SrcDir)/api
InstrumentsDir        = $(SrcDir)/instrument_manager
GUISystemDir          = $(SrcDir)/gui_system
PaintGUISystemDir     = $(SrcDir)/paint_gui_system
PaintGUIComponentsDir = $(SrcDir)/paint_gui_components

CppSrc  = $(notdir $(wildcard $(SrcDir)/*.cpp))                \
          $(notdir $(wildcard $(GraphicsDir)/*.cpp))           \
          $(notdir $(wildcard $(MathDir)/*.cpp))               \
          $(notdir $(wildcard $(ContainersDir)/*.cpp))         \
          $(notdir $(wildcard $(EventDir)/*.cpp))              \
          $(notdir $(wildcard $(InstrumentsDir)/*.cpp))        \
          $(notdir $(wildcard $(GUISystemDir)/*.cpp))          \
          $(notdir $(wildcard $(PaintGUISystemDir)/*.cpp))     \
          $(notdir $(wildcard $(PaintGUIComponentsDir)/*.cpp)) \
          $(notdir $(wildcard $(AppDir)/*.cpp))                \
          $(notdir $(wildcard $(ApiDir)/*.cpp))

Headers = $(wildcard $(SrcDir)/*.hpp)                \
          $(wildcard $(GraphicsDir)/*.hpp)           \
          $(wildcard $(MathDir)/*.hpp)               \
          $(wildcard $(ContainersDir)/*.hpp)         \
          $(wildcard $(EventDir)/*.hpp)              \
          $(wildcard $(InstrumentsDir)/*.hpp)        \
          $(wildcard $(GUISystemDir)/*.hpp)          \
          $(wildcard $(PaintGUISystemDir)/*.hpp)     \
          $(wildcard $(PaintGUIComponentsDir)/*.hpp) \
          $(wildcard $(AppDir)/*.hpp)                \
          $(wildcard $(ApiDir)/*.hpp)

Intermediates = $(addprefix $(BinDir)/, $(CppSrc:.cpp=.o))

paint: $(Intermediates)
	g++ -o paint $(Intermediates) $(LXXFLAGS)

vpath %.cpp $(SrcDir) $(ApiDir) $(GraphicsDir) $(InstrumentsDir) $(MathDir) $(ContainersDir) $(EventDir) $(AppDir) $(GUISystemDir) $(PaintGUIComponentsDir) $(PaintGUISystemDir)
$(BinDir)/%.o: %.cpp $(Headers) makefile
	g++ -c $< $(CXXFLAGS) -o $@

.PHONY: init
init:
	mkdir -p $(BinDir)

.PHONY: clean
clean:
	rm -f $(BinDir)/*.o

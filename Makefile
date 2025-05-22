CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
TARGET = compiler
LDFLAGS =

OBJ_DIR = output

RAW_SRCS = $(shell find . -name '*.cpp' -type f)
SRCS = $(subst ./,,$(RAW_SRCS))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build finished: $(TARGET)"

$(OBJ_DIR)/%.o: %.cpp
	@echo "Compiling $< to $@"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Clean finished."

rebuild: clean all

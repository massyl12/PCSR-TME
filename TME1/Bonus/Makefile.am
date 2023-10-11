CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC_DIR = src
BUILD_DIR = build

# Liste de vos fichiers source
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Générer les noms des fichiers objets correspondants
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Nom de l'exécutable
TARGET = myprogram

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

all: $(TARGET)


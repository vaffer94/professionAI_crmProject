# Compilatore (su macOS g++ punta a clang++)
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -I.
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -I. -Ithird_party

# Nome dell'eseguibile e cartelle di output
TARGET := build/insurapro
OBJDIR := build/obj

# Sorgenti: main.cpp nella radice + tutti i .cpp nelle sottocartelle
SRC := main.cpp $(shell find . -mindepth 2 -name '*.cpp')
# Normalizza il prefisso ./ per il patsubst
SRC := $(patsubst ./%,%,$(SRC))

# Oggetti nella cartella build/obj con stessa struttura delle sorgenti
OBJ := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

.PHONY: all clean run

all: $(TARGET)

# Link finale
$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regola generica per compilare i .cpp -> .o con deps automatiche
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dei file di dipendenze generati (-MMD -MP)
-include $(DEP)

# Esegui l'app
run: $(TARGET)
	./$(TARGET)

# Pulizia
clean:
	rm -rf build

# Compilador
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I./include

# Nombre del ejecutable (en la raíz)
TARGET = sistema_pedidos

# Directorios
SRCDIR = src
OBJDIR = obj

# Archivos fuente y objetos
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Crear directorios si no existen
$(shell mkdir -p $(OBJDIR) data)

# Regla principal
all: $(TARGET)

# Enlazado final (ejecutable en la raíz)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Compilacion exitosa: ./$(TARGET)"

# Compilacion de objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Limpiar archivos generados
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Archivos de compilacion eliminados"

# Limpiar todo incluyendo datos
clean-all:
	rm -rf $(OBJDIR) $(TARGET) data/*.txt
	@echo "Archivos de compilacion y datos eliminados"

# Ejecutar el programa
run: all
	./$(TARGET)

# Recompilar todo
rebuild: clean all

.PHONY: all clean clean-all run rebuild

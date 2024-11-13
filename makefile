# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Archivos fuente
SRCS = main.cpp Persona.cpp Producto.cpp Usuario.cpp ArbolBPlus.cpp AnalizadorSQL.cpp

# Archivos de encabezado
HEADERS = Persona.h Producto.h Usuario.h ArbolBPlus.h AnalizadorSQL.h

# Nombre del ejecutable
TARGET = sql_cli

# Regla principal: compila el proyecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar archivos de compilación
clean:
	rm -f $(TARGET) *.o

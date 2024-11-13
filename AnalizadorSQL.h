#ifndef ANALIZADOR_SQL_H
#define ANALIZADOR_SQL_H

#include "ArbolBPlus.h"  // Biblioteca del árbol B+, para operaciones SQL simuladas
#include <string>        // Para manejo de cadenas de texto (std::string)
#include <vector>        // Para manejo de listas de elementos (std::vector)
#include <map>           // Para pares clave-valor en las asignaciones (std::map)
#include <sstream>       // Para manipulación de flujo de texto (std::istringstream)
#include <algorithm>     // Para operaciones de transformación (std::transform)
#include <set>           // Para manejo de conjuntos (std::set)

// Definición de columnas por defecto para las tablas
#define dColumns std::vector<std::string>({"dID", "nombre", "apellido", "edad"})
#define uColumns std::vector<std::string>({"uID", "usuario", "password", "email"})
#define pColumns std::vector<std::string>({"pID", "nombre", "comprados", "vendidos", "precio"})

// Clase AnalizadorSQL analiza comandos SQL y utiliza ArbolBPlus para ejecutar cada comando
class AnalizadorSQL {
public:
    // Constructor de AnalizadorSQL que recibe una referencia al árbol B+
    AnalizadorSQL(std::vector<ArbolBPlus*> tables);

    // Función principal para analizar y procesar el comando SQL recibido
    void analizar(const std::string& comando);

private:
    std::vector<ArbolBPlus*> tablas;  // Referencia al árbol B+ para ejecutar comandos SQL
    ArbolBPlus *arbol;                // Puntero a un árbol B+ específico para operar en la tabla actual
    std::string tablaActual;          // Nombre de la tabla en la que se está trabajando actualmente

    // Funciones privadas que analizan comandos SQL específicos y los descomponen en parámetros
    void analizarInsertar(std::istringstream& flujo);   // Analiza un comando de inserción
    void analizarSeleccionar(std::istringstream& flujo); // Analiza un comando de selección
    void analizarActualizar(std::istringstream& flujo); // Analiza un comando de actualización
    void analizarEliminar(std::istringstream& flujo);   // Analiza un comando de eliminación

    // Funciones auxiliares para procesar listas de columnas/valores y asignaciones
    std::vector<std::string> procesarLista(const std::string& parte); // Procesa una lista de columnas o valores
    std::map<std::string, std::string> procesarAsignaciones(const std::string& parte); // Procesa asignaciones en formato clave-valor
    std::string limpiar(const std::string& cadena);  // Función para limpiar espacios en blanco de una cadena

    bool erroresInsertar(std::vector<std::string> &columnas, std::vector<std::string> &valores); // Verifica errores en el comando de inserción
    bool erroresSeleccionar(std::vector<std::string> columnas); // Verifica errores en el comando de selección
};

#endif

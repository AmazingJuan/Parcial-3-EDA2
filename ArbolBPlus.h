#ifndef ARBOL_BPLUS_H
#define ARBOL_BPLUS_H

#include <string>    // Biblioteca para manejar cadenas de texto (std::string)
#include <vector>    // Biblioteca para manejar listas de elementos (std::vector)
#include <map>       // Biblioteca para manejar pares clave-valor (std::map)
#include <iostream>  // Biblioteca para operaciones de entrada y salida (std::cout)
#include <algorithm>
#include "Persona.h"
#include "Producto.h"
#include "Usuario.h"


#define dColumns std::vector<std::string>({"dID", "nombre", "apellido", "edad"})
#define uColumns std::vector<std::string>({"uID", "usuario", "password", "email"})
#define pColumns std::vector<std::string>({"pID", "nombre", "comprados", "vendidos", "precio"})

class NodoBP {
public:
    bool esHoja; // Indica si el nodo es una hoja
    NodoBP* siguiente;
    std::vector<std::string> llaves; // Contiene las llaves (valores) en el nodo
    std::vector<NodoBP*> hijos; // Contiene los punteros a los hijos
    NodoBP(bool esNodoHoja) : esHoja(esNodoHoja), siguiente(nullptr) {}
};

// Clase ArbolBPlus simula un árbol B+ con métodos básicos para las operaciones de SQL.
class ArbolBPlus {
private:
    std::string tabla;
    std::string primary_key;
    std::map<std::string, Persona*> personas;
    std::map<std::string, Producto*> productos;
    std::map<std::string, Usuario*> usuarios;
    NodoBP *raiz;
    int max_keys;
public:
    ArbolBPlus();
    ArbolBPlus(int clavePorNodo, std::string clave);
    // Método para simular la inserción en el árbol B+
    // Recibe el nombre de la tabla, una lista de columnas y una lista de valores
    void insertar(const std::vector<std::string>& columnas, const std::vector<std::string>& valores);

    // Método para simular la selección de datos en el árbol B+
    // Recibe el nombre de la tabla y una lista de columnas
    void seleccionar(const std::vector<std::string>& columnas);

    // Método para simular la actualización de datos en el árbol B+
    // Recibe el nombre de la tabla, un mapa de asignaciones (columna=valor), y una condición
    void actualizar(const std::map<std::string, std::string>& asignaciones, const std::string& condicion);

    // Método para simular la eliminación de datos en el árbol B+
    // Recibe el nombre de la tabla y una condición para eliminar filas que la cumplan
    void eliminar(const std::string& condicion);

    // Inserta una clave en un nodo que no está lleno
    void insertarEnNoLleno(NodoBP* nodo, std::string llave);

    // Divide un nodo hijo para mantener el equilibrio del árbol
    void dividirHijo(NodoBP *padre, int index, NodoBP *hijo);

    // Asigna datos a una entidad específica en función de las columnas y valores dados
    void asignarDatos(const std::vector<std::string> &columnas, const std::vector<std::string> &valores, std::string llave);

    // Imprime todos los registros en el árbol B+ en un nivel específico, según las columnas proporcionadas
    void imprimirRegistros(NodoBP* nodo, int nivel, std::vector<std::string> columnas, int &contador);

    // Da formato a los datos de una persona, producto o usuario, según las columnas especificadas
    std::string formatearDatos(Persona *persona, Producto *producto, Usuario *usuario, std::vector<std::string> &columnas);

    // Elimina una clave del árbol B+
    void remover(std::string llave);

    // Elimina una clave específica en un nodo dado
    void remover(NodoBP* nodo, std::string llave);

    // Coge y mueve el valor del siguiente nodo hermano al nodo actual
    void cogerSiguiente(NodoBP* nodo, int index);

    // Coge y mueve el valor del nodo hermano anterior al nodo actual
    void cogerAnterior(NodoBP* nodo, int index);

    // Devuelve una lista de claves que cumplen con una condición dada
    void devolverKeys(NodoBP *nodo, std::vector<std::string> condicion, std::vector<std::string> *keys, int nivel);

    // Une el nodo actual con su nodo hermano
    void unir(NodoBP* nodo, int index);

    // Procesa una condición para hacer consultas en el árbol
    std::vector<std::string> procesar_condicion(std::string condicion);

    // Actualiza datos en las entidades seleccionadas, según las claves, campo y valor especificados
    void actualizarDatos(std::vector<std::string> &keys, std::string campo, std::string valor);
};

#endif

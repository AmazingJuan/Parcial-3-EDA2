#include <iostream>        // Para entrada y salida estándar
#include <string>          // Para manejo de cadenas de texto
#include <vector>
#include "ArbolBPlus.h"    // Encabezado del árbol B+, para operaciones SQL simuladas
#include "AnalizadorSQL.h" // Encabezado del analizador SQL, que interpreta comandos SQL

#define max_keys 3

void add_tables(std::vector<ArbolBPlus*> &tables){
    tables.push_back(new ArbolBPlus(max_keys, "dID"));
    tables.push_back(new ArbolBPlus(max_keys, "pID"));
    tables.push_back(new ArbolBPlus(max_keys, "uID"));
}

int main() {
    std::vector<ArbolBPlus*> tablas;               // Instancia de ArbolBPlus para manejar operaciones de SQL
    add_tables(tablas);
    AnalizadorSQL analizador(tablas);  // Instancia de AnalizadorSQL que interpreta comandos

    std::string comando;
    while (true) {
        std::cout << "SQL> ";                // Indica al usuario que ingrese un comando
        std::getline(std::cin, comando);     // Lee el comando completo ingresado

        if (comando == "exit") break;        // Si el comando es "exit", finaliza el programa
        analizador.analizar(comando);        // Analiza y ejecuta el comando ingresado
        std::cout << std::endl;
    }
    return 0;
}
/*
INSERT INTO personas (dID,nombre,apellido,edad) VALUES (101,Carlos,González,32)
INSERT INTO usuarios (uID,usuario,password,email) VALUES (201,maria92,pass1234,maria@gmail.com)
INSERT INTO personas (dID,nombre,apellido,edad) VALUES (102,Alicia,Herrera,45)
INSERT INTO personas (dID,nombre,apellido,edad) VALUES (103,Roberto,Vargas,27)
INSERT INTO personas (dID,nombre,apellido,edad) VALUES (104,Diana,López,58)
INSERT INTO personas (dID,edad,apellido,nombre) VALUES (105,19,Ruiz,Santiago)
SELECT (dID,nombre) FROM personas
INSERT INTO usuarios (uID,usuario,password,email) VALUES (202,luis34,secret789,luis@hotmail.com)
INSERT INTO usuarios (uID,usuario,password,email) VALUES (203,ana_c,qwerty567,ana@outlook.com)
INSERT INTO usuarios (uID,usuario,password,email) VALUES (204,pedro99,abcdef123,pedro@yahoo.com)
INSERT INTO usuarios (uID,usuario,password,email) VALUES (205,sofia_m,zxcvbn321,sofia@live.com)
INSERT INTO usuarios (uID,usuario,password,email) VALUES (206,marcos87,pass9876,marcos@icloud.com)
SELECT (usuario,uID,email) FROM personas
UPDATE personas SET dID=1095 WHERE dID=101
DELETE FROM personas WHERE dID=102
SELECT (dID,nombre) FROM personas
*/

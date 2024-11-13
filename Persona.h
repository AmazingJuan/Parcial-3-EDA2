#ifndef PERSONA_H
#define PERSONA_H
#include <string>
class Persona{
public:
    const std::string &getdID() const;
    const std::string &getNombre() const;
    const std::string &getEdad() const;
    const std::string &getApellido() const;
    void setdID(const std::string &dato);
    void setNombre(const std::string &dato);
    void setEdad(const std::string &dato);
    void setApellido(const std::string &dato);

private:
    std::string dID, nombre, edad, apellido;
};
#endif

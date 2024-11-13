#include "Persona.h"

const std::string &Persona::getdID() const
{
    return dID;
}

const std::string &Persona::getNombre() const
{
    return nombre;
}

const std::string &Persona::getApellido() const
{
    return apellido;
}

void Persona::setdID(const std::string &dato)
{
    dID = dato;
}

void Persona::setNombre(const std::string &dato)
{
    nombre = dato;
}

void Persona::setEdad(const std::string &dato)
{
    edad = dato;
}

void Persona::setApellido(const std::string &dato)
{
    apellido = dato;
}

const std::string &Persona::getEdad() const
{
    return edad;
}

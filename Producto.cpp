#include "Producto.h"

const std::string &Producto::getpID() const
{
    return pID;
}

const std::string &Producto::getNombre() const
{
    return nombre;
}

const std::string &Producto::getComprados() const
{
    return comprados;
}

const std::string &Producto::getVendidos() const
{
    return vendidos;
}

const std::string &Producto::getPrecio() const
{
    return precio;
}

void Producto::setpID(const std::string &dato) {
    pID = dato;
}

void Producto::setNombre(const std::string &dato) {
    nombre = dato;
}

void Producto::setComprados(const std::string &dato) {
    comprados = dato;
}

void Producto::setVendidos(const std::string &dato) {
    vendidos = dato;
}

void Producto::setPrecio(const std::string &dato) {
    precio = dato;
}

#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <string>

class Producto{
public:
    const std::string &getpID() const;
    const std::string &getNombre() const;
    const std::string &getComprados() const;
    const std::string &getVendidos() const;
    const std::string &getPrecio() const;

    void setpID(const std::string &dato);
    void setNombre(const std::string &dato);
    void setComprados(const std::string &dato);
    void setVendidos(const std::string &dato);
    void setPrecio(const std::string &dato);

private:
    std::string pID, nombre, comprados, vendidos, precio;
};
#endif

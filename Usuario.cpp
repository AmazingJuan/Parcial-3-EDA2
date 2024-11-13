#include "Usuario.h"

const std::string &Usuario::getuID() const
{
    return uID;
}

const std::string &Usuario::getUsuario() const
{
    return usuario;
}

const std::string &Usuario::getPassword() const
{
    return password;
}

const std::string &Usuario::getEmail() const
{
    return email;
}

void Usuario::setuID(const std::string &dato) {
    uID = dato;
}

void Usuario::setUsuario(const std::string &dato) {
    usuario = dato;
}

void Usuario::setPassword(const std::string &dato) {
    password = dato;
}

void Usuario::setEmail(const std::string &dato) {
    email = dato;
}

#ifndef USUARIO_H
#define USUARIO_H
#include <string>

class Usuario{
public:
    const std::string &getuID() const;
    const std::string &getUsuario() const;
    const std::string &getPassword() const;
    const std::string &getEmail() const;

    void setuID(const std::string &dato);
    void setUsuario(const std::string &dato);
    void setPassword(const std::string &dato);
    void setEmail(const std::string &dato);
private:
    std::string uID, usuario, password, email;
};
#endif

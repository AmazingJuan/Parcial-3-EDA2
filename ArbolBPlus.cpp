#include "ArbolBPlus.h"

// Constructor vacío de la clase ArbolBPlus
ArbolBPlus::ArbolBPlus()
{
}

// Constructor que inicializa el árbol con el número máximo de claves por nodo y la clave primaria
ArbolBPlus::ArbolBPlus(int clavePorNodo, std::string clave) : max_keys(clavePorNodo), primary_key(clave)
{
    // Se define el nombre de la tabla en función de la clave primaria
    if(primary_key == "dID") tabla = "personas";
    else if(primary_key == "uID") tabla = "usuarios";
    else if(primary_key == "pID") tabla = "productos";
}

// Implementación del método insertar
// Este método imprime en la consola el comando de inserción simulado con las columnas y valores dados
void ArbolBPlus::insertar(const std::vector<std::string>& columnas, const std::vector<std::string>& valores) {
    std::cout << "Ejecutando: INSERT INTO " << tabla << " (";
    // Itera y muestra cada columna, separadas por comas
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    std::cout << ") VALUES (";
    // Itera y muestra cada valor, separadas por comas
    for (size_t i = 0; i < valores.size(); ++i) {
        std::cout << valores[i];
        if (i < valores.size() - 1) std::cout << ", ";
    }
    std::cout << ")\n";

    // Busca la clave primaria en los valores de las columnas
    std::string llave;
    for(int i = 0; i < columnas.size(); i++){
        if(columnas[i] == primary_key){
            llave = valores[i];
            break;
        }
    }

    // Si el árbol está vacío, se crea la raíz y se inserta la primera llave
    if (raiz == nullptr) {
        raiz = new NodoBP(true);  // Nodo hoja
        raiz->llaves.push_back(llave);  // Insertar llave en la raíz
    }
    else {
        // Si la raíz está llena, se debe dividir y crear una nueva raíz
        if (raiz->llaves.size() == 2 * 2 - 1) {  // Tamaño máximo antes de dividir
            NodoBP* nueva = new NodoBP(false);  // Crear nueva raíz
            nueva->hijos.push_back(raiz);  // Enlace a la raíz antigua
            dividirHijo(nueva, 0, raiz);  // División de la raíz actual
            raiz = nueva;  // La nueva raíz es el nodo recién creado
        }
        // Inserta la llave en un nodo que no está lleno
        insertarEnNoLleno(raiz, llave);
    }
    // Asigna los datos correspondientes a la llave insertada
    asignarDatos(columnas, valores, llave);
}

// Implementación del método seleccionar
// Imprime en la consola el comando de selección simulado con las columnas especificadas
void ArbolBPlus::seleccionar(const std::vector<std::string>& columnas) {
    std::cout << "Ejecutando: SELECT ";
    // Itera y muestra cada columna seleccionada, separadas por comas
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    std::cout << " FROM " << tabla << std::endl;
    int contador = 0;  // Contador de registros mostrados
    imprimirRegistros(raiz, 0, columnas, contador);  // Llama a la función para imprimir los registros
    std::cout << "Se mostraron " << contador << " registros disponibles." << std::endl;
}

// Implementación del método actualizar
// Imprime en la consola el comando de actualización simulado con asignaciones y condición
void ArbolBPlus::actualizar(const std::map<std::string, std::string>& asignaciones, const std::string& condicion) {
    std::cout << "Ejecutando: UPDATE " << tabla << " SET ";
    std::string campo;  // Campo a actualizar
    std::string valor;  // Valor a asignar
    size_t i = 0;
    // Itera y muestra cada asignación en el formato columna=valor
    for (const auto& asignacion : asignaciones) {
        std::cout << asignacion.first << " = " << asignacion.second;
        campo = asignacion.first;
        valor = asignacion.second;
        if (i < asignaciones.size() - 1) std::cout << ", ";
        ++i;
    }
    std::cout << " WHERE " << condicion << std::endl;

    // Procesa la condición y verifica si es válida
    std::vector<std::string> condiciones = procesar_condicion(condicion);
    bool allowed = true;
    std::vector<std::string> aux;
    if(tabla == "personas"){
        aux = dColumns;
    }
    else if(tabla == "productos"){
        aux = pColumns;
    }
    else if(tabla == "usuarios"){
        aux = uColumns;
    } else{
        allowed = true;
    }
    if(allowed){
        if(std::find(aux.begin(), aux.end(), condiciones[0]) != aux.end() && std::find(aux.begin(), aux.end(), campo) != aux.end()){
            allowed = true;
        }
        else{
            allowed = false;
        }
    }

    // Si es válido, busca las claves para actualizar y aplica la actualización
    if(allowed){
        std::vector<std::string> *keys = new std::vector<std::string>;
        devolverKeys(raiz, condiciones , keys, 0);  // Recupera las claves correspondientes
        actualizarDatos(*keys, campo, valor);  // Actualiza los datos
        std::cout << "Se actualizaron " << keys->size() << " registros.";
    }
    else{
        std::cout << "Sintaxis inválida" << std::endl;
    }
}

// Implementación del método eliminar
// Imprime en la consola el comando de eliminación simulado con la condición dada
void ArbolBPlus::eliminar(const std::string& condicion) {
    std::vector<std::string> *keys = new std::vector<std::string>;  // Claves a eliminar
    std::vector<std::string> condiciones = procesar_condicion(condicion);  // Procesa la condición
    bool allowed = true;
    std::vector<std::string> aux;
    if(tabla == "personas"){
        aux = dColumns;
    }
    else if(tabla == "productos"){
        aux = pColumns;
    }
    else if(tabla == "usuarios"){
        aux = uColumns;
    } else{
        allowed = false;
    }

    // Verifica si la condición es válida y si procede, realiza la eliminación
    if(std::find(aux.begin(), aux.end(), condiciones[0]) != aux.end() && allowed){
        std::cout << "Ejecutando: DELETE FROM " << tabla << " WHERE " << condicion << std::endl;
        devolverKeys(raiz, condiciones , keys, 0);  // Recupera las claves para eliminar
        for(std::string &llave: *keys){
            remover(llave);  // Elimina cada clave
        }
        std::cout << "Se eliminaron " << (*keys).size() << " registros correctamente." << std::endl;
    }
    else{
        std::cout << "Sintaxis invalida" << std::endl;
    }
}
// Método para eliminar una llave del árbol B+.
// Si la raíz es nula (el árbol está vacío), retorna de inmediato.
void ArbolBPlus::remover(std::string llave) {
    if (raiz == nullptr) {
        return;
    }
    // Llama al método auxiliar para remover la llave desde la raíz.
    remover(raiz, llave);

    // Si después de eliminar, la raíz está vacía y no es una hoja,
    // ajusta la raíz para que apunte a su primer hijo y libera el nodo vacío.
    if (raiz->llaves.empty() && !raiz->esHoja) {
        NodoBP* tmp = raiz;
        raiz = raiz->hijos[0];
        delete tmp;
    }
}

// Método auxiliar para eliminar una llave desde un nodo específico.
void ArbolBPlus::remover(NodoBP *nodo, std::string llave) {
    // Caso 1: Si el nodo es hoja, intenta encontrar la llave y eliminarla.
    if (nodo->esHoja) {
        auto it = std::find(nodo->llaves.begin(), nodo->llaves.end(), llave);
        if (it != nodo->llaves.end()) {
            nodo->llaves.erase(it);
        }
    }
    // Caso 2: Si el nodo no es hoja, realiza operaciones para mantener el árbol balanceado.
    else {
        int idx = std::lower_bound(nodo->llaves.begin(), nodo->llaves.end(), llave) - nodo->llaves.begin();

        // Si la llave está en el nodo actual:
        if (idx < nodo->llaves.size() && nodo->llaves[idx] == llave) {
            // A. Si el hijo izquierdo de la llave tiene al menos 2 llaves:
            if (nodo->hijos[idx]->llaves.size() >= 2) {
                NodoBP* predNodo = nodo->hijos[idx];
                while (!predNodo->esHoja) {
                    predNodo = predNodo->hijos.back();
                }
                std::string pred = predNodo->llaves.back();
                nodo->llaves[idx] = pred;
                remover(nodo->hijos[idx], pred);
            }
            // B. Si el hijo derecho de la llave tiene al menos 2 llaves:
            else if (nodo->hijos[idx + 1]->llaves.size() >= 2) {
                NodoBP* succNode = nodo->hijos[idx + 1];
                while (!succNode->esHoja) {
                    succNode = succNode->hijos.front();
                }
                std::string succ = succNode->llaves.front();
                nodo->llaves[idx] = succ;
                remover(nodo->hijos[idx + 1], succ);
            }
            // C. Si ambos hijos tienen menos de 2 llaves, se combinan.
            else {
                unir(nodo, idx);
                remover(nodo->hijos[idx], llave);
            }
        }
        // Si la llave no está en el nodo actual, continúa buscando en el hijo adecuado.
        else {
            if (nodo->hijos[idx]->llaves.size() < 2) {
                if (idx > 0 && nodo->hijos[idx - 1]->llaves.size() >= 2) {
                    cogerAnterior(nodo, idx);
                }
                else if (idx < nodo->hijos.size() - 1 && nodo->hijos[idx + 1]->llaves.size() >= 2) {
                    cogerSiguiente(nodo, idx);
                }
                else {
                    if (idx < nodo->hijos.size() - 1) {
                        unir(nodo, idx);
                    }
                    else {
                        unir(nodo, idx - 1);
                    }
                }
            }
            remover(nodo->hijos[idx], llave);
        }
    }
}

// Método para combinar un nodo hijo con su hermano derecho.
void ArbolBPlus::unir(NodoBP* nodo, int index) {
    NodoBP* hijo = nodo->hijos[index];
    NodoBP* hermano = nodo->hijos[index + 1];

    // Inserta la llave y los elementos del hermano al hijo.
    hijo->llaves.push_back(nodo->llaves[index]);
    hijo->llaves.insert(hijo->llaves.end(), hermano->llaves.begin(), hermano->llaves.end());
    if (!hijo->esHoja) {
        hijo->hijos.insert(hijo->hijos.end(), hermano->hijos.begin(), hermano->hijos.end());
    }

    // Elimina la llave en el nodo actual y el puntero al hermano.
    nodo->llaves.erase(nodo->llaves.begin() + index);
    nodo->hijos.erase(nodo->hijos.begin() + index + 1);

    // Libera la memoria ocupada por el hermano.
    delete hermano;
}

// Método para procesar una condición en formato "campo=valor" y separarla en sus partes.
// Devuelve un vector con el campo y el valor como elementos separados.
std::vector<std::string> ArbolBPlus::procesar_condicion(std::string condicion) {
    int i = 0;
    std::string aux = "";
    std::vector<std::string> vector;

    // Recorre la condición y separa en dos partes por el símbolo '='.
    for (char c : condicion) {
        if (c == '=') {
            vector.push_back(aux);
            aux = "";
        }
        else {
            aux += c;
        }
    }

    // Agrega el valor final después del '=' al vector.
    vector.push_back(aux);
    return vector;
}

// Función para tomar prestada una llave del hermano izquierdo de un nodo hijo.
void ArbolBPlus::cogerAnterior(NodoBP* nodo, int index) {
    NodoBP* hijo = nodo->hijos[index];
    NodoBP* hermano = nodo->hijos[index - 1];

    // Inserta la última llave del hermano izquierdo al inicio de las llaves del hijo.
    hijo->llaves.insert(hijo->llaves.begin(), nodo->llaves[index - 1]);

    // Actualiza la llave del nodo actual con la última llave del hermano.
    nodo->llaves[index - 1] = hermano->llaves.back();

    // Remueve la última llave del hermano.
    hermano->llaves.pop_back();

    // Si el hijo no es una hoja, mueve el último hijo del hermano al inicio del hijo.
    if (!hijo->esHoja) {
        hijo->hijos.insert(hijo->hijos.begin(), hermano->hijos.back());
        hermano->hijos.pop_back();
    }
}

// Función para devolver las llaves de un nodo que cumplen una condición específica.
void ArbolBPlus::devolverKeys(NodoBP *nodo, std::vector<std::string> condicion, std::vector<std::string> *keys, int nivel) {
    if (nodo != nullptr) {
        // Itera sobre las llaves del nodo actual y aplica condiciones basadas en el valor de "tabla".
        for (const std::string& llave : nodo->llaves) {
            if(tabla == "personas") {
                Persona *persona = personas[llave];
                // Verifica condiciones sobre el objeto Persona y agrega la llave si se cumple.
                if(condicion[0] == "dID" && persona->getdID() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "nombre" && persona->getNombre() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "apellido" && persona->getApellido() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "edad" && persona->getEdad() == condicion[1]) {
                    keys->push_back(llave);
                }
            }
            else if(tabla == "productos") {
                Producto *producto = productos[llave];
                // Verifica condiciones sobre el objeto Producto y agrega la llave si se cumple.
                if(condicion[0] == "pID" && producto->getpID() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "nombre" && producto->getNombre() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "comprados" && producto->getComprados() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "vendidos" && producto->getVendidos() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "precio" && producto->getPrecio() == condicion[1]) {
                    keys->push_back(llave);
                }
            }
            else if(tabla == "usuarios") {
                Usuario *usuario = usuarios[llave];
                // Verifica condiciones sobre el objeto Usuario y agrega la llave si se cumple.
                if(condicion[0] == "uID" && usuario->getuID() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "usuario" && usuario->getUsuario() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "password" && usuario->getPassword() == condicion[1]) {
                    keys->push_back(llave);
                } else if(condicion[0] == "email" && usuario->getEmail() == condicion[1]) {
                    keys->push_back(llave);
                }
            }
        }
        // Recurre sobre los hijos del nodo para procesar en el siguiente nivel.
        for (NodoBP* hijo: nodo->hijos) {
            devolverKeys(hijo, condicion, keys, nivel + 1);
        }
    }
}

// Función para tomar prestada una llave del hermano derecho del nodo hijo.
void ArbolBPlus::cogerSiguiente(NodoBP* nodo, int index) {
    NodoBP* hijo = nodo->hijos[index];
    NodoBP* hermano = nodo->hijos[index + 1];

    // Agrega la primera llave del hermano derecho al final de las llaves del hijo.
    hijo->llaves.push_back(nodo->llaves[index]);

    // Actualiza la llave del nodo actual con la primera llave del hermano.
    nodo->llaves[index] = hermano->llaves.front();

    // Elimina la primera llave del hermano.
    hermano->llaves.erase(hermano->llaves.begin());

    // Si el hijo no es una hoja, mueve el primer hijo del hermano al final del hijo.
    if (!hijo->esHoja) {
        hijo->hijos.push_back(hermano->hijos.front());
        hermano->hijos.erase(hermano->hijos.begin());
    }
}

// Método para dividir un nodo hijo cuando se supera el número de llaves permitido.
void ArbolBPlus::dividirHijo(NodoBP *padre, int index, NodoBP *hijo) {
    NodoBP* nuevoHijo = new NodoBP(hijo->esHoja);

    // Inserta el nuevo nodo hijo en la posición correspondiente del padre.
    padre->hijos.insert(padre->hijos.begin() + index + 1, nuevoHijo);

    // Mueve la llave central del hijo al padre.
    padre->llaves.insert(padre->llaves.begin() + index, hijo->llaves[1]);

    // Copia la mitad derecha de las llaves del hijo al nuevo hijo.
    nuevoHijo->llaves.assign(hijo->llaves.begin() + 2, hijo->llaves.end());

    // Reduce el tamaño de las llaves del hijo original.
    hijo->llaves.resize(1);

    // Si el hijo no es una hoja, copia también los hijos correspondientes al nuevo hijo.
    if (!hijo->esHoja) {
        nuevoHijo->hijos.assign(hijo->hijos.begin() + 2, hijo->hijos.end());
        hijo->hijos.resize(2);
    }

    // Ajusta el puntero de enlace de las hojas, si el hijo es una hoja.
    if (hijo->esHoja) {
        nuevoHijo->siguiente = hijo->siguiente;
        hijo->siguiente = nuevoHijo;
    }
}

// Función para insertar una llave en un nodo no lleno del árbol B+.
void ArbolBPlus::insertarEnNoLleno(NodoBP* nodo, std::string llave) {
    // Si el nodo es hoja, se inserta la llave en el lugar adecuado.
    if (nodo->esHoja) {
        nodo->llaves.insert(std::upper_bound(nodo->llaves.begin(), nodo->llaves.end(), llave), llave);
    }
    else {
        // Si el nodo no es hoja, busca el hijo adecuado donde insertar la llave.
        int i = nodo->llaves.size() - 1;
        while (i >= 0 && llave < nodo->llaves[i]) {
            i--;
        }
        i++;  // i apunta al índice del hijo adecuado.

        // Si el hijo está lleno (tiene 2 * grado - 1 llaves), se divide.
        if (nodo->hijos[i]->llaves.size() == 2 * 2 - 1) {
            dividirHijo(nodo, i, nodo->hijos[i]);
            // Si la nueva llave debe ir al hijo derecho, incrementa el índice.
            if (llave > nodo->llaves[i]) {
                i++;
            }
        }
        // Llama recursivamente para insertar la llave en el hijo adecuado.
        insertarEnNoLleno(nodo->hijos[i], llave);
    }
}

// Función para asignar los datos a los objetos correspondientes (Persona, Producto, Usuario),
// según los valores de las columnas recibidas.
void ArbolBPlus::asignarDatos(const std::vector<std::string> &columnas, const std::vector<std::string> &valores, std::string llave) {
    // Crea instancias de Persona, Producto y Usuario.
    Persona *persona = new Persona();
    Producto *producto = new Producto();
    Usuario *usuario = new Usuario();

    std::string aux;
    for (int cont = 0; cont < columnas.size(); cont++) {
        aux = columnas[cont];

        // Asigna los valores según la tabla seleccionada (personas, productos o usuarios).
        if (tabla == "personas") {
            if (aux == "dID") {
                persona->setdID(valores[cont]);
            }
            else if (aux == "nombre") {
                persona->setNombre(valores[cont]);
            }
            else if (aux == "apellido") {
                persona->setApellido(valores[cont]);
            }
            else if (aux == "edad") {
                persona->setEdad(valores[cont]);
            }
        }
        else if (tabla == "usuarios") {
            if (aux == "uID") {
                usuario->setuID(valores[cont]);
            }
            else if (aux == "usuario") {
                usuario->setUsuario(valores[cont]);
            }
            else if (aux == "password") {
                usuario->setPassword(valores[cont]);
            }
            else if (aux == "email") {
                usuario->setEmail(valores[cont]);
            }
        }
        else if (tabla == "productos") {
            if (aux == "pID") {
                producto->setpID(valores[cont]);
            }
            else if (aux == "nombre") {
                producto->setNombre(valores[cont]);
            }
            else if (aux == "comprados") {
                producto->setComprados(valores[cont]);
            }
            else if (aux == "vendidos") {
                producto->setVendidos(valores[cont]);
            }
            else if (aux == "precio") {
                producto->setPrecio(valores[cont]);
            }
        }
    }

    // Dependiendo de la tabla, se asigna el objeto creado al contenedor correspondiente.
    if (tabla == "personas") personas[llave] = persona;
    else if (tabla == "productos") productos[llave] = producto;
    else if (tabla == "usuarios") usuarios[llave] = usuario;
}

// Imprime los registros de un nodo en un B+ tree.
void ArbolBPlus::imprimirRegistros(NodoBP* nodo, int nivel, std::vector<std::string> columnas, int &contador) {
    if (nodo != nullptr) {
        // Itera sobre cada llave en el nodo actual y llama a formatearDatos según la tabla.
        for (const std::string& llave : nodo->llaves) {
            if(tabla == "personas") {
                std::cout << formatearDatos(personas[llave], nullptr, nullptr, columnas) << std::endl;
            }
            else if(tabla == "productos") {
                std::cout << formatearDatos(nullptr, productos[llave], nullptr, columnas) << std::endl;
            }
            else if(tabla == "usuarios") {
                std::cout << formatearDatos(nullptr, nullptr, usuarios[llave], columnas) << std::endl;
            }
            contador++;
        }
        // Llama recursivamente para imprimir registros de nodos hijos.
        for (NodoBP* hijo: nodo->hijos) {
            imprimirRegistros(hijo, nivel + 1, columnas, contador);
        }
    }
}

// Formatea los datos de un registro para su impresión.
std::string ArbolBPlus::formatearDatos(Persona *persona, Producto *producto, Usuario* usuario, std::vector<std::string> &columnas) {
    std::string aux = "";
    // Itera por cada columna y agrega el valor correspondiente del objeto según la tabla actual.
    for(std::string &columna : columnas) {
        if(tabla == "personas") {
            if(columna == "dID") aux += persona->getdID();
            else if(columna == "nombre") aux += persona->getNombre();
            else if(columna == "apellido") aux += persona->getApellido();
            else if(columna == "edad") aux += persona->getEdad();
        }
        else if (tabla == "productos") {
            if(columna == "pID") aux += producto->getpID();
            else if(columna == "nombre") aux += producto->getNombre();
            else if(columna == "comprados") aux += producto->getComprados();
            else if(columna == "vendidos") aux += producto->getVendidos();
            else if(columna == "precio") aux += producto->getPrecio();
        }
        else if (tabla == "usuarios") {
            if(columna == "uID") aux += usuario->getuID();
            else if(columna == "usuario") aux += usuario->getUsuario();
            else if(columna == "password") aux += usuario->getPassword();
            else if(columna == "email") aux += usuario->getEmail();
        }
        aux += " "; // Agrega espacio entre columnas.
    }
    return aux;
}

// Actualiza los datos en los registros identificados por las llaves en `keys`.
void ArbolBPlus::actualizarDatos(std::vector<std::string> &keys, std::string campo, std::string valor) {
    for(std::string key: keys) {
        if(tabla == "personas") {
            Persona *persona = personas[key];
            if(campo == "dID") persona->setdID(valor);
            else if(campo == "nombre") persona->setNombre(valor);
            else if(campo == "apellido") persona->setApellido(valor);
            else if(campo == "edad") persona->setEdad(valor);
        }
        else if(tabla == "productos") {
            Producto *producto = productos[key];
            if(campo == "pID") producto->setpID(valor);
            else if(campo == "nombre") producto->setNombre(valor);
            else if(campo == "comprados") producto->setComprados(valor);
            else if(campo == "vendidos") producto->setVendidos(valor);
            else if(campo == "precio") producto->setPrecio(valor);
        }
        else if(tabla == "usuarios") {
            Usuario *usuario = usuarios[key];
            if(campo == "uID") usuario->setuID(valor);
            else if(campo == "usuario") usuario->setUsuario(valor);
            else if(campo == "password") usuario->setPassword(valor);
            else if(campo == "email") usuario->setEmail(valor);
        }
    }
}

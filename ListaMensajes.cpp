#include "ListaMensajes.hpp"

#include <fstream>
#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO A (LISTA DOBLEMENTE ENLAZADA)
// Integrantes:
/*
1. **Saúl Aranguren** — C.I. V-30.889.906
   *Rol:* Estructura de Datos (`ListaMensajes`) y QA

2. **Diego García** — C.I. V-32.683.035
   *Rol:* Estructura de Datos (`ListaMensajes`)

3. **Jeremías Ortega** — C.I. V-32.591.369
   *Rol:* Estructura de Datos (`ListaMensajes`) y QA

4. **Luis Paz** — C.I. V-30.678.152
   *Rol:* Integración (`ChatLista` y sistema de mensajería)

5. **Mayre Rodríguez** — C.I. V-32.211.448
   *Rol:* Integración (`ChatLista` y sistema de mensajería)

6. **Sebastián Olivares** — C.I. V-32.659.089
   *Rol:* Documentación (`README.md`), QA, gestión de Git y demo (`main.cpp`)*/
// ====================================================================
// Completen la implementacion de esta estructura.
// ====================================================================

// Constructor del nodo, inicializa el dato y los punteros a nullptr.
ListaMensajes::Nodo::Nodo(const TextMessage& mensaje)
    : dato(mensaje), siguiente(nullptr), anterior()
{
}

ListaMensajes::ListaMensajes()
    : cabeza(nullptr), cola(nullptr), cantidad(0)
{
}

ListaMensajes::ListaMensajes(const ListaMensajes& otra)
    : cabeza(nullptr), cola(nullptr), cantidad(0)
{
    for (std::shared_ptr<Nodo> actual = otra.cabeza; actual != nullptr; actual = actual->siguiente)
    {
        agregarAlFinal(actual->dato);
    }
}

ListaMensajes& ListaMensajes::operator=(const ListaMensajes& otra)
{
    // TODO: completar.
    (void)otra;
    return *this;
}

ListaMensajes::ListaMensajes(ListaMensajes&& otra) noexcept
    : cabeza(std::move(otra.cabeza)), cola(std::move(otra.cola)), cantidad(otra.cantidad)
{
    otra.cantidad = 0;
}

ListaMensajes& ListaMensajes::operator=(ListaMensajes&& otra) noexcept
{
    // TODO: completar.
    (void)otra;
    return *this;
}

bool ListaMensajes::vacia() const
{
    return cabeza == nullptr;
}

std::size_t ListaMensajes::tamanio() const
{
    return cantidad;
}

bool ListaMensajes::agregarAlFinal(const TextMessage& mensaje)
{
    for (std::shared_ptr<Nodo> actual = cabeza; actual != nullptr; actual = actual->siguiente)
    {
        if (actual->dato.getId() == mensaje.getId())
        {
            return false;
        }
    }

    std::shared_ptr<Nodo> nuevo = std::make_shared<Nodo>(mensaje);

    if (cabeza == nullptr)
    {
        cabeza = nuevo;
        cola = nuevo;
    }
    else
    {
        nuevo->anterior = cola;
        cola->siguiente = nuevo;
        cola = nuevo;
    }

    ++cantidad;
    return true;
}

bool ListaMensajes::agregarAlInicio(const TextMessage& mensaje)
{
    for (std::shared_ptr<Nodo> actual = cabeza; actual != nullptr; actual = actual->siguiente)
    {
        if (actual->dato.getId() == mensaje.getId())
        {
            return false;
        }
    }

    std::shared_ptr<Nodo> nuevo = std::make_shared<Nodo>(mensaje);
    if (cabeza == nullptr)
    {
        cabeza = nuevo;
        cola = nuevo;
    }
    else
    {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }

    ++cantidad;
    return true;
}

bool ListaMensajes::insertarDespuesDe(int idReferencia, const TextMessage& mensaje)
{
    for (std::shared_ptr<Nodo> actual = cabeza; actual != nullptr; actual = actual->siguiente)
    {
        if (actual->dato.getId() == mensaje.getId())
        {
            return false;
        }
    }

    std::shared_ptr<Nodo> actual = cabeza;
    while (actual != nullptr && actual->dato.getId() != idReferencia)
    {
        actual = actual->siguiente;
    }

    if (actual == nullptr)
    {
        return false;
    }

    std::shared_ptr<Nodo> nuevo = std::make_shared<Nodo>(mensaje);
    nuevo->anterior = actual;
    nuevo->siguiente = actual->siguiente;

    if (actual->siguiente != nullptr)
    {
        actual->siguiente->anterior = nuevo;
    }
    else
    {
        cola = nuevo;
    }

    actual->siguiente = nuevo;
    ++cantidad;
    return true;
}

bool ListaMensajes::eliminarPorId(int id)
{
    std::shared_ptr<Nodo> actual = cabeza;
    while (actual != nullptr && actual->dato.getId() != id)
    {
        actual = actual->siguiente;
    }

    if (actual == nullptr)
    {
        return false;
    }

    std::shared_ptr<Nodo> anterior = actual->anterior.lock();
    if (anterior != nullptr)
    {
        anterior->siguiente = actual->siguiente;
    }
    else
    {
        cabeza = actual->siguiente;
    }

    if (actual->siguiente != nullptr)
    {
        actual->siguiente->anterior = anterior;
    }
    else
    {
        cola = anterior;
    }

    actual->siguiente.reset();
    actual->anterior.reset();
    --cantidad;
    return true;
}

TextMessage* ListaMensajes::buscarPorId(int id)
{
    for (std::shared_ptr<Nodo> actual = cabeza; actual != nullptr; actual = actual->siguiente)
    {
        if (actual->dato.getId() == id)
        {
            return &actual->dato;
        }
    }
    return nullptr;
}

const TextMessage* ListaMensajes::buscarPorId(int id) const
{
    for (std::shared_ptr<Nodo> actual = cabeza; actual != nullptr; actual = actual->siguiente)
    {
        if (actual->dato.getId() == id)
        {
            return &actual->dato;
        }
    }
    return nullptr;
}

const TextMessage* ListaMensajes::primero() const
{
    return (vacia()) ? nullptr : &(cabeza->dato);
}

const TextMessage* ListaMensajes::ultimo() const
{
    return (vacia()) ? nullptr : &(cola->dato);
}

bool ListaMensajes::moverAlInicio(int id)
{
    // Caso Base 1: si la lista vacia esta, no hay nada que hacer
    if(vacia()) return false;

    // Caso Base 2: si ya es el primer elemento no hacemos nada
    if(cabeza->dato.getId() == id) return true;

    // Buscar el id que se ha ingresado
    std::shared_ptr<Nodo> actual = cabeza;
    while(actual != nullptr && actual->dato.getId() != id)
    {
        actual = actual->siguiente;
    }

    // se ha llegado al final y no ha sido encontrado
    if(actual == nullptr) return false;

    std::shared_ptr<Nodo> anterior = actual->anterior.lock();

    anterior->siguiente = actual->siguiente;

    if(actual == cola) 
    {
        cola = anterior;
    }
    else
    {
        actual->siguiente->anterior = anterior;
    }
    
    actual->siguiente = cabeza;
    actual->anterior.reset();
    cabeza->anterior = actual;

    cabeza = actual;

    return true;
}

void ListaMensajes::recorrer(const std::function<void(const TextMessage&)>& funcion) const
{
    std::shared_ptr<Nodo> actual = cabeza;

    while(actual != nullptr)
    {
        funcion(actual->dato);
        actual = actual->siguiente;
    }
}

void ListaMensajes::recorrerInverso(const std::function<void(const TextMessage&)>& funcion) const
{
    std::shared_ptr<Nodo> actual = cola;
    
    while(actual != nullptr)
    {
        funcion(actual->dato);
        actual = actual->anterior.lock();
    }
}

std::vector<int> ListaMensajes::ids() const
{
    std::vector<int> resultado;
    std::shared_ptr<Nodo> actual = cabeza;

    while(actual != nullptr)
    {
        resultado.push_back(actual->dato.getId());
        actual = actual->siguiente;
    }

    return resultado;
}

void ListaMensajes::limpiar()
{
    while (cabeza)
    {
        std::shared_ptr<Nodo> siguiente = cabeza->siguiente;
        cabeza->siguiente.reset();
        cabeza = std::move(siguiente);
    }

    cola.reset();
    cantidad = 0;
}

bool ListaMensajes::guardarCSV(const std::string& ruta) const
{
    std::ofstream archivo(ruta);
    if (!archivo.is_open())
    {
        return false;
    }

    for (std::shared_ptr<Nodo> actual = cabeza; actual; actual = actual->siguiente)
    {
        archivo << actual->dato.toCSV() << '\n';
        if (!archivo)
        {
            return false;
        }
    }

    archivo.flush();
    return archivo.good();
}

bool ListaMensajes::cargarCSV(const std::string& ruta)
{
    std::ifstream archivo(ruta);
    if (!archivo.is_open())
    {
        return false;
    }

    limpiar();

    std::string linea;
    const auto normalizarCSVSerializado = [](const std::string& texto) {
        std::string normalizado;
        normalizado.reserve(texto.size());
        bool entreComillas = false;

        for (std::size_t i = 0; i < texto.size(); ++i)
        {
            const char caracter = texto[i];

            if (entreComillas && caracter == '\\' && i + 1 < texto.size() &&
                (texto[i + 1] == '"' || texto[i + 1] == '\\'))
            {
                if (texto[i + 1] == '"')
                {
                    normalizado += "\"\"";
                }
                else
                {
                    normalizado += '\\';
                }
                ++i;
                continue;
            }

            normalizado += caracter;
            if (caracter == '"')
            {
                if (entreComillas && i + 1 < texto.size() && texto[i + 1] == '"')
                {
                    normalizado += '"';
                    ++i;
                }
                else
                {
                    entreComillas = !entreComillas;
                }
            }
        }

        return normalizado;
    };

    while (std::getline(archivo, linea))
    {
        if (linea.empty())
        {
            continue;
        }

        std::shared_ptr<Nodo> nuevo =
            std::make_shared<Nodo>(TextMessage::fromCSV(normalizarCSVSerializado(linea)));
        if (!cola)
        {
            cabeza = nuevo;
            cola = nuevo;
        }
        else
        {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }

        ++cantidad;
    }

    return !archivo.bad();
}

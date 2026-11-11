#include "ListaMensajes.hpp"

#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO A (LISTA DOBLEMENTE ENLAZADA)
// Integrantes:
//   1. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
// ====================================================================
// Completen la implementacion de esta estructura.
// ====================================================================

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
    // TODO: completar.
    (void)otra;
}

ListaMensajes& ListaMensajes::operator=(const ListaMensajes& otra)
{
    // TODO: completar.
    (void)otra;
    return *this;
}

ListaMensajes::ListaMensajes(ListaMensajes&& otra) noexcept
    : cabeza(nullptr), cola(nullptr), cantidad(0)
{
    // TODO: completar.
    (void)otra;
}

ListaMensajes& ListaMensajes::operator=(ListaMensajes&& otra) noexcept
{
    // TODO: completar.
    (void)otra;
    return *this;
}

bool ListaMensajes::vacia() const
{

    return false;
}

std::size_t ListaMensajes::tamanio() const
{
    // TODO: completar.
    return 0;
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
    // TODO: completar.
    (void)id;
    return false;
}

TextMessage* ListaMensajes::buscarPorId(int id)
{
    // TODO: completar.
    (void)id;
    return nullptr;
}

const TextMessage* ListaMensajes::buscarPorId(int id) const
{
    // TODO: completar.
    (void)id;
    return nullptr;
}

const TextMessage* ListaMensajes::primero() const
{
    // TODO: completar.
    return nullptr;
}

const TextMessage* ListaMensajes::ultimo() const
{
    // TODO: completar.
    return nullptr;
}

bool ListaMensajes::moverAlInicio(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

void ListaMensajes::recorrer(const std::function<void(const TextMessage&)>& funcion) const
{
    // TODO: completar.
    (void)funcion;
}

void ListaMensajes::recorrerInverso(const std::function<void(const TextMessage&)>& funcion) const
{
    // TODO: completar.
    (void)funcion;
}

std::vector<int> ListaMensajes::ids() const
{
    // TODO: completar.
    return {};
}

void ListaMensajes::limpiar()
{
    // TODO: completar.
}

bool ListaMensajes::guardarCSV(const std::string& ruta) const
{
    // TODO: completar.
    (void)ruta;
    return false;
}

bool ListaMensajes::cargarCSV(const std::string& ruta)
{
    // TODO: completar.
    (void)ruta;
    return false;
}

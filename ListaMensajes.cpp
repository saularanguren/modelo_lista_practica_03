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
    Nodo* nuevo = new Nodo(mensaje);
    if(cabeza == nullptr){
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->anterior = cola;
        cola->siguiente = nuevo;
        cola = nuevo;
    }
    if(!nuevo->dato == nullptr) return true;
    (void)mensaje;
    return false;
}

bool ListaMensajes::agregarAlInicio(const TextMessage& mensaje)
{
    Nodo* nuevo = new Nodo(mensaje);
    if(cabeza == nullptr){
        cabeza nuevo;
        cola = nuevo;
    } else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
    if(!nuevo->dato == nullptr) return true;
    (void)mensaje;
    return false;
}

bool ListaMensajes::insertarDespuesDe(int idReferencia, const TextMessage& mensaje)
{
    // TODO: completar.
    (void)idReferencia;
    (void)mensaje;
    return false;
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

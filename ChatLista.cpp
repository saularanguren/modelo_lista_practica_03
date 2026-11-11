#include "ChatLista.hpp"

#include <sstream>
#include <utility>

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO A (LISTA DOBLEMENTE ENLAZADA)
// Integrantes:
//   1. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
// ====================================================================
// Completen la integracion del historial con el chat.
// ====================================================================

ChatLista::ChatLista(int id, std::string nombre, std::vector<std::string> participantes)
    : Chat(id, std::move(nombre), std::move(participantes))
{
}

bool ChatLista::enviarMensaje(TextMessage mensaje)
{
    // TODO: completar.
    (void)mensaje;
    return false;
}

bool ChatLista::fijarMensaje(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

bool ChatLista::eliminarMensaje(int id)
{
    // TODO: completar.
    (void)id;
    return false;
}

const ListaMensajes& ChatLista::getHistorial() const
{
    // TODO: completar.
    return historial;
}

ListaMensajes& ChatLista::getHistorial()
{
    // TODO: completar.
    return historial;
}

std::size_t ChatLista::cantidadMensajes() const
{
    // TODO: completar.
    return 0;
}

std::string ChatLista::resumen() const
{
    // TODO: completar.
    return "";
}

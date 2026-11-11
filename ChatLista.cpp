#include "ChatLista.hpp"

#include <sstream>
#include <utility>
#include <iostream>

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
    if (!isParticipant(mensaje.getSenderId()))
    {
        return false;
    }

    if (historial.buscarPorId(mensaje.getId()) == nullptr)
    {
        return false;
    }

    if (mensaje.getStatus() != MessageStatus::Pending)
    {
        return false;
    }

    mensaje.markSent(getId());
    historial.agregarAlFinal(mensaje);

    (void)mensaje;
    return true;
}

bool ChatLista::fijarMensaje(int id)
{    
    if (historial.buscarPorId(id) == nullptr)
    {
        return false;
    }

    historial.moverAlInicio(id);

    (void)id;
    return true;
}

bool ChatLista::eliminarMensaje(int id)
{
    historial.eliminarPorId(id);
    
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

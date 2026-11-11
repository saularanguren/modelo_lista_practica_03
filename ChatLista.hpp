#pragma once

#include <string>
#include <vector>

#include "Chat.hpp"
#include "ListaMensajes.hpp"

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO A (LISTA DOBLEMENTE ENLAZADA)
// Integrantes:
//   1. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
// ====================================================================

class ChatLista : public Chat
{
private:
    ListaMensajes historial;

public:
    ChatLista(int id, std::string nombre, std::vector<std::string> participantes);

    bool enviarMensaje(TextMessage mensaje);
    bool fijarMensaje(int id);
    bool eliminarMensaje(int id);

    const ListaMensajes& getHistorial() const;
    ListaMensajes& getHistorial();
    std::size_t cantidadMensajes() const;
    std::string resumen() const;
};

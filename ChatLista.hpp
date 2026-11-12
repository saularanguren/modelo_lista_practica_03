#pragma once

#include <string>
#include <vector>

#include "Chat.hpp"
#include "ListaMensajes.hpp"

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

#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "TextMessage.hpp"

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO A (LISTA DOBLEMENTE ENLAZADA)
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

class ListaMensajes
{
private:
    struct Nodo
    {
        TextMessage dato;
        std::shared_ptr<Nodo> siguiente;
        std::weak_ptr<Nodo> anterior;

        explicit Nodo(const TextMessage& mensaje);
    };

    std::shared_ptr<Nodo> cabeza;
    std::shared_ptr<Nodo> cola;
    std::size_t cantidad;

public:
    ListaMensajes();
    ListaMensajes(const ListaMensajes& otra);
    ListaMensajes& operator=(const ListaMensajes& otra);
    ListaMensajes(ListaMensajes&& otra) noexcept;
    ListaMensajes& operator=(ListaMensajes&& otra) noexcept;
    ~ListaMensajes() = default;

    bool vacia() const;
    std::size_t tamanio() const;

    bool agregarAlFinal(const TextMessage& mensaje);
    bool agregarAlInicio(const TextMessage& mensaje);
    bool insertarDespuesDe(int idReferencia, const TextMessage& mensaje);

    bool eliminarPorId(int id);

    TextMessage* buscarPorId(int id);
    const TextMessage* buscarPorId(int id) const;

    const TextMessage* primero() const;
    const TextMessage* ultimo() const;

    bool moverAlInicio(int id);

    void recorrer(const std::function<void(const TextMessage&)>& funcion) const;
    void recorrerInverso(const std::function<void(const TextMessage&)>& funcion) const;

    std::vector<int> ids() const;
    void limpiar();

    bool guardarCSV(const std::string& ruta) const;
    bool cargarCSV(const std::string& ruta);
};

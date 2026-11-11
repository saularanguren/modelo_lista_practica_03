#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "TextMessage.hpp"

// ====================================================================
// PRACTICA EVALUADA 03 - MODELO A (LISTA DOBLEMENTE ENLAZADA)
// Integrantes:
//   1. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   2. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   3. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
//   4. Nombre y Apellido - C.I. V-XXXXXXXX - Rol:
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

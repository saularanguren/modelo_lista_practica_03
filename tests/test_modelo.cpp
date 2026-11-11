// ====================================================================
// PRACTICA 03 - MODELO A (LISTA DOBLEMENTE ENLAZADA)
// Verificador de requisitos minimos.
// NO asigna nota: solo indica si el esqueleto ya cumple lo minimo.
// La calificacion la realiza el preparador con la rubrica.
// ====================================================================

#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "ChatLista.hpp"
#include "ListaMensajes.hpp"
#include "TextMessage.hpp"

using namespace std;

static int total[6] = {0, 0, 0, 0, 0, 0};
static int superadas[6] = {0, 0, 0, 0, 0, 0};

static void test(int bloque, const string& nombre, bool ok)
{
    ++total[bloque];
    if (ok)
    {
        ++superadas[bloque];
    }

    cout << "  [" << (ok ? "OK" : "FALLA") << "] " << nombre << endl;
}

int main()
{
    cout << "====================================================================" << endl;
    cout << "     PRACTICA 03 - MODELO A: LISTA DOBLEMENTE ENLAZADA (C++)       " << endl;
    cout << "====================================================================\n" << endl;

    // ------------------------------------------------------------------
    // BLOQUE 1: ESTRUCTURA DESDE CERO
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 1: Estructura desde cero ---" << endl;

    ListaMensajes vacia;
    const bool b1_1 = vacia.vacia() && vacia.tamanio() == 0 &&
                      vacia.primero() == nullptr && vacia.ultimo() == nullptr;
    test(1, "1.1 Lista recien creada: vacia, tamanio 0, primero/ultimo nullptr", b1_1);

    ListaMensajes lista;
    TextMessage m1(1, "u1", "uno");
    TextMessage m2(2, "u1", "dos");
    TextMessage m3(3, "u2", "tres");
    const bool a1 = lista.agregarAlFinal(m1);
    const bool a2 = lista.agregarAlFinal(m2);
    const bool a3 = lista.agregarAlFinal(m3);
    const bool b1_2 = a1 && a2 && a3 && lista.tamanio() == 3 && !lista.vacia() &&
                      lista.ids() == vector<int>{1, 2, 3} &&
                      lista.primero() != nullptr && lista.primero()->getId() == 1 &&
                      lista.ultimo() != nullptr && lista.ultimo()->getId() == 3;
    test(1, "1.2 agregarAlFinal respeta el orden y actualiza tamanio/primero/ultimo", b1_2);

    ListaMensajes listaInicio;
    listaInicio.agregarAlInicio(m1);
    listaInicio.agregarAlInicio(m2);
    listaInicio.agregarAlInicio(m3);
    const bool b1_3 = listaInicio.tamanio() == 3 &&
                      listaInicio.ids() == vector<int>{3, 2, 1} &&
                      listaInicio.primero() != nullptr && listaInicio.primero()->getId() == 3;
    test(1, "1.3 agregarAlInicio inserta correctamente al principio", b1_3);

    vector<int> adelante;
    vector<int> atras;
    lista.recorrer([&adelante](const TextMessage& m) { adelante.push_back(m.getId()); });
    lista.recorrerInverso([&atras](const TextMessage& m) { atras.push_back(m.getId()); });
    const bool b1_4 = adelante == vector<int>{1, 2, 3} && atras == vector<int>{3, 2, 1};
    test(1, "1.4 recorrer() y recorrerInverso() visitan todos los nodos en orden", b1_4);

    cout << endl;

    // ------------------------------------------------------------------
    // BLOQUE 2: OPERACIONES NUCLEO
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 2: Operaciones nucleo ---" << endl;

    const TextMessage* encontrado = lista.buscarPorId(2);
    const bool b2_1 = encontrado != nullptr && encontrado->getContent() == "dos" &&
                      lista.buscarPorId(99) == nullptr;
    test(2, "2.1 buscarPorId() retorna el mensaje correcto o nullptr", b2_1);

    ListaMensajes listaBorrar;
    listaBorrar.agregarAlFinal(TextMessage(10, "u1", "a"));
    listaBorrar.agregarAlFinal(TextMessage(11, "u1", "b"));
    listaBorrar.agregarAlFinal(TextMessage(12, "u1", "c"));
    listaBorrar.agregarAlFinal(TextMessage(13, "u1", "d"));
    const bool e1 = listaBorrar.eliminarPorId(11);
    const bool e2 = listaBorrar.eliminarPorId(10);
    const bool e3 = listaBorrar.eliminarPorId(13);
    const bool b2_2 = e1 && e2 && e3 && listaBorrar.tamanio() == 1 &&
                      listaBorrar.primero() != nullptr && listaBorrar.primero()->getId() == 12 &&
                      listaBorrar.ultimo() != nullptr && listaBorrar.ultimo()->getId() == 12 &&
                      listaBorrar.buscarPorId(10) == nullptr &&
                      listaBorrar.buscarPorId(11) == nullptr &&
                      listaBorrar.buscarPorId(13) == nullptr;
    test(2, "2.2 eliminarPorId() funciona en cabeza, medio y cola", b2_2);

    ListaMensajes listaInsertar;
    listaInsertar.agregarAlFinal(m1);
    listaInsertar.agregarAlFinal(m2);
    const bool insOk = listaInsertar.insertarDespuesDe(1, TextMessage(25, "u2", "entre"));
    const bool insNo = listaInsertar.insertarDespuesDe(99, TextMessage(26, "u2", "no"));
    const bool b2_3 = insOk && !insNo && listaInsertar.ids() == vector<int>{1, 25, 2};
    test(2, "2.3 insertarDespuesDe() inserta en la posicion correcta", b2_3);

    ListaMensajes listaMover;
    listaMover.agregarAlFinal(m1);
    listaMover.agregarAlFinal(m2);
    listaMover.agregarAlFinal(m3);
    const bool movOk = listaMover.moverAlInicio(3);
    const bool movNo = listaMover.moverAlInicio(99);
    const bool b2_4 = movOk && !movNo && listaMover.ids() == vector<int>{3, 1, 2};
    test(2, "2.4 moverAlInicio() reubica un nodo sin romper la lista", b2_4);

    cout << endl;

    // ------------------------------------------------------------------
    // BLOQUE 3: INTEGRACION CON MENSAJERIA
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 3: Integracion con mensajeria ---" << endl;

    ChatLista chat(1, "Equipo PR2", {"u1", "u2"});
    TextMessage c1(1, "u1", "hola");
    const bool envio = chat.enviarMensaje(c1);
    const TextMessage* guardado = chat.getHistorial().buscarPorId(1);
    const bool b3_1 = envio && chat.cantidadMensajes() == 1 && guardado != nullptr &&
                      guardado->getStatus() == MessageStatus::Sent;
    test(3, "3.1 enviarMensaje() agrega al historial y marca el mensaje como Sent", b3_1);

    TextMessage intruso(2, "u3", "no participo");
    const bool rechazo = chat.enviarMensaje(intruso);
    const bool b3_2 = !rechazo && chat.cantidadMensajes() == 1 &&
                      chat.getHistorial().buscarPorId(2) == nullptr;
    test(3, "3.2 enviarMensaje() rechaza a un remitente que no participa", b3_2);

    TextMessage c2(2, "u2", "segundo");
    const bool envio2 = chat.enviarMensaje(c2);
    const bool fijar = chat.fijarMensaje(2);
    const bool b3_3a = envio2 && fijar && chat.getHistorial().primero() != nullptr &&
                       chat.getHistorial().primero()->getId() == 2;
    const bool eliminar = chat.eliminarMensaje(1);
    const bool b3_3b = eliminar && chat.cantidadMensajes() == 1 &&
                       chat.getHistorial().buscarPorId(1) == nullptr;
    test(3, "3.3 fijarMensaje() y eliminarMensaje() operan sobre el historial", b3_3a && b3_3b);

    cout << endl;

    // ------------------------------------------------------------------
    // BLOQUE 4: CASOS BORDE
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 4: Casos borde y robustez ---" << endl;

    ListaMensajes listaDup;
    listaDup.agregarAlFinal(m1);
    const bool dup = listaDup.agregarAlFinal(TextMessage(1, "u2", "duplicado"));
    const bool b4_1 = !dup && listaDup.tamanio() == 1;
    test(4, "4.1 Se rechaza un mensaje con id duplicado", b4_1);

    ListaMensajes listaNo;
    listaNo.agregarAlFinal(m1);
    const bool borrarNo = listaNo.eliminarPorId(999);
    ListaMensajes listaVaciaNo;
    const bool borrarVacia = listaVaciaNo.eliminarPorId(1);
    const bool b4_2 = !borrarNo && !borrarVacia && listaNo.tamanio() == 1;
    test(4, "4.2 eliminar un id inexistente retorna false sin alterar la lista", b4_2);

    ListaMensajes original;
    original.agregarAlFinal(m1);
    original.agregarAlFinal(m2);
    ListaMensajes copia = original;
    const bool copiaOk = copia.tamanio() == 2 && copia.buscarPorId(1) != nullptr;
    copia.eliminarPorId(1);
    const bool independiente = original.tamanio() == 2 && copia.tamanio() == 1;
    ListaMensajes movida = std::move(original);
    const bool moveOk = movida.tamanio() == 2 && original.vacia();
    test(4, "4.3 Copia profunda y movimiento seguros (regla de cinco)", copiaOk && independiente && moveOk);

    cout << endl;

    // ------------------------------------------------------------------
    // BLOQUE 5: PERSISTENCIA
    // ------------------------------------------------------------------
    cout << "--- BLOQUE 5: Persistencia CSV ---" << endl;

    const string ruta = "test_lista.csv";
    ListaMensajes persistente;
    persistente.agregarAlFinal(m1);
    persistente.agregarAlFinal(m2);
    const bool guardo = persistente.guardarCSV(ruta);
    ListaMensajes cargada;
    const bool cargo = cargada.cargarCSV(ruta);
    const TextMessage* recuperado = cargada.buscarPorId(1);
    ListaMensajes inexistente;
    const bool noCarga = inexistente.cargarCSV("archivo_inexistente_12345.csv");
    const bool b5 = guardo && cargo && cargada.ids() == vector<int>{1, 2} &&
                    recuperado != nullptr && recuperado->getContent() == "uno" &&
                    !noCarga && inexistente.vacia();
    std::remove(ruta.c_str());
    test(5, "5.1 Guardar y cargar conserva orden y contenido; archivo ausente falla", b5);

    // ------------------------------------------------------------------
    // VERIFICACION MINIMA
    // ------------------------------------------------------------------
    int totalOk = 0;
    int totalChecks = 0;
    for (int b = 1; b <= 5; ++b)
    {
        totalOk += superadas[b];
        totalChecks += total[b];
    }

    cout << "\n====================================================================" << endl;
    cout << "            VERIFICACION DE REQUISITOS MINIMOS                     " << endl;
    cout << "====================================================================" << endl;
    for (int b = 1; b <= 5; ++b)
    {
        cout << "  Bloque " << b << ": " << superadas[b] << " / " << total[b]
             << " verificaciones" << endl;
    }
    cout << "  TOTAL: " << totalOk << " / " << totalChecks
         << " verificaciones superadas" << endl;
    cout << "  RESULTADO: ";
    if (totalOk == totalChecks)
    {
        cout << "CUMPLE EL MINIMO" << endl;
    }
    else
    {
        cout << "AUN NO CUMPLE EL MINIMO" << endl;
    }
    cout << "\n  Esta suite NO asigna nota." << endl;
    cout << "  La calificacion la asigna el preparador con la rubrica:" << endl;
    cout << "  resultado grupal + aporte individual evidenciado en Git." << endl;
    cout << "====================================================================" << endl;

    return 0;
}

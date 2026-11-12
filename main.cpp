#include <cstdio>
#include <iostream>
#include <string>
#include <utility>

#include "ChatLista.hpp"
#include "ListaMensajes.hpp"

namespace
{
void imprimirLista(const std::string& titulo, const ListaMensajes& mensajes)
{
    std::cout << titulo << " (" << mensajes.tamanio() << "): ";
    mensajes.recorrer([](const TextMessage& mensaje) {
        std::cout << mensaje.getId() << ":" << mensaje.getContent() << " | ";
    });
    std::cout << '\n';
}

void imprimirResultado(const std::string& operacion, bool resultado)
{
    std::cout << operacion << ": " << (resultado ? "correcto" : "no realizado") << '\n';
}
}

int main()
{
    std::cout << "1. Estado inicial\n";
    ListaMensajes mensajes;
    std::cout << "Vacia: " << (mensajes.vacia() ? "si" : "no")
              << ", tamanio: " << mensajes.tamanio()
              << ", primero nulo: " << (mensajes.primero() == nullptr ? "si" : "no")
              << ", ultimo nulo: " << (mensajes.ultimo() == nullptr ? "si" : "no") << "\n\n";

    std::cout << "2. Inserciones y duplicados\n";
    imprimirResultado("Agregar al final id 102",
                      mensajes.agregarAlFinal(TextMessage(102, "ana", "Segundo mensaje")));
    imprimirResultado("Agregar al inicio id 101",
                      mensajes.agregarAlInicio(TextMessage(101, "luis", "Primer mensaje")));
    imprimirResultado("Agregar al final id 103",
                      mensajes.agregarAlFinal(TextMessage(103, "eva", "Tercer mensaje")));
    imprimirResultado("Insertar id 104 despues de 102",
                      mensajes.insertarDespuesDe(102, TextMessage(104, "omar", "Mensaje intermedio")));
    imprimirResultado("Rechazar id duplicado 102",
                      mensajes.agregarAlFinal(TextMessage(102, "ana", "Id repetido")));
    imprimirResultado("Rechazar id duplicado al insertar despues",
                      mensajes.insertarDespuesDe(101, TextMessage(102, "ana", "Otro id repetido")));
    imprimirResultado("Rechazar referencia inexistente 999",
                      mensajes.insertarDespuesDe(999, TextMessage(105, "ines", "Sin referencia")));
    imprimirLista("Orden actual", mensajes);

    const TextMessage* primero = mensajes.primero();
    const TextMessage* ultimo = mensajes.ultimo();
    std::cout << "Primero: " << (primero ? primero->getContent() : "ninguno")
              << ", ultimo: " << (ultimo ? ultimo->getContent() : "ninguno") << '\n';
    const TextMessage* encontrado = mensajes.buscarPorId(104);
    std::cout << "Buscar id 104: " << (encontrado ? encontrado->getContent() : "no encontrado")
              << ", buscar id 999: " << (mensajes.buscarPorId(999) ? "encontrado" : "no encontrado")
              << '\n';
    const ListaMensajes& mensajesConstantes = mensajes;
    const TextMessage* encontradoConstante = mensajesConstantes.buscarPorId(101);
    std::cout << "Busqueda const id 101: "
              << (encontradoConstante ? encontradoConstante->getContent() : "no encontrado") << "\n\n";

    std::cout << "3. Recorridos e identificadores\n";
    std::cout << "De inicio a fin: ";
    mensajes.recorrer([](const TextMessage& mensaje) {
        std::cout << mensaje.getId() << ' ';
    });
    std::cout << "\nDe fin a inicio: ";
    mensajes.recorrerInverso([](const TextMessage& mensaje) {
        std::cout << mensaje.getId() << ' ';
    });
    std::cout << "\nIds:";
    for (int id : mensajes.ids())
    {
        std::cout << ' ' << id;
    }
    std::cout << "\n\n";

    std::cout << "4. Mover al inicio\n";
    imprimirResultado("Mover id 103", mensajes.moverAlInicio(103));
    imprimirLista("Despues de mover", mensajes);
    imprimirResultado("Mover id 999", mensajes.moverAlInicio(999));
    const TextMessage* actualPrimero = mensajes.primero();
    imprimirResultado("Mover el primero actual",
                      actualPrimero != nullptr && mensajes.moverAlInicio(actualPrimero->getId()));
    imprimirLista("Orden final", mensajes);
    std::cout << '\n';

    std::cout << "5. Eliminaciones en cabeza, medio y cola\n";
    ListaMensajes eliminaciones;
    eliminaciones.agregarAlFinal(TextMessage(201, "a", "Cabeza"));
    eliminaciones.agregarAlFinal(TextMessage(202, "b", "Medio"));
    eliminaciones.agregarAlFinal(TextMessage(203, "c", "Medio final"));
    eliminaciones.agregarAlFinal(TextMessage(204, "d", "Cola"));
    imprimirResultado("Eliminar cabeza id 201", eliminaciones.eliminarPorId(201));
    imprimirResultado("Eliminar medio id 203", eliminaciones.eliminarPorId(203));
    imprimirResultado("Eliminar cola id 204", eliminaciones.eliminarPorId(204));
    imprimirResultado("Rechazar id inexistente 999", eliminaciones.eliminarPorId(999));
    imprimirLista("Queda", eliminaciones);
    imprimirResultado("Eliminar el ultimo nodo id 202", eliminaciones.eliminarPorId(202));
    std::cout << "Vacia despues de eliminar todo: "
              << (eliminaciones.vacia() ? "si" : "no") << "\n\n";

    std::cout << "6. Copia y movimiento\n";
    ListaMensajes copia(mensajes);
    imprimirLista("Copia por constructor", copia);
    if (TextMessage* mensajeCopiado = copia.buscarPorId(102))
    {
        mensajeCopiado->setContent("Contenido cambiado solo en la copia");
    }
    std::cout << "Original id 102: " << mensajes.buscarPorId(102)->getContent()
              << "\nCopia id 102: " << copia.buscarPorId(102)->getContent() << '\n';

    ListaMensajes asignada;
    asignada = mensajes;
    imprimirLista("Copia por asignacion", asignada);

    ListaMensajes movida(std::move(copia));
    imprimirLista("Destino del movimiento por constructor", movida);
    std::cout << "Origen del movimiento vacio: " << (copia.vacia() ? "si" : "no") << '\n';

    ListaMensajes destinoMovimiento;
    destinoMovimiento.agregarAlFinal(TextMessage(301, "z", "Destino previo"));
    destinoMovimiento = std::move(asignada);
    imprimirLista("Destino del movimiento por asignacion", destinoMovimiento);
    imprimirLista("Origen de la asignacion por movimiento", asignada);
    std::cout << '\n';

    std::cout << "7. Persistencia CSV y limpieza\n";
    const std::string rutaCSV = "demo_historial.csv";
    ListaMensajes persistencia;
    persistencia.agregarAlFinal(TextMessage(401, "ana", "Hola, equipo"));
    persistencia.agregarAlFinal(TextMessage(402, "luis", "Listo para la practica"));
    imprimirResultado("Guardar CSV", persistencia.guardarCSV(rutaCSV));

    ListaMensajes cargada;
    imprimirResultado("Cargar CSV", cargada.cargarCSV(rutaCSV));
    imprimirLista("Mensajes cargados", cargada);
    std::cout << "Rechazar ruta inexistente: "
              << (cargada.cargarCSV("ruta_inexistente/demo.csv") ? "cargada" : "rechazada")
              << '\n';
    cargada.limpiar();
    std::cout << "Vacia despues de limpiar: " << (cargada.vacia() ? "si" : "no")
              << ", tamanio: " << cargada.tamanio() << '\n';

    std::cout << "\n8. ChatLista: envio, validaciones e historial\n";
    ChatLista chat(501, "Equipo PR2", {"ana", "luis"});
    std::cout << "Resumen inicial: " << chat.resumen()
              << ", participantes: " << chat.getParticipantCount() << '\n';
    imprimirResultado("Enviar mensaje de ana",
                      chat.enviarMensaje(TextMessage(501, "ana", "Hola, equipo")));
    imprimirResultado("Enviar mensaje de luis",
                      chat.enviarMensaje(TextMessage(502, "luis", "Ya revise la lista")));
    imprimirResultado("Rechazar remitente que no participa",
                      chat.enviarMensaje(TextMessage(503, "eva", "No estoy en el chat")));
    imprimirResultado("Rechazar id duplicado",
                      chat.enviarMensaje(TextMessage(501, "ana", "Id repetido")));

    TextMessage mensajeNoPendiente(504, "ana", "Mensaje previamente enviado");
    mensajeNoPendiente.markSent(chat.getId());
    imprimirResultado("Rechazar mensaje que no esta Pending",
                      chat.enviarMensaje(mensajeNoPendiente));

    ListaMensajes& historialEditable = chat.getHistorial();
    TextMessage mensajeHistorial1(601, "ana", "Mensaje fijado");
    TextMessage mensajeHistorial2(602, "luis", "Mensaje para eliminar");
    mensajeHistorial1.markSent(chat.getId());
    mensajeHistorial2.markSent(chat.getId());
    imprimirResultado("Agregar mensaje al historial por acceso no const",
                      historialEditable.agregarAlFinal(mensajeHistorial1));
    imprimirResultado("Agregar segundo mensaje al historial",
                      historialEditable.agregarAlFinal(mensajeHistorial2));
    std::cout << "Resumen con mensajes: " << chat.resumen()
              << ", cantidad: " << chat.cantidadMensajes() << '\n';
    imprimirLista("Historial por acceso no const", historialEditable);

    const ChatLista& chatSoloLectura = chat;
    const ListaMensajes& historialSoloLectura = chatSoloLectura.getHistorial();
    const TextMessage* mensajeEnviado = historialSoloLectura.buscarPorId(601);
    std::cout << "Historial por acceso const, id 601: "
              << (mensajeEnviado ? mensajeEnviado->getContent() : "no encontrado")
              << ", estado: " << (mensajeEnviado ? mensajeEnviado->getStatusText() : "desconocido")
              << ", chat id: " << (mensajeEnviado ? mensajeEnviado->getChatId() : -1) << '\n';

    imprimirResultado("Fijar mensaje existente id 601", chat.fijarMensaje(601));
    imprimirResultado("Fijar mensaje inexistente id 999", chat.fijarMensaje(999));
    imprimirLista("Historial despues de fijar", historialSoloLectura);
    imprimirResultado("Eliminar mensaje id 602", chat.eliminarMensaje(602));
    imprimirResultado("Rechazar eliminacion del id 602", chat.eliminarMensaje(602));
    std::cout << "Resumen final: " << chat.resumen()
              << ", cantidad: " << chat.cantidadMensajes() << '\n';
    imprimirLista("Historial final", chat.getHistorial());

    if (std::remove(rutaCSV.c_str()) != 0)
    {
        std::cerr << "No se pudo eliminar el archivo temporal " << rutaCSV << '\n';
        return 1;
    }

    
    return 0;
}

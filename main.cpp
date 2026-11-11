#include <iostream>

#include "ListaMensajes.hpp"

int main()
{
    ListaMensajes mensajes;

    TextMessage mensaje1(1, "user1", "Hola");
    TextMessage mensaje2(2, "user2", "¿Cómo estás?");
    TextMessage mensaje3(3, "user3", "¡Bienvenido!");

    mensajes.agregarAlInicio(mensaje1);
    mensajes.agregarAlFinal(mensaje2);  
    mensajes.agregarAlInicio(mensaje3);

    

}

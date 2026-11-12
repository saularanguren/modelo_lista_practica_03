# Práctica Evaluada 03 — Modelo A: Lista Doblemente Enlazada

[![MIT](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](LICENSE)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)

**Asignatura:** Programación 2 (PR2)

**Estructura Asignada:** Lista doblemente enlazada de mensajes (`TextMessage`)

**Modelo:** A

## 1. Integrantes del Grupo

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
   *Rol:* Documentación (`README.md`), QA, gestión de Git y demo (`main.cpp`)

## 2. Descripción del Proyecto

Este repositorio contiene la implementación del **Modelo A** para la Práctica Evaluada 03. Consiste en una estructura de datos lineal del tipo **Lista Doblemente Enlazada** destinada a gestionar un conjunto dinámico de objetos de clase `TextMessage`.

La lista soporta:

* Inserción al inicio, al final y después de un mensaje de referencia.

* Búsqueda eficiente y eliminación por ID único de mensaje.

* Recorridos en orden directo e inverso utilizando callbacks.

* Control de unicidad de IDs y semántica de movimiento/copia (Regla de los 5).

* Persistencia de mensajes en formato de archivos CSV.

* Integración con la clase contenedora de chats (`ChatLista`).

## 3. Instrucciones de Compilación y Ejecución

Para compilar y ejecutar las distintas partes de la práctica, asegúrate de estar dentro del directorio raíz del proyecto y utiliza la herramienta `make`:

* **Ejecutar la suite de pruebas unitarias (QA):**

  ```
  make test
  ```

  Compila el ejecutable `test_modelo` y evalúa el cumplimiento de las verificaciones automáticas de los Bloques 1 al 5.

* **Compilar y ejecutar la demo interactiva principal:**

  ```
  make main
  ```

  Compila el archivo `main.cpp` y ejecuta la demostración práctica del funcionamiento de la lista y el chat.

* **Limpiar archivos ejecutables y objetos temporales:**

  ```
  make clean
  ```

  Elimina los binarios generados (`.o`, `main`, `test_modelo` y archivos `.csv` temporales).

## 4. Reparto de Roles y Control de Versiones (Git)

El trabajo fue distribuido organizadamente en el equipo mediante el uso de ramas (`features`) independientes para evitar conflictos de código:

* **Estructura de Datos (`ListaMensajes`) y Apoyo en QA:**
  *Integrantes:* Saúl Aranguren, Diego García, Jeremías Ortega.
  *Rama:* `feature/estructura-listamensajes`
  *Responsabilidades:* Implementación de la lógica interna de nodos (`Nodo`), punteros dobles (`siguiente`/`anterior`), constructores de copia/movimiento, métodos de inserción, eliminación y recorridos. Adicionalmente, **Saúl Aranguren** y **Jeremías Ortega** colaboraron activamente en las pruebas de calidad (QA) y validación de casos borde de la estructura.

* **Integración con Mensajería (`ChatLista`):**
  *Integrantes:* Luis Paz, Mayre Rodríguez.
  *Rama:* `feature/integracion-chatlista`
  *Responsabilidades:* Conexión de `ListaMensajes` con `ChatLista`, validación de participantes en el envío/fijado de mensajes y persistencia CSV.

* **Documentación, QA y Main:**
  *Integrante:* Sebastián Olivares.
  *Rama:* `feature-sebastian` (o `feature/docs-main`)
  *Responsabilidades:* Configuración de infraestructura (`.gitignore`), creación de la documentación base (`README.md`), supervisión del flujo de Pull Requests, ejecución de QA y desarrollo de la demo en `main.cpp`.

## 5. Declaración sobre el uso de Inteligencia Artificial

En el desarrollo de este proyecto, el equipo empleó herramientas de Inteligencia Artificial de manera estratégica y complementaria. La IA se utilizó como un asistente consultivo para revisar detalles puntuales en los métodos de limpieza de memoria y en la persistencia de datos en formato CSV. Asimismo, sirvió de apoyo durante la depuración de errores de compilación complejos y en la estructuración de pruebas unitarias para validar de forma rigurosa la lectura, escritura y manejo de estados de la lista antes de fusionar los cambios finales en Git.

Queremos enfatizar que el diseño conceptual, la lógica de programación, el análisis de punteros y la comprensión integral de la solución fueron desarrollados y asumidos con total responsabilidad por los integrantes del equipo.

*Herramientas de IA consultadas:* **Gemini**, **DeepSeek** y **Claude**.




# Documentación

Este documento reúne toda la información técnica del proyecto, incluyendo una descripción general, la explicación detallada de cada método, y las instrucciones de compilación y ejecución.

---

## 1. Descripción General

Este proyecto implementa un historial de chat navegable para un sistema de mensajería en C++17, construido utilizando una **lista doblemente enlazada desde cero** sin utilizar contenedores estándar prohibidos como `std::list` o `std::deque`.

* **`ListaMensajes`**: Administra los nodos doblemente enlazados de mensajes (`TextMessage`). Permite inserciones al inicio y al final, inserción en posiciones específicas, búsquedas y eliminaciones por ID (en cabeza, medio y cola), recorridos bidireccionales, reubicación de elementos (`moverAlInicio`), gestión de memoria segura y persistencia mediante archivos CSV.
* **`ChatLista`**: Extiende la clase base `Chat` para integrar el historial. Se encarga de validar que el remitente sea un participante activo, evitar duplicados de ID, cambiar el estado de los mensajes al enviarlos y permitir operaciones como fijar o eliminar mensajes del chat.

---

## 2. Resumen de Métodos y su Implementación

### A. Estructura de Datos (`ListaMensajes`)

#### Métodos de Gestión y Estructura Base
* **`ListaMensajes()` (Constructor por defecto)**
  * *Qué hace:* Inicializa una lista vacía.
  * *Cómo se implementó:* Asigna `nullptr` a `cabeza` y `cola`, y establece el contador `cantidad` en `0`.
* **`vacia()` y `tamanio()`**
  * *Qué hace:* Consultan el estado actual de la lista.
  * *Cómo se implementó:* `vacia()` retorna `true` si `cabeza == nullptr`; `tamanio()` retorna el valor del atributo `cantidad`.
* **`limpiar()`**
  * *Qué hace:* Vacía la lista por completo y libera la memoria de todos los nodos.
  * *Cómo se implementó:* Itera desde la cabeza, desconectando y reseteando los punteros mediante `std::shared_ptr` para evitar fugas de memoria, hasta restablecer la estructura.

#### Métodos de Inserción
* **`agregarAlFinal(const TextMessage& mensaje)`**
  * *Qué hace:* Inserta un nuevo mensaje al final de la lista.
  * *Cómo se implementó:* Valida que no exista un ID duplicado recorriendo la lista. Crea un nodo inteligente (`std::make_shared`), ajusta los enlaces bidireccionales con la antigua `cola` y actualiza la referencia final.
* **`agregarAlInicio(const TextMessage& mensaje)`**
  * *Qué hace:* Inserta un nuevo mensaje en la primera posición.
  * *Cómo se implementó:* Comprueba la unicidad del ID, crea el nuevo nodo y enruta sus punteros hacia la `cabeza` actual, reasignando el inicio de la lista.
* **`insertarDespuesDe(int idReferencia, const TextMessage& mensaje)`**
  * *Qué hace:* Inserta un mensaje inmediatamente después de un nodo de referencia por su ID.
  * *Cómo se implementó:* Busca el nodo que coincide con `idReferencia` validando que no haya IDs duplicados, y reajusta los punteros adyacentes (`siguiente` y `anterior`) para intercalar el nuevo elemento.

#### Métodos de Búsqueda y Eliminación
* **`buscarPorId(int id)` (Versiones `const` y no `const`)**
  * *Qué hace:* Retorna un apuntador directo al objeto `TextMessage` con el ID solicitado.
  * *Cómo se implementó:* Recorre secuencialmente la lista y devuelve la dirección del campo `dato` al coincidir, o `nullptr` si no existe.
* **`eliminarPorId(int id)`**
  * *Qué hace:* Localiza un mensaje por su ID, lo desconecta y libera sus recursos.
  * *Cómo se implementó:* Ubica el nodo, actualiza los punteros del nodo anterior y posterior para omitirlo (manejando cabeza, medio y cola), y resetea las referencias inteligentes.

#### Métodos de Navegación y Manipulación Avanzada
* **`primero()` y `ultimo()`**
  * *Qué hace:* Retornan el primer o último mensaje del historial sin modificarlo.
  * *Cómo se implementó:* Retornan el campo `dato` de `cabeza` o `cola` evaluando si la lista está vacía.
* **`moverAlInicio(int id)`**
  * *Qué hace:* Reubica un mensaje existente al inicio de la lista (utilizado al fijar mensajes).
  * *Cómo se implementó:* Busca el nodo, reajusta los enlaces de sus vecinos para cerrar el espacio y lo reconecta al inicio actualizando la `cabeza`.
* **`recorrer` y `recorrerInverso`**
  * *Qué hace:* Aplican una función (`std::function`) a cada elemento en sentido directo o inverso.
  * *Cómo se implementó:* Iteran usando los punteros `siguiente` o los bloqueos de los `weak_ptr` (`anterior.lock()`).
* **`ids()`**
  * *Qué hace:* Retorna un vector con los IDs de los mensajes en orden.
  * *Cómo se implementó:* Recorre la lista acumulando los identificadores en un `std::vector<int>`.

#### Métodos de Persistencia (CSV)
* **`guardarCSV(const std::string& ruta)`**
  * *Qué hace:* Exporta el historial de mensajes a un archivo CSV.
  * *Cómo se implementó:* Abre un flujo `std::ofstream`, recorre la lista invocando `toCSV()` de cada mensaje y escribe cada línea en el archivo.
* **`cargarCSV(const std::string& ruta)`**
  * *Qué hace:* Lee y reconstruye el historial desde un archivo CSV.
  * *Cómo se implementó:* Limpia el historial actual, lee el archivo línea por línea mediante `std::ifstream`, procesa los campos y reinserta los objetos deserializados.

---

### B. Sistema de Chat e Integración (`ChatLista`)

* **`enviarMensaje(TextMessage mensaje)`**
  * *Qué hace:* Valida las reglas de negocio e incorpora un mensaje al historial.
  * *Cómo se implementó:* Comprueba que el remitente pertenezca al chat (`isParticipant`), que el ID no esté duplicado y que su estado sea `Pending`. Si es válido, marca el mensaje como `Sent` y lo agrega al final.
* **`fijarMensaje(int id)`**
  * *Qué hace:* Mueve un mensaje al inicio del historial del chat.
  * *Cómo se implementó:* Valida su existencia con `buscarPorId(id)` y delega la reubicación a `moverAlInicio(id)`.
* **`eliminarMensaje(int id)`**
  * *Qué hace:* Remueve un mensaje del chat.
  * *Cómo se implementó:* Utiliza internamente `historial.eliminarPorId(id)`.
* **`getHistorial()`, `cantidadMensajes()` y `resumen()`**
  * *Qué hace:* Proveen acceso al historial, el conteo de elementos y un texto descriptivo.
  * *Cómo se implementó:* Retornan referencias al historial, el tamaño actual y concatenan el título del chat con el número de mensajes.

---

## 3. Instrucciones de Uso y Compilación

El proyecto cuenta con un `Makefile` configurado para compilar bajo el estándar **C++17** con directivas estrictas (`-Wall -Wextra -Wpedantic`).

### Comandos Disponibles:

1. **Compilar y ejecutar la demo principal (`main.cpp`):**
   ```bash
   make main
   ```
   * *Qué hace:* Compila los archivos fuente de la estructura (`ListaMensajes.cpp`), de la integración (`ChatLista.cpp`), los componentes del núcleo y la demo, generando el ejecutable `main` y ejecutándolo de inmediato en consola.

2. **Ejecutar la suite de pruebas automáticas (`test_modelo.cpp`):**
   ```bash
   make test
   ```
   * *Qué hace:* Compila y ejecuta el conjunto de pruebas unitarias (`tests/test_modelo.cpp`), validando los 5 bloques del sistema e imprimiendo si el código **`CUMPLE EL MINIMO`**.

3. **Limpiar archivos temporales y binarios:**
   ```bash
   make clean
   ```
   * *Qué hace:* Elimina los ejecutables generados (`main`, `test_modelo`), archivos objeto (`*.o`) y archivos CSV temporales.




















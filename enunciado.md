# Práctica Evaluada 03 — Modelo A: Lista doblemente enlazada

**Asignatura:** Programación 2 (PR2) — Sección 02  
**Modalidad:** grupos de 3 o 4 integrantes  
**Lenguaje:** C++17, sin librerías externas  
**Duración:** miércoles 11 de noviembre de 2026, 12:00 p.m. – 2:00 p.m. (90 min de práctica + 30 min de revisión) + trabajo en casa  
**Puntaje:** 20 puntos (12 en clase + 8 en casa)  
**Estructura asignada:** lista doblemente enlazada de mensajes

> [!IMPORTANT]
> **Medio de entrega:** correo electrónico a **`jdanieldp99@gmail.com`**.
> **No se adjuntan archivos `.cpp`.** El mensaje debe incluir **la captura de `make test` funcionando durante la clase** y **el enlace del repositorio** de GitHub/GitLab. Ver la plantilla completa en la **Sección 10**.
>
> **Fecha límite:** **miércoles 11 de noviembre de 2026, 11:59 p.m.** (el mismo día de la práctica).
> **Retardo:** **−5 puntos** sobre la nota final.
> **Puntos extra:** quienes entreguen el **resultado completo durante el tiempo de clase** recibirán puntos extra **a criterio del preparador**.

---

## 1. Contexto

En la Evaluación 1 modelaron un sistema de mensajería con usuarios, chats, mensajes y estados (`Pending → Sent → Delivered → Opened`). Ahora deben extender ese sistema con una nueva funcionalidad: un **historial de chat navegable**, capaz de recorrer los mensajes hacia adelante y hacia atrás, fijar un mensaje al inicio, insertar en una posición y eliminar mensajes.

La regla central es que el historial debe implementarse **desde cero** como una **lista doblemente enlazada**. No se permite usar `std::list` ni `std::deque` para el almacenamiento. El núcleo de mensajería (`User`, `TextMessage`, `Chat`) es una **adaptación mínima de la carpeta original de la Evaluación 1** y ya está resuelto en la carpeta `nucleo/` incluida en este modelo.

---

## 2. Qué debe implementar

### A. `ListaMensajes` (`ListaMensajes.hpp` / `.cpp`)

Lista doblemente enlazada de `TextMessage`. Cada nodo debe tener:

- El `TextMessage`.
- Un apuntador al siguiente nodo.
- Un apuntador al nodo anterior.

Operaciones obligatorias:

| Método | Comportamiento |
| :--- | :--- |
| `ListaMensajes()` | Lista vacía: `vacia() == true`, `tamanio() == 0`, `primero()` y `ultimo()` retornan `nullptr`. |
| `agregarAlFinal(const TextMessage&)` | Inserta al final. Retorna `false` si ya existe un mensaje con el mismo `id`. |
| `agregarAlInicio(const TextMessage&)` | Inserta al inicio. Retorna `false` si el `id` está duplicado. |
| `insertarDespuesDe(int idReferencia, const TextMessage&)` | Inserta después del mensaje con `idReferencia`. Retorna `false` si la referencia no existe o el nuevo `id` está duplicado. |
| `eliminarPorId(int id)` | Desconecta y elimina el nodo. Retorna `false` si el `id` no existe. Debe funcionar en cabeza, medio y cola. |
| `buscarPorId(int id)` | Retorna apuntador al mensaje o `nullptr`. Debe existir versión `const` y no `const`. |
| `primero()` / `ultimo()` | Retornan el primer/último mensaje o `nullptr`. |
| `moverAlInicio(int id)` | Mueve el nodo al inicio. Retorna `false` si no existe. Si ya es el primero, retorna `true` sin cambios. |
| `recorrer(funcion)` | Ejecuta la función por cada mensaje, de cabeza a cola. |
| `recorrerInverso(funcion)` | Ejecuta la función de cola a cabeza. |
| `ids()` | Retorna los ids en orden de recorrido. |
| `limpiar()` | Deja la lista vacía y libera los nodos. |
| `guardarCSV(ruta)` | Guarda una línea por mensaje, en orden. Retorna `false` si no puede abrir el archivo. |
| `cargarCSV(ruta)` | Limpia la lista y carga los mensajes del archivo. Retorna `false` si no puede abrir el archivo. |

**Copia, movimiento y liberación (regla de tres/cinco):** la lista debe poder copiarse (copia profunda) y moverse (el origen queda vacío) sin fugas ni dobles liberaciones.

### B. `ChatLista` (`ChatLista.hpp` / `.cpp`)

Hereda de `Chat` y usa una `ListaMensajes` como historial.

| Método | Comportamiento |
| :--- | :--- |
| `enviarMensaje(TextMessage)` | Valida que el remitente participe en el chat, que el `id` no exista en el historial y que el mensaje esté `Pending`. Luego llama a `markSent(getId())` y lo agrega al final. Retorna `false` si alguna validación falla. |
| `fijarMensaje(int id)` | Mueve el mensaje al inicio del historial. Retorna `false` si no existe. |
| `eliminarMensaje(int id)` | Elimina el mensaje del historial. Retorna `false` si no existe. |
| `getHistorial()` | Retorna el historial (versión `const` y no `const`). |
| `cantidadMensajes()` | Retorna el tamaño del historial. |
| `resumen()` | Retorna un texto breve, por ejemplo `"Chat Equipo PR2 (3 mensajes)"`. |

---

## 3. Reglas técnicas

- **Memoria:** pueden usar apuntadores inteligentes (`std::shared_ptr`, `std::unique_ptr`, `std::weak_ptr`) o apuntadores normales con `new` y `delete`. Si usan apuntadores normales, deben liberar todos los nodos y evitar dobles liberaciones. La ausencia de fugas es parte de la evaluación.
- **No usar** `std::list` ni `std::deque` para la estructura evaluada.
- Sí se permite `std::vector` para apoyo, participantes o resultados.
- Nada de atributos públicos en las clases evaluadas.
- Una clase por par `.hpp` / `.cpp`.
- El código debe compilar con `make test` sin errores y, preferiblemente, sin advertencias con `-Wall -Wextra -Wpedantic`.
- Comentarios en el código sin acentos.
- No modifiquen los archivos de `nucleo/`: ya están resueltos.

---

## 4. Formato CSV

Cada línea representa un mensaje, en orden:

```text
id,"remitente","contenido",Estado
```

Ejemplo:

```text
1,"u1","Hola equipo",sent
2,"u2","Listo para la practica",pending
```

El estado se escribe como `Pending`, `Sent`, `Delivered` o `Opened`. El parser `CsvUtils::splitCSV` del núcleo respeta las comillas.

---

## 5. Estructura de la carpeta

Este modelo es **independiente**: todo lo necesario está dentro de `modelo_a_lista/`.

```text
modelo_a_lista/
├── enunciado.md
├── Makefile
├── main.cpp                  ← demo propia (evaluada en A5)
├── ListaMensajes.hpp / .cpp  ← completar
├── ChatLista.hpp / .cpp      ← completar
├── nucleo/                   ← código dado (no evaluado)
│   ├── User.hpp / .cpp
│   ├── MessageStatus.hpp / .cpp
│   ├── TextMessage.hpp / .cpp
│   ├── Chat.hpp / .cpp
│   └── CSV.hpp
└── tests/test_modelo.cpp     ← suite automática
```

Los archivos `.hpp` y `.cpp` de `ListaMensajes` y `ChatLista`, y `main.cpp`, incluyen al inicio el bloque de **datos del grupo**. Deben completarlo.

---

## 6. Inicio rápido y verificación mínima

```bash
cd modelo_a_lista

make test        # verifica requisitos mínimos (NO asigna nota)
make main        # compila y ejecuta tu demo (main.cpp)
make clean
```

La suite `tests/test_modelo.cpp` **NO asigna nota**. Solo verifica si el esqueleto ya cumple los requisitos mínimos:

| Bloque | Qué verifica |
| :--- | :--- |
| 1. Estructura desde cero | Nodos, enlaces, inserciones y recorridos |
| 2. Operaciones núcleo | Búsquedas, eliminaciones y operaciones propias del modelo |
| 3. Integración con mensajería | Uso real de la estructura dentro del chat |
| 4. Casos borde y robustez | Estructura vacía, ids inexistentes, copia y movimiento |
| 5. Persistencia CSV | Guardar y cargar conservando orden y datos |

Al final imprime `CUMPLE EL MINIMO` o `AÚN NO CUMPLE EL MINIMO` con el número de verificaciones superadas. La nota la asigna el preparador con la rúbrica.

**`main.cpp` es una plantilla que ustedes deben completar.** No lo evalúa la suite: forma parte de la rúbrica (A5) como demo propia del grupo.

---

## 7. Reparto del trabajo (grupos de 3 o 4)

La práctica está diseñada para que **no alcance con que una sola persona programe todo**. Cada integrante debe tener una responsabilidad verificable en Git.

### Grupos de 4

| Rol | Responsabilidad | Evidencia en Git |
| :--- | :--- | :--- |
| **Estructura** | Nodos, enlaces, inserciones/eliminaciones, copia y liberación (regla de tres/cinco), recorridos | Rama `feature/estructura-<nombre>` y commits de los `.cpp` de la estructura |
| **Integración** | `ChatLista`, validaciones de participantes, estados y casos de uso | Rama `feature/integracion-<nombre>` y PR con revisión |
| **Pruebas y persistencia** | Casos borde, CSV, ejecución de `make test`, reporte de fallos | Rama `feature/tests-<nombre>` y comentarios en issues |
| **Main, documentación y QA** | `main.cpp`, README, `.gitignore`, tablero de issues, revisión final | Rama `feature/docs-<nombre>`, PR final y tag |

### Grupos de 3

| Rol | Responsabilidad |
| :--- | :--- |
| **Estructura** | Nodos, enlaces, operaciones, copia y liberación |
| **Integración + persistencia** | `ChatLista`, validaciones y CSV |
| **Pruebas + main + docs + Git** | Casos borde, demo, README, issues, PRs y tag |

> El rol no es excluyente: todos deben entender todo. La participación de cada integrante se evidencia en el historial de Git y en la observación durante la clase.

---

## 8. Cronograma de la sesión

**Miércoles 11 de noviembre de 2026**

| Hora | Actividad |
| :--- | :--- |
| **12:00 – 12:10** | Formar grupos, asignar modelo, crear repositorio y tablero de issues |
| **12:10 – 12:20** | Leer el enunciado, acordar el diseño de nodos y firmar los headers |
| **12:20 – 1:05** | Implementar bloques 1-2 de la suite (estructura y operaciones núcleo) |
| **1:05 – 1:25** | Integrar con el chat (bloque 3) y ejecutar `make test` |
| **1:25 – 1:30** | Commit/PR de cierre, captura del resultado y checkpoint Git |
| **1:30 – 2:00** | Revisión del avance, captura de `make test` y `make main` y cierre de la entrega de clase |

Al terminar la clase deben estar resueltos, como mínimo, los **12 primeros puntos**. El resto (casos borde, persistencia y Git colaborativo) queda como **entrega de casa** desde las 2:00 p.m. hasta las **11:59 p.m. del mismo día**.

> **Puntos extra:** los grupos que entreguen el **resultado completo durante el tiempo de clase** recibirán puntos extra **a criterio del preparador**.

---

## 9. Git/GitHub obligatorio

Cada grupo debe entregar un repositorio con:

1. `README.md` con integrantes, modelo asignado, instrucciones de compilación, uso de IA y reparto de roles.
2. `.gitignore` que excluya `build/`, `*.o`, `*.exe`, binarios, archivos de prueba y temporales.
3. Una rama por integrante y commits con mensajes claros.
4. Al menos **2 Pull Requests** revisados por otro integrante y fusionados a `main`.
5. Un tag `v1.0-entrega` al final.
6. Enlace del repositorio en la entrega.

---

## 10. Rúbrica y entrega

La evaluación se distribuye así:

| Bloque | Puntos | Momento |
| :--- | ---: | :--- |
| A1. Estructura desde cero | 4.0 | En clase |
| A2. Operaciones núcleo | 3.0 | En clase |
| A3. Integración con mensajería | 3.0 | En clase |
| A4. Checkpoint Git | 1.0 | En clase |
| A5. Demo propia (`main.cpp`) | 1.0 | En clase |
| B1. Casos borde y robustez | 3.0 | En casa |
| B2. Persistencia CSV | 2.0 | En casa |
| B3. Git colaborativo y documentación | 3.0 | En casa |
| **Total** | **20.0** | |

La nota es **grupal** y luego se multiplica por el **factor individual** de la rúbrica, calculado con la participación real en Git y la observación durante la clase.

### 10.1. Qué se entrega y cómo

> [!IMPORTANT]
> **No se envían archivos `.cpp` adjuntos.** La entrega es un **mensaje por correo electrónico** a **`jdanieldp99@gmail.com`** con:
>
> 1. **Captura de pantalla** de `make test` y `make main` funcionando **durante la clase**, donde se vean el resultado (`CUMPLE` / `AÚN NO CUMPLE`), la terminal y la fecha/hora.
> 2. **Enlace del repositorio** de GitHub/GitLab (público o con acceso aceptado para el preparador).
> 3. **Nombres, cédulas y roles** de los integrantes.
> 4. **Modelo asignado:** A (lista doblemente enlazada).
> 5. **Resultado de `make test`:** `CUMPLE EL MINIMO` o `AÚN NO CUMPLE EL MINIMO`, indicando cuántas verificaciones se superaron.
> 6. **Herramientas de IA** utilizadas y para qué.

La captura de la clase es la evidencia del **checkpoint de 12 pts**. El repositorio es la evidencia del trabajo completo y de los **8 pts restantes**.

### 10.2. Formato del mensaje

**Asunto:**

```text
[PR2-B2026] Práctica 03 - Modelo A - <Apellido1, Apellido2, ...> - C.I. <V-XXXXXXXX>
```

**Cuerpo:**

```text
Profesor Jesús Díaz y equipo de preparaduría,

Entrego la Práctica Evaluada 03 correspondiente al Modelo A (lista doblemente enlazada).

Datos del grupo:
- Integrante 1: <Nombre y Apellido> - C.I. <V-XXXXXXXX> - Rol: <rol>
- Integrante 2: <Nombre y Apellido> - C.I. <V-XXXXXXXX> - Rol: <rol>
- Integrante 3: <Nombre y Apellido> - C.I. <V-XXXXXXXX> - Rol: <rol>
- Integrante 4 (si aplica): <Nombre y Apellido> - C.I. <V-XXXXXXXX> - Rol: <rol>

Enlace del repositorio:
<https://github.com/usuario/repositorio>

Evidencia:
- Captura de make test durante la clase: adjunta al correo.
- Resultado de make test: <CUMPLE EL MINIMO / AUN NO CUMPLE EL MINIMO> — <X>/<Y> verificaciones.
- Demo propia: `main.cpp` compila y se ejecuta con `make main`.
- Tag de entrega: v1.0-entrega.

Herramientas de IA utilizadas:
<ninguna / ChatGPT / Claude / Copilot / otra> — uso: <para qué>.

Quedo atento a cualquier observación.
```

### 10.3. Fechas y penalización

- **Fecha límite final:** **miércoles 11 de noviembre de 2026, 11:59 p.m.** (el mismo día de la práctica).
- **Retardo:** **−5 puntos** sobre la nota final.
- **Puntos extra:** quienes entreguen el **resultado completo durante el tiempo de clase** recibirán puntos extra **a criterio del preparador**.
- Si el repositorio no es accesible o el enlace está roto, la entrega se considera **no recibida** hasta que se corrija.
- El código debe estar **en el repositorio**, no en el correo. No se aceptan `.cpp`, `.zip`, `.exe` ni `.o` adjuntos.

---

## 11. Uso de inteligencia artificial

Se permite usar asistentes de IA como apoyo (ChatGPT, Claude, Copilot, etc.), pero:

- Deben declararlo en el `README.md` indicando **qué herramienta** usaron y **para qué**.
- Son responsables de todo el código entregado: deben poder explicar cada clase, cada método y cada decisión.
- Si un integrante no participó en el repositorio ni durante la clase, se aplica el factor individual de la rúbrica.
- No se permite entregar código generado sin comprenderlo ni adaptarlo al modelo asignado.

---

## 12. Checklist rápido

- [ ] La lista funciona vacía, con un nodo y con varios nodos.
- [ ] `agregarAlFinal`, `agregarAlInicio` e `insertarDespuesDe` respetan el orden.
- [ ] `eliminarPorId` funciona en cabeza, medio y cola.
- [ ] `recorrer` y `recorrerInverso` visitan todos los nodos.
- [ ] `moverAlInicio` no rompe los enlaces.
- [ ] La copia es profunda y el movimiento deja el origen vacío.
- [ ] `ChatLista` valida participante, duplicados y estado.
- [ ] El CSV conserva orden y contenido.
- [ ] No hay `std::list` ni `std::deque`; la memoria se libera correctamente.
- [ ] El repositorio tiene ramas, PRs, README, `.gitignore` y tag.

---

*Modelo A de la Práctica Evaluada 03 — PR2 Sección 02, ULA.*

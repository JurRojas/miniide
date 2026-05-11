# Mini IDE - Intérprete de Notación Prefija y Postfija

##  Descripción General

Este proyecto implementa un **Mini IDE** (Integrated Development Environment) con un intérprete completo para evaluar expresiones en **notación prefija** y **postfija**. El sistema utiliza estructuras de datos manuales (sin librerías estándar de contenedores) como se requiere para la materia de **Algoritmos y Estructuras de Datos** en la UPIIT.

---

##  Estructuras de Datos Implementadas Manualmente

### 1. **Pila (Stack)**
- Implementación con nodos enlazados
- Operaciones: `push()`, `pop()`, `peek()`, `isEmpty()`
- Usada para evaluar expresiones en notación prefija (recursivamente) y postfija
- Rastrea cada operación para la visualización en tiempo real

### 2. **Cola (Queue)**
- Implementación FIFO (First In, First Out)
- Operaciones: `enqueue()`, `dequeue()`, `isEmpty()`
- Almacena instrucciones de ejecución línea por línea desde el editor

### 3. **Lista Enlazada**
- Almacena las líneas del código fuente en el editor
- Cada nodo contiene el número de línea y el contenido

---

##  Características Principales

### Evaluación de Notación Prefija (Recursiva)
```
Ejemplo: + 5 3
Proceso:
  - Lee el operador +
  - Evalúa recursivamente el primer operando (5)
  - Evalúa recursivamente el segundo operando (3)
  - Retorna 5 + 3 = 8
  
Rastreo de Pila:
  Push: 5
  Push: 3
  Operation: + => 8
```

### Evaluación de Notación Postfija (Iterativa)
```
Ejemplo: 5 3 +
Proceso:
  1. Empuja 5 en la pila
  2. Empuja 3 en la pila
  3. Lee +, desapila 3 y 5, suma y empuja 8
  
Rastreo de Pila:
  Push: 5
  Push: 3
  Pop: 3
  Pop: 5
  Operation: + => 8
```

###  Variables
```
$x = 10
+ $x 5          (Prefija)  => 15
$x 5 +          (Postfija) => 15
```

###  Operaciones Soportadas
- **Suma**: `+`
- **Resta**: `-`
- **Multiplicación**: `*`
- **División**: `/` (con detección de división por cero)
- **Potencia**: `^`

###  Interfaz Visual Dividida en 3 Secciones
1. **CODE EDITOR**: Muestra todas las líneas de código ingresadas
2. **EXECUTION TRACE**: Rastrea cada operación de la pila (Push/Pop/Result)
3. **OUTPUT**: Muestra el resultado de la ejecución
4. **VARIABLES**: Muestra todas las variables definidas

---

##  Cómo Ejecutar

### Compilación
```bash
g++ -fdiagnostics-color=always -g proyecto_ide.cpp -o proyecto_ide.exe
```

### Ejecución
```bash
./proyecto_ide.exe
```

---

##  Ejemplos de Uso

### Ejemplo 1: Notación Prefija Básica
```
Opción: 1
Ingrese: + 5 3

Resultado: 8
Rastreo:
  Push: 5
  Push: 3
  Operation: + => 8
```

### Ejemplo 2: Expresión Prefija Compleja
```
Ingrese: + * 2 3 4
Equivalente a: (2 * 3) + 4 = 10

Rastreo:
  Push: 2
  Push: 3
  Operation: * => 6
  Push: 4
  Operation: + => 10
```

### Ejemplo 3: Variables
```
Opción: 1
Ingrese: $x = 15

Opción: 1
Ingrese: + $x 10

Resultado: 25
Variables: $x = 15
```

### Ejemplo 4: Notación Postfija
```
Opción: 3  (cambiar a POSTFIJA)
Opción: 1
Ingrese: 5 3 +

Resultado: 8
```

### Ejemplo 5: Expresión Postfija Compleja
```
Ingrese: 2 3 * 4 +
Equivalente a: (2 * 3) + 4 = 10

Rastreo:
  Push: 2
  Push: 3
  Pop: 3
  Pop: 2
  Operation: * => 6
  Push: 6
  Push: 4
  Pop: 4
  Pop: 6
  Operation: + => 10
```

---

##  Arquitectura de Clases

### `Node<T>`
Estructura genérica para crear nodos enlazados.

### `Stack<T>`
```cpp
void push(const T& value);      // Inserta en la pila
T pop();                          // Extrae de la pila
T peek() const;                   // Consulta el tope
bool isEmpty() const;             // Verifica si está vacía
```

### `Queue<T>`
```cpp
void enqueue(const T& value);    // Inserta en la cola
T dequeue();                      // Extrae de la cola
bool isEmpty() const;             // Verifica si está vacía
```

### `LinkedList`
Almacena líneas de código con número de línea.

### `ExecutionTracer`
Rastrea todas las operaciones de la pila y las imprime en formato visual.

### `Interpreter`
```cpp
double evaluatePrefix(const string& expr);    // Evalúa notación prefija
double evaluatePostfix(const string& expr);   // Evalúa notación postfija
bool executeLine(const string& line);         // Ejecuta una línea
```

### `Editor`
Administra las líneas de código usando `LinkedList` y la `Queue` de ejecución.

### `Visualizer`
Genera la interfaz visual dividida en 3 secciones.

---

##  Flujo de Ejecución

```
┌─────────────────┐
│   Usuario Elige │
│    Opción 2     │
│   (Ejecutar)    │
└────────┬────────┘
         │
         ▼
┌──────────────────────┐
│  Cola de Ejecución   │
│   (FIFO Queue)       │
└────────┬─────────────┘
         │ Dequeue
         ▼
┌──────────────────────┐
│  Interpreter         │
│  (Evalúa línea)      │
└────────┬─────────────┘
         │
         ▼
┌──────────────────────┐
│  Pila (Stack)        │
│  (Recursiva/Iterativa)
└────────┬─────────────┘
         │
         ▼
┌──────────────────────┐
│ ExecutionTracer      │
│ (Rastrea operaciones)
└────────┬─────────────┘
         │
         ▼
┌──────────────────────┐
│  Visualizer          │
│  (Muestra interfaz)  │
└──────────────────────┘
```

---

##  Requisitos Cumplidos

-  **Lista Enlazada**: Para almacenar líneas del código fuente
-  **Pila (Stack)**: Para evaluación de expresiones (recursiva para prefija)
-  **Cola (Queue)**: Para flujo de ejecución línea por línea
-  **Evaluación Prefija Recursiva**: Implementada con función recursiva
-  **Evaluación Postfija**: Implementada de forma iterativa
-  **Variables**: Soporte para asignación y uso de variables
-  **Interfaz Visual**: 3 secciones (Editor, Trace, Output) con caracteres ASCII
-  **Rastreo de Pila**: Muestra Push, Pop y Results en tiempo real
-  **Modularidad**: Separado en clases (Editor, Interpreter, Visualizer)

---

##  Notas Importantes

1. **Evaluación Recursiva de Prefija**: La función `evaluatePrefixRecursive()` implementa la pila de ejecución de forma natural mediante la recursión del stack de llamadas, cumpliendo con el requisito de "Pila Recursiva".

2. **Rastro Explícito**: Cada operación Push, Pop y Result se registra en `ExecutionTracer` y se muestra en la interfaz.

3. **Variables**: Se almacenan en un `map<string, double>` para fácil consulta y asignación.

4. **Manejo de Errores**: Se implementa validación de:
   - Expresiones inválidas
   - División por cero
   - Variables no definidas
   - Tokens inválidos

---

##  Licencia

Proyecto académico para UPIIT - Algoritmos y Estructuras de Datos

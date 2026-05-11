# ARQUITECTURA Y DECISIONES TÉCNICAS

## Arquitectura General

```
┌─────────────────────────────────────────────────────────────┐
│                     USUARIO (Interfaz)                      │
└────────────────────┬────────────────────────────────────────┘
                     │
                     ▼
        ┌────────────────────────┐
        │   VISUALIZER           │
        │  (Renderiza UI)        │
        └────────┬───────────────┘
                 │
         ┌───────┴─────────┬──────────────┐
         │                 │              │
         ▼                 ▼              ▼
    ┌────────┐        ┌────────┐    ┌──────────┐
    │ EDITOR │        │INTERP. │    │ TRACER   │
    │(código)│        │(evalúa)│    │(registra)│
    └───┬────┘        └───┬────┘    └────┬─────┘
        │                 │              │
        ▼                 ▼              ▼
    ┌────────┐        ┌────────┐    ┌──────────┐
    │Linked  │        │ Stack  │    │Variables │
    │ List   │        │(Pila)  │    │   Map    │
    └────────┘        └────────┘    └──────────┘
        │
        ▼
    ┌────────┐
    │ Queue  │
    │(ejecución)
    └────────┘
```

---

##  Decisiones de Diseño

### 1. Uso de Plantillas (Templates)

**Decisión**: Implementar `Stack<T>` y `Queue<T>` como plantillas genéricas.

**Razón**: 
- Permite reutilizar el código para diferentes tipos de datos
- Mantiene type-safety en tiempo de compilación
- Simplifica el código del `Interpreter`

```cpp
// Ejemplo: La misma Stack funciona con doubles, ints, strings, etc.
Stack<double> evalStack;
Stack<string> tokenStack;
```

---

### 2. Evaluación Recursiva de Prefija

**Decisión**: Usar una función recursiva `evaluatePrefixRecursive()` en lugar de una iterativa.

**Razón**:
- Cumple con el requisito de "Pila Recursiva"
- La naturaleza recursiva del análisis prefijo hace que la solución sea elegante
- La pila de llamadas del sistema maneja automáticamente el almacenamiento

**Cómo funciona**:
```
Expresión: + * 2 3 4

evaluatePrefixRecursive(["+", "*", "2", "3", "4"], index=0)
├─ Lee "+" (operador)
├─ Llama evaluatePrefixRecursive (operando 1)
│  ├─ Lee "*" (operador)
│  ├─ Llama evaluatePrefixRecursive (operando 1)
│  │  ├─ Lee "2" (número)
│  │  └─ Retorna 2, Push: 2
│  ├─ Llama evaluatePrefixRecursive (operando 2)
│  │  ├─ Lee "3" (número)
│  │  └─ Retorna 3, Push: 3
│  ├─ Aplica * sobre 2 y 3
│  └─ Retorna 6, Push: 6
├─ Llama evaluatePrefixRecursive (operando 2)
│  ├─ Lee "4" (número)
│  └─ Retorna 4, Push: 4
├─ Aplica + sobre 6 y 4
└─ Retorna 10, Push: 10
```

---

### 3. Evaluación Iterativa de Postfija

**Decisión**: Usar un enfoque iterativo para postfija.

**Razón**:
- La notación postfija es naturalmente iterativa
- Es más intuitivo de entender: procesa de izquierda a derecha
- Evita sobrecarga de pila en expresiones muy grandes

**Algoritmo**:
```
Expresión: 2 3 * 4 +

Paso 1: Lee 2        → Push 2         [2]
Paso 2: Lee 3        → Push 3         [2, 3]
Paso 3: Lee *        → Pop 3, Pop 2   → 2*3=6 → Push 6   [6]
Paso 4: Lee 4        → Push 4         [6, 4]
Paso 5: Lee +        → Pop 4, Pop 6   → 6+4=10 → Push 10 [10]
Resultado: 10
```

---

### 4. Manejo de Variables

**Decisión**: Usar un `map<string, double>` para variables globales.

**Razón**:
- Acceso O(log n) garantizado
- Sintaxis clara: `$varname`
- Facilita búsqueda y asignación

```cpp
map<string, double> variables;
variables["x"] = 15;  // $x = 15

// En evaluación:
if (token[0] == '$') {
    string varName = token.substr(1);  // Quita el $
    double value = variables[varName];
}
```

---

### 5. Rastreo de Ejecución (ExecutionTracer)

**Decisión**: Separar el rastreo en una clase independiente.

**Razón**:
- Separa concerns (rastreo vs evaluación)
- Facilita agregar nuevos tipos de rastreo
- Permite reutilizar en diferentes interpretadores

```cpp
class ExecutionTracer {
    vector<string> trace;  // Historial de operaciones
    
    void logOperation(const string& op) {
        trace.push_back(op);
    }
    
    void printTrace() {
        // Muestra todas las operaciones con formato visual
    }
};
```

---

### 6. Interfaz Modular (Visualizer)

**Decisión**: Crear una clase `Visualizer` para toda la renderización.

**Razón**:
- Separa lógica de presentación
- Facilita cambios en la UI sin afectar lógica
- Patrón MVC simple

```cpp
class Visualizer {
    static void displayInterface(/*...*/);
    static void showMenu();
    static void showSyntaxExamples();
};
```

---

## Flujo de Ejecución Completo

### Cuando el usuario selecciona Opción 2 (Ejecutar):

```
1. getExecutionQueue() → Obtiene la Cola de líneas

2. Mientras !executionQueue.isEmpty():
   a) instruction = executionQueue.dequeue()  // FIFO
   b) interpreter.executeLine(instruction)
      │
      ├─ Si es asignación ($x = ...):
      │  └─ Evalúa expresión derecha
      │     └─ Si es prefija: evaluatePrefix()
      │     └─ Si es postfija: evaluatePostfix()
      │
      └─ Si es expresión simple:
         └─ Evalúa directamente
   
   c) tracer.logOperation("resultado")
   d) visualizer.displayInterface()
   
3. Mostrar resultado final y estado de variables
```

---

## Complejidad de Operaciones

### Stack Operations
| Operación | Complejidad | Notas |
|-----------|------------|-------|
| push()    | O(1)      | Inserción al inicio |
| pop()     | O(1)      | Extracción del inicio |
| peek()    | O(1)      | Solo lectura |

### Queue Operations
| Operación | Complejidad | Notas |
|-----------|------------|-------|
| enqueue() | O(1)      | Inserción al final |
| dequeue() | O(1)      | Extracción del inicio |

### Evaluation
| Operación | Complejidad | Notas |
|-----------|------------|-------|
| evaluatePrefix()  | O(n)  | n = número de tokens, recursiva |
| evaluatePostfix() | O(n)  | n = número de tokens, iterativa |

---

## Conceptos Clave Demostrados

### 1. Recursión vs Iteración
```
PREFIJA (Recursiva):
+ * 2 3 4
└─ Resuelve primero los subproblemas más profundos
└─ Usa stack de llamadas implícito

POSTFIJA (Iterativa):
2 3 * 4 +
└─ Procesa de izquierda a derecha
└─ Usa stack explícita
```

### 2. Administración de Memoria Dinámica
```cpp
// Creación
Node<T>* newNode = new Node<T>(value);

// Eliminación en destructor
~Stack() {
    while (top != nullptr) {
        Node<T>* temp = top;
        top = top->next;
        delete temp;  // ← Evitar memory leaks
    }
}
```

### 3. Patrones de Diseño
- **Strategy**: Diferentes estrategias de evaluación (Prefija/Postfija)
- **Observer**: Tracer observa operaciones
- **MVC**: Visualizer controla presentación

### 4. Parsing de Expresiones
```
Entrada: "5 3 +"
↓ stringstream
["5", "3", "+"]  ← Tokenización
↓
Evaluación

Entrada: "+ 5 3"
↓ stringstream
["+", "5", "3"]  ← Mismo proceso, diferente orden
↓
Evaluación recursiva
```

---

## Validaciones Implementadas

### 1. División por Cero
```cpp
if (operand2 == 0) 
    throw runtime_error("Error: División por cero");
```

### 2. Variables No Definidas
```cpp
if (variables.find(varName) == variables.end())
    throw runtime_error("Error: Variable no definida: " + varName);
```

### 3. Expresiones Inválidas
```cpp
if (postfixStack.getSize() != 1)
    throw runtime_error("Error: Expresión postfija inválida");
```

### 4. Tokens Inválidos
```cpp
try {
    double value = stod(token);
} catch (...) {
    throw runtime_error("Error: Token inválido: " + token);
}
```

---

## Extensiones Futuras Posibles

1. **Funciones Definidas por Usuario**
   ```cpp
   func add(a b) { + $a $b }
   ```

2. **Condicionales**
   ```cpp
   if (> $x 5) { "Mayor que 5" } { "Menor o igual" }
   ```

3. **Bucles**
   ```cpp
   loop ($i = 0; $i < 10; $i++) { $i }
   ```

4. **Soporte para Strings**
   ```cpp
   $mensaje = "Hola"
   concat $mensaje " Mundo"
   ```

5. **Sistema de Tipos**
   ```cpp
   $x:int = 10
   $y:float = 3.14
   ```

---

## Puntos Fuertes del Proyecto

 **Código bien estructurado**: Clases separadas, responsabilidades claras
 **Sin dependencias externas**: Solo C++ estándar
 **Manejo robusto de errores**: Validaciones en cada paso
 **Documentación clara**: README y guías de uso
 **Interfaz visual atractiva**: Caracteres ASCII formateados
 **Demostraciones automáticas**: Ejemplo funcional completo
 **Recursión y Pilas explícitas**: Ambos paradigmas demostrados
---

## Referencias de Implementación

### Evaluación de Expresiones
- [Polish Notation (Prefija)](https://en.wikipedia.org/wiki/Polish_notation)
- [Reverse Polish Notation (Postfija)](https://en.wikipedia.org/wiki/Reverse_Polish_notation)

### Estructuras de Datos
- Stack (Pila): LIFO - Last In First Out
- Queue (Cola): FIFO - First In First Out
- Linked List: Nodos enlazados dinámicamente

### Patrones de Diseño
- Model-View-Controller (MVC)
- Strategy Pattern
- Template Pattern

---

**Proyecto desarrollado para: UPIIT - Algoritmos y Estructuras de Datos - 2do Parcial**

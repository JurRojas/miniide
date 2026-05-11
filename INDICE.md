#  ÍNDICE DEL PROYECTO - Mini IDE con Notación Prefija/Postfija

##  Descripción Rápida

Mini IDE completo en C++ para evaluar expresiones en notación **Prefija** (+ 5 3) y **Postfija** (5 3 +). 
Implementa todas las estructuras de datos requeridas: **Lista Enlazada**, **Pila** y **Cola** sin usar librerías estándar de contenedores.

**Proyecto académico para:** UPIIT - Algoritmos y Estructuras de Datos - 2do Parcial

---

##  Estructura de Archivos

```
proyecto/
├── 📄 INDICE.md                    ← Estás aquí
├── 🏃 Ejecución Rápida
│   ├── proyecto_ide.exe            ← IDE Interactivo (COMPILADO)
│   └── demo.exe                    ← Demostración Automática (COMPILADO)
├── 💻 Código Fuente
│   ├── proyecto_ide.cpp            ← Programa principal (1050+ líneas)
│   └── demo.cpp                    ← Demostración (500+ líneas)
└──  Documentación
    ├── README.md                   ← Descripción general del proyecto
    ├── GUIA_INSTALACION.md         ← Instrucciones paso a paso
    ├── ARQUITECTURA.md             ← Decisiones de diseño y flujos
    └── EJEMPLOS_DETALLADOS.md      ← Explicación interna de estructuras
```

---

## Inicio 

### Opción 1: Ver Demostración Automática (Recomendado)
```bash
cd proyecto
demo.exe
```
Muestra 7 ejemplos funcionales de todas las características.

### Opción 2: IDE Interactivo Completo
```bash
proyecto_ide.exe
```
Acceso al menú de usuario con todas las opciones.

---

## 📖 Qué Leer Según Tu Necesidad

| Si quieres... | Lee... |
|---|---|
| **Entender el proyecto completo** | [README.md](README.md) |
| **Instruir usuario de uso** | [GUIA_INSTALACION.md](GUIA_INSTALACION.md) |
| **Entender la arquitectura interna** | [ARQUITECTURA.md](ARQUITECTURA.md) |
| **Ver cómo funcionan las estructuras paso a paso** | [EJEMPLOS_DETALLADOS.md](EJEMPLOS_DETALLADOS.md) |
| **Revisar/estudiar código** | [proyecto_ide.cpp](proyecto_ide.cpp) |
| **Ver ejemplos funcionales** | [demo.cpp](demo.cpp) |

---

##  Características Principales

###  Estructuras de Datos Implementadas
- **Stack<T>** - Pila con operaciones push/pop/peek
- **Queue<T>** - Cola FIFO con enqueue/dequeue
- **LinkedList** - Lista enlazada para código fuente
- **ExecutionTracer** - Rastrea operaciones en tiempo real

###  Funcionalidades del Intérprete
- **Evaluación Prefija Recursiva** - `+ 5 3` evaluado recursivamente
- **Evaluación Postfija Iterativa** - `5 3 +` evaluado iterativamente
- **Variables** - `$x = valor` para almacenar y reutilizar
- **Ejecución Cola** - Procesa líneas en orden FIFO
- **Operadores** - +, -, *, /, ^

###  Interfaz Visual
```
┌────────────────────────────────────────────┐
│ CODE EDITOR          │ EXECUTION TRACE     │
│ (Código fuente)      │ (Rastreo de pila)   │
├────────────────────────────────────────────┤
│ OUTPUT (Resultado)                         │
│ VARIABLES (Estado)                         │
└────────────────────────────────────────────┘
```

---

##  Ejemplos de Uso

### Ejemplo 1: Suma Simple
```
INPUT:   + 5 3
OUTPUT:  8
TRACE:   Push: 5 → Push: 3 → Operation: + => 8
```

### Ejemplo 2: Expresión Anidada (Prefija)
```
INPUT:   + * 2 3 4
OUTPUT:  10
EQUIV:   (2 * 3) + 4
TRACE:   Push: 2 → Push: 3 → Operation: * => 6
         → Push: 4 → Operation: + => 10
```

### Ejemplo 3: Con Variables
```
INPUT 1: $x = 15
INPUT 2: + $x 10
OUTPUT:  25
VARS:    $x = 15
```

### Ejemplo 4: Postfija
```
INPUT:   2 3 * 4 +
OUTPUT:  10
EQUIV:   (2 * 3) + 4
TRACE:   Push: 2 → Push: 3 → Pop: 3, Pop: 2
         → Operation: * => 6 → Push: 6
         → Push: 4 → Pop: 4, Pop: 6
         → Operation: + => 10
```

---

##  Arquitectura en 8 Clases

```
┌─────────────────────┐
│  Node<T>            │  Nodo genérico enlazado
└─────────────────────┘
         ▲
         │
    ┌────┴────┬──────────┬──────────┐
    ▼         ▼          ▼          ▼
┌─────────┐┌─────────┐┌─────────┐┌─────────────┐
│ Stack<T>││Queue<T> ││LinkedList││ExecutionTracer
└──┬──────┘└─────────┘└────┬────┘└─────────┬───┘
   │                        │              │
   └────────┬───────────────┴──────────┬───┘
            ▼                          ▼
      ┌──────────────┐          ┌──────────────┐
      │ Interpreter  │          │  Visualizer  │
      └──────┬───────┘          └──────────────┘
             │
         ┌───▼──────┐
         ▼          ▼
      ┌─────────┐┌─────────┐
      │ Editor  ││  main() │
      └─────────┘└─────────┘
```

---


##  Compilación Manual

Si necesitas recompilar:

```bash
# Compilar IDE principal
g++ -fdiagnostics-color=always -g proyecto_ide.cpp -o proyecto_ide.exe

# Compilar demostración
g++ -fdiagnostics-color=always -g demo.cpp -o demo.exe

# Ejecutar
proyecto_ide.exe
demo.exe
```
s al 100%

---

## Resumen Técnico

### Tecnologías Usadas
- **Lenguaje**: C++11/14
- **Compilador**: g++ (MinGW en Windows)
- **Librerías**: Solo `<iostream>`, `<string>`, `<map>`, `<vector>`, `<cmath>`
- **Paradigma**: Orientado a Objetos con Templates

### Patrones de Diseño
- **MVC**: Visualizer actúa como View
- **Strategy**: Diferentes evaluadores (Prefija/Postfija)
- **Template Method**: Clase base Node<T>
- **Observer**: ExecutionTracer rastrea operaciones

### Conceptos Demostrados
- Punteros y memoria dinámica
- Recursión vs Iteración
- Estructuras de datos enlazadas
- Análisis de expresiones
- Uso de templates genéricos
- Manejo de excepciones

---

##  Para el Profesor

Este proyecto demuestra:

1. **Comprensión de Estructuras**: Stack, Queue, LinkedList implementadas manualmente
2. **Programación Recursiva**: Evaluación de notación prefija recursiva
3. **Procesamiento de Colas**: Ejecución línea por línea FIFO
4. **Diseño Modular**: 8 clases con responsabilidades claras
5. **Interfaz de Usuario**: Visualización profesional en consola
6. **Manejo de Memoria**: Destructores y liberación apropiada
7. **Validación y Errores**: Casos edge case considerados
8. **Documentación**: Código comentado y documentación externa

---

**¡Listo para usar y presentar!** 

Para empezar: Ejecuta `demo.exe` para ver un resumen de todas las características en acción.

# GUÍA DE INSTALACIÓN Y USO


### 1. **proyecto_ide.cpp** - Programa Principal Interactivo
- Menú completo con interfaz visual
- Editor de código con lista enlazada
- Ejecución línea por línea con cola
- Rastreo de pila en tiempo real

### 2. **demo.cpp** - Programa de Demostración Automática  
- Ejecuta 7 ejemplos automáticamente
- Muestra funcionamiento de todas las estructuras
- Ideal para validar y entender el código

### 3. **proyecto_ide.exe** - Ejecutable del programa principal
### 4. **demo.exe** - Ejecutable de la demostración

---

## Cómo Ejecutar

### Opción 1: Ejecutar la Demostración (Recomendado para ver ejemplos)
```bash
cd "c:\tu_ruta_del_archivo"
demo.exe
```

### Opción 2: Ejecutar el IDE Interactivo
```bash
proyecto_ide.exe
```

---

## Uso del IDE Interactivo

### Menú Principal
```
╔════════════════════════════════════════════╗
║              MENÚ PRINCIPAL                 ║
╠════════════════════════════════════════════╣
║ 1. Agregar línea de código                 ║
║ 2. Ejecutar código                         ║
║ 3. Cambiar notación (Prefija/Postfija)     ║
║ 4. Limpiar editor                          ║
║ 5. Ver ejemplos de sintaxis                ║
║ 6. Salir                                   ║
╚════════════════════════════════════════════╝
```

### Paso a Paso: Evaluar una Expresión

#### **Secuencia para Notación Prefija:**

1. Seleccione opción **1** (Agregar línea)
2. Ingrese: `+ 5 3`
3. Presione Enter
4. Seleccione opción **2** (Ejecutar código)
5. El programa mostrará:
   - Línea de código en CODE EDITOR
   - Rastreo de pila en EXECUTION TRACE
   - Resultado: 8

#### **Secuencia para Notación Postfija:**

1. Seleccione opción **3** (Cambiar a POSTFIJA)
2. Seleccione opción **1** (Agregar línea)
3. Ingrese: `5 3 +`
4. Seleccione opción **2** (Ejecutar código)

---

## Interfaz 

El programa muestra 4 secciones:

### **1. CODE EDITOR**
```
╔════════════════════════════════════════════╗
║         CODE EDITOR (Editor de Código)      ║
╠════════════════════════════════════════════╣
║ L1: + 5 3                                   ║
║ L2: $x = 10                                 ║
║ L3: * $x 2                                  ║
╚════════════════════════════════════════════╝
```

### **2. EXECUTION TRACE**
```
╔════════════════════════════════════════════╗
║       EXECUTION TRACE (Rastreo de Pila)     ║
╠════════════════════════════════════════════╣
║ Push: 5                                     ║
║ Push: 3                                     ║
║ Operation: + => 8                           ║
║ Result: 8                                   ║
╚════════════════════════════════════════════╝
```

### **3. OUTPUT**
```
╔════════════════════════════════════════════╗
║    OUTPUT (Salida)                         ║
╠════════════════════════════════════════════╣
║ Resultado: 8                                ║
╚════════════════════════════════════════════╝
```

### **4. VARIABLES**
```
╔════════════════════════════════════════════╗
║    VARIABLES                               ║
╠════════════════════════════════════════════╣
║ $x = 10                                     ║
║ $y = 20                                     ║
╚════════════════════════════════════════════╝
```

---

## Ejemplos 

### Ejemplo 1: Suma Simple (Prefija)
```
Opción: 1
Código: + 5 3
Opción: 2
Resultado: 8
```

### Ejemplo 2: Multiplicación Anidada (Prefija)
```
Opción: 1
Código: + * 2 3 4
Opción: 2
Resultado: 10  (equivalente a: (2*3)+4)
```

### Ejemplo 3: Variables
```
Opción: 1
Código: $x = 15
Opción: 1
Código: + $x 10
Opción: 2
Resultado: 25
Variables: $x = 15
```

### Ejemplo 4: Potencia
```
Opción: 1
Código: ^ 2 3
Opción: 2
Resultado: 8  (2^3)
```

### Ejemplo 5: División (Postfija)
```
Opción: 3  (cambiar a POSTFIJA)
Opción: 1
Código: 10 2 /
Opción: 2
Resultado: 5
```

---

## Estructura de Código

### Clases Implementadas:

1. **Node<T>**
   - Nodo genérico para estructuras enlazadas

2. **Stack<T>**
   - Pila con operaciones push/pop
   - Usado en evaluación de expresiones

3. **Queue<T>**
   - Cola FIFO para ejecución de instrucciones
   - Cada línea se desencola y procesa secuencialmente

4. **LinkedList**
   - Almacena líneas de código fuente
   - Mantiene número de línea y contenido

5. **ExecutionTracer**
   - Registra cada operación de pila
   - Muestra Push, Pop y Results

6. **Interpreter**
   - Método `evaluatePrefix()`: Evaluación recursiva
   - Método `evaluatePostfix()`: Evaluación iterativa
   - Método `executeLine()`: Ejecuta una línea completa

7. **Editor**
   - Gestiona líneas usando LinkedList
   - Mantiene la Cola de ejecución

8. **Visualizer**
   - Renderiza la interfaz en consola
   - Muestra las 4 secciones visuales

---

## Compilación Manual

Si necesita recompilar los archivos:

### Compilar proyecto_ide.cpp
```bash
g++ -fdiagnostics-color=always -g proyecto_ide.cpp -o proyecto_ide.exe
```

### Compilar demo.cpp
```bash
g++ -fdiagnostics-color=always -g demo.cpp -o demo.exe
```

---

##  Validación de Requisitos

-  **Lista Enlazada**: Implementada en `LinkedList` para código fuente
-  **Pila Recursiva**: `evaluatePrefixRecursive()` usa recursión
-  **Cola**: Implementada en `Queue` para ejecución línea por línea
-  **Evaluación Prefija**: Función recursiva que maneja operadores
-  **Evaluación Postfija**: Función iterativa con pila
-  **Variables**: Soporte con `$varname = valor`
-  **Interfaz Visual**: 3 secciones (Editor, Trace, Output)
-  **Rastreo de Pila**: Muestra Push/Pop/Result en tiempo real
-  **Modularidad**: Separado en 8 clases bien definidas

---

##  Operadores Soportados

| Símbolo | Operación | Ejemplo Prefija | Ejemplo Postfija |
|---------|-----------|-----------------|------------------|
| + | Suma | + 3 4 | 3 4 + |
| - | Resta | - 10 3 | 10 3 - |
| * | Multiplicación | * 2 5 | 2 5 * |
| / | División | / 20 4 | 20 4 / |
| ^ | Potencia | ^ 2 3 | 2 3 ^ |

---

##  Manejo de Errores

El programa valida:
- ✓ División por cero
- ✓ Variables no definidas
- ✓ Tokens inválidos
- ✓ Expresiones malformadas
- ✓ Pila vacía

Todos los errores se muestran en el EXECUTION TRACE.

---

##  Notas Importantes

1. Las variables deben empezar con `$` (ej: `$x`, `$resultado`)
2. Los comentarios comienzan con `#` y se ignoran
3. La cola de ejecución procesa líneas en orden FIFO
4. Puede cambiar entre notación prefija y postfija en cualquier momento
5. Las variables persisten durante toda la sesión

---

##  Propósito 

Este proyecto demuestra:
- Implementación manual de estructuras de datos
- Evaluación de expresiones con pilas
- Procesamiento de colas en orden
- Recursión vs iteración
- Patrones de diseño (MVC con Visualizer)
- Manejo de memoria dinámica en C++



// EJEMPLOS DE CÓDIGO - Cómo funcionan las estructuras internamente

// ============================================================================
// EJEMPLO 1: FUNCIONAMIENTO DE LA PILA (STACK)
// ============================================================================

/*
Estructura: Nodos enlazados con puntero al siguiente

Node<5> ─→ Node<3> ─→ Node<0> ─→ nullptr
(top)

Operaciones:
┌─────────────────────────────────────────────────────────────┐
│ push(5):  Crea nodo, lo coloca en top, avanza puntero       │
│ push(3):  Crea nodo, lo coloca en top, avanza puntero       │
│ peek():   Retorna 3 sin eliminar                            │
│ pop():    Retorna 3, borra nodo, top apunta a 5             │
│ pop():    Retorna 5, borra nodo, top apunta a nullptr       │
└─────────────────────────────────────────────────────────────┘

Código interno:
void push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = top;        // Nuevo nodo apunta al anterior top
    top = newNode;              // El nuevo nodo es ahora el top
    size++;
}

T pop() {
    T value = top->data;        // Guarda el valor del top
    Node<T>* temp = top;
    top = top->next;            // Siguiente nodo es ahora el top
    delete temp;                // Libera memoria
    return value;
}
*/

// ============================================================================
// EJEMPLO 2: FUNCIONAMIENTO DE LA COLA (QUEUE)
// ============================================================================

/*
Estructura: Nodos enlazados con puntero a front y rear

Node<10> ─→ Node<20> ─→ Node<30> ─→ nullptr
(front)                  (rear)

Operaciones:
┌─────────────────────────────────────────────────────────────┐
│ enqueue(10):  Crea nodo, rear.next = nodo, rear = nodo      │
│ enqueue(20):  Crea nodo, rear.next = nodo, rear = nodo      │
│ enqueue(30):  Crea nodo, rear.next = nodo, rear = nodo      │
│ dequeue():    Retorna 10, front = front.next                │
│ dequeue():    Retorna 20, front = front.next                │
│ dequeue():    Retorna 30, front = nullptr, rear = nullptr   │
└─────────────────────────────────────────────────────────────┘

Código interno:
void enqueue(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (rear == nullptr) {
        front = rear = newNode;     // Cola vacía
    } else {
        rear->next = newNode;       // Conecta al final
        rear = newNode;             // Actualiza rear
    }
}

T dequeue() {
    T value = front->data;
    Node<T>* temp = front;
    front = front->next;            // Avanza front
    if (front == nullptr)
        rear = nullptr;             // Cola vacía
    delete temp;
    return value;
}
*/

// ============================================================================
// EJEMPLO 3: EVALUACIÓN PREFIJA RECURSIVA
// ============================================================================

/*
Expresión: + * 2 3 4
Tokens: ["+", "*", "2", "3", "4"]

Traza de ejecución (con pila de llamadas):

evaluatePrefix(index=0)
│
└─ index++ → index=1, token="+"
   Operador detectado
   ├─ Llamar evaluatePrefix (operando 1)
   │  ├─ index++ → index=2, token="*"
   │  │  Operador detectado
   │  │  ├─ Llamar evaluatePrefix (operando 1)
   │  │  │  ├─ index++ → index=3, token="2"
   │  │  │  │  Número detectado
   │  │  │  │  Push: 2
   │  │  │  │  Retorna: 2
   │  │  │  │
   │  │  │  └─ Llamar evaluatePrefix (operando 2)
   │  │  │     ├─ index++ → index=4, token="3"
   │  │  │     │  Número detectado
   │  │  │     │  Push: 3
   │  │  │     │  Retorna: 3
   │  │  │
   │  │  ├─ Calcular: 2 * 3 = 6
   │  │  │  Push: 6
   │  │  │  Retorna: 6
   │  │
   │  └─ Llamar evaluatePrefix (operando 2)
   │     ├─ index++ → index=5, token="4"
   │     │  Número detectado
   │     │  Push: 4
   │     │  Retorna: 4
   │
   ├─ Calcular: 6 + 4 = 10
   │  Push: 10
   │  Retorna: 10

Estado de Pila:
[2] → [2,3] → [6] → [6,4] → [10]

Código:
double evaluatePrefixRecursive(const vector<string>& tokens, int& index) {
    string token = tokens[index++];
    
    if (token == "+") {
        double op1 = evaluatePrefixRecursive(tokens, index);  // Recursión
        double op2 = evaluatePrefixRecursive(tokens, index);  // Recursión
        double result = op1 + op2;
        evalStack.push(result);
        return result;
    }
    // ... más casos
}
*/

// ============================================================================
// EJEMPLO 4: EVALUACIÓN POSTFIJA ITERATIVA
// ============================================================================

/*
Expresión: 2 3 * 4 +
Tokens: ["2", "3", "*", "4", "+"]

Traza de ejecución (línea por línea):

Paso 1: token="2" (número)
   Push 2
   Estado Pila: [2]

Paso 2: token="3" (número)
   Push 3
   Estado Pila: [2, 3]

Paso 3: token="*" (operador)
   Pop operand2 = 3
   Pop operand1 = 2
   Calcular: 2 * 3 = 6
   Push 6
   Estado Pila: [6]

Paso 4: token="4" (número)
   Push 4
   Estado Pila: [6, 4]

Paso 5: token="+" (operador)
   Pop operand2 = 4
   Pop operand1 = 6
   Calcular: 6 + 4 = 10
   Push 10
   Estado Pila: [10]

Resultado: 10

Código:
double evaluatePostfix(const string& expression) {
    Stack<double> postfixStack;
    
    for (const string& token : tokens) {
        if (token == "+") {
            double op2 = postfixStack.pop();  // Orden inverso
            double op1 = postfixStack.pop();
            double result = op1 + op2;
            postfixStack.push(result);
        } else {
            double value = stod(token);
            postfixStack.push(value);
        }
    }
    
    return postfixStack.pop();
}
*/

// ============================================================================
// EJEMPLO 5: COLA DE EJECUCIÓN
// ============================================================================

/*
Usuario ingresa:
1. + 5 3
2. $x = 10
3. * $x 2

Cola de Ejecución (FIFO):
["+ 5 3"] → ["+ 5 3", "$x = 10"] → ["+ 5 3", "$x = 10", "* $x 2"]

Cuando selecciona "Ejecutar":

1. Dequeue: "+ 5 3"
   Resultado: 8
   
2. Dequeue: "$x = 10"
   Resultado: Variable x = 10
   
3. Dequeue: "* $x 2"
   Sustituye $x por 10
   Calcula: 10 * 2 = 20
   Resultado: 20

Código en Editor:
Queue<string> executionQueue;

void addLine(const string& code) {
    executionQueue.enqueue(code);  // Se agrega a la cola
}

// En ejecutar:
while (!executionQueue.isEmpty()) {
    string instruction = executionQueue.dequeue();  // FIFO
    interpreter.executeLine(instruction);
}
*/

// ============================================================================
// EJEMPLO 6: LISTA ENLAZADA PARA CÓDIGO FUENTE
// ============================================================================

/*
El usuario ingresa 3 líneas:

1. addLine(1, "+ 5 3")
   Node<CodeLine> {
       lineNumber: 1,
       content: "+ 5 3",
       next: nullptr
   }

2. addLine(2, "$x = 10")
   Node<CodeLine> {
       lineNumber: 1,
       content: "+ 5 3",
       next: ─→ Node<CodeLine> {
                   lineNumber: 2,
                   content: "$x = 10",
                   next: nullptr
               }
   }

3. addLine(3, "* $x 2")
   Node<CodeLine> {
       lineNumber: 1,
       content: "+ 5 3",
       next: ─→ Node<CodeLine> {
                   lineNumber: 2,
                   content: "$x = 10",
                   next: ─→ Node<CodeLine> {
                               lineNumber: 3,
                               content: "* $x 2",
                               next: nullptr
                           }
               }
   }

Visualización:
┌─────────────────────────────────────┐
│ CODE EDITOR                         │
├─────────────────────────────────────┤
│ L1: + 5 3                           │
│ L2: $x = 10                         │
│ L3: * $x 2                          │
└─────────────────────────────────────┘

Código:
class LinkedList {
    Node<CodeLine>* head;
    
    void addLine(int lineNum, const string& content) {
        Node<CodeLine>* newNode = new Node<CodeLine>(...);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<CodeLine>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
};
*/

// ============================================================================
// EJEMPLO 7: VARIABLES Y DICCIONARIO
// ============================================================================

/*
map<string, double> variables;

Usuario ingresa: $x = 15
Después ingresa: + $x 10

Proceso:
1. "$x = 15"
   ├─ Detecta asignación (=)
   ├─ Parte derecha: "15"
   ├─ Evalúa: evaluatePrefix("15") → 15
   └─ variables["x"] = 15
   
   variables {
       "x" → 15
   }

2. "+ $x 10"
   ├─ No es asignación
   ├─ Es expresión: "+ $x 10"
   ├─ Token "$x" detectado
   │  ├─ Obtiene varName = "x"
   │  ├─ Busca en map: variables["x"] = 15
   │  └─ Usa 15 en lugar de $x
   └─ Calcula: 15 + 10 = 25

Visualización Final:
┌─────────────────────────────────────┐
│ VARIABLES                           │
├─────────────────────────────────────┤
│ $x = 15                             │
└─────────────────────────────────────┘

Código:
// Asignación
string varName = "$x".substr(1);  // Quita $
variables[varName] = evaluado;

// Uso en expresión
if (token[0] == '$') {
    string varName = token.substr(1);
    double value = variables[varName];
    evalStack.push(value);
}
*/

// ============================================================================
// EJEMPLO 8: FLUJO COMPLETO DE EJECUCIÓN
// ============================================================================

/*
┌─────────────────────────────────────────────────────────────────┐
│ USUARIO → Opción 1: Agregar "+ 5 3"                            │
└──────────────────────┬──────────────────────────────────────────┘
                       │ Editor.addLine()
                       ▼
              ┌─────────────────────┐
              │ LinkedList          │
              │ L1: "+ 5 3"         │
              └────────────────────┬┘
                                   │ Queue.enqueue()
                                   ▼
                          ┌─────────────────────┐
                          │ Queue               │
                          │ [" + 5 3"]          │
                          └────────────────────┬┘
                                               │
┌──────────────────────────────────────────────┴──────────────────┐
│ USUARIO → Opción 2: Ejecutar                                   │
└──────────────────────────────────────────────┬──────────────────┘
                                               │
                                               ▼
                                    ┌──────────────────────┐
                                    │ Queue.dequeue()      │
                                    │ Obtiene: "+ 5 3"     │
                                    └──────────┬───────────┘
                                               │
                                               ▼
                        ┌──────────────────────────────────┐
                        │ Interpreter.executeLine()        │
                        │ evaluatePrefix("+ 5 3")          │
                        └──────────────────┬───────────────┘
                                           │
                ┌──────────────────────────┴──────────────────────┐
                │                                                 │
                ▼                                                 ▼
         ┌────────────────┐                              ┌─────────────────┐
         │ Stack.push(5)  │                              │ ExecutionTracer │
         │ Stack.push(3)  │                              │ log: Push 5     │
         │ Stack.pop(3)   │ ─────────────────────────→   │ log: Push 3     │
         │ Stack.pop(5)   │                              │ log: Op: +=>8   │
         │ 5+3=8          │                              │ log: Result: 8  │
         │ Stack.push(8)  │                              └─────────────────┘
         └────────────────┘
                │
                ▼
         ┌────────────────────────────────────┐
         │ Visualizer.displayInterface()      │
         │ - CODE EDITOR (mostrar líneas)     │
         │ - EXECUTION TRACE (mostrar log)    │
         │ - OUTPUT (mostrar resultado)       │
         │ - VARIABLES (mostrar estado)       │
         └────────────────────────────────────┘

Resultado visual:
╔════════════════════════════════════════╗
║ CODE EDITOR                            ║
╠════════════════════════════════════════╣
║ L1: + 5 3                              ║
╚════════════════════════════════════════╝

╔════════════════════════════════════════╗
║ EXECUTION TRACE                        ║
╠════════════════════════════════════════╣
║ Push: 5                                ║
║ Push: 3                                ║
║ Operation: + => 8                      ║
║ Result: 8                              ║
╚════════════════════════════════════════╝

╔════════════════════════════════════════╗
║ OUTPUT                                 ║
╠════════════════════════════════════════╣
║ Resultado: 8                           ║
╚════════════════════════════════════════╝

╔════════════════════════════════════════╗
║ VARIABLES                              ║
╠════════════════════════════════════════╣
║ (Sin variables definidas)              ║
╚════════════════════════════════════════╝
*/

// ============================================================================
// CONCLUSIÓN
// ============================================================================

/*
Este proyecto demuestra cómo:

1. Stack (Pila) se usa para:
   - Evaluar expresiones aritméticas
   - Manejar llamadas recursivas
   - Almacenar operandos temporales

2. Queue (Cola) se usa para:
   - Procesar instrucciones en orden FIFO
   - Ejecutar línea por línea
   - Mantener el flujo de programa

3. Linked List se usa para:
   - Almacenar dinámicamente líneas de código
   - Permitir agregar/remover código fácilmente
   - Mostrar el programa al usuario

4. Recursión se usa para:
   - Evaluación natural de notación prefija
   - Manejo de expresiones anidadas
   - Implementación elegante del análisis

5. Programación orientada a objetos para:
   - Separación de responsabilidades
   - Código modular y reutilizable
   - Fácil mantenimiento y extensión
*/

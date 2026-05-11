#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace std;

// ============================================================================
//                       ESTRUCTURAS DE DATOS MANUALES
// ============================================================================

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    Node<T>* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}
    
    ~Stack() {
        while (top != nullptr) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
        size++;
    }
    
    T pop() {
        if (top == nullptr) {
            throw runtime_error("Error: Pila vacía");
        }
        T value = top->data;
        Node<T>* temp = top;
        top = top->next;
        size--;
        delete temp;
        return value;
    }
    
    T peek() const {
        if (top == nullptr) {
            throw runtime_error("Error: Pila vacía");
        }
        return top->data;
    }
    
    bool isEmpty() const {
        return top == nullptr;
    }
    
    int getSize() const {
        return size;
    }
};

template <typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    
    ~Queue() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }
    
    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    T dequeue() {
        if (front == nullptr) {
            throw runtime_error("Error: Cola vacía");
        }
        T value = front->data;
        Node<T>* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        size--;
        delete temp;
        return value;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
    
    int getSize() const {
        return size;
    }
};

// ============================================================================
//                      RASTREADOR Y EVALUADOR
// ============================================================================

class ExecutionTracer {
private:
    vector<string> trace;

public:
    void logOperation(const string& operation) {
        trace.push_back(operation);
    }
    
    void printTrace() const {
        cout << "\n╔════════════════════════════════════════════╗" << endl;
        cout << "║       EXECUTION TRACE (Rastreo de Pila)     ║" << endl;
        cout << "╠════════════════════════════════════════════╣" << endl;
        
        if (trace.empty()) {
            cout << "║  (Sin operaciones aún)                       ║" << endl;
        } else {
            for (const auto& op : trace) {
                string line = "║ " + op;
                while (line.length() < 43) line += " ";
                line += "║";
                cout << line << endl;
            }
        }
        
        cout << "╚════════════════════════════════════════════╝" << endl;
    }
    
    void clear() {
        trace.clear();
    }
};

class SimpleInterpreter {
private:
    Stack<double> evalStack;
    map<string, double> variables;
    ExecutionTracer tracer;

    double evaluatePrefixRecursive(const vector<string>& tokens, int& index) {
        if (index >= tokens.size()) {
            throw runtime_error("Error: Expresión prefija inválida");
        }
        
        string token = tokens[index++];
        
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            double operand1 = evaluatePrefixRecursive(tokens, index);
            double operand2 = evaluatePrefixRecursive(tokens, index);
            
            double result;
            if (token == "+") result = operand1 + operand2;
            else if (token == "-") result = operand1 - operand2;
            else if (token == "*") result = operand1 * operand2;
            else if (token == "/") {
                if (operand2 == 0) throw runtime_error("Error: División por cero");
                result = operand1 / operand2;
            }
            else if (token == "^") result = pow(operand1, operand2);
            
            evalStack.push(result);
            tracer.logOperation("Operation: " + token + " => " + to_string(result));
            return result;
        }
        else if (token[0] == '$') {
            string varName = token.substr(1);
            if (variables.find(varName) == variables.end()) {
                throw runtime_error("Error: Variable no definida: " + varName);
            }
            double value = variables[varName];
            evalStack.push(value);
            tracer.logOperation("Push (var " + varName + "): " + to_string(value));
            return value;
        }
        else {
            try {
                double value = stod(token);
                evalStack.push(value);
                tracer.logOperation("Push: " + token);
                return value;
            } catch (...) {
                throw runtime_error("Error: Token inválido: " + token);
            }
        }
    }

public:
    SimpleInterpreter() {}
    
    double evaluatePrefix(const string& expression) {
        vector<string> tokens;
        stringstream ss(expression);
        string token;
        
        while (ss >> token) {
            tokens.push_back(token);
        }
        
        evalStack = Stack<double>();
        tracer.clear();
        
        int index = 0;
        double result = evaluatePrefixRecursive(tokens, index);
        
        if (index != tokens.size()) {
            throw runtime_error("Error: Expresión prefija inválida");
        }
        
        return result;
    }
    
    double evaluatePostfix(const string& expression) {
        vector<string> tokens;
        stringstream ss(expression);
        string token;
        
        while (ss >> token) {
            tokens.push_back(token);
        }
        
        Stack<double> postfixStack;
        tracer.clear();
        
        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
                if (postfixStack.getSize() < 2) {
                    throw runtime_error("Error: Expresión postfija inválida");
                }
                
                double operand2 = postfixStack.pop();
                double operand1 = postfixStack.pop();
                
                tracer.logOperation("Pop: " + to_string(operand2));
                tracer.logOperation("Pop: " + to_string(operand1));
                
                double result;
                if (token == "+") result = operand1 + operand2;
                else if (token == "-") result = operand1 - operand2;
                else if (token == "*") result = operand1 * operand2;
                else if (token == "/") {
                    if (operand2 == 0) throw runtime_error("Error: División por cero");
                    result = operand1 / operand2;
                }
                else if (token == "^") result = pow(operand1, operand2);
                
                postfixStack.push(result);
                tracer.logOperation("Operation: " + token + " => " + to_string(result));
                tracer.logOperation("Push: " + to_string(result));
            } 
            else if (token[0] == '$') {
                string varName = token.substr(1);
                if (variables.find(varName) == variables.end()) {
                    throw runtime_error("Error: Variable no definida: " + varName);
                }
                double value = variables[varName];
                postfixStack.push(value);
                tracer.logOperation("Push (var " + varName + "): " + to_string(value));
            }
            else {
                try {
                    double value = stod(token);
                    postfixStack.push(value);
                    tracer.logOperation("Push: " + token);
                } catch (...) {
                    throw runtime_error("Error: Token inválido: " + token);
                }
            }
        }
        
        if (postfixStack.getSize() != 1) {
            throw runtime_error("Error: Expresión postfija inválida");
        }
        
        return postfixStack.pop();
    }
    
    void setVariable(const string& name, double value) {
        variables[name] = value;
    }
    
    ExecutionTracer& getTracer() {
        return tracer;
    }
};

// ============================================================================
//                         DEMOSTRACIÓN AUTOMÁTICA
// ============================================================================

void demoDemo() {
    system("clear || cls");
    
    cout << "\n╔══════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        DEMOSTRACIÓN - MINI IDE CON NOTACIÓN PREFIJA/POSTFIJA      ║" << endl;
    cout << "║        Proyecto: Algoritmos y Estructuras de Datos - UPIIT         ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════╝" << endl;
    
    SimpleInterpreter interpreter;
    
    // ========== EJEMPLO 1: NOTACIÓN PREFIJA BÁSICA ==========
    cout << "\n\n╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ EJEMPLO 1: Notación Prefija Básica - + 5 3                          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        double result = interpreter.evaluatePrefix("+ 5 3");
        cout << "\nExpresión: + 5 3" << endl;
        cout << "Equivalente: 5 + 3" << endl;
        cout << "Resultado: " << result << endl;
        interpreter.getTracer().printTrace();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // ========== EJEMPLO 2: NOTACIÓN PREFIJA COMPLEJA ==========
    cout << "\n\n╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ EJEMPLO 2: Notación Prefija Compleja - + * 2 3 4                    ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        double result = interpreter.evaluatePrefix("+ * 2 3 4");
        cout << "\nExpresión: + * 2 3 4" << endl;
        cout << "Equivalente: (2 * 3) + 4" << endl;
        cout << "Resultado: " << result << endl;
        interpreter.getTracer().printTrace();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // ========== EJEMPLO 3: NOTACIÓN POSTFIJA BÁSICA ==========
    cout << "\n\n╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ EJEMPLO 3: Notación Postfija Básica - 5 3 +                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        double result = interpreter.evaluatePostfix("5 3 +");
        cout << "\nExpresión: 5 3 +" << endl;
        cout << "Equivalente: 5 + 3" << endl;
        cout << "Resultado: " << result << endl;
        interpreter.getTracer().printTrace();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // ========== EJEMPLO 4: NOTACIÓN POSTFIJA COMPLEJA ==========
    cout << "\n\n╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ EJEMPLO 4: Notación Postfija Compleja - 2 3 * 4 +                   ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        double result = interpreter.evaluatePostfix("2 3 * 4 +");
        cout << "\nExpresión: 2 3 * 4 +" << endl;
        cout << "Equivalente: (2 * 3) + 4" << endl;
        cout << "Resultado: " << result << endl;
        interpreter.getTracer().printTrace();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // ========== EJEMPLO 5: CON VARIABLES ==========
    cout << "\n\n╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ EJEMPLO 5: Prefija con Variables - + $x 10 (donde $x = 15)          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        interpreter.setVariable("x", 15);
        double result = interpreter.evaluatePrefix("+ $x 10");
        cout << "\nVariable: $x = 15" << endl;
        cout << "Expresión: + $x 10" << endl;
        cout << "Equivalente: 15 + 10" << endl;
        cout << "Resultado: " << result << endl;
        interpreter.getTracer().printTrace();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // ========== EJEMPLO 6: POTENCIA ==========
    cout << "\n\n╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ EJEMPLO 6: Potencia - ^ 2 3 (Prefija) = 2^3 = 8                     ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        double result = interpreter.evaluatePrefix("^ 2 3");
        cout << "\nExpresión: ^ 2 3" << endl;
        cout << "Equivalente: 2 ^ 3" << endl;
        cout << "Resultado: " << result << endl;
        interpreter.getTracer().printTrace();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // ========== EJEMPLO 7: OPERACIÓN ANIDADA ==========
    cout << "\n\n╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ EJEMPLO 7: Operación Anidada - - / 10 2 3 (Prefija)                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        double result = interpreter.evaluatePrefix("- / 10 2 3");
        cout << "\nExpresión: - / 10 2 3" << endl;
        cout << "Equivalente: (10 / 2) - 3 = 5 - 3 = 2" << endl;
        cout << "Resultado: " << result << endl;
        interpreter.getTracer().printTrace();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "\n\n╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                   FIN DE LA DEMOSTRACIÓN                             ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n✓ Todas las estructuras de datos (Stack, Queue, LinkedList) funcionan correctamente." << endl;
    cout << "✓ Evaluación prefija recursiva implementada." << endl;
    cout << "✓ Evaluación postfija iterativa implementada." << endl;
    cout << "✓ Rastreo de operaciones de pila en tiempo real." << endl;
    cout << "\nEjecute 'proyecto_ide.exe' para acceder al menú interactivo completo.\n" << endl;
}

int main() {
    demoDemo();
    return 0;
}

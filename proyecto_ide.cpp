#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <windows.h>
using namespace std;

//                       ESTRUCTURAS DE DATOS 



template <typename T>
struct Node {
    T data;
    Node* next;
    
    Node(const T& value) : data(value), next(nullptr) {}
};

//  PILA 
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
    
    void printStack() const {
        cout << "Pila: [ ";
        Node<T>* current = top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "]" << endl;
    }
};

// ----- COLA (QUEUE) - Implementación Manual -----
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
    
    T getFront() const {
        if (front == nullptr) {
            throw runtime_error("Error: Cola vacía");
        }
        return front->data;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
    
    int getSize() const {
        return size;
    }
};

// ----- LISTA ENLAZADA PARA ALMACENAR LÍNEAS DE CÓDIGO -----
class CodeLine {
public:
    int lineNumber;
    string content;
    
    CodeLine(int num, const string& line) 
        : lineNumber(num), content(line) {}
};

class LinkedList {
private:
    Node<CodeLine>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}
    
    ~LinkedList() {
        while (head != nullptr) {
            Node<CodeLine>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void addLine(int lineNum, const string& content) {
        CodeLine* codeLine = new CodeLine(lineNum, content);
        Node<CodeLine>* newNode = new Node<CodeLine>(*codeLine);
        delete codeLine;
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<CodeLine>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    
    Node<CodeLine>* getHead() const {
        return head;
    }
    
    int getSize() const {
        return size;
    }
    
    void printAll() const {
        Node<CodeLine>* current = head;
        while (current != nullptr) {
            cout << current->data.lineNumber << ": " << current->data.content << endl;
            current = current->next;
        }
    }
};

// ============================================================================
//                      RASTREADOR DE EJECUCIÓN (TRACER)
// ============================================================================

class ExecutionTracer {
private:
    vector<string> trace;

public:
    void logOperation(const string& operation) {
        trace.push_back(operation);
    }
    
    void printTrace() const {
        cout << "\n+=============================================+" << endl;
        cout << "|       EXECUTION TRACE (Rastreo de Pila)     |" << endl;
        cout << "+=============================================+" << endl;
        
        if (trace.empty()) {
            cout << "|  (Sin operaciones aún)                       |" << endl;
        } else {
            for (const auto& op : trace) {
                string line = "| " + op;
                while (line.length() < 43) line += " ";
                line += "|";
                cout << line << endl;
            }
        }
        
        cout << "+=============================================+" << endl;
    }
    
    void clear() {
        trace.clear();
    }
};

// ============================================================================
//                        INTÉRPRETE (INTERPRETER)
// ============================================================================

class Interpreter {
private:
    Stack<double> evalStack;
    map<string, double> variables;
    ExecutionTracer tracer;
    string lastOutput;
    bool usePrefix; // true = prefija, false = postfija

    // Función recursiva para evaluar NOTACIÓN PREFIJA
    double evaluatePrefixRecursive(const vector<string>& tokens, int& index) {
        if (index >= tokens.size()) {
            throw runtime_error("Error: Expresión prefija inválida");
        }
        
        string token = tokens[index++];
        
        // Es un operador
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
        // Es una variable
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
        // Es un número
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
    Interpreter() : usePrefix(true) {}
    
    void setNotationType(bool isPrefix) {
        usePrefix = isPrefix;
        evalStack = Stack<double>();
        tracer.clear();
    }
    
    // Evaluar NOTACIÓN POSTFIJA (iterativo)
    double evaluatePostfix(const string& expression) {
        vector<string> tokens;
        stringstream ss(expression);
        string token;
        
        while (ss >> token) {
            tokens.push_back(token);
        }
        
        Stack<double> postfixStack;
        
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
    
    // Evaluar NOTACIÓN PREFIJA (recursiva)
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
    
    // Ejecutar una línea de comando
    bool executeLine(const string& line) {
        try {
            // Ignorar líneas vacías y comentarios
            if (line.empty() || line[0] == '#') {
                return true;
            }
            
            // Asignación de variable
            if (line.find("=") != string::npos) {
                size_t eqPos = line.find("=");
                string varPart = line.substr(0, eqPos);
                string exprPart = line.substr(eqPos + 1);
                
                // Limpiar espacios
                varPart.erase(0, varPart.find_first_not_of(" "));
                varPart.erase(varPart.find_last_not_of(" ") + 1);
                exprPart.erase(0, exprPart.find_first_not_of(" "));
                exprPart.erase(exprPart.find_last_not_of(" ") + 1);
                
                if (varPart[0] != '$') {
                    throw runtime_error("Error: Las variables deben empezar con $");
                }
                
                double value;
                if (usePrefix) {
                    value = evaluatePrefix(exprPart);
                } else {
                    value = evaluatePostfix(exprPart);
                }
                
                string varName = varPart.substr(1);
                variables[varName] = value;
                
                lastOutput = "Variable " + varName + " = " + to_string(value);
                tracer.logOperation("Variable assigned: $" + varName + " = " + to_string(value));
                return true;
            }
            
            // Evaluación de expresión
            double result;
            if (usePrefix) {
                result = evaluatePrefix(line);
            } else {
                result = evaluatePostfix(line);
            }
            
            lastOutput = to_string(result);
            tracer.logOperation("Result: " + to_string(result));
            return true;
            
        } catch (const exception& e) {
            lastOutput = string(e.what());
            tracer.logOperation("ERROR: " + lastOutput);
            return false;
        }
    }
    
    string getLastOutput() const {
        return lastOutput;
    }
    
    ExecutionTracer& getTracer() {
        return tracer;
    }
    
    map<string, double>& getVariables() {
        return variables;
    }
};

// ============================================================================
//                      EDITOR DE CÓDIGO (CODE EDITOR)
// ============================================================================

class Editor {
private:
    LinkedList codeLines;
    Queue<string> executionQueue;
    int lineCounter;

public:
    Editor() : lineCounter(0) {}
    
    void addLine(const string& code) {
        codeLines.addLine(++lineCounter, code);
        executionQueue.enqueue(code);
    }
    
    void displayCode() const {
        cout << "\n+=============================================+" << endl;
        cout << "|         CODE EDITOR (Editor de Código)      |" << endl;
        cout << "+=============================================+" << endl;
        
        Node<CodeLine>* current = codeLines.getHead();
        if (current == nullptr) {
            cout << "|  (Código vacío)                             |" << endl;
        } else {
            while (current != nullptr) {
                string line = "| L" + to_string(current->data.lineNumber) + ": " + 
                             current->data.content;
                while (line.length() < 43) line += " ";
                line += "|";
                cout << line << endl;
                current = current->next;
            }
        }
        
        cout << "+=============================================+" << endl;
    }
    
    Queue<string>& getExecutionQueue() {
        return executionQueue;
    }
    
    void clearCode() {
        codeLines = LinkedList();
        executionQueue = Queue<string>();
        lineCounter = 0;
    }
};

// ============================================================================
//                      VISUALIZADOR (VISUALIZER)
// ============================================================================

class Visualizer {
public:
    static void displayInterface(const Editor& editor, 
                                 const Interpreter& interpreter,
                                 const string& notationType) {
        system("clear || cls");
        
        cout << "\n";
        cout << "+==================================================================+" << endl;
        cout << "|        MINI IDE - INTÉRPRETE CON NOTACIÓN PREFIJA/POSTFIJA       |" << endl;
        cout << "|        Algoritmos y Estructuras de Datos - UPIIT 2do Parcial     |" << endl;
        cout << "+==================================================================+" << endl;
        
        cout << "\n[Tipo de Notación: " << notationType << "]\n" << endl;
        
        editor.displayCode();
        
        cout << "\n";
        cout << "+=============================================+" << endl;
        cout << "|    OUTPUT (Salida)                         |" << endl;
        cout << "+=============================================+" << endl;
        cout << "| Resultado: " << interpreter.getLastOutput() << endl;
        cout << "+=============================================+" << endl;
        
        const_cast<Interpreter&>(interpreter).getTracer().printTrace();
        
        // Mostrar variables
        cout << "\n+=============================================+" << endl;
        cout << "|    VARIABLES                               |" << endl;
        cout << "+=============================================+" << endl;
        
        const auto& vars = const_cast<Interpreter&>(interpreter).getVariables();
        if (vars.empty()) {
            cout << "| (Sin variables definidas)                   |" << endl;
        } else {
            for (const auto& [name, value] : vars) {
                string line = "| $" + name + " = " + to_string(value);
                while (line.length() < 43) line += " ";
                line += "|";
                cout << line << endl;
            }
        }
        cout << "+=============================================+\n" << endl;
    }
    
    static void showMenu() {
        cout << "\n+=============================================+" << endl;
        cout << "|              MENÚ PRINCIPAL                 |" << endl;
        cout << "+=============================================+" << endl;
        cout << "| 1. Agregar línea de código                 |" << endl;
        cout << "| 2. Ejecutar código                         |" << endl;
        cout << "| 3. Cambiar notación (Prefija/Postfija)     |" << endl;
        cout << "| 4. Limpiar editor                          |" << endl;
        cout << "| 5. Ver ejemplos de sintaxis                |" << endl;
        cout << "| 6. Salir                                   |" << endl;
        cout << "+=============================================+" << endl;
        cout << "Seleccione opción: ";
    }
    
    static void showSyntaxExamples() {
        system("clear || cls");
        cout << "\n+=======================================================================+" << endl;
        cout << "|              EJEMPLOS DE SINTAXIS                                  |" << endl;
        cout << "+=======================================================================+" << endl;
        
        cout << "\n▶ NOTACIÓN PREFIJA (Operador primero):" << endl;
        cout << "  + 5 3                    => 5 + 3 = 8" << endl;
        cout << "  * 4 2                    => 4 * 2 = 8" << endl;
        cout << "  + * 2 3 4                => (2 * 3) + 4 = 10" << endl;
        cout << "  - / 10 2 3               => (10 / 2) - 3 = 2" << endl;
        cout << "  ^ 2 3                    => 2^3 = 8" << endl;
        
        cout << "\n▶ NOTACIÓN POSTFIJA (Operador al final):" << endl;
        cout << "  5 3 +                    => 5 + 3 = 8" << endl;
        cout << "  4 2 *                    => 4 * 2 = 8" << endl;
        cout << "  2 3 * 4 +                => (2 * 3) + 4 = 10" << endl;
        cout << "  10 2 / 3 -               => (10 / 2) - 3 = 2" << endl;
        cout << "  2 3 ^                    => 2^3 = 8" << endl;
        
        cout << "\n▶ VARIABLES:" << endl;
        cout << "  $x = 10                  => Asignar valor a variable" << endl;
        cout << "  + $x 5                   => Usar variable en expresión (Prefija)" << endl;
        cout << "  $x 5 +                   => Usar variable en expresión (Postfija)" << endl;
        
        cout << "\n▶ COMENTARIOS:" << endl;
        cout << "  # Esto es un comentario" << endl;
        
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
};

// ============================================================================
//                           FUNCIÓN PRINCIPAL
// ============================================================================

int main() {
    Editor editor;
    Interpreter interpreter;
    Visualizer visualizer;
    
    string notationType = "PREFIJA";
    int choice;
    
    // Configurar consola para caracteres UTF-8 (soporte para español)
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    cout << "+=======================================================================+" << endl;
    cout << "|        MINI IDE CON NOTACIÓN PREFIJA/POSTFIJA                      |" << endl;
    cout << "|        Algoritmos y Estructuras de Datos - UPIIT                   |" << endl;
    cout << "+=======================================================================+" << endl;
    
    while (true) {
        Visualizer::displayInterface(editor, interpreter, notationType);
        Visualizer::showMenu();
        
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                cout << "\nIngrese la línea de código (o '#' para comentario):\n> ";
                string line;
                getline(cin, line);
                editor.addLine(line);
                interpreter.executeLine(line);
                break;
            }
            
            case 2: {
                system("clear || cls");
                cout << "\n+=============================================+" << endl;
                cout << "|  Ejecutando todas las líneas en la Cola...  |" << endl;
                cout << "+=============================================+\n" << endl;
                
                Queue<string>& execQueue = editor.getExecutionQueue();
                int instrNum = 1;
                
                while (!execQueue.isEmpty()) {
                    string instruction = execQueue.dequeue();
                    cout << "Instrucción " << instrNum << ": " << instruction << endl;
                    interpreter.executeLine(instruction);
                    cout << "  Resultado: " << interpreter.getLastOutput() << "\n" << endl;
                    instrNum++;
                }
                
                cout << "Presione Enter para continuar...";
                cin.get();
                break;
            }
            
            case 3: {
                if (notationType == "PREFIJA") {
                    notationType = "POSTFIJA";
                    interpreter.setNotationType(false);
                } else {
                    notationType = "PREFIJA";
                    interpreter.setNotationType(true);
                }
                cout << "\nNotación cambiada a: " << notationType << endl;
                cout << "Presione Enter para continuar...";
                cin.get();
                break;
            }
            
            case 4: {
                editor.clearCode();
                cout << "\nEditor limpiado." << endl;
                cout << "Presione Enter para continuar...";
                cin.get();
                break;
            }
            
            case 5: {
                Visualizer::showSyntaxExamples();
                break;
            }
            
            case 6: {
                cout << "\nPrograma finalizado" << endl;
                return 0;
            }
            
            default:
                cout << "\nOpción inválida. Intente nuevamente." << endl;
                cout << "Presione Enter para continuar...";
                cin.get();
        }
    }
    
    return 0;
}

#include <iostream>
#include <cctype>  // Para isdigit()
#include <cstring> // Para strlen()
using namespace std;

#define MAX 100

//---------------- Estructura de la pila ----------------//
struct Pila {
    char datos[MAX];
    int tope;
};

// Inicializa la pila vacía
void inicializar(Pila &p) {
    p.tope = -1;
}

// Inserta un elemento en la pila
void push(Pila &p, char valor) {
    if (p.tope < MAX - 1)
        p.datos[++p.tope] = valor;
}

// Elimina el tope de la pila
void pop(Pila &p) {
    if (p.tope >= 0)
        p.tope--;
}

// Devuelve el elemento del tope
char cima(Pila &p) {
    return (p.tope >= 0) ? p.datos[p.tope] : '\0';
}

// Verifica si la pila está vacía
bool vacia(Pila &p) {
    return p.tope == -1;
}

// Muestra el contenido actual de la pila
void mostrarPila(Pila &p) {
    cout << "Estado de la pila: [ ";
    for (int i = 0; i <= p.tope; i++) {
        cout << p.datos[i] << " ";
    }
    cout << "]" << endl;
}

//---------------- Programa principal ----------------//
int main() {
    Pila pila;
    inicializar(pila);

    char expresion[MAX];
    cout << "Ingrese la expresion aritmetica: ";
    cin.getline(expresion, MAX);

    bool error = false;
    int posicionError = -1;

    for (int i = 0; i < strlen(expresion); i++) {
        char c = expresion[i];

        // Detectar paréntesis de apertura
        if (c == '(') {
            cout << "( Parentesis que abre" << endl;
            push(pila, c);
            mostrarPila(pila);
        }
        // Detectar paréntesis de cierre
        else if (c == ')') {
            cout << ") Parentesis que cierra" << endl;
            if (vacia(pila)) {
                error = true;
                posicionError = i + 1;
                break;
            }
            pop(pila);
            mostrarPila(pila);
        }
        // Detectar operadores
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            cout << c << " Simbolo" << endl;
        }
        // Detectar números (enteros o reales)
        else if (isdigit(c) || (c == '-' && isdigit(expresion[i + 1]))) {
            string numero;
            bool punto = false;

            // Leer el número completo (incluyendo decimales)
            int j = i;
            if (expresion[j] == '-') numero += expresion[j++]; // signo negativo
            while (isdigit(expresion[j]) || expresion[j] == '.') {
                if (expresion[j] == '.') punto = true;
                numero += expresion[j];
                j++;
            }

            // Clasificar el número
            if (punto)
                cout << numero << " Real" << (numero[0] == '-' ? " negativo" : "") << endl;
            else
                cout << numero << " Entero" << (numero[0] == '-' ? " negativo" : "") << endl;

            i = j - 1; // avanzar índice
        }
        // Ignorar espacios
        else if (isspace(c)) {
            continue;
        }
        // Detectar caracteres no válidos
        else {
            cout << "Carácter no reconocido '" << c << "' en posición " << i + 1 << endl;
            error = true;
            posicionError = i + 1;
            break;
        }
    }

    // Verificación final de paréntesis
    if (!error) {
        if (!vacia(pila)) {
            error = true;
            posicionError = strlen(expresion);
        }
    }

    if (error)
        cout << "Invalido, error en la posicion " << posicionError << endl;
    else
        cout << "El uso de parentesis es correcto" << endl;

    return 0;
}

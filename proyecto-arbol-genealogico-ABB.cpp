#include <iostream>
#include <string>
using namespace std;

// Estructura del nodo
struct Persona {
    int diaNacimiento;    // Día de nacimiento
    int mesNacimiento;    // Mes de nacimiento
    int anioNacimiento;   // Año de nacimiento
    string nombre;        // Nombre de la persona
    Persona* izquierda;   // Puntero al hijo izquierdo
    Persona* derecha;     // Puntero al hijo derecho
};

// Función para crear una nueva persona con día, mes y año
Persona* crearPersona(int dia, int mes, int anio, string nombre) {
    Persona* nueva = new Persona; 
    nueva->diaNacimiento = dia;
    nueva->mesNacimiento = mes;
    nueva->anioNacimiento = anio;
    nueva->nombre = nombre;
    nueva->izquierda = NULL;
    nueva->derecha = NULL;
    return nueva;
}

// Función de Insertación de Persona con fecha completa
void insertarPersona(Persona*& raiz, int dia, int mes, int anio, string nombre) {
    if (raiz == NULL) {  
        raiz = crearPersona(dia, mes, anio, nombre);
    } else if (anio < raiz->anioNacimiento || (anio == raiz->anioNacimiento && mes < raiz->mesNacimiento) || 
               (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia < raiz->diaNacimiento)) { 
        insertarPersona(raiz->izquierda, dia, mes, anio, nombre);
    } else if (anio > raiz->anioNacimiento || (anio == raiz->anioNacimiento && mes > raiz->mesNacimiento) || 
               (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia > raiz->diaNacimiento)) { 
        insertarPersona(raiz->derecha, dia, mes, anio, nombre);
    } else { 
        cout << "Ya existe una persona con esa fecha de nacimiento.\n"; 
    }
}

// Función de Busqueda de Persona en el Árbol (con fecha completa)
bool buscarPersona(Persona* raiz, int dia, int mes, int anio) {
    if (raiz == NULL) {
        return false;
    }  
    if (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia == raiz->diaNacimiento) {
        cout << "Persona encontrada: " << raiz->nombre << " (" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ")\n";
        return true;
    } else if (anio < raiz->anioNacimiento || (anio == raiz->anioNacimiento && mes < raiz->mesNacimiento) || 
               (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia < raiz->diaNacimiento)) {
        return buscarPersona(raiz->izquierda, dia, mes, anio);
    } else {
        return buscarPersona(raiz->derecha, dia, mes, anio);
    }
}

// Busca el nodo con el año más pequeño, empezando en un punto dado
Persona* encontrarMinimo(Persona* nodo) {
    while (nodo->izquierda != NULL) 
        nodo = nodo->izquierda; 
    return nodo; 
}

// Elimina a una persona del árbol según el año, mes y día ingresado
Persona* eliminarPersona(Persona* raiz, int dia, int mes, int anio) {
    if (raiz == NULL) {
        cout << "No se encontró la persona\n";
        return NULL; 
    }

    if (anio < raiz->anioNacimiento || (anio == raiz->anioNacimiento && mes < raiz->mesNacimiento) || 
        (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia < raiz->diaNacimiento)) { 
        raiz->izquierda = eliminarPersona(raiz->izquierda, dia, mes, anio);
    } else if (anio > raiz->anioNacimiento || (anio == raiz->anioNacimiento && mes > raiz->mesNacimiento) || 
               (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia > raiz->diaNacimiento)) { 
        raiz->derecha = eliminarPersona(raiz->derecha, dia, mes, anio);
    } else { 
        string nombreEliminado = raiz->nombre;
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ") [era hoja]\n";
            delete raiz; 
            return NULL; 
        } else if (raiz->izquierda == NULL) {
            Persona* temp = raiz->derecha;
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ") [tenía un hijo derecho]\n";
            delete raiz; 
            return temp; 
        } else if (raiz->derecha == NULL) {
            Persona* temp = raiz->izquierda;
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ") [tenía un hijo izquierdo]\n";
            delete raiz; 
            return temp;
        } else { 
            Persona* temp = encontrarMinimo(raiz->derecha); 
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ") [tenía dos hijos, se reemplazó por " << temp->nombre << "]\n";
            raiz->anioNacimiento = temp->anioNacimiento; 
            raiz->nombre = temp->nombre;
            raiz->diaNacimiento = temp->diaNacimiento;
            raiz->mesNacimiento = temp->mesNacimiento;
            raiz->derecha = eliminarPersona(raiz->derecha, temp->diaNacimiento, temp->mesNacimiento, temp->anioNacimiento); 
        }
    }
    return raiz; 
}

// Recorrido INORDEN: Funcion de más antiguo a más reciente
void inorden(Persona* raiz) {
    if (raiz != NULL) { 
        inorden(raiz->izquierda); 
        cout << raiz->nombre << " \t(" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ")\n"; 
        inorden(raiz->derecha); 
    }
}

// Recorrido PREORDEN: Se usa para jerarquía generacional
void preorden(Persona* raiz) {
    if (raiz != NULL) { 
        cout << raiz->nombre << " \t(" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ")\n"; 
        preorden(raiz->izquierda);  
        preorden(raiz->derecha);  
    }
}

// Recorrido POSTORDEN: Se usa para eliminaciones
void postorden(Persona* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierda); 
        postorden(raiz->derecha); 
        cout << raiz->nombre << " \t(" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ")\n"; 
    }
}

// Mostrar jerarquía de forma visual
void mostrarJerarquia(Persona* raiz, int nivel = 0) {
    if (raiz != NULL) {
        mostrarJerarquia(raiz->derecha, nivel + 1); 
        for (int i = 0; i < nivel; i++) cout << "   "; 
        cout << "|--- " << raiz->nombre << " (" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ")\n"; 
        mostrarJerarquia(raiz->izquierda, nivel + 1); 
    }
}

// Menú 
void menu() {
    cout << "\n--- Árbol Genealógico (ABB) ---\n";
    cout << "1. Insertar persona\n";
    cout << "2. Buscar persona\n";
    cout << "3. Eliminar persona\n";
    cout << "4. Mostrar inorden\n";
    cout << "5. Mostrar preorden\n";
    cout << "6. Mostrar postorden\n";
    cout << "7. Visualizar jerarquía\n";
    cout << "8. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    setlocale(LC_CTYPE, "Spanish"); 
    Persona* raiz = NULL; 
    int opcion, dia, mes, anio; 
    string nombre;

    do {
        menu();
        cin >> opcion; 

        switch (opcion) {
            case 1: // Inserción
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese día de nacimiento: ";
                cin >> dia;
                cout << "Ingrese mes de nacimiento: ";
                cin >> mes;
                cout << "Ingrese año de nacimiento: ";
                cin >> anio;
                insertarPersona(raiz, dia, mes, anio, nombre);
                break;
            case 2: // Búsqueda
                cout << "Ingrese día a buscar: ";
                cin >> dia;
                cout << "Ingrese mes a buscar: ";
                cin >> mes;
                cout << "Ingrese año a buscar: ";
                cin >> anio;
                if (!buscarPersona(raiz, dia, mes, anio)){
                    cout << "No se encontró a la persona.\n";
                }
                break;    
            case 3: //  Eliminar persona
                cout << "Ingrese día a eliminar: ";
                cin >> dia;
                cout << "Ingrese mes a eliminar: ";
                cin >> mes;
                cout << "Ingrese año a eliminar: ";
                cin >> anio;
                raiz = eliminarPersona(raiz, dia, mes, anio);
                break;
            case 4: // Mostrar inorden
                cout << "\n--- Recorrido Inorden (IRD - De más antiguo a más reciente) ---\n";
                inorden(raiz);
                break;
            case 5: // Mostrar preorden
                cout << "\n--- Recorrido Preorden (RID - Jerarquía generacional) ---\n";
                preorden(raiz);
                break;
            case 6: // Mostrar postorden
                cout << "\n--- Recorrido Postorden (IDR - Para eliminaciones) ---\n";
                postorden(raiz);
                break;
            case 7: // Visualización jerarquía
                cout << "\n--- Visualización Jerárquica del Árbol ---\n";
                mostrarJerarquia(raiz);
                break;
            case 8: // Salir
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 8);

    return 0;
}

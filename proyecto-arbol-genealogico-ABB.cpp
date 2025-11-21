#include <iostream>
#include <string>
using namespace std;

// Estructura del nodo
struct Persona {
    int diaNacimiento;
    int mesNacimiento;
    int anioNacimiento;
    string nombre;
    Persona* izquierda;
    Persona* derecha;
};

// ============ FUNCIÓN DE VALIDACIÓN  ============
// Valida que la fecha sea correcta
bool validarFecha(int dia, int mes, int anio) {
    // Validar año (debe ser entre 0 y 2025)
    if (anio < 0 || anio > 2025) {
        cout << "Año inválido. Debe estar entre 0 y 2025.\n";
        return false;
    }

    // Validar mes (debe estar entre 1 y 12)
    if (mes < 1 || mes > 12) {
        cout << "Mes inválido. Debe estar entre 1 y 12.\n";
        return false;
    }
    
    // Días por mes 
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Validar día (debe estar entre 1 y el número de días del mes correspondiente)
    if (dia < 1 || dia > diasPorMes[mes]) {
        cout << "Día inválido para el mes " << mes << ". Debe estar entre 1 y " 
             << diasPorMes[mes] << ".\n";
        return false;
    }
    
    return true;
}

// Valida que el nombre no esté vacío
bool validarNombre(string nombre) {
    if (nombre.empty()) {
        cout << "El nombre no puede estar vacío.\n";
        return false;
    }
    return true;
}
// ============================================================

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
    if (nodo == NULL) {
        return NULL;
    }
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

        // Validación de entrada de opción
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada inválida. Por favor ingrese un número.\n";
            continue;
        }

        switch (opcion) {
            case 1: // Inserción
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nombre);
                
                // Validar nombre (no vacío)
                if (!validarNombre(nombre)) {
                    break;
                }

                cout << "Ingrese día de nacimiento: ";
                cin >> dia;
                
                cout << "Ingrese mes de nacimiento: ";
                cin >> mes;

                cout << "Ingrese año de nacimiento: ";
                cin >> anio;

                // Validar fecha
                if (!validarFecha(dia, mes, anio)) {
                    break;
                }

                insertarPersona(raiz, dia, mes, anio, nombre);
                cout << "Persona insertada correctamente.\n";
                break;

            case 2: // Buscar persona
                // Similar al código de inserción
                break;

            case 3: // Eliminar persona
                // Similar al código de inserción
                break;

            case 4: // Mostrar inorden
                cout << "\n--- Recorrido Inorden (De más antiguo a más reciente) ---\n";
                inorden(raiz);
                break;

            case 5: // Mostrar preorden
                cout << "\n--- Recorrido Preorden (Jerarquía generacional) ---\n";
                preorden(raiz);
                break;

            case 6: // Mostrar postorden
                cout << "\n--- Recorrido Postorden (Eliminación) ---\n";
                postorden(raiz);
                break;

            case 7: // Mostrar jerarquía visual
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

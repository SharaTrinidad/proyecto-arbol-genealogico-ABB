#include <iostream>                 // Librería para entrada y salida estándar
#include <string>                   // Librería para usar strings
using namespace std;                // Permite usar los nombres estándar sin std::

 // Estructura del nodo
struct Persona {                    // Define la estructura Persona que será cada nodo del árbol
    int diaNacimiento;              // Día de nacimiento
    int mesNacimiento;              // Mes de nacimiento
    int anioNacimiento;             // Año de nacimiento
    string nombre;                  // Nombre de la persona
    Persona* izquierda;             // Puntero al hijo izquierdo (nodos menores)
    Persona* derecha;               // Puntero al hijo derecho (nodos mayores)
};

 // ============ FUNCIÓN DE VALIDACIÓN  ============

 // Valida que la fecha sea correcta
bool validarFecha(int dia, int mes, int anio) {          // Función que valida una fecha completa
    if (anio < 0 || anio > 2025) {                       // Valida que el año esté dentro del rango permitido
        cout << "Año inválido. Debe estar entre 0 y 2025.\n";   // Mensaje de error
        return false;                                    // Retorna falso si no es válido
    }

    if (mes < 1 || mes > 12) {                           // Valida que el mes esté entre 1 y 12
        cout << "Mes inválido. Debe estar entre 1 y 12.\n";     // Mensaje de error
        return false;                                    // Retorna falso si no es válido
    }

    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   // Días máximos por mes (sin bisiesto)

    if (dia < 1 || dia > diasPorMes[mes]) {              // Valida que el día corresponda al mes
        cout << "Día inválido para el mes " << mes << ". Debe estar entre 1 y "
             << diasPorMes[mes] << ".\n";                // Mensaje de error
        return false;                                    // Retorna falso si el día no es válido
    }

    return true;                                         // Retorna verdadero si la fecha es válida
}

 // Valida que el nombre no esté vacío
bool validarNombre(string nombre) {                      // Función que verifica si el nombre tiene contenido
    if (nombre.empty()) {                                // Comprueba si está vacío
        cout << "El nombre no puede estar vacío.\n";     // Mensaje de error
        return false;                                    // Retorna falso si no es válido
    }
    return true;                                         // Retorna verdadero si el nombre no está vacío
}

 // ============================================================

 // Función para crear una nueva persona con día, mes y año
Persona* crearPersona(int dia, int mes, int anio, string nombre) {   // Crea un nodo Persona con datos
    Persona* nueva = new Persona;                    // Reserva memoria para el nuevo nodo
    nueva->diaNacimiento = dia;                      // Asigna el día
    nueva->mesNacimiento = mes;                      // Asigna el mes
    nueva->anioNacimiento = anio;                    // Asigna el año
    nueva->nombre = nombre;                          // Asigna el nombre
    nueva->izquierda = NULL;                         // Inicializa puntero izquierdo vacío
    nueva->derecha = NULL;                           // Inicializa puntero derecho vacío
    return nueva;                                    // Retorna el nodo creado
}

 // Función de Inserción de Persona con fecha completa
void insertarPersona(Persona*& raiz, int dia, int mes, int anio, string nombre) {   // Inserta una persona en el ABB
    if (raiz == NULL) {                           // Caso base: si el árbol está vacío
        raiz = crearPersona(dia, mes, anio, nombre);   // Crea el nodo como raíz
    } else if (anio < raiz->anioNacimiento ||
              (anio == raiz->anioNacimiento && mes < raiz->mesNacimiento) ||
              (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia < raiz->diaNacimiento)) {
        insertarPersona(raiz->izquierda, dia, mes, anio, nombre);   // Inserta en el subárbol izquierdo
    } else if (anio > raiz->anioNacimiento ||
              (anio == raiz->anioNacimiento && mes > raiz->mesNacimiento) ||
              (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia > raiz->diaNacimiento)) {
        insertarPersona(raiz->derecha, dia, mes, anio, nombre);    // Inserta en el subárbol derecho
    } else {
        cout << "Ya existe una persona con esa fecha de nacimiento.\n";  // Fecha duplicada
    }
}

 // Función de Búsqueda de Persona en el Árbol (con fecha completa)
bool buscarPersona(Persona* raiz, int dia, int mes, int anio) {     // Busca un nodo por fecha completa
    if (raiz == NULL) {                          // Si el árbol está vacío o no se encontró
        return false;                            // Retorna falso
    }
    if (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia == raiz->diaNacimiento) {
        cout << "Persona encontrada: " << raiz->nombre << " (" << raiz->diaNacimiento << "/"
             << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ")\n";   // Muestra información encontrada
        return true;                             // Coincidencia exacta
    } else if (anio < raiz->anioNacimiento ||
              (anio == raiz->anioNacimiento && mes < raiz->mesNacimiento) ||
              (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia < raiz->diaNacimiento)) {
        return buscarPersona(raiz->izquierda, dia, mes, anio);   // Busca en el subárbol izquierdo
    } else {
        return buscarPersona(raiz->derecha, dia, mes, anio);     // Busca en el subárbol derecho
    }
}

 // Busca el nodo con el valor menor dentro de un subárbol
Persona* encontrarMinimo(Persona* nodo) {         // Encuentra el nodo más pequeño (más antiguo)
    if (nodo == NULL) {                           // Si no existe nodo
        return NULL;                              // Retorna NULL
    }
    while (nodo->izquierda != NULL)               // Avanza hacia el extremo izquierdo
        nodo = nodo->izquierda;                   // Continúa moviéndose al hijo izquierdo
    return nodo;                                  // Retorna el nodo mínimo
}

 // Elimina a una persona del árbol según año, mes y día
Persona* eliminarPersona(Persona* raiz, int dia, int mes, int anio) {   // Elimina un nodo del ABB
    if (raiz == NULL) {                          // Si el árbol está vacío o no se encontró la persona
        cout << "No se encontró la persona\n";   // Mensaje de error
        return NULL;                             
    }

    if (anio < raiz->anioNacimiento ||
        (anio == raiz->anioNacimiento && mes < raiz->mesNacimiento) ||
        (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia < raiz->diaNacimiento)) {
        raiz->izquierda = eliminarPersona(raiz->izquierda, dia, mes, anio);   // Busca en subárbol izquierdo

    } else if (anio > raiz->anioNacimiento ||
              (anio == raiz->anioNacimiento && mes > raiz->mesNacimiento) ||
              (anio == raiz->anioNacimiento && mes == raiz->mesNacimiento && dia > raiz->diaNacimiento)) {
        raiz->derecha = eliminarPersona(raiz->derecha, dia, mes, anio);      // Busca en subárbol derecho

    } else {                                           // Nodo encontrado
        string nombreEliminado = raiz->nombre;         // Guarda el nombre para imprimirlo

        if (raiz->izquierda == NULL && raiz->derecha == NULL) {   // Caso 1: Es una hoja
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->diaNacimiento << "/"
                 << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ") [era hoja]\n";
            delete raiz;                                // Libera memoria
            return NULL;                                // Retorna NULL porque ya no existe

        } else if (raiz->izquierda == NULL) {           // Caso 2: Tiene solo hijo derecho
            Persona* temp = raiz->derecha;              // Guarda el hijo derecho
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->diaNacimiento << "/"
                 << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ") [tenía un hijo derecho]\n";
            delete raiz;                                // Borra nodo actual
            return temp;                                // Retorna el hijo derecho

        } else if (raiz->derecha == NULL) {             // Caso 3: Tiene solo hijo izquierdo
            Persona* temp = raiz->izquierda;            // Guarda el hijo izquierdo
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->diaNacimiento << "/"
                 << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ") [tenía un hijo izquierdo]\n";
            delete raiz;                                // Borra nodo actual
            return temp;                                // Retorna el hijo izquierdo

        } else {                                        // Caso 4: Tiene dos hijos
            Persona* temp = encontrarMinimo(raiz->derecha);   // Busca sucesor en subárbol derecho
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->diaNacimiento << "/"
                 << raiz->mesNacimiento << "/" << raiz->anioNacimiento << ") [tenía dos hijos, se reemplazó por "
                 << temp->nombre << "]\n";

            raiz->anioNacimiento = temp->anioNacimiento;   // Copia el año del sucesor
            raiz->nombre = temp->nombre;                   // Copia el nombre del sucesor
            raiz->diaNacimiento = temp->diaNacimiento;     // Copia el día
            raiz->mesNacimiento = temp->mesNacimiento;     // Copia el mes

            raiz->derecha = eliminarPersona(raiz->derecha, temp->diaNacimiento,
                                            temp->mesNacimiento, temp->anioNacimiento); // Elimina sucesor
        }
    }
    return raiz;                                    // Retorna el nodo actualizado
}

 // Recorrido INORDEN: Imprime de más antiguo a más reciente
void inorden(Persona* raiz) {                       // Función de recorrido inorden
    if (raiz != NULL) {                             // Si el nodo no es nulo
        inorden(raiz->izquierda);                   // Recorre subárbol izquierdo
        cout << raiz->nombre << " \t(" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/"
             << raiz->anioNacimiento << ")\n";      // Imprime datos
        inorden(raiz->derecha);                     // Recorre subárbol derecho
    }
}

 // Recorrido PREORDEN: útil para mostrar jerarquía
void preorden(Persona* raiz) {                      // Función de recorrido preorden
    if (raiz != NULL) {                             // Si el nodo no es nulo
        cout << raiz->nombre << " \t(" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/"
             << raiz->anioNacimiento << ")\n";      // Imprime nodo actual
        preorden(raiz->izquierda);                  // Recorre subárbol izquierdo
        preorden(raiz->derecha);                    // Recorre subárbol derecho
    }
}

 // Recorrido POSTORDEN: útil para procesos de eliminación
void postorden(Persona* raiz) {                     // Función de recorrido postorden
    if (raiz != NULL) {                             // Si el nodo no es nulo
        postorden(raiz->izquierda);                 // Recorre subárbol izquierdo
        postorden(raiz->derecha);                   // Recorre subárbol derecho
        cout << raiz->nombre << " \t(" << raiz->diaNacimiento << "/" << raiz->mesNacimiento << "/"
             << raiz->anioNacimiento << ")\n";      // Imprime nodo al final
    }
}

 // Mostrar jerarquía de forma visual
void mostrarJerarquia(Persona* raiz, int nivel = 0) {   // Imprime árbol de forma gráfica
    if (raiz != NULL) {                                 // Si el nodo existe
        mostrarJerarquia(raiz->derecha, nivel + 1);     // Muestra subárbol derecho con más indentación
        for (int i = 0; i < nivel; i++) cout << "   ";  // Indentación visual
        cout << "|--- " << raiz->nombre << " (" << raiz->diaNacimiento << "/" << raiz->mesNacimiento
             << "/" << raiz->anioNacimiento << ")\n";   // Imprime nodo
        mostrarJerarquia(raiz->izquierda, nivel + 1);   // Muestra subárbol izquierdo
    }
}

 // Menú en consola
void menu() {                                      // Imprime el menú de opciones
    cout << "\n--- Árbol (ABB) ---\n";
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

int main() {                                       // Función principal del programa
    setlocale(LC_CTYPE, "Spanish");                // Configura idioma para mostrar tildes y ñ
    Persona* raiz = NULL;                          // Puntero raíz del árbol genealógico
    int opcion, dia, mes, anio;                    // Variables para opciones y fecha
    string nombre;                                 // Variable para almacenar el nombre

    do {                                           // Bucle principal del menú
        menu();                                    // Muestra opciones
        cin >> opcion;                             // Solicita opción al usuario

        if (cin.fail()) {                          // Verifica si la entrada fue inválida
            cin.clear();                           // Limpia el error del buffer
            cin.ignore(10000, '\n');               // Descarta la entrada incorrecta
            cout << "Entrada inválida. Por favor ingrese un número.\n";
            continue;                              // Vuelve al menú
        }

        switch (opcion) {                          // Evalúa la opción ingresada
            case 1:                                 // Inserción
                cout << "Ingrese nombre: ";
                cin.ignore();                      // Limpia buffer del enter pendiente
                getline(cin, nombre);              // Lee nombre completo

                if (!validarNombre(nombre)) {      // Valida que el nombre no esté vacío
                    break;                         // Sale del case
                }

                cout << "Ingrese día de nacimiento: ";
                cin >> dia;

                cout << "Ingrese mes de nacimiento: ";
                cin >> mes;

                cout << "Ingrese año de nacimiento: ";
                cin >> anio;

                if (!validarFecha(dia, mes, anio)) {   // Valida fecha completa
                    break;                             // Si es inválida, no inserta
                }

                insertarPersona(raiz, dia, mes, anio, nombre);   // Inserta en el árbol
                cout << "Persona insertada correctamente.\n";
                break;

            case 2:                                  // Buscar persona
                // Similar al código de inserción
                break;

            case 3:                                  // Eliminar persona
                // Similar al código de inserción
                break;

            case 4:                                  // Mostrar inorden
                cout << "\n--- Recorrido Inorden (De más antiguo a más reciente) ---\n";
                inorden(raiz);                      // Llama función inorden
                break;

            case 5:                                  // Mostrar preorden
                cout << "\n--- Recorrido Preorden (Jerarquía generacional) ---\n";
                preorden(raiz);
                break;

            case 6:                                  // Mostrar postorden
                cout << "\n--- Recorrido Postorden (Eliminación) ---\n";
                postorden(raiz);
                break;

            case 7:                                  // Visualización jerárquica
                cout << "\n--- Visualización Jerárquica del Árbol ---\n";
                mostrarJerarquia(raiz);
                break;

            case 8:                                  // Salida
                cout << "Saliendo del programa.\n";
                break;

            default:                                 // Opciones no válidas
                cout << "Opción inválida.\n";
        }

    } while (opcion != 8);                           // Repite hasta que elija salir

    return 0;                                       // Fin del programa
}


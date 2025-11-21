#include <iostream>            // Incluye la biblioteca estándar para entrada/salida (cin, cout).
#include <string>              // Incluye la clase string para manejar cadenas de texto.
using namespace std;           // Permite usar directamente nombres del espacio std (cout, string, etc.).

// Estructura del nodo
struct Persona {               // Define una estructura llamada Persona que será el nodo del árbol.
    int anioNacimiento;        // Guarda el año de nacimiento (clave para el ABB).
    string nombre;             // Guarda el nombre de la persona.
    Persona* izquierda;        // Puntero al hijo izquierdo (nodos con año menor).
    Persona* derecha;          // Puntero al hijo derecho (nodos con año mayor).
};

// Función para crear una nueva persona
Persona* crearPersona(int anio, string nombre) { // Prototipo de función que reserva y devuelve un nuevo nodo.
    Persona* nueva = new Persona; // Reserva dinámicamente memoria para un nuevo nodo Persona.
    nueva->anioNacimiento = anio; // Asigna el año pasado como argumento al campo anioNacimiento del nodo.
    nueva->nombre = nombre;      // Asigna el nombre pasado como argumento al campo nombre del nodo.
    nueva->izquierda = NULL;     // Inicializa el puntero izquierdo en NULL (sin hijos aún).
    nueva->derecha = NULL;       // Inicializa el puntero derecho en NULL (sin hijos aún).
    return nueva;                // Devuelve la dirección del nuevo nodo creado.
}

// Función de Insertacion de Persona 
void insertarPersona(Persona*& raiz, int anio, string nombre) { // Inserta un nodo en el ABB (por referencia a la raiz).
    if (raiz == NULL) {  // Si el subárbol (o árbol) está vacío...
        raiz = crearPersona(anio, nombre); // ...crea el nodo y lo asigna como nueva raíz/subraíz.
    } else if (anio < raiz->anioNacimiento) { // Si el año es menor que el de la raíz actual...
        insertarPersona(raiz->izquierda, anio, nombre); // ...insertar recursivamente en el subárbol izquierdo.
    } else if (anio > raiz->anioNacimiento) { // Si el año es mayor que el de la raíz actual...
        insertarPersona(raiz->derecha, anio, nombre); // ...insertar recursivamente en el subárbol derecho.
    } else { // Si el año es exactamente igual al de la raíz...
        cout << "Ya existe una persona con ese año de nacimiento.\n"; // ...no permite duplicados y muestra mensaje.
    }
}

// Función de Busqueda de Persona en el Arbol
bool buscarPersona(Persona* raiz, int anio) { // Busca un nodo por su año; devuelve true si lo encuentra.
    if (raiz == NULL) {       // Si el subárbol está vacío...
    	return false;         // ...no se encontró la persona (caso base).
	}  
    if (anio == raiz->anioNacimiento){ // Si el año buscado coincide con la raíz actual...
    	cout<<"Persona encontrada: "<<raiz->nombre<<"\t("<<raiz->anioNacimiento<<")\n"; // ...imprime datos.
    	return true;           // Devuelve true (encontrado).
	} 
    else if (anio < raiz->anioNacimiento) return buscarPersona(raiz->izquierda, anio); // Si es menor, buscar a la izquierda.
    else return buscarPersona(raiz->derecha, anio); // Si es mayor, buscar a la derecha.
}
// Busca el nodo con el año mas pequeño, empezando en un punto dado
Persona* encontrarMinimo(Persona* nodo) { // Devuelve el nodo con la clave mínima en el subárbol dado.
    while (nodo->izquierda != NULL) // Mientras exista un hijo izquierdo...
        nodo = nodo->izquierda;     // ...avanza hacia la izquierda (más pequeño).
    return nodo;                    // Retorna el nodo más a la izquierda (mínimo).
}

//Elimina a una persona del árbol segun el año ingresado
Persona* eliminarPersona(Persona* raiz, int anio) { // Elimina y devuelve la nueva raíz del subárbol modificado.
    if (raiz == NULL) {            // Si el subárbol está vacío...
    	cout << "No se encontro la persona\n"; // ...informa que no se encontró el año a eliminar.
    	return NULL;               // Retorna NULL (nada que hacer).
	}

    if (anio < raiz->anioNacimiento) { // Si el año buscado es menor al de la raíz...
        raiz->izquierda = eliminarPersona(raiz->izquierda, anio); // ...elimina recursivamente en izquierda.
    } else if (anio > raiz->anioNacimiento) {  // Si el año buscado es mayor...
        raiz->derecha = eliminarPersona(raiz->derecha, anio);   // ...elimina recursivamente en derecha.
    } else {    // Si el año coincide con la raíz => encontramos el nodo a eliminar
    
	//Si el año coincide, ya se encontro a la persona a eliminar
        // Nodo encontrado
        string nombreEliminado = raiz->nombre; // Guarda el nombre para imprimir después.

        if (raiz->izquierda == NULL && raiz->derecha == NULL) { // Caso 1: no tiene hijos (hoja)
        	cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->anioNacimiento << ") [era hoja]\n";
            delete raiz; // Libera la memoria del nodo.
            return NULL; // Retorna NULL para desconectar este nodo del padre.
        } else if (raiz->izquierda == NULL) { // Caso 2: solo tiene hijo derecho
        	cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->anioNacimiento << ") [tenía un hijo derecho]\n";
            Persona* temp = raiz->derecha; // Guarda el puntero al hijo derecho.
            delete raiz; // Elimina el nodo actual.
            return temp; // Devuelve el hijo derecho para que el padre lo enlace (reemplazo).
        } else if (raiz->derecha == NULL) { // Caso 3: solo tiene hijo izquierdo
        	cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->anioNacimiento << ") [tenía un hijo izquierdo]\n";
            Persona* temp = raiz->izquierda; // Guarda el puntero al hijo izquierdo.
            delete raiz; // Elimina el nodo actual.
            return temp; // Devuelve el hijo izquierdo para que el padre lo enlace (reemplazo).
        } else { 
            // Caso 4: tiene dos hijos
            Persona* temp = encontrarMinimo(raiz->derecha); // Encuentra el sucesor inorden (mínimo del subárbol derecho).
            cout << "Persona eliminada: " << nombreEliminado << " (" << raiz->anioNacimiento << ") [tenía dos hijos, se reemplazó por " << temp->nombre << "]\n";
            raiz->anioNacimiento = temp->anioNacimiento; // Copia la clave (año) del sucesor al nodo actual.
            raiz->nombre = temp->nombre;                 // Copia el nombre del sucesor al nodo actual.
            raiz->derecha = eliminarPersona(raiz->derecha, temp->anioNacimiento); // Elimina recursivamente el sucesor duplicado.
            
        }
    }
    return raiz; // Retorna la raíz (posiblemente modificada) del subárbol.
}



// Recorrido INORDEN: Funcion de m?s antiguo a m?s reciente
void inorden(Persona* raiz) { // Recorre el árbol en orden: izquierda, raíz, derecha.
    if (raiz != NULL) { // Si el nodo no es NULL...
        inorden(raiz->izquierda); // Recorre primero todo el subárbol izquierdo.
        cout << raiz->nombre << " \t(" << raiz->anioNacimiento << ")\n"; // Imprime el nodo actual (nombre y año).
        inorden(raiz->derecha); // Recorre el subárbol derecho.
    }
}

// Recorrido PREORDEN: Se usa para jerarquia generacional
void preorden(Persona* raiz) { // Recorre en preorden: raíz, izquierda, derecha.
    if (raiz != NULL) { 
        cout << raiz->nombre << " \t(" << raiz->anioNacimiento << ")\n"; // Imprime primero la raíz.
        preorden(raiz->izquierda);  // Luego recorre el izquierdo.
        preorden(raiz->derecha);  // Luego recorre el derecho.
    }
}

// Recorrido POSTORDEN: Se usa para eliminaciones
void postorden(Persona* raiz) { // Recorre en postorden: izquierda, derecha, raíz.
    if (raiz != NULL) {
        postorden(raiz->izquierda); // Recorre izquierdo primero.
        postorden(raiz->derecha); // Recorre derecho después.
        cout << raiz->nombre << " \t(" << raiz->anioNacimiento << ")\n"; // Imprime el nodo al final.
    }
}

//Mostrar jerarquía de forma visual
void mostrarJerarquia(Persona* raiz, int nivel = 0) { // Muestra estructura visual con indentación (nivel por defecto 0).
    if (raiz != NULL) {
        mostrarJerarquia(raiz->derecha, nivel + 1); // Imprime primero el subárbol derecho (para que se vea "arriba" en pantalla).
        for (int i = 0; i < nivel; i++) cout << "   "; // Imprime espacios según el nivel para indentar.
        cout << "|--- " << raiz->nombre << " (" << raiz->anioNacimiento << ")\n"; // Imprime el nodo actual con su prefijo.
        mostrarJerarquia(raiz->izquierda, nivel + 1); // Luego imprime el subárbol izquierdo.
    }
}


// Menú 
void menu() { // Imprime las opciones del menú por consola.
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


int main() { // Función principal donde inicia la ejecución del programa.
    setlocale(LC_CTYPE, "Spanish"); // Configura la localización para mostrar correctamente caracteres especiales en consola.
    Persona* raiz = NULL; // Inicializa la raíz del árbol como NULL (árbol vacío).
    int opcion, anio; // Variables para almacenar la opción del menú y el año ingresado por el usuario.
    string nombre; // Variable para almacenar el nombre ingresado por el usuario.

    do { // Bucle principal que muestra el menú hasta que el usuario elija salir (opción 8).
        menu(); // Muestra el menú.
        cin >> opcion; // Lee la opción elegida por el usuario.

        switch (opcion) { // Controla el flujo según la opción ingresada.
            case 1: // Inserción
                cout << "Ingrese nombre: ";
                cin.ignore(); // Limpia el buffer de entrada (descarta '\n' restante) antes de getline.
                getline(cin, nombre); // Lee el nombre completo con espacios.
                cout << "Ingrese año de nacimiento: ";
                cin >> anio; // Lee el año como entero.
                insertarPersona(raiz, anio, nombre); // Llama a la función para insertar la persona en el árbol.
                break;
            case 2: // Busqueda
                cout << "Ingrese año a buscar: ";
                cin >> anio; // Lee el año a buscar.
                if (!buscarPersona(raiz, anio)){ // Llama a buscarPersona; si devuelve false...
                	cout << "No se encontró a la persona.\n"; // ...muestra mensaje de no encontrado.
				}
                break;    
                
            case 3: //  Eliminar una persona del arbol segun su año de nacimiento
                cout << "Ingrese año a eliminar: ";
                cin >> anio; // Lee el año a eliminar.
                raiz = eliminarPersona(raiz, anio); // Llama a eliminarPersona y actualiza la raíz (por si cambia).
                break;
            case 4:  //  Mostrar el recorrido inorden (de mas antiguo a mas reciente)
                cout << "\n--- Recorrido Inorden (IRD - De mas antiguo a mas reciente) ---\n";
                inorden(raiz); // Llama a la función que imprime el recorrido inorden.
                break;
            case 5: // Mostrar el recorrido preorden (jerarquia generacional)
                cout << "\n--- Recorrido Preorden (RID - Jerarquia generacional) ---\n";
                preorden(raiz); // Llama a la función que imprime el recorrido preorden.
                break;
            case 6: // Mostrar el recorrido postorden (para eliminaciones o limpieza)
                cout << "\n--- Recorrido Postorden (IDR - Para eliminaciones) ---\n";
                postorden(raiz); // Llama a la función que imprime el recorrido postorden.
                break;
            case 7: // Mostrar visualmente la jerarquia del arbol genealogico
                cout << "\n--- Visualización Jerárquica del Árbol ---\n";
                mostrarJerarquia(raiz); // Llama a la función que dibuja la jerarquía con indentación.
                break;
            case 8: // Salir del programa
                cout << "Saliendo del programa.\n"; // Mensaje de salida.
                break;
            default: // En caso de que se ingrese una opcion que no esta en el menu
                cout << "Opción inválida.\n"; // Mensaje de error por opción inválida.
        }
    } while (opcion != 8); // Repite mientras la opción elegida no sea 8 (Salir).

    return 0; // Retorna 0 al sistema operativo indicando que el programa finalizó correctamente.
}

#include <iostream>
#include <cstdlib> // Para malloc
#include <cstring> // Para strcpy

using namespace std;

struct nodo {
    char placa[51]; // eta monda define un char array para la placa con un máximo de 50 caracteres
    string tipo; // "Carro" o "Moto", pa que sepa...tontito
    nodo* sig;
};

struct nodo *aux, *top_carros, *top_motos, *top_aux;
int totalIngresos = 0;

void registrar(char placa[], string tipo) {
    aux = static_cast<struct nodo*>(malloc(sizeof(struct nodo))); // aqui se hace uso de malloc
    strcpy(aux->placa, placa); // en esta vuelta se copia la placa al char array
    aux->tipo = tipo;
    aux->sig = NULL;

    if (tipo == "Moto") {
        if (top_motos == NULL) {
            top_motos = aux;
        } else {
            aux->sig = top_motos;
            top_motos = aux;
        }
    } else if (tipo == "Carro") {
        if (top_carros == NULL) {
            top_carros = aux;
        } else {
            aux->sig = top_carros;
            top_carros = aux;
        }
    }
}

void mostrar() {
    cout << endl << "Motos:" << endl;
    for (aux = top_motos; aux != NULL; aux = aux->sig) {
        cout << "Placa: " << aux->placa << endl;
    }
    cout << endl << "Carros:" << endl;
    for (aux = top_carros; aux != NULL; aux = aux->sig) {
        cout << "Placa: " << aux->placa << endl;
    }
}

void sacarVehiculo(char placa[]) {
    char** movidos = NULL; // este array dinámico sirve para almacenar las placas de los vehículos movidos (no funciona pa ni verga)
    int numMovidos = 0;
    int cobro = 0;
    bool encontrado = false;

    // deberia buscar y sacar el vehículo del parqueadero, pero no va :,(
    while (top_motos != NULL && !encontrado) {
        if (strcmp(top_motos->placa, placa) == 0) {
            encontrado = true;
            cobro = 500; // Cobro por moto: $500 lukas
            aux = top_motos;
            top_motos = top_motos->sig;
            free(aux);
        } else {
            numMovidos++;
            movidos = (char**)realloc(movidos, numMovidos * sizeof(char*)); // pa aumentar el tamaño del array (le hace el campito al proximo dato)
            movidos[numMovidos - 1] = strdup(top_motos->placa); // pa copiar la placa al array de movidos
            aux = top_motos;
            top_motos = top_motos->sig;
            aux->sig = top_aux;
            top_aux = aux;
        }
    }

    // Si no se encontró la moto, buscar en los carros, pa que sepa >:/
    if (!encontrado) {
        while (top_carros != NULL && !encontrado) {
            if (strcmp(top_carros->placa, placa) == 0) {
                encontrado = true;
                cobro = 1000; // Cobro por carro: $1000 lukas
                aux = top_carros;
                top_carros = top_carros->sig;
                free(aux);
            } else {
                numMovidos++;
                movidos = (char**)realloc(movidos, numMovidos * sizeof(char*)); // Aumentar el tamaño del array (como el anterior...tontito)
                movidos[numMovidos - 1] = strdup(top_carros->placa); // Copiar la placa al array de movidos (lo mismo)
                aux = top_carros;
                top_carros = top_carros->sig;
                aux->sig = top_aux;
                top_aux = aux;
            }
        }
    }

    // pa reubicar los vehículos movidos si no se encontró el vehículo, no funciona, toca mejorar la logica
    if (!encontrado) {
        for (int i = 0; i < numMovidos; i++) {
            registrar(movidos[i], "Carro"); // Todos los movidos se tratan como carros, para la prueba, pero pasa los datos de la pila moto a carro
            free(movidos[i]); // pa liberar memoria para cada placa copiada
        }
        free(movidos); // pa liberar memoria para el array de placas movidas
    }

    // pa mostrar el cobro realizado si se encontró el vehículo
    if (cobro > 0) {
        cout << "Se ha retirado el vehículo con placa " << placa << " del parqueadero." << endl;
        cout << "Cobro realizado: $" << cobro << endl;
    } else {
        cout << "La placa ingresada no corresponde a ningún vehículo en el parqueadero." << endl;
    }
}


void calcularIngresos() {
    int totalCarros = 0;
    int totalMotos = 0;

    for (aux = top_motos; aux != NULL; aux = aux->sig) {
        totalMotos += 500; // Cada moto paga $500 lukas
    }

    for (aux = top_carros; aux != NULL; aux = aux->sig) {
        totalCarros += 1000; // Cada carro paga $1000 lukas
    }

    cout << "Ingresos por motos: $" << totalMotos << endl;
    cout << "Ingresos por carros: $" << totalCarros << endl;
}

int main() {
    int opc;
    char placa[51]; // Se define un char array para la placa con un máximo de 50 caracteres... ya se que son 51 >:/
    string tipo;
    top_motos = NULL;
    top_carros = NULL;
    top_aux = NULL;

    do {
        cout << "------ MENU ------" << endl;
        cout << "1. Registrar moto" << endl;
        cout << "2. Registrar carro" << endl;
        cout << "3. Mostrar vehiculos en el parqueadero" << endl;
        cout << "4. Sacar vehiculo" << endl;
        cout << "5. Calcular ingresos totales" << endl;
        cout << "6. Salir" << endl;
        cout << "------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;

        switch (opc) {
            case 1:
                cout << "Ingrese la placa de la moto: ";
                cin.ignore(); // Limpiar el buffer (eta verga la puse pero no se ni pa que)
                cin.getline(placa, 51); // pa poder leer la placa con espacios y límite de 50 caracteres
                registrar(placa, "Moto");
                break;
            case 2:
                cout << "Ingrese la placa del carro: ";
                cin.ignore(); // pa limpiar el buffer
                cin.getline(placa, 51); // Leer la placa con espacios y límite de 50 caracteres
                registrar(placa, "Carro");
                break;
            case 3:
                mostrar();
                break;
            case 4:
                cout << "Ingrese la placa del vehiculo a sacar: ";
                cin.ignore(); // Limpiar el buffer (nota: La función cin.ignore() se utiliza comúnmente para descartar caracteres adicionales del búfer de entrada después de leer un valor con cin, especialmente cuando se combina con getline() para evitar problemas con los saltos de línea.)
                cin.getline(placa, 51); // Leer la placa con espacios y límite de 50 caracteres
                sacarVehiculo(placa);
                mostrar();
                break;
            case 5:
                calcularIngresos();
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

        cout << "------------------" << endl;

    } while (opc != 6);

    return 0;
}

//me quiero mataaaaaaaa
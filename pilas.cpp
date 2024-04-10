#include <malloc.h>
#include <iostream>
using namespace std;

// Definición de la estructura Parqueadero4 para almacenar vehículos
struct Parqueadero4 {
    int placa;
    Parqueadero4 *sig;
};

// Declaración de variables y punteros para el parqueadero de autos y motos
Parqueadero4 *topauto, *topmoto, *auxauto, *auxmoto, *actualmoto, *actualauto, *anteriormoto, *anteriorauto;
int valorAuto = 0;
int valorMoto = 0;
int auxiliarauto = 0;
int auxiliarmoto = 0;
int eliminarAuto = 0;
int eliminarMoto = 0;
int auxeliminarAuto = 0;
int auxeliminarMoto = 0;
int totalDevengado = 0;
int devengadoAuto = 0;
int devengadoMoto = 0;

// Función para parquear un vehículo
void parquear() {
    int opc = 0;
    cout << "Ingrese el tipo de vehículo que quiere parquear" << endl;
    cout << "1: Carro" << endl;
    cout << "2: Moto" << endl;
    cout << "Ingrese su opcion: ";
    cin >> opc;

    switch (opc) {
        case 1: // autos
            auxauto = (Parqueadero4 *)malloc(sizeof(Parqueadero4));
            if (topauto == NULL) {
                topauto = auxauto;
                cout << "Ingrese la placa del auto: ";
                cin >> topauto->placa;
                topauto->sig = NULL;
            } else {
                auxauto->sig = topauto;
                cout << "Ingrese la placa del siguiente auto: ";
                cin >> auxauto->placa;
                topauto = auxauto;
            }
            auxiliarauto = 1000;
            valorAuto += auxiliarauto;
            auxiliarauto = 0;
            break;
        case 2: // motos
            auxmoto = (Parqueadero4 *)malloc(sizeof(Parqueadero4));
            if (topmoto == NULL) {
                topmoto = auxmoto;
                cout << "Ingrese la placa de la moto: ";
                cin >> topmoto->placa;
                topmoto->sig = NULL;
            } else {
                auxmoto->sig = topmoto;
                cout << "Ingrese la placa del siguiente moto: ";
                cin >> auxmoto->placa;
                topmoto = auxmoto;
            }
            auxiliarmoto = 500;
            valorMoto += auxiliarmoto;
            auxiliarmoto = 0;
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
    }
}

// Función para mostrar los vehículos parqueados
void mostrar() {
    if (topauto == NULL && topmoto == NULL) {
        cout << "No hay vehiculos ingresados para ser mostrados. Intente por ingresar uno." << endl;
        return;
    }

    cout << "Autos parqueados:" << endl;
    for (auxauto = topauto; auxauto != NULL; auxauto = auxauto->sig) {
        cout << "===" << endl;
        cout << auxauto->placa << endl;
        cout << "===" << endl;
    }

    cout << "Motos parqueadas:" << endl;
    for (auxmoto = topmoto; auxmoto != NULL; auxmoto = auxmoto->sig) {
        cout << "===" << endl;
        cout << auxmoto->placa << endl;
        cout << "===" << endl;
    }
}

// Función para eliminar un vehículo del parqueadero
void eliminar() {
    int placa;
    cout << "Ingrese la placa del vehículo a despachar: ";
    cin >> placa;

    Parqueadero4 *temp_auto, *prev_auto;
    temp_auto = topauto;
    prev_auto = NULL;

    // Buscar y eliminar en la sección de autos
    while (temp_auto != NULL) {
        if (temp_auto->placa == placa) {
            if (prev_auto == NULL) {
                topauto = temp_auto->sig;
            } else {
                prev_auto->sig = temp_auto->sig;
            }
            delete temp_auto;
            cout << "Vehículo con placa " << placa << " despachado del parqueadero de autos." << endl;
            return;
        }
        prev_auto = temp_auto;
        temp_auto = temp_auto->sig;
    }

    Parqueadero4 *temp_moto, *prev_moto;
    temp_moto = topmoto;
    prev_moto = NULL;

    // Buscar y eliminar en la sección de motos
    while (temp_moto != NULL) {
        if (temp_moto->placa == placa) {
            if (prev_moto == NULL) {
                topmoto = temp_moto->sig;
            } else {
                prev_moto->sig = temp_moto->sig;
            }
            delete temp_moto;
            cout << "Vehículo con placa " << placa << " despachado del parqueadero de motos." << endl;
            return;
        }
        prev_moto = temp_moto;
        temp_moto = temp_moto->sig;
    }

    cout << "El vehículo con placa " << placa << " no se encuentra registrado en el parqueadero." << endl;
}

// Función para calcular y mostrar el total devengado
void totalParquear() {
    devengadoAuto = valorAuto - eliminarAuto;
    devengadoMoto = valorMoto - eliminarMoto;
    cout << "Dinero recolectado del parqueadero de autos: $" << devengadoAuto << endl;
    cout << "Dinero recolectado del parqueadero de motos: $" << devengadoMoto << endl;
    totalDevengado = devengadoAuto + devengadoMoto;
    cout << "El total devengado es: $" << totalDevengado << endl;
}

// Función principal que controla el menú del sistema
int main() {
    int opcion;
    do {
        cout << "Bienvenido al Sistema de Manejo de Parqueadero" << endl;
        cout << "Opciones de Parqueadero Disponibles:" << endl;
        cout << "1. Parquear vehiculo" << endl;
        cout << "2. Mostrar vehiculos Parqueados" << endl;
        cout << "3. Despachar vehiculo" << endl;
        cout << "4. Mostrar el total devengado" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                parquear();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                eliminar();
                break;
            case 4:
                totalParquear();
                break;
            case 5:
                cout << "Programa Finalizado, gracias por usar nuestro Software." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}
//me quiero mataaaaaaaa
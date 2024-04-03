#include <iostream>
#include <malloc.h>
#include <stack>
using namespace std;

struct nodo {      
    string placa; 
    string tipo; // "Carro" o "Moto"
    nodo* sig; 
};

struct nodo *aux, *top_carros, *top_motos, *top_aux;
int totalIngresos = 0;

void registrar(string placa, string tipo) {
    aux = ((struct nodo *) malloc(sizeof(struct nodo)));
    aux->placa = placa;
    aux->tipo = tipo;
    
    if (tipo == "Moto") {
        if(top_motos == NULL){
            top_motos = aux;
            aux->sig = NULL;
        } else {
            aux->sig = top_motos;
            top_motos = aux;
        }
    } else if (tipo == "Carro") {
        if(top_carros == NULL){
            top_carros = aux;
            aux->sig = NULL;
        } else {
            aux->sig = top_carros;
            top_carros = aux;
        }
    }
}

void mostrar() {
    cout << endl << "Motos:" << endl;
    for(aux = top_motos; aux != NULL; aux = aux->sig){
        cout << "Placa: " << aux->placa << endl;
    }
    cout << endl << "Carros:" << endl;
    for(aux = top_carros; aux != NULL; aux = aux->sig){
        cout << "Placa: " << aux->placa << endl;
    }
}

void sacarVehiculo(string placa) {
    stack<string> movidos;
    int cobro = 0;
    
    // Buscar y sacar el vehículo del parqueadero
    bool encontrado = false;
    while(top_motos != NULL && !encontrado){
        if (top_motos->placa == placa) {
            encontrado = true;
            cobro = 50;
            aux = top_motos;
            top_motos = top_motos->sig;
            free(aux);
        } else {
            movidos.push(top_motos->placa);
            aux = top_motos;
            top_motos = top_motos->sig;
            aux->sig = top_aux;
            top_aux = aux;
        }
    }
    
    while(top_carros != NULL && !encontrado){
        if (top_carros->placa == placa) {
            encontrado = true;
            cobro = 100;
            aux = top_carros;
            top_carros = top_carros->sig;
            free(aux);
        } else {
            movidos.push(top_carros->placa);
            aux = top_carros;
            top_carros = top_carros->sig;
            aux->sig = top_aux;
            top_aux = aux;
        }
    }
    
    // Reubicar los vehículos movidos
    while (!movidos.empty()) {
        registrar(movidos.top(), (cobro == 50) ? "Moto" : "Carro");
        movidos.pop();
    }
    
    // Cobrar si se movieron otros vehículos
    if (cobro > 0) {
        totalIngresos += cobro;
        cout << "Se ha retirado el vehículo con placa " << placa << " del parqueadero." << endl;
        cout << "Cobro realizado: $" << cobro << endl;
    } else {
        cout << "La placa ingresada no corresponde a ningún vehículo en el parqueadero." << endl;
    }
}

int main() {
    int opc;
    string placa, tipo;
    top_motos = NULL;
    top_carros = NULL;
    top_aux = NULL;
    
    do {
        cout << "------ MENU ------" << endl;
        cout << "1. Registrar moto" << endl;
        cout << "2. Registrar carro" << endl;
        cout << "3. Mostrar vehiculos en el parqueadero" << endl;
        cout << "4. Sacar vehiculo" << endl;
        cout << "5. Salir" << endl;
        cout << "------------------" << endl;
        cout << "Seleccione una opción: ";
        cin >> opc;
        
        switch (opc) {
            case 1:
                cout << "Ingrese la placa de la moto: ";
                cin >> placa;
                registrar(placa, "Moto");
                mostrar();
                break;
                
            case 2:
                cout << "Ingrese la placa del carro: ";
                cin >> placa;
                registrar(placa, "Carro");
                mostrar();
                break;
                
            case 3:
                mostrar();
                break;
                
            case 4:
                cout << "Ingrese la placa del vehiculo a sacar: ";
                cin >> placa;
                sacarVehiculo(placa);
                mostrar();
                break;
                
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
                
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
        
        cout << "------------------" << endl;
    } while (opc != 5);
    
    return 0;
}
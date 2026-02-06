#include "../include/utils/Menu.h"
#include <iostream>

using namespace std;

int main(){
    try {
        cout << "\n||====================================================||" << endl;
        cout << "||                                                    ||" << endl;
        cout << "||   SISTEMA DE ANALISIS ESTRUCTURADO DE DATOS        ||" << endl;
        cout << "||                                                    ||" << endl;
        cout << "||   Proyecto: Sistema de Gestion de Pedidos          ||" << endl;
        cout << "||   Curso: Estructura de Datos                       ||" << endl;
        cout << "||                                                    ||" << endl;
        cout << "||====================================================||" << endl;
        
        cout << "\nPresione Enter para iniciar...";
        cin.get();
        
        Menu menu;
        menu.ejecutar();
        
    } catch (const exception& e) {
        cerr << "\n❌ Error fatal: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
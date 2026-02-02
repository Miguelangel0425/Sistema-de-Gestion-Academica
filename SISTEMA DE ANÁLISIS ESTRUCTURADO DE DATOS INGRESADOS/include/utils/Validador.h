#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <string>
#include <vector>
#include <regex> 
#include <sstream>

using namespace std;

class Validador{
    public:
    static bool esNumero(const string& str);

    static bool esEmailValido(const string& email);

    static bool esTelefonoValido(const string& telefono);

    //static bool esFechaValida(const string& fecha);

    static bool enRango(int numero, int min, int max);
    
    static bool esPrecioValido(double precio);

    static vector<string> split(const string& str,char delimitador);

    static bool validarCliente(const string& entrada,vector<string>& campos);

    static bool validarProducto(const string& entrada, vector<string>& campos);

    static bool validarPedido(const string& entrada, vector<string>& campos);
    
    static string trim(const string& str);
};

#endif
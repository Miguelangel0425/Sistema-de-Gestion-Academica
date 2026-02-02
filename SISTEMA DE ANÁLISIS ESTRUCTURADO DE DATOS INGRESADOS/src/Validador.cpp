#include "../include/utils/Validador.h"
#include <algorithm>
#include <cctype>

bool Validador::esNumero(const string& str){
    if(str.empty()) return false;

    for(char c : str){
        if(!isdigit(c)) return false;
    }
    return true;
}

bool Validador::esEmailValido(const string& email){
    regex patron(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    regex_match(email,patron);
}

bool Validador::esTelefonoValido(const string& telefono){
    string tel = telefono;

    //eliminar posibles espacios o guiones
    tel.erase(remove_if(tel.begin(),tel.end(),[](char c){return c == ' ' || c == '-';}), tel.end());

    return tel.length() >= 8 && tel.length()<=10 && esNumero(tel);
}

bool Validador::enRango(int numero, int min, int max){
    return numero >= min && numero <= max;
}

bool Validador::esPrecioValido(double precio){
    return precio > 0.0 && precio < 10000000.0;
}

string Validador::trim(const string& str) {
    size_t inicio = str.find_first_not_of(" \t\n\r");
    if (inicio == string::npos) return "";
    
    size_t fin = str.find_last_not_of(" \t\n\r");
    return str.substr(inicio, fin - inicio + 1);
}

vector<string> Validador::split( const string& str,char delimitador) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while(getline(ss,token,delimitador)){
        tokens.push_back(trim(token));
    }
    return tokens;
}

bool Validador::validarCliente(const string& entrada, vector<string>& campos){
    
}

bool Validador::validarProducto(const string& entrada, vector<string>& campos){

}

bool Validador::validarPedido(const string& entrada, vector<string>& campos){

}


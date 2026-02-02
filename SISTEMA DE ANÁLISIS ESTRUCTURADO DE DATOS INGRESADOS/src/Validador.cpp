#include "../include/utils/Validador.h"
#include <algorithm>
#include <cctype>
#include <iostream> 

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
    campos = split(entrada, ',');
    if (campos.size() != 4){
        cout << "Error: Se espera que se llenen los 4 campos en el orden: Nombre, Email,Telefono, Direccion." << endl;
        return false;
    }

    if(campos[0].empty()){
        cout << "Error: El campo del nombre no puede estar vacio!" << endl;
        return false;
    }

    if(!esEmailValido(campos[1])){
        cout << "Error: Email invalido. " << endl;
        return false;
    } 

    if(!esTelefonoValido(campos[2])){
        cout << "Error: Telefono invalido!" << endl;
        return false;
    }

    if(campos[3].empty()){
        cout << "Error:La direccion no puede estar Vacia. " << endl;
        return false;
    }
    cout << "Campos Validados Exitosamente." << endl;
    return true;
}

bool Validador::validarProducto(const string& entrada, vector<string>& campos){
    campos = split(entrada,',');

    if (campos.size() != 4) {
        cout << " Error: Se esperan 4 campos (Nombre,Precio,Cantidad,Categoria)" << endl;
        return false;
    }
    
    if (campos[0].empty()) {
        cout << " Error: El nombre del producto no puede estar vacío" << endl;
        return false;
    }

    try
    {
        double precio = stod(campos[1]);
        if(!esPrecioValido(precio)){
            cout << "Error: Precio invalido, debe ser mayor a 0" << endl;
            return false;
        }
    }
    catch(...)
    {
        cout << "Error: Precio debe ser un numero" << endl;
        return false;
    }
    
    if (!esNumero(campos[2])) {
        cout << " Error: Cantidad debe ser un número entero" << endl;
        return false;
    }

    int cantidad = stoi(campos[2]);
    if (cantidad <= 0) {
        cout << " Error: Cantidad debe ser mayor a 0" << endl;
        return false;
    }
    
    if (campos[3].empty()) {
        cout << " Error: La categoría no puede estar vacía" << endl;
        return false;
    }
    
    cout << " Validación exitosa" << endl;
    return true;
}

bool Validador::validarPedido(const string& entrada, vector<string>& campos){
    campos = split(entrada,',');
    if (campos.size() < 2) {
        cout << " Error: Se esperan al menos 2 campos (IdCliente,Prioridad)" << endl;
        return false;
    }
    
    if (!esNumero(campos[0])) {
        cout << " Error: ID de cliente debe ser numerico" << endl;
        return false;
    }
    
    if (!esNumero(campos[1])) {
        cout << " Error: Prioridad debe ser numerica" << endl;
        return false;
    }
    
    int prioridad = stoi(campos[1]);
    if (!enRango(prioridad, 1, 3)) {
        cout << " Error: Prioridad debe estar entre 1 (urgente) y 3 (baja)" << endl;
        return false;
    }
    
    cout << " Validacion exitosa" << endl;
    return true;
}


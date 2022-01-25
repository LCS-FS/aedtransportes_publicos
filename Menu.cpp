//
// Created by Lucas Gaming on 22/01/2022.
//

#include "Menu.h"

using namespace std;

void Menu::drawEscolhaDN() {
    cout << "--- Escolha o Tipo de Horario ---" << endl;
    cout << "1 - Dia" << endl;
    cout << "2 - Noite" << endl << endl;
    cout << "0 - Sair" << endl;
}

void Menu::drawEscolhaParCor() {
    cout << "--- Como Pretende Escolher a sua Viagem? ---" << endl;
    cout << "1 - Nomes das Paragens" << endl;
    cout << "2 - Coordenadas" << endl << endl;
    cout << "0 - Sair" << endl;
}


void Menu::drawInputPar(bool origem) {
    if(origem){
        cout << "--- Indique o Nome da Paragem de Origem ---" << endl;
        cout << "Origem: ";
    }
    else{
        cout << "--- Indique o Nome da Paragem de Destino ---" << endl;
        cout << "Destino: ";
    }
}


void Menu::drawInputCoord(bool origem, bool lat) {
    if(origem){
        if(lat){
            cout << "--- Indique as Coordenadas da Latitude da Origem ---" << endl;
            cout << "Latitude: ";
        }
        else{
            cout << "--- Indique as Coordenadas de Longitude da Origem ---" << endl;
            cout << "Longitude: ";
        }
    }
    else{
        if(lat){
            cout << "--- Indique as Coordenadas da Latitude do Destino ---" << endl;
            cout << "Latitude: ";
        }
        else{
            cout << "--- Indique as Coordenadas de Longitude do Destino ---" << endl;
            cout << "Longitude: ";
        }
    }
}


int Menu::getNumInput() {
    int input = -1;
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Esta etapa so aceita numeros! Por favor evite letras e simbolos" << endl;
    }
    return input;
}

string Menu::getStrInput() {
    string input = "";
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Ocorreu um Problema. Por favor Contacte os Administradores do Sistema" << endl;
    }
    return input;
}


double Menu::getDoubleInput() {
    double input = 0.0;
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Esta etapa so aceita numeros com virgula! Por favor evite letras, simbolos e numeros inteiros." << endl;
    }
    return input;
}


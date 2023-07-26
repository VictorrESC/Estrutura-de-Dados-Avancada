#include <iostream>
#include "menu.hpp"
using namespace std;

void primeiro_menu() {
    cout << endl;
    cout << "╔═════════════════════════════════════════════╗" << endl;
    cout << "║(1) - Ver arvores                            ║" << endl;
    cout << "║(2) - Busca por dados                        ║" << endl;
    cout << "║(3) - Sair                                   ║" << endl;
    cout << "╚═════════════════════════════════════════════╝" << endl;
    cout << "⤷ Opcao: ";
}

void menu_Arvore() {
    cout << endl;
    cout << "╔═════════════════════════════════════════════╗" << endl;
    cout << "║(1) - Ver Arvore de CPF                      ║" << endl;
    cout << "║(2) - Ver Arvore de Nome                     ║" << endl;
    cout << "║(3) - Ver Arvore de Data                     ║" << endl;
    cout << "║(4) - Voltar                                 ║" << endl;
    cout << "╚═════════════════════════════════════════════╝" << endl;
    cout << "⤷ Opcao: ";
}

void menu_Busca() {
    cout << endl;
    cout << "╔═════════════════════════════════════════════╗" << endl;
    cout << "║(1) - Busca por CPF                          ║" << endl;
    cout << "║(2) - Busca por Nome                         ║" << endl;
    cout << "║(3) - Busca por intervalo de Datas           ║" << endl;
    cout << "║(4) - Voltar                                 ║" << endl;
    cout << "╚═════════════════════════════════════════════╝" << endl;
    cout << "⤷ Opcao: ";    
}

void menu_CPF() {
    cout << endl;
    cout << "Digite o CPF que voce deseja buscar: ";
    cout << "⤷  ";
}

void menu_Nome() {
    cout << "Digite o Nome que voce deseja buscar: ";
    cout << "⤷  ";
}

void menu_Datainicial() {
    cout << "Digite a data inicial do intervalo que voce deseja buscar " << endl;
    cout << "Insira o dia, o mes e o ano inicial ";
    cout << "⤷  ";
}

void menu_Datafinal() {
    cout << endl;
    cout << "Digite a data final do intervalo que voce deseja buscar " << endl;
    cout << "Insira o dia, o mes e o ano final ";
    cout << "⤷  ";
}

void menu_saida() {
    system("clear || cls");
    cout << endl;
    cout << "╔══════════════════════════════════╗\n";
    cout << "║           DESENVOLVIDO           ║\n";
    cout << "║               POR:               ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║         - VICTOR EMANUEL         ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║   CIENCIA DA COMPUTACAO 2023.1   ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║      UFC - CAMPUS DE QUIXADA     ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║            DISCIPLINA:           ║\n";
    cout << "║    ESTRUTURA DE DADOS AVANÇADA   ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║              PROJETO:            ║\n";  
    cout << "║ APLICACAO DE ARVORES BALANCEADAS ║\n";
    cout << "╠══════════════════════════════════╣\n";
    cout << "║             PROFESSOR:           ║\n";
    cout << "║            ATILIO GOMES          ║\n";
    cout << "╚══════════════════════════════════╝\n";    
}
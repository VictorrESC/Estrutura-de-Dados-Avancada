#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include "avl.hpp"
#include "pessoa.hpp"
#include "data.hpp"
#include "cpf.hpp"
#include "nome.hpp"
#include "menu.hpp"

using namespace std;
 
void le_arquivo(string dados, vector<Person> &Pessoas) {
    
    ifstream arquivo(dados);
    string line;

    if (arquivo.is_open()) {
        while (getline(arquivo, line)) {
            stringstream ss(line);
            string cpf, primeiroNome, segundoNome,data, cidade; 

            getline (ss, cpf, ',');            
            getline (ss, primeiroNome, ',');
            getline (ss, segundoNome, ',');
            getline (ss, data, ',');
            getline (ss, cidade, ',');
            
            stringstream ss2(data);
            int dia, mes, ano;
            ss2 >> mes;
            ss2.ignore(1);
            ss2 >> dia;
            ss2.ignore(1);
            ss2 >> ano;
            Data dataNascimento(mes, dia, ano);

            Person pessoa (cpf, primeiroNome, segundoNome, dataNascimento, cidade); 
            Pessoas.push_back(pessoa);
        }
    }
    else {
        cerr << "Não foi possível abrir o arquivo" << endl;   
    }

    arquivo.close();
}

// coloca os cpf do vetor de pessoas em uma arvore avl
avl_tree<Cpf> *vectorToAVL_CPF(vector<Person> &Pessoas) {
    // alocação de memória para a arvore avl com unique_ptr
    unique_ptr<avl_tree<Cpf>> cpf(new avl_tree<Cpf>());
    for (int i = 0; i < Pessoas.size(); i++) {
        Person &pessoa = Pessoas[i];
        cpf->add(pessoa.getCpf(), &pessoa);
    }
    return cpf.release();
}

// coloca as datas do vetor de pessoas em uma arvore avl
avl_tree<Data> *vectorToAVL_Data(vector<Person> &Pessoas) {
    // alocação de memória para a arvore avl com unique_ptr
    unique_ptr<avl_tree<Data>> data(new avl_tree<Data>());
    for (int i = 0; i < Pessoas.size(); i++) {
        Person &pessoa = Pessoas[i];
        data->add(pessoa.getData(), &pessoa);
    }
    return data.release();
}

// coloca os nomes do vetor de pessoas em uma arvore avl
avl_tree<Nome> *vectorToAVL_Nome(vector<Person> &Pessoas) {
    // alocação de memória para a arvore avl com unique_ptr
    unique_ptr<avl_tree<Nome>> nome(new avl_tree<Nome>());
    for (int i = 0; i < Pessoas.size(); i++) {
        Person &pessoa = Pessoas[i];
        nome->add(pessoa.getNome(), &pessoa);
    }
    return nome.release();
}

int leitura = 0;

int main() {
    system("chcp 65001 > nul");

    vector<Person> Pessoas;
    le_arquivo("data.csv", Pessoas);

    avl_tree<Cpf> *cpf = nullptr;
    cpf = vectorToAVL_CPF(Pessoas);
    avl_tree<Data> *data = nullptr;
    data = vectorToAVL_Data(Pessoas);
    avl_tree<Nome> *nome = nullptr;
    nome = vectorToAVL_Nome(Pessoas);

    int opcao;
    do 
    {
        primeiro_menu();
        cin >> opcao;
        cout << endl;
        system("clear || cls");
        switch (opcao)
        {
            case 1: 
            {
                    int opcao2;
                    do {
                        menu_Arvore();
                        cin >> opcao2;
                        system("clear || cls");
                        cout << endl;

                        switch (opcao2)
                        {
                            case 1: 
                            {  
                                system("clear || cls");
                                cout << endl;
                                cpf->bshow();
                                cout << endl;
                                cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
                                break;
                            }
                            case 2: 
                            {
                                system("clear || cls");
                                cout << endl;
                                nome->bshow();
                                cout << endl;
                                cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
                                break;
                            }
                            case 3: 
                            {
                                system("clear || cls");
                                cout << endl;
                                data->bshow();
                                cout << endl;
                                cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
                                break;
                            }
                            case 4:
                            {
                                cout << "Voltando..." << endl;
                                break; 
                            }
                            default:
                            {
                                cout << endl;
                                cerr << "Opcao invalida" << endl;
                                break;
                            }
                            break;
                        }
                    } while (opcao2 != 4);
                break;
            }
            case 2: 
            {
                int opcao3;
                do {
                    menu_Busca();
                    cin >> opcao3;
                    system("clear || cls");
                    cout << endl;

                    switch (opcao3) {
                        case 1:
                        {
                            menu_CPF();
                            string cpfBusca;
                            cin >> cpfBusca;
                            cout << endl;

                            cpf->searchCPF(cpfBusca);
                            break;
                        }
                        case 2:
                        {
                            menu_Nome();
                            string nomeBusca;
                            cin >> nomeBusca;
                            cout << endl;
                            
                            // verifica se as letras são minusculas ou maiusculas
                            if (nomeBusca[0] >= 97 && nomeBusca[0] <= 122) {
                                    nomeBusca[0] -= 32;
                                }
                            for (int i = 1; i < nomeBusca.size(); i++) {
                                if (nomeBusca[i] >= 65 && nomeBusca[i] <= 90) {
                                    nomeBusca[i] += 32;
                                }
                            }
                            nome->searchNome(nomeBusca);
                            break;
                        }
                        case 3:
                        {
                            menu_Datainicial();
                            int mes, dia, ano;
                            cin >> mes;
                            cin.ignore(1);
                            cin >> dia;
                            cin.ignore(1);
                            cin >> ano;
                            if ((mes > 12 || mes < 1) || (mes == 2 && dia > 29) || (mes == 4 && dia > 30) || (mes == 6 && dia > 30) || (mes == 9 && dia > 30) || (mes == 11 && dia > 30) || (dia > 31 || dia < 1)) {
                                cout << "Data invalida" << endl;
                                break;
                            }
                            Data dataInicial(mes, dia, ano);

                            menu_Datafinal();
                            cin >> mes;
                            cin.ignore(1);
                            cin >> dia;
                            cin.ignore(1);
                            cin >> ano;
                            if ((mes > 12 || mes < 1) || (mes == 2 && dia > 29) || (mes == 4 && dia > 30) || (mes == 6 && dia > 30) || (mes == 9 && dia > 30) || (mes == 11 && dia > 30) || (dia > 31 || dia < 1)) {
                                cout << "Data invalida" << endl;
                                break;
                            }
                            Data dataFinal(mes, dia, ano);

                            cout << endl;
                            data->searchData(dataInicial, dataFinal);

                            break;
                        }
                        case 4:
                        {
                            cout << "Voltando..." << endl;
                            break; 
                        }
                        default:
                        {
                            cout << endl;
                            cerr << "Opcao invalida" << endl;
                            break;
                        }
                        break;
                    }
                } while (opcao3 != 4);
                break;
            }
            case 3:
            {
                menu_saida();
                break;
            }
            default:
            {
                cout << endl;
                cerr << "Opcao invalida" << endl;
                break;
            }
            break;
        }
    } while (opcao != 3);

    return 0;
}
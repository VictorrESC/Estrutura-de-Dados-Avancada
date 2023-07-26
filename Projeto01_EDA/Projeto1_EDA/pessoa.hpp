#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <iostream>
#include "data.hpp"
#include "cpf.hpp"
#include "nome.hpp"
#include "node.hpp"

using namespace std;

class Person {
    private:
        Cpf cpf;
        Nome nome;
        // fomato MM/DD/AAAA
        Data data;
        string cidade;

    public:
        // método print
        void print(){
            cout << "┣━━━━━━━━━━━━━━━━     Pessoa     ━━━━━━━━━━━━━━━━━┛" << endl;
            cout << "┃"<< endl;
            cout << "┃ CPF: " << getCpf() << endl;
            cout << "┃ Nome: " << getNome() << endl;
            cout << "┃ Data de nascimento: " << data.getMes() << "/" << data.getDia() << "/" << data.getAno() << endl;
            cout << "┃ Cidade: " << cidade << endl;
        }

        //constructor
        Person(Cpf cpf, string primeiroNome, string segundoNome, Data data, string cidade){
            this->cpf = Cpf(cpf);
            this->nome = Nome(primeiroNome, segundoNome);
            this->data = Data(data.getMes(), data.getDia(), data.getAno());
            this->cidade = cidade;
        }

        // constructor default
        Person() = default;

        // getters
        Cpf getCpf(){
            return Cpf(cpf.getCpf());
        }

        Nome getNome(){
            return nome;
        }

        Data getData(){
            return Data(data.getMes(), data.getDia(), data.getAno());
        }

        string getCidade(){
            return cidade;
        }

        // sobrecarga de operadores de pessoa com todos os atributos
        bool operator<(const Person& p) const {
            if (cpf < p.cpf) {
                return true;
            } else if (cpf == p.cpf) {
                if (nome < p.nome) {
                    return true;
                } else if (nome == p.nome) {
                    if (data < p.data) {
                        return true;
                    } else if (data == p.data) {
                        if (cidade < p.cidade) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        bool operator>(const Person& p) const {
            if (cpf > p.cpf) {
                return true;
            } else if (cpf == p.cpf) {
                if (nome > p.nome) {
                    return true;
                } else if (nome == p.nome) {
                    if (data > p.data) {
                        return true;
                    } else if (data == p.data) {
                        if (cidade > p.cidade) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        bool operator==(const Person& p) const {
            if (cpf == p.cpf && nome == p.nome && data == p.data && cidade == p.cidade) {
                return true;
            }
            return false;
        }

        bool operator!=(const Person& p) const {
            if (cpf != p.cpf || nome != p.nome || data != p.data || cidade != p.cidade) {
                return true;
            }
            return false;
        }

        // sobrecarga de operador == de nome
        bool operator==(const Nome& n) const {
            if (nome == n) {
                return true;
            }
            return false;
        }

};


#endif
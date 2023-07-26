#ifndef NOME_HPP
#define NOME_HPP

#include <iostream>
#include <string>

class Nome {
    private:
        std::string primeiroNome;
        std::string segundoNome;
        std::string nome;
    public:
        // constructor
        Nome(std::string primeiroNome, std::string segundoNome) {
            this->primeiroNome = primeiroNome;
            this->segundoNome = segundoNome;
            this->nome = primeiroNome + " " + segundoNome;
        }

        // constructor default
        Nome() = default;

        std::string getNome(){
            return nome;
        }

        int size() {
            return nome.size();
        }

        bool operator<(const Nome& n) const {
            if (nome < n.nome) {
                return true;
            }
            return false;
        }

        bool operator<(const std::string& n) const {
            if (nome < n) {
                return true;
            }
            return false;
        }

        bool operator>(const Nome& n) const {
            if (nome > n.nome) {
                return true;
            }
            return false;
        }

        bool operator>(const std::string& n) const {
            if (nome > n) {
                return true;
            }
            return false;
        }

        bool operator==(const Nome& n) const {
            for (int i = 0; i < nome.size(); i++) {
                if (nome[i] != n.nome[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator==(const std::string& n) const {
            for (int i = 0; i < nome.size(); i++) {
                if (nome[i] != n[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Nome& n) const {
            if (nome != n.nome) {
                return true;
            }
            return false;
        }

        bool operator<=(const Nome& n) const {
            if (nome <= n.nome) {
                return true;
            }
            return false;
        }

        bool operator>=(const Nome& n) const {
            if (nome >= n.nome) {
                return true;
            }
            return false;
        }

        friend std::ostream& operator<<(std::ostream& os, const Nome& n) {
            os << n.primeiroNome << " " << n.segundoNome;
            return os;
        }
};


#endif
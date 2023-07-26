#ifndef CPF_HPP
#define CPF_HPP
#include <iostream>
#include <string>

struct Cpf{
    std::string cpf;

    Cpf(std::string cpf){
        this->cpf = cpf;
    }

    Cpf() = default;

    std::string getCpf(){
        return cpf;
    }

    bool operator<(const Cpf& c) const {
        if (cpf < c.cpf) {
            return true;
        }
        return false;
    }

    bool operator>(const Cpf& c) const {
        if (cpf > c.cpf) {
            return true;
        }
        return false;
    }

    bool operator==(const Cpf& c) const {
        if (cpf == c.cpf) {
            return true;
        }
        return false;
    }

    bool operator!=(const Cpf& c) const {
        if (cpf != c.cpf) {
            return true;
        }
        return false;
    }

    bool operator<=(const Cpf& c) const {
        if (cpf <= c.cpf) {
            return true;
        }
        return false;
    }

    bool operator>=(const Cpf& c) const {
        if (cpf >= c.cpf) {
            return true;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cpf& c) {
        os << c.cpf;
        return os;
    }
};

#endif
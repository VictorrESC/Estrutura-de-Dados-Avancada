#ifndef DATA_HPP
#define DATA_HPP 

#include <iostream>
#include <sstream>
#include <string>

struct Data
{
    int mes;
    int dia;
    int ano;
  
    Data(int mes, int dia, int ano) : mes(mes), dia(dia), ano(ano) {
        this->mes = mes;
        this->dia = dia;
        this->ano = ano;
    }
    Data() = default;

    int getDia() {
        return dia;
    }

    int getMes() {
        return mes;
    }

    int getAno() {
        return ano;
    }

    Data getData() {
        Data data = Data(mes, dia, ano);
        return data;
    }
    
    bool operator<(const Data& d) const {
        if (ano < d.ano) {
            return true;
        } else if (ano == d.ano) {
            if (mes < d.mes) {
                return true;
            } else if (mes == d.mes) {
                if (dia < d.dia) {
                    return true;
                }
            }
        }
        return false;
    }
    bool operator>(const Data& d) const {
        if (ano > d.ano) {
            return true;
        } else if (ano == d.ano) {
            if (mes > d.mes) {
                return true;
            } else if (mes == d.mes) {
                if (dia > d.dia) {
                    return true;
                }
            }
        }
        return false;
    }
    bool operator==(const Data& d) const {
        if (ano == d.ano && mes == d.mes && dia == d.dia) {
            return true;
        }
        return false;
    }
    bool operator>=(const Data& d) const {
        if (ano > d.ano) {
            return true;
        } else if (ano == d.ano) {
            if (mes > d.mes) {
                return true;
            } else if (mes == d.mes) {
                if (dia >= d.dia) {
                    return true;
                }
            }
        }
        return false;
    }
    bool operator<=(const Data& d) const {
        if (ano < d.ano) {
            return true;
        } else if (ano == d.ano) {
            if (mes < d.mes) {
                return true;
            } else if (mes == d.mes) {
                if (dia <= d.dia) {
                    return true;
                }
            }
        }
        return false;
    }
    bool operator!=(const Data& d) const {
        if (ano != d.ano || mes != d.mes || dia != d.dia) {
            return true;
        }
        return false;
    }
};

std::ostream& operator << (std::ostream& os, const Data& D) {
    os << D.mes << "/" << D.dia << "/" << D.ano;
    return os;
}

#endif
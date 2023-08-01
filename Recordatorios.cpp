#include <iostream>
#include <string>
#include <list>

using namespace std;

using uint = unsigned int;

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
public:
    //default constructor
    Fecha();
    //overload constructor
    Fecha(int, int);

    //getters
    int mes();
    int dia();

    //otras funciones
    bool operator==(Fecha f);
    void incrementar_dia();

private:
    int mes_;
    int dia_;
};
//default constructor
Fecha::Fecha(){
}

//overload constructor
Fecha::Fecha(int mes, int dia){
    mes_ = mes;
    dia_ = dia;
}
//getters
int Fecha::mes(){
    return mes_;
}

int Fecha::dia(){
    return dia_;
}

//otras funciones
//extender el operador << para la clase fecha
ostream& operator<<(ostream& os, Fecha f){
    os << f.dia() << "/" << f.mes();
}

//extender el operador == para la clase fecha
bool Fecha::operator==(Fecha f){
    //el this es como el self
    return ((this->dia() == f.dia()) and (this->mes() == f.mes()));
}

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
            // ene, feb, mar, abr, may, jun
            31, 28, 31, 30, 31, 30,
            // jul, ago, sep, oct, nov, dic
            31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}
void Fecha::incrementar_dia(){
    if ((this->dia() + 1) > dias_en_mes(this->mes()) ){
        if (this->mes() == 12){
            dia_ = 1;
            mes_ = 1;
        }else {
            dia_ = 1;
            mes_ = this->mes() + 1;
        }
    }else{
        dia_ = dia() + 1;
    }
}

// Ejercicio 11, 12

// Clase Horario
class Horario {
public:
    //default constructor
    Horario();
    //overload constructor
    Horario(uint, uint);

    //getters
    uint hora();
    uint min();

    //otras funciones
    bool operator==(Horario h);
    bool operator<(Horario h);

private:
    uint hora_, min_;
};
//default constructor
Horario::Horario(){
}

//overload constructor
Horario::Horario(uint hora, uint min){
    hora_ = hora;
    min_ = min;
}

//getters
uint Horario::hora(){
    return hora_;
}

uint Horario::min(){
    return min_;
}

//otras funciones
ostream& operator<<(ostream& os, Horario h){
    os << h.hora() << ":" << h.min();
}

bool Horario::operator==(Horario h){
    return ((this->hora() == h.hora()) and (this->min() == h.min()));
}

bool Horario::operator<(Horario h){
    return ((this->hora() < h.hora()) or ((this->hora()==h.hora()) and (this->min() < h.min())));
}

// Ejercicio 13

// Clase Recordatorio

class Recordatorio : public Fecha, public Horario {
public:
    //default constructor
    Recordatorio();
    //overload constructor
    Recordatorio(Fecha, Horario, string);

    //getters
    Fecha f();
    Horario h();
    string rec();

    bool operator<(Recordatorio);


private:
    Fecha f_;
    Horario h_;
    string rec_;
};

//default constructor
Recordatorio::Recordatorio() {
    //nada por aqui
}

//overload constructor
Recordatorio::Recordatorio(Fecha f, Horario h, string rec) {
    f_ = f;
    h_ = h;
    rec_ = rec;
}

//getters
Fecha Recordatorio::f() {
    return f_;
}
Horario Recordatorio::h() {
    return h_;
}
string Recordatorio::rec() {
    return rec_;
}

//otras funciones
ostream& operator<<(ostream& os, Recordatorio r){
    os << r.rec() << " @ " << r.f() << " " << r.h();
}
bool Recordatorio::operator<(Recordatorio r){
    return (this->h()).operator<(r.h());
}

// Ejercicio 14

// Clase Agenda
class Agenda : public Recordatorio {
public:
    //default constructor
    Agenda();
    //overload constructor
    Agenda(Fecha);

    //getters
    list<Recordatorio> recs();
    Fecha hoy();

    //otras funciones
    list<Recordatorio> recordatorios_de_hoy();
    void agregar_recordatorio(Recordatorio);
    void incrementar_dia();

private:
    Fecha f_;
    list<Recordatorio> recs_;
};

//default constructor
Agenda::Agenda() {
}

//overload constructor
Agenda::Agenda(Fecha f) {
    f_ = f;
}

//getters
list<Recordatorio> Agenda::recs(){
    return recs_;
}
Fecha Agenda::hoy(){
    return f_;
}

//otras funciones
list<Recordatorio> Agenda::recordatorios_de_hoy(){
    list<Recordatorio>::iterator r;
    list<Recordatorio> records = this->recs();
    list<Recordatorio> records_hoy;
    for (r = records.begin(); r != records.end(); ++r){
        if (this->hoy() == r->f()){
            records_hoy.push_front(*r);
        }
    }
    return records_hoy;
}

void Agenda::incrementar_dia() {
    f_.incrementar_dia();
}
void Agenda::agregar_recordatorio(Recordatorio r) {
    recs_.push_front(r);
}

ostream& operator<<(ostream& os, Agenda a){
    list<Recordatorio>::iterator r;
    list<Recordatorio> records = a.recordatorios_de_hoy();
    //stringstream ss;
    records.sort();
    os << a.hoy();
    os << "\n";
    os << "=====";
    os << "\n";
    for (r = records.begin(); r != records.end(); ++r){
        os << *r;
        os << "\n";
    }
}


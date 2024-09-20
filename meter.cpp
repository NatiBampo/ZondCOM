#include "meter.h"


int Meter::open_connection(const char* ip_address)
{ return 1;}

void Meter::close_connection(){}

int Meter::write_package(const char*)
{ return 0;}

const char* Meter::read_responce(const char*)
{ return "";}

void Meter::zero_correction(int){}
void Meter::set_05V(int, int){}
void Meter::set_1V(int){}
void Meter::set_10mV(int){}

QList<double> Meter::single_measurement(struct Delays*)
{
    QList<double> res;
    return res;
}

double Meter::forward_current(struct Delays*)
{return 0.0;}


void Meter::dark_currents()
{}

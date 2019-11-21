#include "simulator.h"
#include <cmath>

//----------------------------------------------------------------------
component::component(connection& A, connection& B) : a{A}, b{B} { }
double component::voltage() const
{
    return std::abs(a.voltage - b.voltage);
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
battery::battery(connection& A, connection& B, double base_voltage)
    : component{A, B}, base_voltage{base_voltage} { }

double battery::current() const
{
    return 0;
}
void battery::update(double time_step)
{
    a.voltage = base_voltage;
    b.voltage = 0;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
resistor::resistor(connection& A, connection& B, double resistance)
    : component{A, B}, resistance{resistance} { }

double resistor::current() const
{
    return voltage() / resistance;
}
void resistor::update(double time_step)
{
    connection* most_charged;
    connection* least_charged;
    if (std::abs(a.voltage) > std::abs(b.voltage))
    {
	most_charged = &a;
	least_charged = &b;
    }
    else
    {
	most_charged = &b;
	least_charged = &a;
    }
    double moved{time_step * current()};
    most_charged->voltage -= moved;
    least_charged->voltage += moved;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
capacitor::capacitor(connection& A, connection& B, double capacitance)
    : component{A, B}, capacitance{capacitance}, charge{0} { }

double capacitor::current() const
{
    return capacitance * (voltage() - charge);
}
void capacitor::update(double time_step)
{
    connection* most_positive;
    connection* least_positive;
    if (a.voltage > b.voltage)
    {
	most_positive = &a;
	least_positive = &b;
    }
    else
    {
	most_positive = &b;
	least_positive = &a;
    }
    double moved{time_step * current()};
    most_positive->voltage -= moved;
    charge += moved;
    least_positive->voltage += moved;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
void circuit::simulate(int iterations, int lines, double time_step) { }
//----------------------------------------------------------------------

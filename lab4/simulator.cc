#include "simulator.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

//----------------------------------------------------------------------
component::component(std::string const& name, connection& A, connection& B)
    : name{name}, a{A}, b{B} { }
double component::voltage() const
{
    return std::abs(a.voltage - b.voltage);
}
std::string component::get_name() const
{
    return name;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
battery::battery(std::string const& name, connection& A, connection& B, double base_voltage)
    : component{name, A, B}, base_voltage{base_voltage} { }

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
resistor::resistor(std::string const& name, connection& A, connection& B, double resistance)
    : component{name, A, B}, resistance{resistance} { }

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
capacitor::capacitor(std::string const& name, connection& A, connection& B, double capacitance)
    : component{name, A, B}, capacitance{capacitance}, charge{0} { }

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
void circuit::add_bat(std::string const& name, connection& A, connection& B, double base_voltage)
{
    components.push_back(new battery(name, A, B, base_voltage));
}

void circuit::add_res(std::string const& name, connection& A, connection& B, double resistance)
{
    components.push_back(new resistor(name, A, B, resistance));
}
void circuit::add_cap(std::string const& name, connection& A, connection& B, double capacitance)
{
    components.push_back(new capacitor(name, A, B, capacitance));
}

void circuit::simulate(int iterations, int lines, double time_step)
{
    std::ostringstream oss;
    for (component* cpn : components)
    {
        std::cout << std::setw(12) << cpn->get_name();
        oss << std::setw(6) << "Volt" << std::setw(6) << "Curr";
    }
    std::cout << std::endl << oss.str() << std::endl;

    std::cout << std::setprecision(2) << std::fixed;
    for (int i = 0; i < iterations; ++i)
    {
        for (component* cpn : components)
        {
            cpn->update(time_step);
            if (i % (iterations / lines) == 0)
            {
                std::cout << std::setw(6) << cpn->voltage()
                          << std::setw(6) << cpn->current();
            }
        }
        if (i % (iterations / lines) == 0)
            std::cout << std::endl;
    }
}
circuit::~circuit()
{
    for (component* cpn : components)
    {
	delete cpn;
    }
}
//----------------------------------------------------------------------

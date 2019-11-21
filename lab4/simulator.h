#pragma once

#include <vector>

struct connection
{
    double voltage;
};


class component
{
public:
    connection& a, b;

    component(connection& A, connection& B);
    
    double voltage() const;
    virtual double current() const = 0;

    virtual void update(double time_step) = 0;
};

class battery : public component
{
public:
    double base_voltage;

    battery(connection& A, connection& B, double base_voltage);

    double current() const override;

    void update(double time_step) override;
};

class resistor : public component
{
public:
    double resistance;

    resistor(connection& A, connection& B, double resistance);

    double current() const override;

    void update(double time_step) override;
};

class capacitor : public component
{
public:
    double capacitance, charge;
    
    capacitor(connection& A, connection& B, double capacitance);

    double current() const override;

    void update(double time_step) override;
};


class circuit
{
public:
    std::vector<connection> connections;
    std::vector<component> components;

    void simulate(int iterations, int lines, double time_step);
};

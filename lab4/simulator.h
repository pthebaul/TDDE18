#pragma once

#include <vector>
#include <string>

struct connection
{
    double voltage;
};


class component
{
public:
    std::string name;
    connection& a;
    connection& b;

    component(std::string const& name, connection& A, connection& B);
    
    double voltage() const;
    virtual double current() const = 0;

    virtual void update(double time_step) = 0;
};

class battery : public component
{
public:
    double base_voltage;

    battery(std::string const& name, connection& A, connection& B, double base_voltage);

    double current() const override;

    void update(double time_step) override;
};

class resistor : public component
{
public:
    double resistance;

    resistor(std::string const& name, connection& A, connection& B, double resistance);

    double current() const override;

    void update(double time_step) override;
};

class capacitor : public component
{
public:
    double capacitance, charge;
    
    capacitor(std::string const& name, connection& A, connection& B, double capacitance);

    double current() const override;

    void update(double time_step) override;
};


class circuit
{
public:
    void add_bat(std::string const& name, connection& A, connection& B, double base_voltage);
    void add_res(std::string const& name, connection& A, connection& B, double resistance);
    void add_cap(std::string const& name, connection& A, connection& B, double capacitance);

    void simulate(int iterations, int lines, double time_step);
private:
    std::vector<component*> components;
};

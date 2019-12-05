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
    component(std::string const& name, connection& A, connection& B);

    double voltage() const;
    virtual double current() const = 0;
    std::string get_name() const;

    virtual void update(double time_step) = 0;

    virtual ~component() = default;
    
protected:
    std::string name;
    connection& a;
    connection& b;
};

class battery : public component
{
public:
    battery(std::string const& name, connection& A, connection& B, double base_voltage);

    double current() const override;

    void update(double time_step) override;

private:
    double base_voltage;
};

class resistor : public component
{
public:
    resistor(std::string const& name, connection& A, connection& B, double resistance);

    double current() const override;

    void update(double time_step) override;

private:
    double resistance;
};

class capacitor : public component
{
public:
    capacitor(std::string const& name, connection& A, connection& B, double capacitance);

    double current() const override;

    void update(double time_step) override;

private:
    double capacitance, charge;
};


class circuit
{
public:
    void add_bat(std::string const& name, connection& A, connection& B, double base_voltage);
    void add_res(std::string const& name, connection& A, connection& B, double resistance);
    void add_cap(std::string const& name, connection& A, connection& B, double capacitance);

    void simulate(int iterations, int lines, double time_step);

    ~circuit();

private:
    std::vector<component*> components;
};

#include "simulator.h"
#include <iostream>
#include <iomanip>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cout << "Syntax error: exit 1" << std::endl;
        return 1;
    }

    int iterations;
    int lines;
    double time_step;
    double base_voltage;

    try
    {
	iterations   = std::stoi(argv[1]);
	lines        = std::stoi(argv[2]);
	time_step    = std::stod(argv[3]);
	base_voltage = std::stod(argv[4]);
    }
    catch (std::invalid_argument& e)
    {
        std::cout << "Type error: exit 2" << std::endl;
        return 2;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Out of range error: exit 3" << std::endl;
        return 3;
    }
    catch (std::exception& e)
    {
        std::cout << "Unknown error: exit 4" << std::endl;
        return 4;
    }

    std::cout << "Iter: " << iterations << "; Lines: " << lines
	      << "; Step: " << time_step << "; Voltage: " << base_voltage << std::endl << std::endl;
    //--------------------------------------------------------------------
    {
        connection p, n, r124, r23;
        circuit c1;

        c1.add_bat(std::string("Bat"), p, n, base_voltage);
        c1.add_res(std::string("R1"), r124, p, 6);
        c1.add_res(std::string("R2"), r23, r124, 4);
        c1.add_res(std::string("R3"), n, r23, 8);
        c1.add_res(std::string("R4"), n, r124, 12);

        c1.simulate(iterations, lines, time_step);
    }
    {
        connection p, n, l, r;
        circuit c2;

        c2.add_bat(std::string("Bat"), p, n, base_voltage);
        c2.add_res(std::string("R1"), l, p, 150);
        c2.add_res(std::string("R2"), r, p, 50);
        c2.add_res(std::string("R3"), r, l, 100);
        c2.add_res(std::string("R4"), n, l, 300);
        c2.add_res(std::string("R5"), n, r, 250);

        c2.simulate(iterations, lines, time_step);
    }
    {
        connection p, n, l, r;
        circuit c3;

        c3.add_bat(std::string("Bat"), p, n, base_voltage);
        c3.add_res(std::string("R1"), l, p, 150);
        c3.add_res(std::string("R2"), r, p, 50);
        c3.add_cap(std::string("C3"), r, l, 1);
        c3.add_res(std::string("R4"), n, l, 300);
        c3.add_cap(std::string("C5"), n, r, 0.75);

        c3.simulate(iterations, lines, time_step);
    }
    return 0;
}

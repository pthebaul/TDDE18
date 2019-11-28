#include "simulator.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
	std::cout << "Syntax error: exit 1" << std::endl;
	return 1;
    }

    std::stringstream ss;
    for (int i = 1; i < argc; ++i)
    {
	ss << argv[i] << " ";
    }

    int iterations;
    ss >> iterations;
    
    int lines;
    ss >> lines;
    
    double time_step;
    ss >> time_step;
    
    double base_voltage;
    ss >> base_voltage;

    if (ss.fail())
    {
	std::cout << "Type error: exit 2" << std::endl;
	return 2;
    }
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
    return 0;
}

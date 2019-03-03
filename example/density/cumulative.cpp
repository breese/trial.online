// Read a file containing x,y coordinates and output the cumulative density of y

#include <iostream>
#include <iomanip>
#include <fstream>
#include <trial/online/cumulative/hermite_density.hpp>

using namespace trial::online;

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    cumulative::hermite_cumulated_density<double, 5> filter;

    double x;
    double y;
    char separator;

    std::ifstream file(argv[1]);
    while (file)
    {
        file >> x >> separator >> y;
        filter.push(y);
    }

    const auto step = (filter.upper() - filter.lower()) / 1000;
    for (auto position = filter.lower(); position <= filter.upper(); position += step)
    {
        std::cout << std::setprecision(15)
                  << position
                  << separator << filter.at(position)
                  << separator << filter.until(position)
                  << '\n';
    }
    return 0;
}

// Read a file containing x,y coordinates and output the cumulative regression

#include <iostream>
#include <fstream>
#include <trial/online/window/regression.hpp>

using namespace trial::online;

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    window::regression<double, 64> filter;

    double x;
    double y;
    char separator;

    std::ifstream file(argv[1]);
    while (file)
    {
        file >> x >> separator >> y;
        filter.push(x, y);
        std::cout << x << ',' << y << ',' << filter.slope() << ',' << filter.at(0) << '\n';
    }
    return 0;
}

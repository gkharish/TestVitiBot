#include "radar_span.hpp"

bool compareIndices(const std::pair<int, double> &a, const std::pair<int, double>  &b) {
    return a.second < b.second;
}

RadarSpan::RadarSpan()
{

}

RadarSpan::~RadarSpan()
{
    
}

double RadarSpan::getDistance(double& x, double& y)
{
    return sqrt(x*x + y*y);
}

double RadarSpan::getAngularDistance(double& x, double& y)
{
    auto ang = std::atan2(y,x);

}

void RadarSpan::loadInputFile()
{
    std::ifstream input_file_("input1.txt");

    

}

int  main(int * argc, char ** argv)
{
    std::cout << "Hello Radara world!" << std::endl;

}


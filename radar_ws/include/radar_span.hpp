#pragma once

#include "iostream"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

class RadarSpan
{
public: 
    RadarSpan();
    ~RadarSpan();

    void orderRadarInput(std::ifstream& input_file);

    double getDistance(double& x, double& y);
    double getAngularDistance(double& x, double& y);

private:
    std::vector<std::pair<int, double>> m_indexed_angular_dist;

    double m_visibility_range;
    int m_number_obstacles;
};

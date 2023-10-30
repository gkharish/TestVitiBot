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
void loadInputFile();

double getDistance(double& x, double& y);
double getAngularDistance(double& x, double& y);




private:
std::vector<std::pair<int, double>> indexed_angular_dist_;
std::vector<double> angular_dist_store_;
std::vector<int> sorted_obstacle_index_;


std::string input_file_name_ = "1-Radar/input1.txt";
std::string output_file_name = "1-Radar/tets_output1.txt";


double visibility_range_;
int number_obstacles_;

};

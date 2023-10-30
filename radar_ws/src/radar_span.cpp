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
    if (ang < 0.) 
        ang += 2*M_PI;
    return ang;
}

void RadarSpan::orderRadarInput(std::ifstream& input_file)
{
    if (!input_file.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }
    std::string line;
    
    int idx = 0;
    while (std::getline(input_file, line)) {
        std::stringstream iss(line);
        idx++;

        if(idx == 1)
        {   
            iss >> visibility_range_;
            continue;
        }
            
       
       if(idx == 2)
       {
            iss >> number_obstacles_;
            continue;
       }

        

        double x,y;
        iss >> x >> y;
 

        if (getDistance(x,y) > visibility_range_)
            continue;
        indexed_angular_dist_.push_back({idx-3, getAngularDistance(x,y)});

    }

    std::cout << "Debug: angular_dist_store_ " << indexed_angular_dist_.size() << std::endl;;

    // Sort the array and display the output
    std::sort(indexed_angular_dist_.begin(), indexed_angular_dist_.end(), compareIndices);
    
    // Extract the sorted indices
    // std::vector<int> sortedIndices;
    for (const auto &pair : indexed_angular_dist_) {
        sorted_obstacle_index_.push_back(pair.first);
        std::cout << pair.first << " ";
    }

}

int  main(int * argc, char ** argv)
{
    std::cout << "'Hello Radar world!\n" << std::endl;
    std::ifstream input_file("test_input/input2.txt");
    RadarSpan rad_span;
    rad_span.orderRadarInput(input_file);
    std::cout << "\n\n Radara spannig done!!" << std::endl;
    input_file.close();

}


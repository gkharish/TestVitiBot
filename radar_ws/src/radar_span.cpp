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

void RadarSpan::loadInputFile()
{
    std::ifstream input_file_("test_input/input2.txt");

    if (!input_file_.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }
    std::string line;
    
    int idx = 0;
    while (std::getline(input_file_, line)) {
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


    // Display the angles 
    for (auto ang : angular_dist_store_) {
        std::cout << ang*180.0/M_PI << std::endl;
    }
    std::cout << "Debug: indexed_angular_dist_ " << indexed_angular_dist_.size() << std::endl;;

    // Sort the array and display the output
    std::sort(indexed_angular_dist_.begin(), indexed_angular_dist_.end(), compareIndices);
    
    // Extract the sorted indices
    // std::vector<int> sortedIndices;
    for (const auto &pair : indexed_angular_dist_) {
        sorted_obstacle_index_.push_back(pair.first);
        std::cout << pair.first << " " << pair.second*180.0/M_PI << std::endl;
    }

}

int  main(int * argc, char ** argv)
{
    std::cout << "Hello Radar world!" << std::endl;
    RadarSpan rad_span;
    rad_span.loadInputFile();
    std::cout << " Radara spannig done!!" << std::endl;

}

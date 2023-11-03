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

        double x, y;
        iss >> x >> y;
 

        if (getDistance(x, y) > visibility_range_)
            continue;
        indexed_angular_dist_.push_back({idx-3, getAngularDistance(x, y)});

    }

    std::cout << "Debug: angular_dist_store_ " << indexed_angular_dist_.size() << std::endl;

    // Sort the array 
    std::sort(indexed_angular_dist_.begin(), indexed_angular_dist_.end(), compareIndices);
    
    // Extract the sorted indices and display the output
    for (const auto &pair : indexed_angular_dist_) {
        std::cout << pair.first << " ";
    }

}

int  main(int  argc, char ** argv)
{
    std::cout << "'Hello Radar world!\n" << std::endl;
    std::string input_file_name = "test_input/input5.txt";
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        std::cout << "WARNING: Using default file name: " << input_file_name << std::endl;
    }
    else 
    {
        // Get the filename from the command-line arguments.
        input_file_name = argv[1];
    }
    std::ifstream input_file(input_file_name);

    RadarSpan rad_span;
    rad_span.orderRadarInput(input_file);

    std::cout << "\n\n Radar spannig done!!" << std::endl;
    input_file.close();

}


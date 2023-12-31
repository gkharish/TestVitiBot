#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <math.h>
#include <cmath>
#include <algorithm>
#include <random>

class Ransac 
{
public:

    Ransac(int n, int k,  int d, double  t );
    Ransac(std::string config_file_name);

    ~Ransac();

    typedef struct coordinate{
        float x;
        float y;
    }Coordinate;
   
    std::pair<double, double>  calculateSlopeIntercept(std::vector<Coordinate>& coordinate_list); // model 
   
    void extractDataFromInput(const std::string file_name);
    
    std::pair<std::vector<Coordinate>, std::vector<Coordinate>> generateRandomSamples(int num_sample); 

    double getDistanceFromLineError(float x, float y, double slope, double intercept); // Error model

    double sumOfSquaredError(std::vector<Coordinate>& coordinate_list, double slope, double intercept);
   
    std::pair<double, double>  ransacFit();
    
    void loadConfigFile(std::string config_file_name);

private:
    std::vector<Coordinate> m_entire_data_points;

    double m_slope, m_intercept;
    
    // regression parameter
    int n, k, d;
    double  t;   
};
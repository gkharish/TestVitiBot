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

    ~Ransac();

    typedef struct coordinate{
        float x;
        float y;
    }Coordinate;

    // std::pair<double, double>  calculateSlopeIntercept(std::vector<float>& x, std::vector<float>& y);
    
    std::pair<double, double>  calculateSlopeIntercept(std::vector<Coordinate>& coordinate_list);
   

    void extractDataFromInput(const std::string file_name);
    
    void generateRandomSamples(int num_sample);

    void errorModel();

    double getDistanceFromLineError(float x, float y, double slope, double intercept);

    // double sumOfSquaredError(std::vector<float>selected_x, std::vector<float>selected_y, double slope, double intercept);
    double sumOfSquaredError(std::vector<Coordinate>& coordinate_list, double slope, double intercept);
   
    std::pair<double, double>  ransacFit();

private:
    int m_length;
    // std::vector<float> m_x, m_selected_x, m_nonselected_x;
    // std::vector<float> m_y, m_selected_y, m_nonselected_y;

    std::vector<Coordinate> m_entire_data_points;
    std::vector<Coordinate> m_selected_data_points;
    std::vector<Coordinate> m_nonselected_data_points;

    double m_slope, m_intercept;
    
    int n, k, d;
    double  t;

    // regression parameter
    
};
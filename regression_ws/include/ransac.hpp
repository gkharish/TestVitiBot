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

    Ransac(int n, int k,  int d, float t );

    ~Ransac();


    std::pair<double, double>  calculateSlopeIntercept(std::vector<float>& x, std::vector<float>& y);
    
    float predict(float& input_x);
    
    float sumOfSquaredError();

    float errorIn(float num);

    void extractDataFromInput(const std::string file_name);
    
    void generateRandomSamples(int num_sample);

    void errorModel();

    float getDistanceFromLineError(float x, float y, float slope, float intercept);

    double sumOfSquaredError(std::vector<float>selected_x, std::vector<float>selected_y, float slope, float intercept);
    
    std::pair<double, double>  ransacFit();

private:
    int m_length;
    std::vector<float> m_x, m_random_x, m_nonselected_x;
    std::vector<float> m_y, m_random_y, m_nonselected_y;

    float m_slope, m_intercept;
    int n, k, d;
    float t;

    // regression parameter
    
};
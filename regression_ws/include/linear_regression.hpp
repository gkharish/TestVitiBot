#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <math.h>
#include <cmath>
#include <algorithm>

class LinearRegression 
{
public:

    LinearRegression(int n);

    ~LinearRegression();

    void  calculateSlopeIntercept();

    float predict(float& input_x);
    float sumOfSquaredError();

    float errorIn(float num);

    void extractDataFromInput(const std::string file_name);
    
    std::vector<float> getModel();

private:
    int m_length;
    std::vector<float>m_model;
    std::vector<float> m_x;
    std::vector<float> m_y;

    float m_slope, m_intercept;

    float m_sum_x;
    float m_sum_y;
    float m_sum_xy;
    float m_sum_x2;
    float m_sum_y2;

    // regression parameter
    
};
#include "linear_regression.hpp"

LinearRegression::LinearRegression()
{

}

LinearRegression::~LinearRegression()
{
    
}

void  LinearRegression::calculateIntercept()
{
    int data_size = m_x.size();

    // intercept
    float numerator
            = (m_sum_y *m_sum_x2 - m_sum_x * m_sum_xy);
    
    float denominator
            = (data_size * m_sum_x2 - m_sum_x * m_sum_x);
    
    m_intercept = numerator / denominator;

    // Slope
    float numerator
            = (data_size*m_sum_xy - m_sum_x * m_sum_y);
    
    m_slope = numerator / denominator;

}

void  LinearRegression::calculateSlope()
{
    int data_size = m_x.size();
    float numerator
            = (data_size*m_sum_xy - m_sum_x * m_sum_y);
    
    float denominator
            = (data_size * m_sum_x2 - m_sum_x * m_sum_x);
    
    m_slope = numerator / denominator;

}
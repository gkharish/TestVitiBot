#include "linear_regression.hpp"

LinearRegression::LinearRegression()
{

    m_sum_x = 0.f;
    m_sum_y = 0.f;
    m_sum_xy = 0.f;
    m_sum_x2 = 0.f;
    m_sum_y2 = 0.f;
}

LinearRegression::~LinearRegression()
{
    
}

void  LinearRegression::calculateSlopeIntercept()
{
    int data_size = m_x.size();

    // intercept
    float numerator_intercept
            = (m_sum_y *m_sum_x2 - m_sum_x * m_sum_xy);
    
    float denominator
            = (data_size * m_sum_x2 - m_sum_x * m_sum_x);
    
    m_intercept = numerator_intercept / denominator;

    // Slope
    float numerator_slope
            = (data_size*m_sum_xy - m_sum_x * m_sum_y);
    
    m_slope = numerator_slope / denominator;

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

void LinearRegression::extractDataFromInput(const std::string file_name)
{
    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }
    std::string line;


    while(std::getline(input_file, line))
    {
        std::stringstream ss(line);
        float x,y;
        ss >>x >>y;

        m_x.push_back(x);
        m_y.push_back(x);

        m_sum_x += x;
        m_sum_y += y;

        m_sum_xy += x*y;

        m_sum_y2 += y*y;
        m_sum_x2 += x*x;
    }

    input_file.close();
}

std::vector<float> LinearRegression::getModel()
{
    calculateSlopeIntercept();

    m_model.push_back(m_slope);
    m_model.push_back(m_intercept);

    return m_model;
}

int  main(int * argc, char ** argv)
{
    std::cout << "'Linear Regression module!\n" << std::endl;
    std::string input_file_name = ("test_input/input.txt");

    LinearRegression linear_regression;
    linear_regression.extractDataFromInput(input_file_name);
    auto model = linear_regression.getModel();

    std::cout << "\n\n Linear model slope: " << model[0]<< std::endl;
    std::cout << "\n\n Linear model intercept: " << model[1]<< std::endl;

}

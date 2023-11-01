#include "ransac.hpp"

Ransac::Ransac(int n, int k,  int d, float t ):n(n), k(k), d(d), t(t)
{

}

Ransac::~Ransac()
{
    
}

std::pair<double, double>  Ransac::calculateSlopeIntercept(std::vector<float>& x, std::vector<float>& y)
{
    auto data_size = x.size();
    float sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;

    for (auto i =0; i < data_size; i++)
    {
        sum_x += x[i];
        sum_y += y[i];

        sum_xy += x[i]*y[i];
        sum_x2 += x[i]*x[i];
    }

        // intercept
    float numerator_intercept
            = (sum_y *sum_x2 - sum_x * sum_xy);
    
    float denominator
            = (data_size * sum_x2 - sum_x * sum_x);
    
    float intercept = numerator_intercept / denominator;

    // Slope
    float numerator_slope
            = (data_size*sum_xy - sum_x * sum_y);
    
    float slope = numerator_slope / denominator;

    return std::make_pair(slope, intercept);
}

void Ransac::extractDataFromInput(const std::string file_name)
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
        m_y.push_back(y);
    }

    input_file.close();
}

void Ransac::generateRandomSamples(int num_sample)
{
    auto data_size = m_x.size();
    if (num_sample <= 0 || num_sample > data_size) 
    {
        std::cerr << "Invalid sample size." << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, data_size - 1);

    m_nonselected_x = m_x;
    m_nonselected_y = m_y;
    for (int i = 0; i < num_sample; ++i) 
    {
        int index = distribution(gen);
        m_random_x.push_back(m_x[index]);
        m_random_y.push_back(m_y[index]);
        m_nonselected_x.erase(m_nonselected_x.begin() + index);
        m_nonselected_y.erase(m_nonselected_y.begin() + index);
    }
    std::cout << "Debug in generateRandomSamples: " << m_random_x.size() << ", " << m_nonselected_x.size() << ", " << m_x.size() << std::endl;
}

float Ransac::getDistanceFromLineError(float x, float y, float slope, float intercept)
{
    auto dist = std::abs(slope * x - y + intercept) / std::sqrt( slope* slope + 1);

     std::cout << "getDistanceFromLineError: "  << x << ", " << y  << ", " << slope << ", " << intercept << std::endl;

    return dist;
}

double Ransac::sumOfSquaredError(std::vector<float>selected_x, std::vector<float>selected_y, float slope, float intercept)
{
    float sumError = 0.f;
    for (auto i =0; i < selected_x.size(); i++)
    {
        sumError += getDistanceFromLineError(selected_x[i], selected_y[i], slope, intercept);
    }
}

// main algo is here!
std::pair<double, double>  Ransac::ransacFit()
{
    int iterations = 0;
    std::pair<double, double>  best_model;
    double best_error = 1.0*1e10;


    while (iterations < k)
    {
        generateRandomSamples(n);
        auto model = calculateSlopeIntercept(m_random_x, m_random_y);

   

        for(auto i = 0; i < m_nonselected_x.size(); ++i)
        {
            auto err = getDistanceFromLineError(m_nonselected_x[i], m_nonselected_y[i], model.first, model.second);
            if (err < t)
            {
                m_random_x.push_back(m_nonselected_x[i]);
                m_random_y.push_back(m_nonselected_y[i]);
            }
        }
    
        if (m_random_x.size() > d)
        {
            auto better_model = calculateSlopeIntercept(m_random_x, m_random_y);
            auto sum_err = sumOfSquaredError(m_random_x, m_random_y, better_model.first, better_model.second);

            if (sum_err < best_error)
            {
                best_model = better_model;
                best_error = sum_err;
            }
        }
        // reset all vectors
        m_random_x.clear();
        m_random_y.clear();
        m_nonselected_x.clear();
        m_nonselected_y.clear();

        iterations++;
        std::cout << "Debug in ransacFit: iter="<< iterations << std::endl;
    }

    return best_model;
}


int  main(int * argc, char ** argv)
{
    std::cout << "'Ransac using Linear Regression!\n" << std::endl;
    std::string input_file_name = ("test_input/input.txt");

    // Ransac parameters
    int n = 2;
    int k = 85;
    int d = 20;
    float t =  0.02;

    Ransac ransac(n,k,d,t);
    ransac.extractDataFromInput(input_file_name);
    auto bes_model = ransac.ransacFit();

    std::cout << "\n Best ransacFit Linear model slope: " << bes_model.first<< std::endl;
    std::cout << "\n Best ransacFit Linear model intercept: " << bes_model.second<< std::endl;

}


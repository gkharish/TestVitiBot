#include "ransac.hpp"

Ransac::Ransac(int n, int k,  int d, double t ):n(n), k(k), d(d), t(t)
{

}

Ransac::~Ransac()
{
    
}

std::pair<double, double>  Ransac::calculateSlopeIntercept(std::vector<Coordinate>& coordinate_list)
{
    auto data_size = coordinate_list.size();
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;

    for (auto i =0; i < data_size; i++)
    {
        sum_x += coordinate_list[i].x;
        sum_y += coordinate_list[i].y;

        sum_xy += coordinate_list[i].x * coordinate_list[i].y;
        sum_x2 += coordinate_list[i].x * coordinate_list[i].x ;
    }

        // intercept
    double numerator_intercept
            = (sum_y *sum_x2 - sum_x * sum_xy);
    
    double denominator
            = (data_size * sum_x2 - sum_x * sum_x);
    
    double intercept = numerator_intercept / denominator;

    // Slope
    double numerator_slope
            = (data_size*sum_xy - sum_x * sum_y);
    
    double slope = numerator_slope / denominator;

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

        Coordinate point;
        point.x = x;
        point.y = y;
        m_entire_data_points.push_back(point);
    }

    input_file.close();
}

void Ransac::generateRandomSamples(int num_sample)
{
    auto data_size = m_entire_data_points.size();

    if (num_sample <= 0 || num_sample > data_size) 
    {
        std::cerr << "Invalid sample size." << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, data_size - 1);

    // Getting selected n samples
    std::vector<int> selected_index;
    for (int i = 0; i < num_sample; ++i) 
    {
        int index = distribution(gen);
  
        Coordinate point_selected = m_entire_data_points[index];
        m_selected_data_points.push_back(point_selected);

        selected_index.push_back(index);
    }

    // Getting a vector of non selected samples
    for(int i = 0; i < data_size; ++i)
    {
        bool is_already_selected = false ;
        for(int j =0; j < num_sample; ++j)
        {
            if (i == selected_index[j])
            {
                is_already_selected = true;
                break;
            }
        }
        if(!is_already_selected)
        {

            Coordinate point_nonselected = m_entire_data_points[i];
            m_nonselected_data_points.push_back(point_nonselected);
        }
        
    }
}

double Ransac::getDistanceFromLineError(float x, float y, double slope, double intercept)
{
    double dist = std::abs(slope * x - y + intercept) / std::sqrt( slope* slope + 1);
    return dist;
}


double Ransac::sumOfSquaredError(std::vector<Coordinate>& selected_coordinate_list, double slope, double intercept)
{
    double  sumError = 0.0;
    for (auto i =0; i < selected_coordinate_list.size(); i++)
    {
        sumError += getDistanceFromLineError(selected_coordinate_list[i].x, selected_coordinate_list[i].y, slope, intercept);
    }
    std::cout << "Debug in sumOfSquaredError:1 "  << ", "<< sumError << std::endl;
    return sumError;
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
        auto model = calculateSlopeIntercept(m_selected_data_points);

   

        for(auto i = 0; i < m_nonselected_data_points.size(); ++i)
        {
            auto err = getDistanceFromLineError(m_nonselected_data_points[i].x, m_nonselected_data_points[i].y, model.first, model.second);
            if (err < t)
            {
                m_selected_data_points.push_back(m_nonselected_data_points[i]);

            }
        }

        if (m_selected_data_points.size() > d)
        {
            auto better_model = calculateSlopeIntercept(m_selected_data_points);
            auto sum_err = sumOfSquaredError(m_selected_data_points, better_model.first, better_model.second);
            if (sum_err < best_error)
            {
                best_model = better_model;
                best_error = sum_err;
            }
        }
        // reset all vectors
        m_selected_data_points.clear();
        m_nonselected_data_points.clear();


        iterations++;

        std::cout << "Debug in ransacFit: iter="<< iterations << std::endl;

    }

    return best_model;
}


int  main(int argc, char ** argv)
{
    std::cout << "'Ransac using Linear Regression!\n" << std::endl;
    std::string input_file_name = ("test_input/input.txt");

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        std::cout << "WARNING: Using default file name: " << input_file_name << std::endl;
    }
    else 
    {
        // Get the filename from the command-line arguments.
        input_file_name = argv[1];
    }

    // Ransac parameters
    int n = 2;
    int k = 85;
    int d = 20;
    double t =  0.02;

    Ransac ransac(n,k,d,t);
    ransac.extractDataFromInput(input_file_name);
    auto best_model = ransac.ransacFit();

    std::cout << "\n Best ransacFit Linear model slope: " << best_model.first<< std::endl;
    std::cout << "\n Best ransacFit Linear model intercept: " << best_model.second<< std::endl;

}


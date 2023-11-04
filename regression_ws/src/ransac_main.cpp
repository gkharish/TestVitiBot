#include "ransac.hpp"

void launchRansac(std::string& input_file_name, std::string& config_file_name)
{
    Ransac ransac(config_file_name);
    ransac.extractDataFromInput(input_file_name);
    auto best_model = ransac.ransacFit();

    std::cout << "\n Best ransacFit Linear model slope: " << best_model.first<< std::endl;
    std::cout << "\n Best ransacFit Linear model intercept: " << best_model.second<< std::endl;

}

int  main(int argc, char ** argv)
{
    std::cout << "'Ransac using Linear Regression!\n" << std::endl;
    std::string input_file_name = ("test_input/input.txt");
    std::string config_file_name = ("config.txt");

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        std::cout << "WARNING: Using default file name: " << input_file_name << std::endl;
    }
    else 
    {
        // Get the filename from the command-line arguments.
        input_file_name = argv[1];
    }

    launchRansac(input_file_name, config_file_name);
}
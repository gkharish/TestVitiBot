
#include "ransac.hpp"
#include <gtest/gtest.h>


TEST(basicFunsuite, getDistanceFromLine) 
{
    int n = 2;
    int k = 85;
    int d = 20;
    double t = 0.02;

    Ransac ransac = Ransac(n,k,d,t);

    // test distance from line
    // let it be a line along x axis then y = 0*x + 0 and point p(1, 1)
    auto dist = ransac.getDistanceFromLineError(1.f, 1.f, 0.f, 0.f);
    EXPECT_EQ(dist, 1.0);
}

TEST(basicFunsuite, sumOfSquaredError) 
{
    int n = 2;
    int k = 85;
    int d = 20;
    double t = 0.02;

    Ransac ransac = Ransac(n,k,d,t);

    // test sum of distance from line
    // let it be a line along x axis then y = 0*x + 0 and set of points on y-axis
    Ransac::Coordinate p;
    std::vector<Ransac::Coordinate> p_list;
    for (auto i = 1; i <= 5;  ++i)
    {
        p.y = 1.f*i; p.x = 0;
        p_list.push_back(p);
    }
    auto sum_err = ransac.sumOfSquaredError(p_list, 0.f, 0.f);

    EXPECT_EQ(sum_err, 15.0);
}

TEST(basicFunsuite, calculateSlopeIntercept) 
{
    int n = 2;
    int k = 85;
    int d = 20;
    double t = 0.02;

    Ransac ransac = Ransac(n,k,d,t);

    // test model estimation
    // Expected model is y = 1*x + 0. So m = 1 and c = 0
    Ransac::Coordinate p;
    std::vector<Ransac::Coordinate> p_list;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 0.3);
    
    for (auto i = 1; i <= 5;  ++i)
    {
        p.x = 1.f*i + dist(gen); p.y = 1.f*i + dist(gen);
        p_list.push_back(p);
    }
    auto model = ransac.calculateSlopeIntercept(p_list);

    double tolerance = 0.1;
    EXPECT_NEAR(model.first, 1.0, tolerance);
    EXPECT_NEAR(model.second, 0.0, tolerance);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
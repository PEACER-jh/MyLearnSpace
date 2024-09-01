// Curve Fitting

#include <cmath>
#include <ctime>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "ceres/ceres.h"
#include <opencv2/opencv.hpp>

const int kNumObservations = 100;
std::vector<cv::Point2d> data;
const double real_m = 1.0, real_c = 1.0;

struct ExponentialResidual
{
    ExponentialResidual(double x, double y) : x_(x), y_(y) {}
    template <typename T>
    bool operator () (const T* const m, const T* const c, T* residual) const
    {
        residual[0] = y_ - exp(m[0] * x_ + c[0]);
        return true;
    }

private:
    const double x_;
    const double y_;
};

void generateNosiyPoints()
{
    for(int i = 0; i < kNumObservations; ++i)
    {
        double iter = i / 100.0;
        double x = iter + 0.1 * (static_cast<double>(std::rand()) / RAND_MAX - 0.5f);
        double y = exp(real_m * iter + real_c) + 0.1 * (static_cast<double>(std::rand()) / RAND_MAX - 0.5f);
        data.push_back(cv::Point2d(x, y));
        std::cout << "x: " << data[i].x << "\t y: " << data[i].y << std::endl;
    }    
}

void CostFunction()
{
    double m = 0.0;
    double c = 0.0;

    ceres::Problem problem;
    for(int i = 0; i < kNumObservations; i++)
    {
        ceres::CostFunction* cost_function = 
                new ceres::AutoDiffCostFunction<ExponentialResidual, 1, 1, 1>(new ExponentialResidual(data[i].x, data[i].y));
        // problem.AddResidualBlock(cost_function, nullptr, &m, &c);
        problem.AddResidualBlock(cost_function, new ceres::CauchyLoss(0.5), &m, &c);
    }
    ceres::Solver::Options options;
    options.max_num_iterations = 100;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    std::cout << summary.BriefReport() << std::endl;
    std::cout << "Initial m: " << 0.0 << "\t\t c: " << 0.0 << std::endl;
    std::cout << "Final   m: " << m << "\t c: " << c << std::endl;
    std::cout << "Real    m: " << real_m << "\t\t c: " << real_c << std::endl;
}

int main(int argc, char** argv)
{
    std::chrono::steady_clock::time_point start,end;
    std::chrono::duration<double> duration;
    generateNosiyPoints();

    start = std::chrono::steady_clock::now();
    CostFunction();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    return 0;
}
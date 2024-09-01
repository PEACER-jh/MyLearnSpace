// ceres用来解决边界约束鲁棒非线性最小二乘问题 

#include <chrono>
#include <iostream>
#include "ceres/ceres.h"

// Automatic Differentives（自动微分）
struct CostFunctor
{
    template <typename T>
    bool operator () (const T* const x, T* residual) const
    {
        residual[0] = 10.0 - x[0];
        return true;
    }
};
void TestCeres()
{
    ceres::Problem problem;
    double initial_x = 5.0;
    double x = initial_x;
    ceres::CostFunction* cost_function = 
            new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
    problem.AddResidualBlock(cost_function, nullptr, &x);

    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    std::cout << summary.BriefReport() << std::endl;
    std::cout << "x : " << initial_x << " -> " << x << std::endl;
}

// Numerical Derivatives（数值求导）
// 推荐自动微分（Automatic Differentiation）来取代数值微分（Numerical Differentiation）
// C++的模板类让自动微分十分高效，而数值微分计算量大，容易产生数值误差（numeric error）,并且收敛（convergence）更慢
struct NumericalDiffCostFunctor
{
    bool operator () (const double* const x, double* residual) const
    {
        residual[0] = 10.0 - x[0];
        return true;
    }
};
void TestCeresNumerical()
{
    ceres::Problem problem;
    double initial_x = 5.0;
    double x = initial_x;
    ceres::CostFunction* cost_function = 
            new ceres::NumericDiffCostFunction<NumericalDiffCostFunctor, ceres::CENTRAL, 1, 1>(new NumericalDiffCostFunctor);
    problem.AddResidualBlock(cost_function, nullptr, &x);

    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    std::cout << summary.BriefReport() << std::endl;
    std::cout << "x : " << initial_x << " -> " << x << std::endl;
}

int main(int argc, char** argv)
{
    std::chrono::steady_clock::time_point start,end;
    std::chrono::duration<double> duration;

    std::cout << "***Automatic Differentives***" << std::endl;
    start = std::chrono::steady_clock::now();
    TestCeres();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "automatic differentives time: " << duration.count() << "s" << std::endl;

    std::cout << "***Numerical Differentives***" << std::endl;
    start = std::chrono::steady_clock::now();
    TestCeresNumerical();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "numerical differentives time: " << duration.count() << "s" << std::endl;

    return 0;
}
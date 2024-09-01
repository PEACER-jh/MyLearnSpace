// 导数
// 依赖于能够在任意参数下评估（evaluate）目标函数中每一项的函数值与导数
// 1. Automatic Differentives   （自动微分）
// 2. Analytic Derivatives      （解析微分）
// 3. Numerical Derivatives     （数值求导）

#include <chrono>
#include <iostream>
#include "ceres/ceres.h"

// Analytic Derivatives（解析微分）
// 需要提供你自己的残差（residual）与 雅可比（Jacobian）计算代码
class QuadraticCostFunction : public ceres::SizedCostFunction<1, 1>
{
public:
    virtual ~QuadraticCostFunction() {}
    virtual bool Evaluate(double const* const* parameters, double* residuals, double** jacobians) const
    {
        const double x = parameters[0][0];
        residuals[0] = 10.0 - x;
        if(jacobians != nullptr && jacobians[0] != nullptr)
            jacobians[0][0] = -1;
        return true;
    }
};

void testQuadraticCostFunction()
{
    ceres::Problem problem;
    double initial_x = 5.0;
    double x = initial_x;
    std::unique_ptr<ceres::CostFunction> cost_function(new QuadraticCostFunction());
    problem.AddResidualBlock(cost_function.get(), nullptr, &x);

    ceres::Solver::Options option;
    option.linear_solver_type = ceres::DENSE_QR;
    option.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary;
    ceres::Solve(option, &problem, &summary);
    std::cout << summary.BriefReport() << std::endl;
    std::cout << "x : " << initial_x << " -> " << x << std::endl;
}


int main(int argc, char** argv)
{
    std::chrono::steady_clock::time_point start,end;
    std::chrono::duration<double> duration;

    std::cout << "***Analytic Differentives***" << std::endl;
    start = std::chrono::steady_clock::now();
    testQuadraticCostFunction();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "analytic differentives time: " << duration.count() << "s" << std::endl;

    return 0;
}

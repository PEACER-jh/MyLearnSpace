// 预备知识：仿函数
// ceres当中代价函数（cost function）的构建当中用到了仿函数（functor）
// 使用方法是在costfunction函数中重载了（）运算符（operator）

#include <iostream>
#include "ceres/ceres.h"

class Functor
{
private:
    const char* ss;
    int count;
public:
    explicit Functor(const char* str) : ss(str), count(0)
    {
        std::cout << "Functor: " << ss << std::endl;
    }

    void operator () (std::string str)
    {
        count++;
        std::cout << "the Functor is called " << count << " times " << str << std::endl;
    }

};

int main(int argc, char** argv) 
{
    Functor f0("construct0");
    f0("first0");
    f0("second0");

    Functor f1("construct1");
    f1("first1");
    f1("second1");

    return 0;
}
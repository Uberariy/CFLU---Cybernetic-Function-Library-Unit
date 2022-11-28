/**
 * @file Function.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CYBERNETIC_FUNCTION_
#define CYBERNETIC_FUNCTION_

#include <string>
#include <memory>
#include <vector>
#include <map>

#include <stdio.h>

/* Virtual Function */

class BaseFunction {
public:
    virtual std::string ToString() const = 0;
    virtual double Deriative(double x) = 0;
    virtual double operator()(double x) = 0;
    virtual std::shared_ptr<BaseFunction> Copy() = 0;
    // template <typename T>
    // friend bool operator==(BaseFunction &lop, T &rop);

};

/* Operation handlers */

class Compose : public BaseFunction {
public:
    Compose(BaseFunction& lop_, BaseFunction& rop_, std::string type_);
    std::string ToString() const;
    double Deriative(double x);
    double operator()(double x);
    std::shared_ptr<BaseFunction> Copy();

private:
    std::shared_ptr<BaseFunction> lop, rop;
    std::string type;
};

/* Others.. */

class Exponential : public BaseFunction {
public:
    Exponential() : coef(0) {};
    explicit Exponential(double coef_) : coef(coef_) {};
    explicit Exponential(std::vector<double> coef_);
    std::string ToString() const;
    double Deriative(double x);
    double operator()(double x);
    std::shared_ptr<BaseFunction> Copy();

protected:
    double coef;
};

class Polynomial : public BaseFunction {
public:
    Polynomial();
    explicit Polynomial(double coef_);
    explicit Polynomial(std::vector<double> coef_);
    std::string ToString() const;
    double Deriative(double x);
    double operator()(double x);
    std::shared_ptr<BaseFunction> Copy();

protected:
    std::map<unsigned int, double> PolyDict;
};

class Identical : public Polynomial {
public:
    Identical();
    explicit Identical(double coef_);
    explicit Identical(std::vector<double> coef_); 

};

class Constant : public Polynomial {
public:
    Constant();
    explicit Constant(double coef_);
    explicit Constant(std::vector<double> coef_);

};

class Power : public Polynomial {
public:
    Power();
    explicit Power(double coef_);
    explicit Power(std::vector<double> coef_);

};

template <typename TFunction>
Compose operator+(BaseFunction& lop, TFunction& rop) {
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>) {
        return Compose(lop, rop, "+");
    } else {
        throw std::logic_error("One of the types is wrong!");
    }
}

template <typename TFunction>
Compose operator-(BaseFunction& lop, TFunction& rop) {
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>) {
        return Compose(lop, rop, "-");
    } else {
        throw std::logic_error("One of the types is wrong!");
    }
}

template <typename TFunction>
Compose operator*(BaseFunction& lop, TFunction& rop) {
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>) {
        return Compose(lop, rop, "*");
    } else {
        throw std::logic_error("One of the types is wrong!");
    }
}

template <typename TFunction>
Compose operator/(BaseFunction& lop, TFunction& rop) {
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>) {
        return Compose(lop, rop, "/");
    } else {
        throw std::logic_error("One of the types is wrong!");
    }
}

/* Gradient method */

double GoldenSelection(Compose& f2, double grad, double x, double eps, double a = 0, double b = 0.05);

template <typename TFunction>
double FindRoot(TFunction& f, unsigned long it, double init_x = 0, double eps = 0.00000001) {
    /* Source: https://vlab.fandom.com/ru/wiki/%D0%93%D1%80%D0%B0%D0%B4%D0%B8%D0%B5%D0%BD%D1%82%D0%BD%D1%8B%D0%B9_%D1%81%D0%BF%D1%83%D1%81%D0%BA */
    
    double cur_x = init_x;
    double last_x;
    auto f2 = f * f;

    for (unsigned long i = 0; i < it; i++) {
        last_x = cur_x;
        double grad = f2.Deriative(cur_x);
        double lambda = GoldenSelection(f2, grad, cur_x, eps);
        cur_x = cur_x - lambda * grad;
        if (std::abs(f2(cur_x) - f2(last_x)) < eps)
            break;
    }
    return cur_x;
}

#endif
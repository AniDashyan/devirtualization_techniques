#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include <random>
#include <iomanip>
#include "macros.h"

class Shape {
    public:
        virtual ~Shape() = default;
        virtual double area() const = 0;
};

class Circle FINAL : public Shape {
    public:
        Circle(double r) : radius(r) {}
        
        double area() const override {
            return PI * radius * radius;
        }
        
        // Non-virtual functions for comparison
        double direct_area() const {
            return PI * radius * radius;
        }

    private:
        double radius;
};

template<typename T>
double calc_area_template(const T& shape) {
    return shape.direct_area();
}

template<typename Container, typename Func>
auto test_function_calls(const Container& container, int iters, Func func) {
    volatile double total = 0.0;
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < iters; ++i) {
        for (const auto& item : container) {
            total += func(item);
        }
    }

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    std::cout << "=== Devirtualization Techniques Demo ===" << std::endl;
    
    const int num_objects = 10000;
    const int iters = 1000;
    
    std::vector<std::unique_ptr<Shape>> shapes;
    std::vector<Circle> circles;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10.0);
    
    for (int i = 0; i < num_objects; ++i) {
        double radius = dis(gen);
        shapes.push_back(std::make_unique<Circle>(radius));
        circles.emplace_back(radius);
    }
    
    std::cout << "\nTesting with " << num_objects << " objects, " << iters << " iters each\n" << std::endl;
    
    // Run performance tests
    auto virtual_time = test_function_calls(shapes, iters, [](const std::unique_ptr<Shape>& shape) { return shape->area(); });
    auto direct_time = test_function_calls(circles, iters, [](const Circle& circle) { return circle.direct_area(); });
    auto devirt_time = test_function_calls(circles, iters, [](const Circle& circle) { return circle.area(); });
    auto template_time = test_function_calls(circles, iters, [](const Circle& circle) { return calc_area_template(circle); });
    
    std::cout << "\n=== Performance Results ===" << std::endl;
    std::cout << "Virtual calls:      " << virtual_time << " us" << std::endl;
    std::cout << "Direct calls:       " << direct_time << " us" << std::endl;
    std::cout << "Devirtualized:      " << devirt_time << " us" << std::endl;
    std::cout << "Template calls:     " << template_time << " us" << std::endl;
    
    std::cout << "\nSpeedup ratios (compared to virtual calls):" << std::endl;
    std::cout << "Direct calls:       " << (double)virtual_time / direct_time << "x" << std::endl;
    std::cout << "Devirtualized:      " << (double)virtual_time / devirt_time << "x" << std::endl;
    std::cout << "Template calls:     " << (double)virtual_time / template_time << "x" << std::endl;
    
    return 0;
}
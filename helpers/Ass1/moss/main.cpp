#include <comp6771/euclidean_vector.hpp>
#include <iostream>
#include <memory>

auto print(comp6771::euclidean_vector& v) -> void {
    for (auto i = 0; i < v.dimensions(); ++i) {
            std::cout << v.at(i) << '\n';
    }
    std::cout << std::endl;
}

int main(){
    // {
    //     auto a = comp6771::euclidean_vector();
    //     print(a);
    // }

    // {
    //     auto a = comp6771::euclidean_vector(1);
    //     print(a);

    //     int i {3};
    //     auto b = comp6771::euclidean_vector(i);
    //     print(b);
    // }

    // {
    //     auto a = comp6771::euclidean_vector(3, 4.0);
    //     print(a);

    //     auto x = int{5};
    //     auto y = double{6.66};
    //     auto b = comp6771::euclidean_vector(x, y);
    //     print(b);
    // }

    // {
    //     std::vector<double> v;
    //     v.push_back(1);
    //     v.push_back(2);
    //     v.push_back(3);
    //     auto b = comp6771::euclidean_vector(v.begin(),v.end());
    //     print(b);
    // }

    // {
    //     auto b = comp6771::euclidean_vector{1.0, 2.0, 3.0};
    //     print(b);
    // }

    // {
    //     const auto b = comp6771::euclidean_vector{1.0, 2.0, 3.0,4,5,6,7};
    //     auto a = comp6771::euclidean_vector(b);
    //     print(a);
    // }

    // {
    //     auto a = comp6771::euclidean_vector(1);      // a Euclidean Vector in 1 dimension, with default magnitude 0.0.
    //     auto b = comp6771::euclidean_vector(2, 4.0); // a Euclidean Vector in 2 dimensions with magnitude 4.0 in both dimensions

    //     auto v = std::vector<double>{5.0, 6.5, 7.0};
    //     auto c = comp6771::euclidean_vector(v.begin(), v.end()); // a Euclidean Vector in 3 dimensions constructed from a vector of magnitudes
    //     print(a);
    //     print(b);
    //     print(c);
    // }

    // {
    //     auto a = comp6771::euclidean_vector();
    //     print(a);
    //     comp6771::euclidean_vector const b{1,2};
    //     a = b;
    //     print(a);
    //     // print(b);
    // }

    // {
    //     comp6771::euclidean_vector b{1,2};
    //     print(b);
    //     double a {b[1]};
    //     std::cout << a << "\n\n";
    //     b[1] = 3.0;
    //     print(b);
    //     comp6771::euclidean_vector const c{3,4};
    //     std::cout << c[1] << "\n";
    // }

    // {
    //     auto const b = comp6771::euclidean_vector(2, 4.0);
    //     // print(b);
    //     auto a = +b;
    //     print(a);
    //     comp6771::euclidean_vector c{1,2};
    //     a = +c;
    //     print(a);
    // }

    // {
    //     auto b = comp6771::euclidean_vector(5,6);
    //     // print(b);
    //     auto a = -b;
    //     print(a);
    // }

    // {
    //     auto a = comp6771::euclidean_vector{0,0,1};
    //     std::vector<double> v;
    //     v.push_back(1);
    //     v.push_back(2);
    //     v.push_back(3);
    //     auto b = comp6771::euclidean_vector(v.begin(),v.end());
    //     a += b;
    //     print(a);
    // }

    // {
    //     auto a = comp6771::euclidean_vector{0,0,1};
    //     std::vector<double> v;
    //     v.push_back(1);
    //     v.push_back(2);
    //     v.push_back(3);
    //     auto b = comp6771::euclidean_vector(v.begin(),v.end());
    //     a -= b;
    //     print(a);
    // }

    // {
    //     auto a = comp6771::euclidean_vector{3,6};
    //     auto s = double {0.3};
    //     a *= s;
    //     print(a);
    // }

    // {
    //     auto a = comp6771::euclidean_vector{3,6};
    //     auto s = double {3};
    //     a /= s;
    //     print(a);
    // }

    // {
    //     auto const a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
    //     auto const vf = static_cast<std::vector<double>>(a);
    //     for (auto ele : vf)
    //         std::cout << ele << " ";
    //     std::cout << "\n";
    // }

    {
        auto const a = comp6771::euclidean_vector{1,9,9,5,0,1,20};
        auto lf = static_cast<std::list<double>>(a);
        for (auto ele : lf)
            std::cout << ele << " ";
        std::cout << "\n";
    }
}
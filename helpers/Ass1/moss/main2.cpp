#include <comp6771/euclidean_vector.hpp>
#include <iostream>
#include <memory>

auto print(comp6771::euclidean_vector& v) -> void {
    for (auto i = 0; i < v.dimensions(); ++i) {
        std::cout << v.at(i) << '\n';
    }
    std::cout << std::endl;
}

int main() {
    // {
    //  std::cout << "Default Constructor\n";
    //  auto a = comp6771::euclidean_vector();
    //  print(a);
    // }

    // {
    //  std::cout << "Single-Argument Constructor\n";
    //  auto a = comp6771::euclidean_vector(1);
    //  print(a);

    //  int i{3};
    //  auto b = comp6771::euclidean_vector(i);
    //  print(b);
    // }

    // {
    //  std::cout << "Double-Argument Constructor\n";
    //  auto a = comp6771::euclidean_vector(3, 4.0);
    //  print(a);

    //  auto x = int{5};
    //  auto y = double{6.66};
    //  auto b = comp6771::euclidean_vector(x, y);
    //  print(b);
    // }

    // {
    //  std::cout << "Iterator Constructor\n";
    //  std::vector<double> v;
    //  v.push_back(1);
    //  v.push_back(2);
    //  v.push_back(3);
    //  auto b = comp6771::euclidean_vector(v.begin(), v.end());
    //  print(b);
    // }

    // {
    //  std::cout << "Initlizer list Constructor\n";
    //  auto b = comp6771::euclidean_vector{1.0, 2.0, 3.0};
    //  print(b);
    // }

    // {
    //  std::cout << "Vector Constructor\n";
    //  const auto b = comp6771::euclidean_vector{1.0, 2.0, 3.0, 4, 5, 6, 7};
    //  auto a = comp6771::euclidean_vector(b);
    //  print(a);
    // }

    // {
    //  std::cout << "Copy Constructor\n";
    //  auto b = comp6771::euclidean_vector(1, 2);
    //  print(b);
    //  auto a = comp6771::euclidean_vector(b);
    //  print(a);
    // }

    // {
    //  std::cout << "Spec example\n";
    //  auto a = comp6771::euclidean_vector(1); // a Euclidean Vector in 1 dimension, with default
    //                                          // magnitude 0.0.
    //  auto b = comp6771::euclidean_vector(2, 4.0); // a Euclidean Vector in 2 dimensions with
    //                                               // magnitude 4.0 in both dimensions

    //  auto v = std::vector<double>{5.0, 6.5, 7.0};
    //  auto c = comp6771::euclidean_vector(v.begin(), v.end()); // a Euclidean Vector in 3
    // dimensions
    //                                                           // constructed from a vector of
    //                                                           // magnitudes
    //  print(b);
    //  print(c);
    // }

    // {
    //  std::cout << "=\n";
    //  // auto a = comp6771::euclidean_vector();
    //  // print(a);
    //  // // comp6771::euclidean_vector const b{1, 2};
    //  // a = *&a;
    //  // print(a);
    //  // // print(b);
    //  auto a = comp6771::euclidean_vector{1, 2, 3};
    //  print(a);
    //  auto b = comp6771::euclidean_vector{1, 2, 5};
    //  a = b;
    //  print(b);
    //  b[0] = 2;
    //  print(a);
    //  print(b);
    // }

    // {
    //  std::cout << "[]\n";
    //  comp6771::euclidean_vector b{1, 2};
    //  print(b);
    //  double a{b[1]};
    //  std::cout << a << "\n\n";
    //  b[1] = 3.0;
    //  print(b);
    //  comp6771::euclidean_vector const c{3, 4};
    //  std::cout << c[1] << "\n\n";
    // }

    // {
    //  std::cout << "+\n";
    //  auto const b = comp6771::euclidean_vector(2, 4.0);
    //  // print(b);
    //  auto a = +b;
    //  print(a);
    //  comp6771::euclidean_vector c{1, 2};
    //  a = +c;
    //  print(a);
    // }

    // {
    //  std::cout << "-\n";
    //  auto const actual = comp6771::euclidean_vector{-6, 1};
    //  auto const expected = comp6771::euclidean_vector{6, -1};
    //  if (expected == -actual)
    //      std::cout << "TRUE\n";
    //  else
    //      std::cout << "FALSE\n";
    // }

    // {
    //  std::cout << "+=\n";
    //  auto a = comp6771::euclidean_vector{0, 0, 1};
    //  std::vector<double> v;
    //  v.push_back(1);
    //  v.push_back(2);
    //  v.push_back(3);
    //  auto b = comp6771::euclidean_vector(v.begin(), v.end());
    //  a += b;
    //  print(a);
    // }

    // {
    //  std::cout << "-=\n";
    //  auto a = comp6771::euclidean_vector{0, 0, 1};
    //  std::vector<double> v;
    //  v.push_back(1);
    //  v.push_back(2);
    //  v.push_back(3);
    //  auto b = comp6771::euclidean_vector(v.begin(), v.end());
    //  a -= b;
    //  print(a);
    // }

    // {
    //  std::cout << "*=\n";
    //  auto a = comp6771::euclidean_vector{3, 6};
    //  auto s = double{0.3};
    //  a *= s;
    //  print(a);
    // }

    // {
    //  std::cout << "/=\n";
    //  auto a = comp6771::euclidean_vector{3, 6};
    //  auto s = double{3};
    //  a /= s;
    //  print(a);
    // }

    // {
    //  std::cout << "vec cast\n";
    //  auto const a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
    //  auto const vf = static_cast<std::vector<double>>(a);
    //  for (auto ele : vf)
    //      std::cout << ele << " ";
    //  std::cout << "\n";
    // }

    // {
    //  std::cout << "list cast\n";
    //  auto const a = comp6771::euclidean_vector{1, 9, 9, 5, 0, 1, 20};
    //  auto lf = static_cast<std::list<double>>(a);
    //  for (auto ele : lf)
    //      std::cout << ele << " ";
    //  std::cout << "\n";
    // }

    // {
    //  std::cout << "==\n";
    //  auto a = comp6771::euclidean_vector{1, 2, 4, 5};
    //  auto b = comp6771::euclidean_vector{1, 2, 4, 5};
    //  if (a == b)
    //      std::cout << "TRUE\n";
    //  else
    //      std::cout << "FALSE\n";
    // }

    // {
    //  std::cout << "!=\n";
    //  auto a = comp6771::euclidean_vector{1, 2, 4, 5};
    //  auto b = comp6771::euclidean_vector{1, 2, 5};
    //  if (a != b)
    //      std::cout << "FALSE\n";
    //  else
    //      std::cout << "TRUE\n";
    // }

    // {
    //  std::cout << "c = a + b\n";
    //  auto a = comp6771::euclidean_vector(1);
    //  auto b = comp6771::euclidean_vector{1, 2, 3};

    //  auto v = std::vector<double>{2, 3, 4};
    //  auto c = comp6771::euclidean_vector(v.begin(), v.end());

    //  print(a);
    //  print(b);
    //  print(c);
    //  a = b + c;
    //  print(a);
    // }

    // {
    //  std::cout << "c = a - b\n";
    //  auto a = comp6771::euclidean_vector(1);
    //  auto b = comp6771::euclidean_vector{8, 12};

    //  auto v = std::vector<double>{3, 5};
    //  auto c = comp6771::euclidean_vector(v.begin(), v.end());

    //  print(a);
    //  print(b);
    //  print(c);
    //  a = b - c;
    //  print(a);
    // }

    // {
    //  std::cout << "c = a * double\n";
    //  auto b = comp6771::euclidean_vector{1, 2};
    //  auto a = b * 3;
    //  print(a);
    //  a = 3 * b;
    //  print(a);
    // }

    // {
    //  std::cout << "c = a / double\n";
    //  auto b = comp6771::euclidean_vector(1, 3.0);
    //  auto c = double{2.0};
    //  auto a = b / c;
    //  print(a);
    // }

    // {
    //  std::cout << "std::cout << a;\n";
    //  auto a = comp6771::euclidean_vector{1, 2, 3};
    //  std::cout << a << '\n';
    //  auto b = comp6771::euclidean_vector(0);
    //  std::cout << b << '\n';
    // }

    // {
    //  std::cout << "comp6771::euclidean_norm(a);\n";
    //  auto a = comp6771::euclidean_vector{1, 2, 3};
    //  std::cout << a << '\n';
    //  auto b = euclidean_norm(a);
    //  std::cout << b << '\n';
    // }

    // {
    //  std::cout << "comp6771::euclidean_norm(a);\n";
    //  auto a = comp6771::euclidean_vector{1, 2, 3};
    //  std::cout << a << '\n';
    //  auto b = euclidean_norm(a);
    //  std::cout << b << '\n';
    // }

    // {
    //  std::cout << "comp6771::unit(a);\n";
    //  auto a = comp6771::euclidean_vector{1, 1};
    //  std::cout << a << '\n';
    //  auto c = comp6771::unit(a);
    //  std::cout << c << '\n';
    // }

    {
        auto a = comp6771::euclidean_vector{1,2};
        auto b = comp6771::euclidean_vector{3,4};
        auto c = double{comp6771::dot(a, b)};
        std::cout << c << "\n";
    }
}
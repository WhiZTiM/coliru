#undef NDEBUG
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <array>
using namespace std;

const size_t primer_length = 6;
const array<double, primer_length> first_primer = {18, 21, 13, 32, 11, 24},
    second_primer = {1, 1, 1, 1, 1, 1};

const pair<double, double> answers = {109, 0};
//const pair<double, double> answers = {19.46875, 1000};

enum Arithmetic {plus, minus, multiply, division};

array<Arithmetic, primer_length-1> expr;

pair<double, double> compute()
{
    auto first_primer = ::first_primer, second_primer = ::second_primer;
    auto expr = ::expr;
    auto primer_length = ::primer_length;
    for (size_t i = 0; i < primer_length-1;)
        if (expr[i] == multiply || expr[i] == division) {
            if (expr[i] == Arithmetic::multiply) {
                first_primer[i] = first_primer[i] * first_primer[i+1];
                second_primer[i] = second_primer[i] * second_primer[i+1];
            }
            if (expr[i] == Arithmetic::division) {
                first_primer[i] = first_primer[i] / first_primer[i+1];
                second_primer[i] = second_primer[i] / second_primer[i+1];
            }
            for (size_t j = i+1; j < primer_length-1; ++j)
                expr[j-1] = expr[j];
            for (size_t j = i+2; j < primer_length; ++j) {
                first_primer[j-1] = first_primer[j];
                second_primer[j-1] = second_primer[j];
            }
            --primer_length;
        } else {
            ++i;
        }
    pair<double, double> result = {first_primer[0], second_primer[0]};
    for (size_t i = 0; i < primer_length-1; ++i) {
        assert(expr[i] == Arithmetic::plus || expr[i] == Arithmetic::minus);
        if (expr[i] == Arithmetic::plus) {
            result.first += first_primer[i+1];
            result.second += second_primer[i+1];
        }
        if (expr[i] == Arithmetic::minus) {
            result.first -= first_primer[i+1];
            result.second -= second_primer[i+1];
        }
    }
    //cout << first_primer[0] << ' ' << second_primer[0];
    return result;
}

bool eq(const pair<double, double> lhs, const pair<double, double> rhs)
{
    constexpr double eps = 1e-8;
    return abs(lhs.first - rhs.first) < eps;
}

unsigned depth = 0;
array<unsigned, 4> used = {};
bool used_twice = false;

void perebor()
{
    if (depth < primer_length-1) {
        for (int i = Arithmetic::plus; i <= Arithmetic::division; ++i)
            if (used[i] == 0 || (used[i] == 1 && !used_twice)) {
                ++used[i];
                if (used[i] == 2)
                    used_twice = true;
                expr[depth] = static_cast<Arithmetic>(i);
                ++depth;
                perebor();
                --depth;
                if (used[i] == 2)
                    used_twice = false;
                --used[i];
            }
    } else {
        static unsigned count = 0;
        //cout << ++count << '\n';
        if (eq(compute(), answers)) {
            for (const auto znak : expr) {
                switch (znak) {
                    case Arithmetic::plus:
                        cout << '+';
                    break;
                    case Arithmetic::minus:
                        cout << '-';
                    break;
                    case Arithmetic::multiply:
                        cout << '*';
                    break;
                    case Arithmetic::division:
                        cout << '/';
                    break;
                }
            }
            cout << '\n';
        }
    }
}

int main()
{
    /*
    expr = {Arithmetic::plus, Arithmetic::multiply, Arithmetic::division, Arithmetic::minus, Arithmetic::multiply};
    auto res = compute();
    cout << res.first << ' ' << res.second << '\n';
    */
    perebor();   
}

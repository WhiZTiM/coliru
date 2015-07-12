#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

std::ostream& operator<<(std::ostream& os, std::vector<int> const& vec) {
    for (auto e : vec)
        std::cout << e << ' ';
    return os;
}

bool Merge(std::vector<int> const& A, std::size_t p, std::size_t q, std::size_t r) {
    auto n1 = q - p + 1;
    auto n2 = r - q;
    auto from = begin(A) + p;
    auto middle = from + n1;
    auto to = middle + n2;
    std::vector<int> L;
    std::copy(from, middle, back_inserter(L));
    std::vector<int> R;
    std::copy(middle, to, back_inserter(R));
    std::cout << "Divido: \n";
    std::cout << "  L: " << L << "\n";
    std::cout << "  R: " << R << "\n";
    L.push_back(100);
    R.push_back(100);
    auto i = 0;
    auto j = 0;
    for (auto k = q; k <= r; k++) {
        std::cout << "Comparo: " << L[i] << " and " << R[j] << "\n";
        if (L[i] < R[j])
            i++;
        else if (L[i] > R[j])
            j++;
        else return true;
    }
    return false;
}

bool MergeSort(std::vector<int> const& A, std::size_t p, std::size_t r) {
    if (p < r) {
        auto q = (p + r) / 2;
        auto a = MergeSort(A, p, q);
        auto b = MergeSort(A, q + 1, r);
        auto c = Merge(A, p, q, r);
        return a || b || c;
    } else {
        return false;
    }
}

int main() {
    std::vector<int> A {4, 2, 2, 6};
    std::cout << MergeSort(A, 0, 3);
}
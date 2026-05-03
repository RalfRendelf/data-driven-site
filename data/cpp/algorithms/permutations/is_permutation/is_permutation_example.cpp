#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {3, 2, 1};
    std::vector<int> c = {1, 2, 4};

    bool is_perm_ab = std::is_permutation(a.begin(), a.end(), b.begin());
    bool is_perm_ac = std::is_permutation(a.begin(), a.end(), c.begin());

    std::cout << "b является перестановкой a: " << (is_perm_ab ? "true" : "false") << std::endl;
    std::cout << "c является перестановкой a: " << (is_perm_ac ? "true" : "false") << std::endl;

    return 0;
}

#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Remove the element at index 2 (3rd element)
    numbers.erase(numbers.begin() + 2);

    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}

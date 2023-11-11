#include <iostream>
#include <string>
using namespace std;
bool endsWith(const std::string& str, const std::string& suffix) {
    if (suffix.size() > str.size()) {
        return false;
    }

    return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int main() {
    std::string input_file = "some_string$";

    if(endsWith(input_file, "$")) {
        cout<<"hello"<<endl;
    }
    cout<<input_file;
    // Handle any post-loop logic here

    return 0;
}

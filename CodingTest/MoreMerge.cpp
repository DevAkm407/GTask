#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    string n_a = to_string(a) + to_string(b);
    string n_b = to_string(b) + to_string(a);

    int answer = atoi(n_a.c_str()) >= atoi(n_b.c_str()) ? atoi(n_a.c_str()) : atoi(n_b.c_str());
    return answer;
}
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> num_list, int n) {
    vector<int> answer = num_list;
    for (int i = 0; i < n; i++)
    {
        answer.push_back(answer.front());
        answer.erase(answer.begin(), answer.begin() + 1);
    }
    return answer;
}
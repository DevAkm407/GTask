#include <string>
#include <vector>
using namespace std;

int solution(string my_string, string is_prefix) {
    int answer = 0;
    for (int i = 0; i < is_prefix.length(); i++)
    {
        answer = my_string[i] == is_prefix[i] ? 1 : 0;
        vector<int>::iterator
    }
    return answer;
}
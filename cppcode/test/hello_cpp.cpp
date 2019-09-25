#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{ /*
    vector<int> v1 = {1, 2, 3, 4, 5, 6};
    sort(v1.begin(), v1.end(), greater<int>());

    for (auto &&val : v1)
    {
        cout << val << ' ';
    }
    cout << endl;

    auto printStr = [](string_view str) {
        cout << str << endl;
    };

    cout << "Hello CPP!" << endl;
    //system("pause");*/

    char *a;
    char ch[10] = "abcdefghi";
    a = ch;
    cout << a[0] << endl;
    a++;
    cout << a[0] << endl;
    return 0;
}
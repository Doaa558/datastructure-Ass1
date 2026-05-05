#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n ;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> v;

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);
    }


    vector<int> result(n, -1); 
    stack<int> st; 

    for (int i = 0; i < 2 * n; i++) {
        int index = i % n;

       
        while (!st.empty() && v[index] >v[st.top()]) {
            result[st.top()] = v[index];
            st.pop();
        }

        
        if (i < n) {
            st.push(index);
        }
    }

   
    for (int x : result) {
        cout << x << " ";
    }

    return 0;
}

#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve(){
    int n;
    cin >> n;
    int s = 0;
    while (n > 0)
    {
        int lastDigit = n % 10;
        s += lastDigit;
        n /= 10;
    }

    cout << s << "\n";
    
}


int main() {
    
    int T;
    cin>>T;
    while(T--){
        solve();

    }

}
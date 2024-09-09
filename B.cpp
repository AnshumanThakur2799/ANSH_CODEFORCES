#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve(){
    int n  , s , m;
    cin >> n >> s >> m;
    int maxi = INT_MIN;
    int prev = 0;
    for(int i = 0 ; i < n; i++){
        int l , r;
        cin >> l >> r;
        maxi = max(maxi , l - prev);
        prev = r;
    }
    maxi = max(maxi , m - prev);

    if(maxi >= s) cout << "YES" << endl;
    else cout << "NO" << endl;
    
}


int main() {
    
    int T;
    cin>>T;
    while(T--){
        solve();

    }

}
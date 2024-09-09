#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve(){
    string s , t;
    cin >> s >> t;
    int i = 0 , j = 0;
    int cnt = 0;
    int sz = t.size();
    while(j < sz && i < s.size()){
        if(s[j] == s[i]){
            cnt++;
            j++;
        }
        if(s[i] == '?'){
            s[i] = s[j];
            cnt++;
            j++;
        }
        i++;
    }
    while(i < s.size()){
        if(s[i] == '?'){
            s[i] = 'a';
        }
        i++;
    }

    if(cnt != sz) cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        cout << s << endl;
    }
}


int main() {
    
    int T;
    cin>>T;
    while(T--){
        solve();

    }

}
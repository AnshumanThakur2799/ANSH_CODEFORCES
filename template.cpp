#include <bits/stdc++.h>
#define ll long long
using namespace std;

random_device rd;
mt19937_64 gen(rd());
const ll MOD = 1e9 + 7;

ll fact(ll n){ 
    ll res = 1; for(ll i = 2; i <= n; i++){res = (res * i) % MOD;} return res;
}

ll exp(ll a, ll b) {
    return b ? ((b & 1) ? (a * exp((a * a) % MOD, b >> 1) % MOD) : exp((a * a) % MOD, b >> 1) % MOD) : 1;
}

ll ncr(ll n , ll r){
    return (fact(n) * exp(fact(r), MOD - 2) % MOD * exp(fact(n - r), MOD - 2) % MOD) % MOD;
}

ll npr(ll n , ll r){
    return (fact(n) * exp(fact(n - r), MOD - 2) % MOD) % MOD;
}

ll lcm(ll a , ll b){
    return (a * b) / __gcd(a, b);
}

vector<bool> seive(ll n){
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i){
                is_prime[j] = false;
            }
        }
    }

    return is_prime;

}
unordered_set<long long> trial_division1(long long n) {
    unordered_set<long long> factorization;
    factorization.insert(1);
    for (long long d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            factorization.insert(d);
            factorization.insert(n/d);
        }
    }
    if (n > 1)
        factorization.insert(n);
    return factorization;
}

void solve(){

}


int main() {
    
    int T;
    cin>>T;
    while(T--){
        solve();

    }

}
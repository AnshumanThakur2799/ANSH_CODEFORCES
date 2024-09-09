#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../debug.h"
#else
#define dbg(...)
#endif

namespace mint_ns {
template<auto P>
struct Modular {
    using value_type = decltype(P);
    value_type value;
 
    Modular(long long k = 0) : value(norm(k)) {}
 
    friend Modular<P>& operator += (      Modular<P>& n, const Modular<P>& m) { n.value += m.value; if (n.value >= P) n.value -= P; return n; }
    friend Modular<P>  operator +  (const Modular<P>& n, const Modular<P>& m) { Modular<P> r = n; return r += m; }
 
    friend Modular<P>& operator -= (      Modular<P>& n, const Modular<P>& m) { n.value -= m.value; if (n.value < 0)  n.value += P; return n; }
    friend Modular<P>  operator -  (const Modular<P>& n, const Modular<P>& m) { Modular<P> r = n; return r -= m; }
    friend Modular<P>  operator -  (const Modular<P>& n)                      { return Modular<P>(-n.value); }
 
    friend Modular<P>& operator *= (      Modular<P>& n, const Modular<P>& m) { n.value = n.value * 1ll * m.value % P; return n; }
    friend Modular<P>  operator *  (const Modular<P>& n, const Modular<P>& m) { Modular<P> r = n; return r *= m; }
 
    friend Modular<P>& operator /= (      Modular<P>& n, const Modular<P>& m) { return n *= m.inv(); }
    friend Modular<P>  operator /  (const Modular<P>& n, const Modular<P>& m) { Modular<P> r = n; return r /= m; }
 
    Modular<P>& operator ++ (   ) { return *this += 1; }
    Modular<P>& operator -- (   ) { return *this -= 1; }
    Modular<P>  operator ++ (int) { Modular<P> r = *this; *this += 1; return r; }
    Modular<P>  operator -- (int) { Modular<P> r = *this; *this -= 1; return r; }
 
    friend bool operator == (const Modular<P>& n, const Modular<P>& m) { return n.value == m.value; }
    friend bool operator != (const Modular<P>& n, const Modular<P>& m) { return n.value != m.value; }
 
    explicit    operator       int() const { return value; }
    explicit    operator      bool() const { return value; }
    explicit    operator long long() const { return value; }
 
    constexpr static value_type mod()      { return     P; }
 
    value_type norm(long long k) {
        if (!(-P <= k && k < P)) k %= P;
        if (k < 0) k += P;
        return k;
    }
 
    Modular<P> inv() const {
        value_type a = value, b = P, x = 0, y = 1;
        while (a != 0) { value_type k = b / a; b -= k * a; x -= k * y; swap(a, b); swap(x, y); }
        return Modular<P>(x);
    }
 
    friend void __print(Modular<P> v) {
        cerr << v.value;
    }
};
template<auto P> Modular<P> pow(Modular<P> m, long long p) {
    Modular<P> r(1);
    while (p) {
        if (p & 1) r *= m;
        m *= m;
        p >>= 1;
    }
    return r;
}
 
template<auto P> ostream& operator << (ostream& o, const Modular<P>& m) { return o << m.value; }
template<auto P> istream& operator >> (istream& i,       Modular<P>& m) { long long k; i >> k; m.value = m.norm(k); return i; }
template<auto P> string   to_string(const Modular<P>& m) { return to_string(m.value); }
 
}
constexpr int mod = (int)1e9 + 7;
using mod_int = mint_ns::Modular<mod>;


 
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  const int NN = 2e5 + 2;
  vector<int> prime, P(NN, 1);
  for(int i = 2 ; i < NN ; ++i) if(P[i]) {
    prime.push_back(i);
    for(int j = 2 * i ; j < NN ; j += i)
      P[j] = 0;
  }
  auto __solve_testcase = [&](int test) {
    int N;  cin >> N;
    vector<int> color(N + 1); color[1] = 1;
    for(int k = 1 ; k <= N ; ++k) {
      for(int &j: prime) {
        if(j * k > N) break;
        color[j * k] = color[k] + 1;
      }
    }
    cout << *max_element(color.begin(), color.end()) << '\n';
    for(int i = 1 ; i <= N ; ++i)
      cout << color[i] << " \n"[i == N];
  };
  
  int NumTest = 1;
  cin >> NumTest;
  for(int testno = 1; testno <= NumTest ; ++testno) {
    __solve_testcase(testno);
  }
  
  return 0;
}
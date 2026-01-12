#include<bits/stdc++.h>
#define ll long long
#define ALL(x) (x).begin(), (x).end()
#define R_ALL(x) (x).rbegin(), (x).rend()
using namespace std;

const ll MOD = 1e9 + 7;

const int PRIME_MAXN = 1000001;
int prime[PRIME_MAXN];
void eratosthenes(){
    for(int i = 0; i < PRIME_MAXN; i++) prime[i] = 1;
    prime[0] = prime[1] = 0;
    for(int i = 2; i * i < PRIME_MAXN; i++){
        if(prime[i] == 1){
            for(int j = i * i; j < PRIME_MAXN; j += i){
                prime[j] = 0;
            }
        }
    }
}
bool checkprime(int n){
    if(n < 0 || n >= PRIME_MAXN) return false;
    return prime[n];
}

const int SPF_MAXN = 10000001;
int spf[SPF_MAXN];
void seivespf(){
    iota(spf, spf + SPF_MAXN, 0);
    for(int i = 2; i * i < SPF_MAXN; i++){
        if(spf[i] == i){
            for(int j = i * i; j < SPF_MAXN; j += i){
                if(spf[j] == j) spf[j] = i;
            }
        }
    }
}

// O(log n) using SPF
vector<int> primefactors(int n){
    vector<int> factors;
    while(n > 1){
        factors.push_back(spf[n]);
        n = n / spf[n];
    }
    return factors;
}

// O(sqrt n) using Trial Division
template<class U>
vector<U> getPrimeFactors(U n){
    vector<U> pf;
    for (U i = 2; i * i <= n; i++){
        while(n % i == 0) {
            pf.push_back(i);
            n /= i;
        }
    }
    if(n > 1) pf.push_back(n);
    return pf;
}

template<class T>
vector<int> getDivisors(T n){
    vector<int> divisors;
    for(int i = 1; i * i <= n; i++){
        if(n % i == 0){
            divisors.push_back(i);
            if(1LL * i * i != n){
                divisors.push_back(n / i);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}

template<class T>
T lcm(T a, T b){
    return (a / __gcd(a, b)) * b;
}

namespace number_theory{
    template<class T> 
    T exp(T x, T n, T m = MOD){
        if(n == 0) return 1LL;
        T p = exp(x, n / 2, m);
        T val = (p * p) % m;
        return (n % 2 == 0) ? val  : (val * x) % m;
    }

}
#include <iostream>
using namespace std;
#define ll long long 

ll gcdExtended(ll a, ll m, ll &x, ll &y) 
{ 
    if (m == 0) 
    {
        x = 0;
        y = 1; 
        return m; 
    } 
  
    ll gcd = gcdExtended(m, a%m, x, y); 
    ll temp = x;
    x = y - (a/m) * temp; 
    y = temp; 
  
    return gcd; 
} 

ll inverseModulus(ll a, ll b) {
	ll m = a;
	gcdExtended(a, b, a, b);
	return (a + m) % m;
}

int main(int argc, char const *argv[])
{
	
	ll x = 1000000007, y = 4;
	cout<<inverseModulus(x, y)<<endl;
	return 0;
}
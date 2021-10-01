// * $GCD(a_1 + b_j, …, a_n + b_j) = GCD(a[0] + b[j], a[1] - a[0], a[2] - a[1], ......, a[n - 2] - a[n - 3], a[n - 1] - a[n - 2])$
// $a[0] < a[1] < a[2] < a[3]...$
// 用法
// * 因為只有 b~j~ 是不固定的，所以求 $GCD(a_1 + b_j, …, a_n + b_j)$ 就只要算 $GCD(a[0] + b[j], baseGcd)$
//     * $baseGcd = GCD(a[1] - a[0], a[2] - a[1], ......, a[n - 2] - a[n - 3], a[n - 1] - a[n - 2])$

#include <iostream>
#include <map>
#include <queue>
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
const int mod=1e9+7;
typedef long long ll;
map<string, int>mp;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
ll a[maxn];
int main() {
	int n,m;cin>>n>>m;
	for(int i=0;i<n;i++) cin>>a[i];
	sort(a,a+n);
	ll g=0;
	for(int i=1;i<n;i++) g=__gcd(a[i]-a[i-1],g);
	for(int i=0;i<m;i++){
		ll x;cin>>x;
		cout<<__gcd(x+a[0],g)<<" ";
	}
	return 0;
}
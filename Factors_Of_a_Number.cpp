#include<bits/stdc++.h>
using namespace std;
#define N 1000000
vector<int> spf(N+1,1);
void calc_spf(){
    for(int i = 2;i*i <= N;i++){
        if(spf[i] == 1){
            for(int j = i;j <= N ;j+=i){
                spf[j] = i;
            }
        }
    }
}
void get_factors(int idx,int siz,int value,vector<int> &factors,vector<pair<int,int>> &prime_factors){

if(idx == siz){
    factors.push_back(value);
    return;
}
int st = 1;
for(int i = 0;i<prime_factors[idx].second;i++){
    get_factors(idx+1,siz,value*st,factors,prime_factors);
    st *= prime_factors[idx].first;
}
get_factors(idx+1,siz,value*st,factors,prime_factors);
}
int main(){
calc_spf();// first we will store smallest prime factor for each number
// now we can find the prime factorization of any number in logn
// example --> 35 --> spf[35] --> 5    35/5 = 7 and spf[5] = 5 so we get the prime factorization as 5*7 (order can vary)

for(int i = 1;i <= 100;i++){
int val = i;
map<int,int> prime_fac;
while(spf[val] != 1){
    //cout<<spf[val]<<" ";
    prime_fac[spf[val]]++;
    val /= spf[val];
}
vector<pair<int,int>> prime_factors;
for(auto it:prime_fac)prime_factors.push_back({it.first,it.second});
vector<int> factors;
get_factors(0,prime_factors.size(),1,factors,prime_factors);
// sort(factors.begin(),factors.end());
for(auto it:factors)cout<<it<<" "<<"\n";
}
}
#include<bits/stdc++.h>
using namespace std;
const int MOD=1e4+7;
typedef int ll ;
ll mod_pow(ll a,ll b )
{
    ll ret=1;
    ll A=a;
    while(b)
    {
        if(b&1) ret=(ret*A)%MOD;
        A=(A*A)%MOD;
        b>>=1;
    }
    return ret;
}
ll factorial[100000];
void init()
{
    factorial[0]=1;
    for(int i=1;i<=MOD;i++)
    factorial[i]=factorial[i-1]*i%MOD;
}
ll lucas_(ll a,ll k)
{
    ll ret=1;
    while(a && k)
    {
        ll aa=a%MOD,bb=k%MOD;
        if(aa<bb) return 0;
        ret*=factorial[aa]*mod_pow(factorial[bb]*factorial[aa-bb]%MOD,MOD-2)%MOD;
            a/=MOD;
            k/=MOD;
    }
    return ret;
}
int T;
int x,y;
int main(){
    scanf("%d",&T);
    init();
    while(T--)
    {
        scanf("%d%d",&x,&y);
        ll ans=(x-y+1)%MOD;
        ans *= lucas_(x+y,y);
        ans=ans*mod_pow(x+1,MOD-2)%MOD;
        printf("%d\n",ans);
    }
    return 0;
}

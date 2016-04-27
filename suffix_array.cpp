/**
 *    author:  [itmo] enot.1.10
 *    created: 06.04.2016 18:29:04       
**/
#define __USE_MINGW_ANSI_STDIO 0
#include <bits/stdc++.h>

#define F first
#define S second
#define pb push_back
#define mp make_pair
#define forn(i, n) for(int i = 0 ; (i) < (n) ; ++i)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define pw(x) (1LL<<(x))

using namespace std;

typedef long long ll;
typedef double dbl;
typedef vector<int> vi;
typedef pair<int, int> pi;

const int inf = 1.01e9;
const dbl eps = 1e-9;

/* --- main part --- */

const int N = 1e5 + 10;

char s[N];
int p[N];

int f[N];
pair<pi, int> v[N];

void build()
{
    int n = strlen(s) + 1;
    forn(i, n) f[i] = s[i];
    for (int k = 1; k < n; k <<= 1)
    {
        forn(i, n) v[i] = mp(mp(f[i], f[(i + k) % n]), i);
        sort(v, v + n);
        int cnt = 0;
        forn(i, n)
        {
            if (i && v[i - 1].F != v[i].F) ++cnt;
            f[v[i].S] = cnt;
        }
        if (cnt ==  n - 1) break;
    }
    forn(i, n - 1) p[i] = v[i + 1].S;
}

int main()
{
    #ifdef home
        assert(freopen("1.in", "r", stdin));
        assert(freopen("1.out", "w", stdout));
    #endif
    scanf("%s", s);
    build();
    int n = strlen(s);
    forn(i, n) printf("%d%c", p[i], " \n"[i + 1 == n]);    
    #ifdef home
        eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
    #endif
    return 0;
}

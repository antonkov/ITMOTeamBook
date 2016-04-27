/**
 *    author:  [itmo] enot.1.10
 *    created: 06.04.2016 18:12:01       
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
const int C = 26;

int Next[N][C], Suf[N], Len[N];
int CNT = 1;

char s[N];

void build()
{
    int last = 1;
    int n = strlen(s);
    forn(i, n)
    {
        int c = s[i] - 'a';
        int x = last;
        last = ++CNT;
        Len[last] = i + 1;
        while (x && !Next[x][c])
        {
            Next[x][c] = last;
            x = Suf[x];
        }
        if (x)
        {
            int y = Next[x][c];
            if (Len[y] == Len[x] + 1)
            {
                Suf[last] = y;
            }
            else
            {
                int z = ++CNT;
                forn(j, C) Next[z][j] = Next[y][j];
                Suf[z] = Suf[y];
                Suf[y] = Suf[last] = z;
                Len[z] = Len[x] + 1;
                while (x && Next[x][c] == y)
                {
                    Next[x][c] = z;
                    x = Suf[x];
                }
            }
        }
        else
        {
            Suf[last] = 1;
        }
    }
}

int d[N];

int dfs(int x)
{
    if (d[x]) return d[x];
    d[x] = 1;
    forn(i, C) if (Next[x][i]) d[x] += dfs(Next[x][i]);
    return d[x];
}


int main()
{
    #ifdef home
        assert(freopen("1.in", "r", stdin));
        assert(freopen("1.out", "w", stdout));
    #endif
    scanf("%s", s);
    build();
    int res = dfs(1) - 1;
    printf("%d\n", res);
    #ifdef home
        eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
    #endif
    return 0;
}

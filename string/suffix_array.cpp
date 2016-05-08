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

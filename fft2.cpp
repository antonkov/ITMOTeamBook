/**
 *    author:  [itmo] enot.1.10
 *    created: 06.04.2016 16:16:41       
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

const int base = 10;
const int N = 1 << base;
const int mod = 1e9 + 7;

struct num
{
    dbl x, y;
    num(){}
    num(dbl xx, dbl yy): x(xx), y(yy) {}
};

inline num operator + (num a, num b) { return num(a.x + b.x, a.y + b.y); }
inline num operator - (num a, num b) { return num(a.x - b.x, a.y - b.y); }
inline num operator * (num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline num conj(num a) { return num(a.x, -a.y); }

const dbl PI = acos(-1);

num rt[N];
int rev[N];

void prep()
{
    forn(i, N) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
    int NN = N >> 1;
    forn(i, NN) rt[i + NN] = num(cos(2 * PI * i / N), sin(2 * PI * i / N));
    for (int i = NN - 1; i >= 1; --i) rt[i] = rt[2 * i];
}

void fft(num *a, num *f)
{
    forn(i, N) f[i] = a[rev[i]];
    for (int k = 1; k < N; k <<= 1) for (int i = 0; i < N; i += 2 * k) forn(j, k)
    {
        num z = f[i + j + k] * rt[j + k];
        f[i + j + k] = f[i + j] - z;
        f[i + j] = f[i + j] + z;
    }
}

num a[N], b[N], f[N], g[N];
int A[N], B[N], C[N];

int tmp[N];

void mult()
{
    forn(i, N) a[i] = num(A[i] & (pw(15) - 1), A[i] >> 15);
    forn(i, N) b[i] = num(B[i] & (pw(15) - 1), B[i] >> 15);

    fft(a, f);
    fft(b, g);

    forn(i, N)
    {
        int j = (N - i) & (N - 1);
        num a1 = (f[i] + conj(f[j])) * num(0.5, 0);
        num a2 = (f[i] - conj(f[j])) * num(0, -0.5);
        num b1 = (g[i] + conj(g[j])) * num(0.5 / N, 0);
        num b2 = (g[i] - conj(g[j])) * num(0, -0.5 / N);
        a[j] = a1 * b1 + a2 * b2 * num(0, 1);
        b[j] = a1 * b2 + a2 * b1;
    }
    
    fft(a, f);
    fft(b, g);

    forn(i, N)
    {
        ll aa = f[i].x + 0.5;
        ll bb = g[i].x + 0.5;
        ll cc = f[i].y + 0.5;
        C[i] = (aa + bb % mod * pw(15) + cc % mod * pw(30)) % mod;
    }

    memset(tmp, 0, sizeof tmp);
    forn(i, N) forn(j, N) if (i + j < N) tmp[i + j] = (tmp[i + j] + A[i] * (ll)B[j]) % mod;
    forn(i, N) assert(tmp[i] == C[i]);
}

int main()
{
    prep();
    forn(i, 20) A[i] = abs(rand() * pw(15) + rand());
    forn(i, 20) B[i] = abs(rand() * pw(15) + rand());
    mult();

    #ifdef home
        eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
    #endif
    return 0;
}

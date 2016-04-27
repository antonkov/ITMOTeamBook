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

num rt[N];
int rev[N];

const dbl PI = acos(-1);

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

num a[N], f[N];
int A[N], B[N], C[N];

int tmp[N];

void mult()
{
    forn(i, N) a[i] = num(A[i], B[i]);
    fft(a, f);
    forn(i, N)
    {
        int j = (N - i) & (N - 1);
        a[i] = (f[j] * f[j] - conj(f[i] * f[i])) * num(0, -0.25 / N);
    }
    fft(a, f);
    forn(i, N) C[i] = (int)round(f[i].x);

    memset(tmp, 0, sizeof tmp);
    forn(i, N) forn(j, N) if (i + j < N) tmp[i + j] += A[i] * B[j];
    forn(i, N) assert(tmp[i] == C[i]);

}

        


int main()
{
    prep();
    forn(i, 20) A[i] = rand() % 20;
    forn(i, 20) B[i] = rand() % 20;
    mult();

    #ifdef home
        eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
    #endif
    return 0;
}

const int base = 18;
const int N = 1 << base;

struct num
{
    dbl x, y;
    num(){}
    num(dbl xx, dbl yy): x(xx), y(yy) {}
    num(dbl alp): x(cos(alp)), y(sin(alp)) {}
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

    rt[1] = num(1, 0);
    for (int k = 1; k < base; ++k)
    {
        num x(2 * PI / pw(k + 1));
        for (int i = pw(k - 1); i < pw(k); ++i)
        {
            rt[2 * i] = rt[i];
            rt[2 * i + 1] = rt[i] * x;
        }
    } 
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
ll A[N], B[N], C[N];

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
    forn(i, N) C[i] = (ll)round(f[i].x);
}

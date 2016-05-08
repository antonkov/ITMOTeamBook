const int base = 18;
const int N = 1 << base;
const dbl PI = acos(-1);

typedef complex<dbl> num;

num rt[N];
int rev[N];

void prep()
{
    forn(i, N) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
    forn(i, N / 2) rt[i + N / 2] = num(cos(2 * PI * i / N), sin(2 * PI * i / N));
    for (int i = N / 2 - 1; i >= 1; --i) rt[i] = rt[2 * i];
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

inline num conj(num z)
{
    return num(z.real(), -z.imag());
}

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
    forn(i, N) C[i] = (ll)round(f[i].real());
}

num a[N], b[N], f[N], g[N];
int A[N], B[N], C[N];

void mult(int mod)
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
}

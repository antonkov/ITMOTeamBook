int D[N];

void multLL()
{
    int mod1 = 1.5e9;
    int mod2 = mod1 + 1;
    mult(mod1);
    forn(i, N) D[i] = C[i];
    mult(mod2);
    forn(i, N)
    {
        C[i] = D[i] + (C[i] - D[i] + (ll)mod2) * (ll)mod1 % mod2 * mod1;
    }
}

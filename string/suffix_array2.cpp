pair<pair<int, int>, int> p[N], pp[N];
int c[22][N];
 
int cnt[N], st[N];

vector<int> so(string s) {
    int n = s.size();
    for (int i = 0; i < n; i++) p[i] = mp(mp(s[i], 0), i);
    sort(p, p + n);
    int e = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && p[i - 1].F != p[i].F) e++;
        c[0][p[i].S] = e;
    }
    int it = 0;
    while (e + 1 < n) {
        it++;
        memset(cnt, 0, sizeof(int) * e);
 
        for (int i = 0; i < n; i++) cnt[c[it - 1][i]]++;
        st[0] = 0;
        for (int i = 0; i < n; i++) st[i + 1] = st[i] + cnt[i];
 
        for (int i = n - 1; (i >= 0 && i + pw(it - 1) >= n); i--) {
            pp[st[c[it - 1][i]]++] = mp(mp(c[it - 1][i], -1), i);
        }
        for (int i = 0; i < n; i++) if (p[i].S - pw(it - 1) >= 0) {
            int h = c[it - 1][p[i].S - pw(it - 1)];
            pp[st[h]++] = mp(mp(h, c[it - 1][p[i].S]), p[i].S - pw(it - 1));
            }
            memcpy(p, pp, n * sizeof(p[0]));
 
        e = 0;
        for (int i = 0; i < n; i++) {
            if (i > 0 && p[i - 1].F != p[i].F) e++;
            c[it][p[i].S] = e;
        }  
    }
    vector<int> ret;
    for (int i = 0; i < n; i++) ret.pb(p[i].S);
    return ret;
}

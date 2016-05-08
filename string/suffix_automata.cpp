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

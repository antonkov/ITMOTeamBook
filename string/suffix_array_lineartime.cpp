#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(),(c).end()
#define sz(c) (int)(c).size()
#define pb push_back
#define mp make_pair
#define x first
#define y second
void lms_sort(const int n, const vector<int>& s, const vector<bool>& type, const vector<int>& pos, const int alp, vector<int>& sa1, vector<int>& sa) {
  fill(all(sa), -1);
  vector<int> cntL(alp + 1, 0);
  vector<int> cntR(alp + 1, 0);
  for (int c : s) {
    cntL[c + 1]++;
  }
  for (int i = 1; i <= alp; i++) {
    cntL[i] += cntL[i - 1];
    cntR[i - 1] = cntL[i] - 1;
  }
  reverse(all(sa1));
  for (int p : sa1) {
    sa[cntR[s[pos[p]]]--] = pos[p];
  }
  for (int p : sa1) {
    cntR[s[pos[p]]]++;
  }
  for (int i = 0; i < n; i++) if (sa[i] > 0) {
    if (!type[sa[i] - 1]) {
      sa[cntL[s[sa[i] - 1]]++] = sa[i] - 1;
    }
  }
  for (int i = n - 1; i >= 0; i--) if (sa[i] > 0) {
    if (type[sa[i] - 1]) {
      sa[cntR[s[sa[i] - 1]]--] = sa[i] - 1;
    }
  }  
}
void calc_sa(const vector<int>& s, vector<int>& sa) {
  int n = sz(s);
  cerr<<n<<endl;
  vector<bool> type(n, true);
  for (int i = n - 2; i >= 0; i--) {
    type[i] = (s[i] != s[i + 1]) ? s[i] < s[i + 1] : type[i + 1];
  }
  int alp = *max_element(all(s)) + 1;  
  int cnt_lms = 0;
  vector<int> where(n);
  vector<int> pos;
  for (int i = 1; i < n; i++) if (type[i] && !type[i - 1]) {
    pos.pb(i);
    where[i] = cnt_lms++;
  }
  vector<int> s1(cnt_lms, -1);
  vector<int> sa1(cnt_lms);  
  for (int i = 0; i < cnt_lms; i++) {
    sa1[i] = i;
  }
  lms_sort(n, s, type, pos, alp, sa1, sa);
  int cur = 0;
  int cc = 0;
  for (int i = 0; i < n; i++) if (sa[i] > 0 && type[sa[i]] && !type[sa[i] - 1]) {
    if (cc) {
      int p1 = sa[cc - 1];
      int p2 = sa[i];
      for (; ; p1++, p2++) {
        if (s[p1] < s[p2] || type[p1] < type[p2]) {
          cur++;
          break;
        }
        if ((!type[p1] && type[p1 + 1]) || 
            (!type[p2] && type[p2 + 1])) {
              if (!(!type[p2] && type[p2 + 1])) {
                cur++;
              }
              break;
            }
      }
    }
    s1[where[sa[i]]] = cur;
    sa[cc++] = sa[i];
  }
  if (cc == cur + 1) {
    for (int i = 0; i < sz(s1); i++) {
      sa1[s1[i]] = i;
    }
  } else {
    calc_sa(s1, sa1);
  }
  lms_sort(n, s, type, pos, alp, sa1, sa);
}
int main(){
  assert(freopen("output.txt","wt",stdout));
  assert(freopen("input.txt","rt",stdin));
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  vector<int> vs(sz(s) + 1);
  for (int i = 0; i < sz(s); i++) {
    vs[i] = s[i] - 'a' + 1;
  }
  vector<int> sa(sz(vs));
  calc_sa(vs, sa);
  cerr<<clock() * 1. / CLOCKS_PER_SEC<<endl;
  return 0;
}


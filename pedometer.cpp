// PROBLEM: https://atcoder.jp/contests/abc367/tasks/abc367_d

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for (int i = a; i < n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
mt19937_64 mrand(random_device{}());
const ll mod = 998244353;
int rnd(int x) { return mrand() % x; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
// head

// declaring the amount of numbers and the module
int n, m;
// declaring the result, it's long long since the constraints of the problem are big
ll res;

int main()
{
  // micro optimizations
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // entering the data
  cin >> n >> m;
  // declaring the vector A
  VI A(n);
  // entering each value
  for(auto &i: A) cin >> i;
  // declaring a vector that will hold the accumulative sums of the values
    // this is done since we're going to compute how many steps a path take from any point to another one
      // example: If we have 4 areas: 1,2,3,4 and the following amount of steps to reach the following one in clockwise sense are 1,2,3,4, with m = 6
        // then to reach the third area  from the fourth area we will need to traverse the following areas 4->1->2->3, the amount of steps needed to get to the
        // third area from the fourth is the same as the amount of steps we would have done to get to the third area in a second round minus the amount of steps we'd done to get to the fourth area in a first round
        // as following: [get to 3 in the second round from 1] 1->2->3->4->1->2->3
        //               [get to 4 in the first round from 1] 1->2->3->4
        // the difference is the following : (4)->1->2->3 (knowing that we're starting from four)
    // that's why we are doing the accumulative sums twice, so the differences in a round are helping us to count the paths from a different point from the area 1
  VI R(2*n+1, 0);
  // So we do so, computing the accumulative sums
  rep(i, 1, 2*n+1) R[i] = (R[i-1] + A[(i-1)%n]%m)%m;
  // This vector will hold the amount of occurrences of each remainder for a path
    // How do we know if the length of a path is multiple of "m"?
      // The only way to know it is if the amount of steps to get to the first one modulo m reamains the same for the second one, why?
        // Because if the amount of steps remains the same it means that there was a multiple of m amount of steps between them!
        // This suits perfectly the logic defined above (the doubled computed accumulative distances)
  VI B(m, 0);
  // Now, how do we count occurrences efficiently?
    // This involves the usage of a "slicing window" technique, which basically counts the ocurrences of a certain value within a certain range
      // The idea is the following, if our accumulative sums array us like this: [0, 1, 3, 0, 4, 5, 1, 4, 2]
        // Then on the first round starting at the fist area we have the following possible distances: [0, 1, 3, 0]
        // We count the occurrences of each one of the numbers there, so we count the reaminders, which will help us to count how many same of them are
        // NB: There's no need count paths that go over a round! We're only doing it so to make differences and effectively compute the path from different areas than the starter one
        // SO this yield the following B array: 2, 1, 0, 1, 0, 0 <- it's the most easy hash map to interpret (by indices)
        // SO going forward our next window is [1, 3, 0, 4]
        // We decrement B[R[i-n]] because we're not anymore counting the element that is no more in the window, and this preserves the logic of the circular behavior of the problem, since we are only counting minimum paths (based on the problem statement) and there's no way a minimum path could take more than one round to be minimum
        // Then we see how many of B[R[i]] are in our window, in this example it'll be. How many 4 are in the window given that the prior element was removed (the one that is no more part of the window)?
          // Going like this we effectively count the amount of paths module m that are minimum between the "n" areas
  rep(j, 0, n) B[R[j]]++; 
  rep(i, n, 2*n){
    B[R[i-n]]--;
    res += B[R[i]];
    B[R[i]]++;
  }
  cout << res << endl;
}

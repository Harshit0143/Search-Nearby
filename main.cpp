#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include <list>
#include <iterator>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <bitset>
#include <random>
#include <map>
#include <unordered_map>
#include <stdio.h>
#include <complex>
#include <math.h>
#include <cstring>
#include <chrono>
#include <string>

// ################################################################################################
// ################################################################################################

using namespace std;
#define ll long long
#define pb push_back
#define pob pop_back()
#define mp make_pair
#define fastio                      \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL)
#define pf push_front
#define pof pop_front()
#define mod 1000000007
#define add_m(a, b) (((a % mod) + (b % mod)) % mod)
#define sub_m(a, b) (((a % mod) - (b % mod) + mod) % mod)
#define mul_m(a, b) (((a % mod) * (b % mod)) % mod)

void print(vector<pair<int, int>> &vec)
{
  for (pair<int, int> &p : vec)
    cout << '(' << p.first << ',' << p.second << ") ";
  cout << '\n';
}

class search_nearby
{
private:
  int n;
  vector<vector<int>> tree;
  vector<pair<int, int>> points;
  vector<pair<int, int>> answer;
  void take_input()
  {
    cin >> n;
    points.resize(n);
    for (int point = 0; point < n; point++)
      cin >> points[point].first >> points[point].second;
  }
  void merge_by_y_coordinate(vector<int> &list1, vector<int> &list2, vector<int> &result)
  {
    int len1 = list1.size(), len2 = list2.size();
    int ptr1 = 0, ptr2 = 0;
    while (ptr1 < len1 && ptr2 < len2)
    {
      if (points[list1[ptr1]].second <= points[list2[ptr2]].second)
        result.push_back(list1[ptr1++]);

      else
        result.push_back(list2[ptr2++]);
    }
    while (ptr1 < len1)
      result.push_back(list1[ptr1++]);
    while (ptr2 < len2)
      result.push_back(list2[ptr2++]);
  }

  void build_tree(int id, int le, int rt)
  {
    if (le == rt)
    {
      tree[id].push_back(le);
      return;
    }
    int mid = le + (rt - le) / 2;
    build_tree(2 * id + 1, le, mid);
    build_tree(2 * id + 2, mid + 1, rt);
    merge_by_y_coordinate(tree[2 * id + 1], tree[2 * id + 2], tree[id]);
  }

  int search_left_most(vector<int> &vec, int target)
  {
    int le = 0, rt = vec.size() - 1, mid, res = n;
    while (le <= rt)
    {
      mid = le + (rt - le) / 2;
      int curr_y = points[vec[mid]].second;
      if (curr_y >= target)
      {
        res = mid;
        rt = mid - 1;
      }
      else
        le = mid + 1;
    }

    return res;
  }
  int search_right_most(vector<int> &vec, int target)
  {
    int le = 0, rt = vec.size() - 1, mid, res = -1;
    while (le <= rt)
    {
      mid = le + (rt - le) / 2;
      int curr_y = points[vec[mid]].second;
      if (curr_y <= target)
      {
        res = mid;
        le = mid + 1;
      }
      else
        rt = mid - 1;
    }
    return res;
  }

  void add_to_answer(vector<int> &vec, int y, int d)
  {
    int left = search_left_most(vec, y - d);
    int right = search_right_most(vec, y + d);

    for (int i = left; i <= right; i++)
      answer.push_back(points[vec[i]]);
  }

  void make_query(int x, int y, int d_max, int id, int le, int rt)
  {
    if (points[le].first > x + d_max || points[rt].first < x - d_max)
      return;
    if (x - d_max <= points[le].first && points[rt].first <= x + d_max)
    {
      add_to_answer(tree[id], y, d_max);
      return;
    }

    int mid = le + (rt - le) / 2;
    make_query(x, y, d_max, 2 * id + 1, le, mid);
    make_query(x, y, d_max, 2 * id + 2, mid + 1, rt);
  }

public:
  search_nearby()
  {
    take_input();
    sort(points.begin(), points.end());
    tree.resize(4 * n + 1);
    build_tree(0 , 0 , n - 1);
  }
  vector<pair<int, int>> search_near_points(int x, int y, int d_max)
  {
    answer.resize(0);
    make_query(x, y, d_max, 0, 0, n - 1);
    sort(answer.begin() , answer.end());
    print(answer);
    return answer;
  }
};

signed main()
{

  fastio;
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  search_nearby tree;
  int q;
  cin >> q;
  for (int i = 0; i < q; i++)
  {
    int x, y, d;
    cin >> x >> y >> d;
    tree.search_near_points(x, y, d);
  }
  fclose(stdin);
  fclose(stdout);

  return 0;
}

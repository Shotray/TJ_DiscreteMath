#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

//存储边的结构，分为起点、终点以及边权
struct Edge {
  string from;
  string to;
  int distance;
  bool operator <(const Edge& rhs)const {
    return distance < rhs.distance;
  }
};

//并查集的实现
string unionFind(map<string, string> m, string x){
  return m[x] == x ? x : m[x] = unionFind(m, m[x]);
}

//判断是否能生成一个最小生成树
//标志为所有的结点都处在一个并查集之中
bool checkUnionFind(map<string, string>m) {
  map<string, string>::iterator it = m.begin();
  string ans = unionFind(m, it->first);
  for (it = m.begin();it != m.end();it++) {
    if (unionFind(m,it->second) != ans)
      return false;
  }
  return true;
}

//Kruskal算法
/*
算法的核心思想是：
(1)假设该图G是不连通的，对该图的边以权值非降序重新排列；
(2)对于排序表中的每条边，如果现在把它放入最小生成树T不会形成回路的话，则把它加入到T中；否则丢弃；
(3)输出最小生成树T的结果，得到想要的答案。
*/
vector<Edge> Kruskal(vector<Edge> edge, map<string, string> m, vector<string> vertex) {
  vector<Edge> ans;
  sort(edge.begin(), edge.end());
  for (int i = 0;i < edge.size();i++) {
    if (unionFind(m, edge[i].from) == unionFind(m, edge[i].to))
      continue;
    m[unionFind(m, edge[i].to)] = unionFind(m, edge[i].from);
    ans.push_back(edge[i]);
  }
  if (!checkUnionFind(m))
  {
    cout << "There is no minimum spanning tree in the graph." << endl;
    ans.clear();
  }
  return ans;
}

//输出当前最小生成树
void print(vector<Edge> MST) {
  if (MST.size() == 0) {
    cout << "The tree is empty!" << endl;
    return;
  }
  for (int i = 0;i < MST.size();i++) {
    cout << MST[i].from << "-<" << MST[i].distance << ">->" << MST[i].to << "      ";
  }
  cout << endl;
  return;
}

//判断输入边是否合法
bool is_valid(string s, vector<string> ver) {
  for (int i = 0;i < ver.size();i++)
    if (s == ver[i]) return true;
  return false;
}

//测试函数
void solve() {
  cout << "**      Power grid cost simulation system      **" << endl;
  cout << "=================================================" << endl;
  cout << "**          A---Creating grid vertices         **" << endl;
  cout << "**             B---Add side of grid            **" << endl;
  cout << "**    C---Constructing minimum spanning tree   **" << endl;
  cout << "**        D---Show minimum spanning tree       **" << endl;
  cout << "**                   E---Exit                  **" << endl;
  cout << "=================================================" << endl;
  vector<Edge> min_spanning_tree;
  vector<Edge> edge;
  vector<string> vertices;
  map<string, string> union_find;
  while (true) {
    cout << "Please select an action:";
    char op;
    cin >> op;
    if (op == 'A') {
      int total;
      cout << "Please input the number of vertices:";
      cin >> total;
      if (cin.fail())
        throw invalid_argument("Wrong Input!");
      cout << "Please input the vertices:";
      for (int i = 0;i < total;i++) {
        string vertex;
        cin >> vertex;
        vertices.push_back(vertex);
      }
    }
    else if (op == 'B') {
      while (true) {
        cout << "Please input two vertices and edge(end with ? ? 0 ):";
        Edge e;
        cin >> e.from >> e.to >> e.distance;
        if (e.from == "?" && e.to == "?" && e.distance == 0)
          break;
        if (!is_valid(e.from, vertices) || !is_valid(e.to, vertices))
          throw invalid_argument("Wrong Input!");
        union_find[e.from] = e.from;
        union_find[e.to] = e.to;
        edge.push_back(e);
      }
    }
    else if (op == 'C') {
      //Kruskal
      min_spanning_tree = Kruskal(edge, union_find, vertices);

      if(min_spanning_tree.size()!=0)
        cout << "Minimum spanning tree generated!" << endl;
    }
    else if (op == 'D') {
      cout << "Vertices and edges in minimum spanning tree are:" << endl;
      print(min_spanning_tree);
    }
    else if (op == 'E') {
      break;
    }
    else {
      throw invalid_argument("Wrong Input");
    }
  }
  return;
}

int main(void) {
  solve();
  return 0;
}
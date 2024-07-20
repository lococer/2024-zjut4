

#include <iostream>
#include <set>
#include <queue>
#include <map>
using namespace std;

typedef pair<int, int> zb;
typedef pair<int, zb> element;

int heuristic(const zb& now, const zb& target);
vector<zb> getneibor(const zb& current, const int& n, const int& m);

int main()
{
    int m = 6, n = 6;
    set<zb> ban = { {0,1} ,{1,1} };
    zb start = { 0,0 }, target = { 5,5 };
    priority_queue < element, vector <element>, greater< element>> dl;
    map<zb,int> cost_so_far;
    map<zb, zb> come_from;
    cost_so_far[start] = 0;
    

    dl.push(element(0,start));
    while (!dl.empty()) {
        auto [cost,current]=dl.top();
        dl.pop();
        if (current == target)break;
        for (auto next : getneibor(current, n, m)) {
            if (ban.find(next) != ban.end())continue;
            int newcost = cost_so_far[current] + 1;//每次移动消耗1
            if (cost_so_far.find(next) == cost_so_far.end() || newcost < cost_so_far[next]) {
                cost_so_far[next] = newcost;
                dl.push(element(newcost+heuristic(next,target),next));
                come_from[next] = current;
            }
        }
    }
    string grid = "";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ban.find(zb{ i,j }) != ban.end())grid+="X";
            else if (zb(i, j) == start)grid+= "S";
            else if (zb(i, j) == target)grid+= "T";
            else grid+="O";
        }
        grid += "\n";
    }
    zb tmp = target;
    while (tmp != start) {
        if (come_from.find(tmp) == come_from.end())break;
        auto& [x1, y1] = come_from[tmp];
        auto& [x2, y2] = tmp;
        if (x1 == x2)grid[y1 + x1 * (m+1)] = '-';
        else if (y1 == y2)grid[y1 + x1 * (m+1)] = '|';
        else if((x1-x2)*(y1-y2)<0)grid[y1 + x1 * (m+1)] = '\\';
        else grid[y1 + x1 * (m+1)] = '/';
        tmp = come_from[tmp];
    }
    cout << grid;

    return 0;
}



/*
启发函数
*/
int heuristic(const zb& now, const zb& target) {
    return abs(now.first - target.first) + abs(now.second - target.second);
}

/*
获取周围格子
*/
vector<zb> getneibor(const zb &current,const int &n,const int &m) {
    vector<zb> ret;
    auto &[x, y] = current;
    int dx[] = { 0,1,0,-1 }, dy[] = { 1,0,-1,0 };
    for (int i = 0; i < 4; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if (xx >= 0 && xx < n && yy >= 0 && yy < m)ret.push_back(zb(xx, yy));
    }
    return ret;
}
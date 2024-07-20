//alpha-beta剪枝
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int son_num[100],son[100][100],val[100];
int main(){

    return 0;
}
/// @brief alpha_beta剪枝
/// @param u 当前节点
/// @param alph 下界
/// @param beta 上届
/// @param is_max 是否最大化节点
/// @return 节点值
int alpha_beta(int u, int alph, int beta, bool is_max) {
  if (!son_num[u]) return val[u];
  if (is_max) {
    for (int i = 0; i < son_num[u]; ++i) {
      int d = son[u][i];
      alph = max(alph, alpha_beta(d, alph, beta, is_max ^ 1));
      if (alph >= beta) break;
    }
    return alph;
  } else {
    for (int i = 0; i < son_num[u]; ++i) {
      int d = son[u][i];
      beta = min(beta, alpha_beta(d, alph, beta, is_max ^ 1));
      if (alph >= beta) break;
    }
    return beta;
  }
}
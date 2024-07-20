#include <iostream>

using namespace std;

class qianzhui {
public:
    bool end=false;                                //单词终止标记
    qianzhui* next[26]{};  //1                          //指向下一个字符
    
};


class qzcaozuo {
private:
    qianzhui* p = new qianzhui;
public:
    void insert(string a);
    bool cword(string a);
    bool cpre(string a);
};

void qzcaozuo::insert(string word) {
    qianzhui* tmp = this->p;
    for (auto a : word) {
        if (tmp->next[a - 'a']==NULL)tmp->next[a - 'a'] = new qianzhui;
        tmp = tmp->next[a - 'a'];
        
    }
    tmp->end = true;
    return;

}

bool qzcaozuo::cword(string word)
{
    qianzhui* tmp= this->p;
    for (auto a : word) {
        if (!tmp->next[a - 'a'])return false;
        tmp = tmp->next[a - 'a'];
    }
    return tmp->end;
}

bool qzcaozuo::cpre(string word)
{
    qianzhui* tmp = this->p;
    for (auto a : word) {
        if (!tmp->next[a - 'a'])return false;
        tmp = tmp->next[a - 'a'];
    }
    return true;
}




int main(void)
{
    int type = 0; //0插 1全 2前
    string a;
    qzcaozuo dic;
    cout << "输入单词组\n";
    dic.insert("word");
    while (cin >> a) {
        if (a == "插入") { type = 0; continue; }
        if (a == "单词"){type = 1; continue;}
        if (a == "前缀"){type = 2; continue;}
        if (type == 0) {
            dic.insert(a);
            cout << a << "已插入\n";
        }
        if (type == 1) {
            cout << (dic.cword(a) ? "单词存在\n" : "未找到\n");
        }
        if (type == 2) {
            cout << (dic.cpre(a) ? "前缀存在\n" : "未找到\n");
        }
    }
    return 0;
}




/* 简单的散列表应用 开放定址法 线性探测法 */
#include<iostream>
#define MAXSIZE 12
#define NULLKEY -32768
using namespace std;

class Hashtable
{
private:
    int *elem;
    int count;
    int size;
public:
    Hashtable();
    int Hash(int key){return key%size;}
    void Insert(int key);
    bool Search(int key);
    void Show();
};
Hashtable::Hashtable()
{
    size=MAXSIZE;
    count=0;
    //elem=new int[MAXSIZE];
    for(int i=0;i!=size;i++)
        elem[i]=NULLKEY;
}
void Hashtable::Insert(int key)
{
    int addr=Hash(key);
    while(elem[addr]!=NULLKEY)
    {
        addr=(addr+1)%size;
    }
    elem[addr]=key;
    count++;
}
bool Hashtable::Search(int key)
{
    int addr;
    addr=Hash(key);
    while(elem[addr]!=key)
    {
        addr=(addr+1)%size;
        if(elem[addr]==NULLKEY||addr==Hash(key))
        {
            return false;
        }
    }
    return true;
}
void Hashtable::Show()
{
    cout<<"存在个数："<<count<<endl;
}
int main()
{
    Hashtable hs;
    int k;
    int a[]={12,67,56,16,25,37,22,29,15,47,48,34};
    for(int i=0;i!=12;i++)
        hs.Insert(a[i]);
        hs.Show();
        k=28;
    cout<<"search for "<<k<<":"<<endl;
    cout<<hs.Search(k)<<endl;
    return 0;
}

//平衡二叉树
#include <iostream>
#define TRUE 1
#define FALSE 0
#define LH +1
#define EH 0
#define RH -1
using namespace std;

class BiNode
{
public:
    int date;
    int bf;
    BiNode *left;
    BiNode *right;
};

class AVL
{
private:
    BiNode *root;
    int taller;
    bool SearchAVL(BiNode *T,int key);
    void preorder(BiNode *T);
    void inorder(BiNode *T);
    void postorder(BiNode *T);
    bool DeleteBST(BiNode *&T,int key);
    bool DeleteEle(BiNode *&T);
    void R_Rotate(BiNode* &T);
    void L_Rotate(BiNode* &T);
    void R_Balance(BiNode *&T);
    void L_Balance(BiNode *&T);
    int InsertAVL(BiNode* &T,int key);
public:
    AVL(){root=NULL;taller=FALSE;};
    ~AVL(){root=NULL;};
    //void Insert();
    void Insert(int key){InsertAVL(root,key);};
    bool Search(int key){return SearchAVL(root,key);};
    void showpreorder(){preorder(root);cout<<endl;};
    void showinorder(){inorder(root);cout<<endl;};
    void showpostorder(){postorder(root);cout<<endl;};
};
int AVL::InsertAVL(BiNode* &T,int key)//需要传入实体型变量
{
    if(!T)                                 //插入新元素
    {
        T=new BiNode;
        T->date=key;
        T->left=T->right=NULL;
        T->bf=EH;
        taller=true;
    }
    else
    {
        if(T->date==key)                        //存在元素
        {
            taller=FALSE;
            return FALSE;
        }
        else if(key<T->date)
        {
            if(!InsertAVL(T->left,key))  //插入失败
                return FALSE;
            if(taller)
            {
                switch(T->bf)
                {
                case LH:
                    L_Balance(T);
                    taller=FALSE;
                    break;
                case EH:
                    T->bf=LH;
                    taller=TRUE;
                    break;
                case RH:
                    T->bf=EH;
                    taller=FALSE;
                    break;
                }
            }
        }
        else
        {
            if(!InsertAVL(T->right,key))
                return FALSE;
            if(taller)
            {
                switch(T->bf)
                {
                case RH:
                    R_Balance(T);
                    taller=FALSE;
                    break;
                case EH:
                    T->bf=RH;
                    taller=TRUE;
                    break;
                case LH:
                    T->bf=EH;
                    taller=FALSE;
                    break;
                }
            }
        }
    }
    return TRUE;
}
void AVL::L_Balance(BiNode *&T)
{
    BiNode *L,*LR;
    L=T->left;
    switch(L->bf)
    {
        case LH:
            T->bf=L->bf=EH;
            R_Rotate(T);
            break;
        case RH:
            LR=L->right;
            switch(L->bf)
            {
            case LH:
                T->bf=RH;
                L->bf=EH;
                break;
            case EH:
                T->bf=EH;
                L->bf=EH;
                break;
            case RH:
                T->bf=EH;
                L->bf=LH;
                break;
            }
            LR->bf=EH;
            L_Rotate(T->left);
            R_Rotate(T);
            break;
    }
}
void AVL::R_Rotate(BiNode *&p)
{
    BiNode* L   ;
    L=p->left;
    p->left=L->right;
    L->right=p;
    p=L;
}
void AVL::L_Rotate(BiNode *&p)
{
    BiNode* R;
    R=p->right;
    p->right=R->left;
    R->left=p;
    p=R;
}
void AVL::R_Balance(BiNode *&T)
{
    BiNode *R,*RL;
    R=T->right;
    switch(R->bf)
    {
    case RH:
        T->bf=R->bf=EH;
        L_Rotate(T);
        break;
    case LH:
        RL=R->left;
        switch(RL->bf)
        {
        case RH:
            T->bf=LH;
            R->bf=EH;
            break;
        case EH:
            T->bf=R->bf=EH;
            break;
        case LH:
            T->bf=EH;
            R->bf=RH;
            break;
            }
            RL->bf=EH;
            R_Rotate(T->right);
            L_Rotate(T);
            break;
    }
}

//查找函数的实现
bool AVL::SearchAVL(BiNode *T,int key)
{
    if(T==NULL)
        return FALSE;
    else if(T->date==key)
    {
            return TRUE;
    }
    else if(T->date>key)
    {
        return SearchAVL(T->left,key);
    }
    else
        return SearchAVL(T->right,key);
}
void AVL::preorder(BiNode *root)
{
    if(root==NULL)  return;
    else{
        cout<<root->date<<" ";
        preorder(root->left);
        preorder(root->right);
        }

}
void AVL::inorder(BiNode *T)
{
    if(T==NULL)  return;
    else{
        inorder(T->left);
        cout<<T->date<<" ";
        inorder(T->right);
    }
}
void AVL::postorder(BiNode *T)
{
    if(T==NULL)  return;
    else{
        postorder(T->left);
        postorder(T->right);
        cout<<T->date<<" ";
    }
}
int main()
{
    cout<<"AVL________"<<endl;
    AVL avl;
    int  i,k;
    //int a[10]={62,88,58,47,35,73,51,99,37,93};
    int a[10]={3,2,1,4,5,6,7,10,9,8};
    cout<<"输入数据："<<endl;
    for(i=0;i!=10;i++)
    {
        avl.Insert(a[i]);
        cout<<a[i]<<" ";
    }
    //avl.Insert();
    cout<<endl<<endl;
    cout<<"前序遍历:"<<endl;
    avl.showpreorder();
    cout<<"中序遍历:"<<endl;
    avl.showinorder();
    cout<<"后序遍历:"<<endl;
    avl.showpostorder();
    cout<<endl;
//    k=58;
//    cout<<"查找："<<k<<" "<<avl.Search(k)<<endl;
//    k=57;
//    cout<<"查找："<<k<<" "<<avl.Search(k)<<endl;
//    k=58;
//    cout<<"中序遍历:"<<endl;
//    avl.showinorder();
//    cout<<"root:"<<avl.GetRoot()<<endl;
//    k=99;
//    cout<<"删除："<<k<<" "<<avl.Delete(k)<<endl;
//    cout<<"删除后遍历:"<<endl;
//    avl.showinorder();

    return 0;
}

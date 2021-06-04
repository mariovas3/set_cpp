#include<iostream>
#include <stack>
using namespace std;

struct Node{
    int value;
    Node*left=nullptr;
    Node*right=nullptr;
    int height;//this is to be used later for checking the balance of the node
};


class AVL{
    Node*root=nullptr;

    //helper functions for insertion
    int Balance(Node*node);
    int NodeHeight(Node*node);
    Node* LLrotation(Node*node);
    Node* LRrotation(Node*node);
    Node* RRrotation(Node*node);
    Node* RLrotation(Node*node);
    Node* RecInsert(Node*tree,int val);//recursive insert

    
    //helper functions for deletion
    Node* RecDelete(Node*tree,int val);
    Node* InPred(Node*tree);//gets inorder predecessor
    Node* InSucc(Node*tree);//gets inorder successor


    //helper functions for displaying outputting
    int RecCount(Node*tree);//counts number of nodes
    int Height(Node*tree);//gets the height of the tree
    void RecInorder(Node*tree);//recursive inorder traversal

    //recursively delete tree if you do not want the implementation with the stack (iterative)
    void DeleteTree(Node*tree);

public:
    AVL(){}
    bool Contains(int val);//check if value is contained
    int Height(){return Height(root);}
    void Insert(int val);//inserts a node
    void Delete(int val);//deletes a node
    void Inorder(){RecInorder(root);cout<<'\n';}
    int Count(){return RecCount(root);}

    ~AVL();

};


void AVL::DeleteTree(Node*tree){
    if(!tree)return;
    DeleteTree(tree->left);
    DeleteTree(tree->right);
    delete [] tree;

}

void AVL::Delete(int val){
    if(Contains(val))RecDelete(root,val);
}

void AVL::Insert(int val){
    if(!Contains(val))RecInsert(root,val);
}

int AVL::Height(Node*tree){
    if(tree){
        int x=Height(tree->left)+1;
        int y=Height(tree->right)+1;
        return x>y?x:y;
    }
    return -1;

}

bool AVL::Contains(int val){
    Node*p=root;
    while(p){
        if(p->value>val)p=p->left;
        else if(p->value<val)p=p->right;
        else return true;
    }
    return false;
}


Node* AVL::InPred(Node*tree){
    tree=tree->left;
    while(tree&&tree->right)tree=tree->right;
    return tree;
}

Node* AVL::InSucc(Node*tree){
    tree=tree->right;
    while(tree&&tree->left)tree=tree->left;
    return tree;
}

Node* AVL::RecDelete(Node*tree,int val){
    if(!tree){return nullptr;}

    if(tree->value>val)tree->left=RecDelete(tree->left,val);
    else if(tree->value<val)tree->right=RecDelete(tree->right,val);
    else{
        if(!tree->left&&!tree->right){
            delete tree;
            return nullptr;
        }
        
        else{
            Node*q=InPred(tree);

            if(q){
                tree->value=InPred(tree)->value;
                tree->left=RecDelete(tree->left,tree->value);
            }
            else if(InSucc(tree)){
                tree->value=InSucc(tree)->value;
                tree->right=RecDelete(tree->right,tree->value);
            }
        }
    }
    
    tree->height=NodeHeight(tree);
    if(Balance(tree)==2&&Balance(tree->left)==1)return LLrotation(tree);
    else if(Balance(tree)==2&&Balance(tree->left)==-1)return LRrotation(tree);
    else if(Balance(tree)==2&&Balance(tree->left)==0)return LLrotation(tree);
    else if(Balance(tree)==-2&&Balance(tree->right)==-1)return RRrotation(tree);
    else if(Balance(tree)==-2&&Balance(tree->right)==1)return RLrotation(tree);
    else if(Balance(tree)==-2&&Balance(tree->right)==0)return RRrotation(tree);
    return tree;
}


AVL::~AVL(){
    // DeleteTree(root);
    
    if(root){
        stack<Node**>stk;
        Node**p=&root;
        stk.push(p);

        while(!stk.empty()){
            if((*p)->left){
                p=&(*p)->left;
                stk.push(p);
            }
            else if((*p)->right){
                p=&(*p)->right;
                stk.push(p);
            }
            else{
                stk.pop();
                delete (*p);
                (*p)=nullptr;
                if(!stk.empty())p=stk.top();
            }
        }
    }
    if(!root)cout<<"tree deleted\n";
}

void AVL::RecInorder(Node*tree){
    if(!tree)return;
    RecInorder(tree->left);
    cout<<tree->value<<' ';
    RecInorder(tree->right);
}

int AVL::RecCount(Node*tree){
    if(!tree)return 0;
    return 1+RecCount(tree->left)+RecCount(tree->right);
}

Node* AVL::LLrotation(Node*node){
    Node*pl=node->left;

    
    node->left=pl->right;
    pl->right=node;

    node->height=NodeHeight(node);
    pl->height=NodeHeight(pl);
    if(root==node)root=pl;
    return pl;
    
}

Node* AVL::LRrotation(Node*node){
    Node*plr=node->left->right;
    node->left->right=plr->left;
    plr->left=node->left;
    node->left=plr->right;
    plr->right=node;

    
    if(root==node)root=plr;

    plr->left->height=NodeHeight(plr->left);
    node->height=NodeHeight(node);
    plr->height=NodeHeight(plr);
    
    return plr;

}


Node* AVL::RRrotation(Node*node){

    Node*pr=node->right;
    node->right=pr->left;
    pr->left=node;

    node->height=NodeHeight(node);
    pr->height=NodeHeight(pr);
    if(root==node)root=pr;
    return pr;
}

Node* AVL::RLrotation(Node*node){
    Node*prl=node->right->left;
    node->right->left=prl->right;
    prl->right=node->right;
    node->right=prl->left;
    prl->left=node;

    node->height=NodeHeight(node);
    prl->right->height=NodeHeight(prl->right);
    prl->height=NodeHeight(prl);

    if(root==node)root=prl;
    return prl;

}

int AVL::Balance(Node*node){
    int lh,rh;
    lh=node->left?node->left->height:-1;
    rh=node->right?node->right->height:-1;

    return lh-rh;
}

int AVL::NodeHeight(Node*node){
    int lh,rh;
    lh=node->left?node->left->height:-1;
    rh=node->right?node->right->height:-1;
    return lh>rh?lh+1:rh+1;
}

Node* AVL::RecInsert(Node* tree,int val){
    if(!tree){
        if(!root){
            root=new Node;
            root->value=val;
            root->height=0;
            return root;
        }
        tree=new Node;
        tree->value=val;
        tree->height=0;
        return tree;
    }
        
    if(tree->value>val)tree->left=RecInsert(tree->left,val);
        
    else if(tree->value<val)tree->right=RecInsert(tree->right,val);
        
    tree->height=NodeHeight(tree);

    if(Balance(tree)==2&&Balance(tree->left)==1)return LLrotation(tree);
    else if(Balance(tree)==2&&Balance(tree->left)==-1)return LRrotation(tree);
    else if(Balance(tree)==-2&&Balance(tree->right)==-1)return RRrotation(tree);
    else if(Balance(tree)==-2&&Balance(tree->right)==1)return RLrotation(tree);
    
    return tree;    
}

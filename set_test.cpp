#include "set_avl_tree.h"
using namespace std;

int main(){
    AVL tree;
    int A[]={1,2,3,4,5,6,7,7,7,9};
    for(int x:A)tree.Insert(x);
    tree.Insert(9);
    cout<<"the height of the tree is: "<<tree.Height()<<'\n';
    cout<<"number of nodes is: "<<tree.Count()<<'\n';
    tree.Inorder();
    
    
    tree.Delete(6);
    cout<<"number of nodes is: "<<tree.Count()<<'\n';
    tree.Delete(13);//will not do anything if 13 not in the tree
    tree.Inorder();
    
    cout<<"the height of the tree is: "<<tree.Height()<<'\n';
    

    return 0;
}
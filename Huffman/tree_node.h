#ifndef TREE_NODE_H_
#define TREE_NODE_H_

typedef struct TreeNode {
    char byte;
    unsigned int frequency;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char byte, unsigned short frequency);
    bool isLeaf();
}TreeNode;

class CompareTreeNode{
    public:
        bool operator() (TreeNode* t1, TreeNode* t2){
            return t1->frequency > t2->frequency;
        }
};


#endif // TREE_NODE_H_
#define DataType int
typedef struct BTree{
	struct BTtree * left;
	struct BTtree * right;
	DataType data;
	
}*BT;
extern void createBinaryTree(BT *tree,DataType data);
extern  void printString(BT);

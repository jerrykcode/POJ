#include <cstdio>
#include <cstdlib>

class BalancedTree {
public:
	BalancedTree() : tree(NULL) {}
	~BalancedTree() { deleteTree(tree); }

	void insert(int key);
	void remove(int key);

	/* ����key������������keyС����������+1 */
	int rank(int key);

	/* ��������Ϊrank���� */
	int select(int rank);

	/* ����key��ǰ�� */
	int pre(int key);

	/* ����key�ĺ�� */
	int next(int key);
private:
	//SBT��
	typedef struct TNode {
		int key;
		int num; //key���ֵĴ���
		int num_size; //���Ľ��洢�����������������н��num֮��
		int node_size; //���Ľ��������SBT�Դ�ά��ƽ��
		struct TNode * left;
		struct TNode * right;
		TNode(int key) : key(key), num(1), num_size(1), node_size(1), left(NULL), right(NULL) {}
	} *Tree;

	int getNum(Tree tree) { return tree ? tree->num : 0; }
	int getNumSize(Tree tree) { return tree ? tree->num_size : 0; }
	int getNodeSize(Tree tree) { return tree ? tree->node_size : 0; }

	Tree leftRotate(Tree tree); //����
	Tree rightRotate(Tree tree); //����

	/* ά��ƽ�� */
	Tree maintain(Tree tree);

	/* ά��ƽ��--�������ĺ��ӵ�node_size������������node_size 
	    ����SBT�Խ�������(node_size)ά��ƽ�⣬��������������(num_size) */
	Tree maintainLeft(Tree tree);

	/* ά��ƽ��--�������ĺ��ӵ�node_size������������node_size */
	Tree maintainRight(Tree tree);

	/* ������ */
	Tree insert(Tree tree, int key);

	/* ɾ����� */
	Tree remove(Tree tree, int key);

	/* �����rank���ص��Ǳ�keyС������������û�� + 1 */
	int rank(Tree tree, int key);

	/* ��key�ĺ��С����������������keyС���������� + key���ֵĴ��� */
	int rankNext(Tree tree, int key);

	/* ������rank��������С���� */
	int select(Tree tree, int rank);

	void deleteTree(Tree tree);
private:
	Tree tree;
};

/*----------------------------------------------------SBT---------------------------------------------------------*/
BalancedTree::Tree BalancedTree::leftRotate(Tree tree) {
	//����
	Tree k = tree->right;
	tree->right = k->left;
	k->left = tree;
	//num_size��node_size��Ҫ����
	k->num_size = tree->num_size;
	k->node_size = tree->node_size;
	tree->num_size = getNumSize(tree->left) + getNumSize(tree->right) + tree->num;
	tree->node_size = getNodeSize(tree->left) + getNodeSize(tree->right) + 1;
	return k;
}

BalancedTree::Tree BalancedTree::rightRotate(Tree tree) {
	//����
	Tree k = tree->left;
	tree->left = k->right;
	k->right = tree;
	//num_size��node_size��Ҫ����
	k->num_size = tree->num_size;
	k->node_size = tree->node_size;
	tree->num_size = getNumSize(tree->left) + getNumSize(tree->right) + tree->num;
	tree->node_size = getNodeSize(tree->left) + getNodeSize(tree->right) + 1;
	return k;
}

BalancedTree::Tree BalancedTree::maintain(Tree tree) {
	tree = maintainLeft(tree);
	tree = maintainRight(tree);
	return tree;
}

BalancedTree::Tree BalancedTree::maintainLeft(Tree tree) {
	if (tree == NULL) return NULL;
	if (tree->left == NULL) return tree;
	if (tree->left->left && tree->left->left->node_size > getNodeSize(tree->right)) { //����������������node_size������������node_size
		tree = rightRotate(tree);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	else if (tree->left->right && tree->left->right->node_size > getNodeSize(tree->right)) { //����������������node_size��������node_size
		tree->left = leftRotate(tree->left);
		tree = rightRotate(tree);
		tree->left = maintain(tree->left);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	return tree;
}

BalancedTree::Tree BalancedTree::maintainRight(Tree tree) {
	if (tree == NULL) return NULL;
	if (tree->right == NULL) return tree;
	if (tree->right->right && tree->right->right->node_size > getNodeSize(tree->left)) { //����������������node_size������������node_size
		tree = leftRotate(tree);
		tree->left = maintain(tree->left);
		tree = maintain(tree);
	}
	else if (tree->right->left && tree->right->left->node_size > getNodeSize(tree->left)) { //����������������node_size������������node_size
		tree->right = rightRotate(tree->right);
		tree = leftRotate(tree);
		tree->left = maintain(tree->left);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	return tree;
}

BalancedTree::Tree BalancedTree::insert(Tree tree, int key) {
	if (tree == NULL) {
		return new TNode(key); //�½����
	}
	if (key == tree->key) { //key�Ѿ�����
		//ע�ⲻ���½���㣡��
		tree->num++; //key���ֵĴ�������
		tree->num_size++; //tree�Ľ���������䣬��������������1
	}
	else if (key < tree->key) { 	
		int node_size = getNodeSize(tree->left); //������ԭ���Ľ����
		tree->left = insert(tree->left, key);	//�ݹ����������
		tree->num_size++; //����������1
		if (getNodeSize(tree->left) > node_size) { //���������Ľ���������ӣ�������������ʱ�½��˽��
			tree->node_size++; //���������1
			tree = maintainLeft(tree); //��������ı䣬��ı������Ľṹ����Ҫά��ƽ�⡣���������½���㣬��maintainLeftά��ƽ��
		}
	}
	else { //key > tree->key
		//�������߶Գ�
		int node_size = getNodeSize(tree->right); //������ԭ���Ľ����
		tree->right = insert(tree->right, key);	//�ݹ����������
		tree->num_size++; //����������1
		if (getNodeSize(tree->right) > node_size) { //���������Ľ���������ӣ�������������ʱ�½��˽��
			tree->node_size++; //���������1
			tree = maintainRight(tree); //��������ı䣬��ı������Ľṹ����Ҫά��ƽ�⡣���������½���㣬��maintainRightά��ƽ��
		}
	}
	return tree;
}

BalancedTree::Tree BalancedTree::remove(Tree tree, int key) {
	if (tree == NULL) {
		//key�����ڣ��޷�ɾ�������������ԭ������ı�
		return NULL;
	}
	if (key == tree->key) { //�ҵ�key
		if (tree->num > 1) { //��key�ж��������ֻɾ��һ��������ɾ�����
			tree->num--; //key��������1
			tree->num_size--; //����������1
		}
		//��keyֻ��һ������ɾ��key��ɾ��һ�����
		else if (tree->left && tree->right) { //��tree����������������
			Tree pre = tree->left;
			while (pre->right) pre = pre->right; //tree��ǰ����������������
			tree->key = pre->key; //��pre����tree
			tree->num = pre->num; //��pre����tree
			//��ʱ��Ҫ����������ɾ��pre����ע��Ҫ��pre������ɾ��			
			if (pre->num > 1) {
				//��pre->num > 1�����ֱ�ӵ���remove����û��ɾ�����
				int sub_num = pre->num - 1;
				pre->num = 1;
				pre = tree->left;
				while (pre->right) {
					pre->num_size -= sub_num;
					pre = pre->right;
				}
				pre->num_size -= sub_num;
			}
			//��ʱpre->numΪ1������remove����ɾ�����
			tree->left = remove(tree->left, pre->key);
			tree->num_size--; //����������1
			tree->node_size--; //����������1
			tree = maintainRight(tree); //��������ɾ���˽�㣬�������Ľ������������ˣ�������maintainRightά��ƽ��
		}
		else {
			Tree tmp = tree;
			tree = tree->left ? tree->left : tree->right; //����������
			delete tmp; //ɾ��
		}
	}
	else if (key < tree->key) {
		int node_size = getNodeSize(tree->left); //������ԭ���Ľ������
		int num_size = getNumSize(tree->left); //������ԭ������������
		tree->left = remove(tree->left, key); //�ݹ����������ɾ��
		if (getNumSize(tree->left) < num_size) { //�������������������٣���key����
			tree->num_size--; //����������1
		}
		if (getNodeSize(tree->left) < node_size) { //�������Ľ���������٣���ɾ����һ�����
			tree->node_size--; //���������1
			tree = maintainRight(tree); //����������٣��ı������Ľṹ����Ҫά��ƽ�⡣������ɾ����㣬�������Ľ������������ˣ�������maintainRightά��ƽ��
		}
	}
	else { //key > tree->key
		int node_size = getNodeSize(tree->right); //������ԭ���Ľ������
		int num_size = getNumSize(tree->right); //������ԭ������������
		tree->right = remove(tree->right, key); //�ݹ����������ɾ��
		if (getNumSize(tree->right) < num_size) { //�������������������٣���key����
			tree->num_size--; //����������1
		}
		if (getNodeSize(tree->right) < node_size) { //�������Ľ���������٣���ɾ����һ�����
			tree->node_size--; //���������1
			tree = maintainLeft(tree); //����������٣��ı������Ľṹ����Ҫά��ƽ�⡣������ɾ����㣬�������Ľ������������ˣ�������maintainLeftά��ƽ��
		}
	}
	return tree;
}

int BalancedTree::rank(Tree tree, int key) {
	if (tree == NULL) return 0;
	if (key == tree->key) {
		//������������������������tree�б�keyС����������
		return getNumSize(tree->left);
	}
	else if (key < tree->key) {
		return rank(tree->left, key);
	}
	else {
		//���������������� + tree��key������ + �������б�keyС������
		return getNumSize(tree->left) + getNum(tree) + rank(tree->right, key);
	}
}

int BalancedTree::rankNext(Tree tree, int key) {
	if (tree == NULL) return 0;
	if (key == tree->key) {
		//���������������� + tree��key������
		return getNumSize(tree->left) + getNum(tree);
	}
	else if (key < tree->key) {
		return rankNext(tree->left, key);
	}
	else {
		return getNumSize(tree->left) + getNum(tree) + rankNext(tree->right, key);
	}
}

int BalancedTree::select(Tree tree, int rank) {
	// ������rank��������С����
	if (tree == NULL) return 0;
	if (rank < getNumSize(tree->left)) {
		return select(tree->left, rank);
	}
	else if (rank >= getNumSize(tree->left) && rank < getNumSize(tree->left) + getNum(tree)) {
		//���ڵ������������������� && С������������������ + tree��key������
		return tree->key;
	}
	else {
		return select(tree->right, rank - getNumSize(tree->left) - getNum(tree));
	}
}
void BalancedTree::deleteTree(Tree tree) {
	if (tree == NULL) return;
	if (tree->left) deleteTree(tree->left);
	if (tree->right) deleteTree(tree->right);
	delete tree;
}
/*----------------------------------------------------SBT---------------------------------------------------------*/

void BalancedTree::insert(int key) {
	tree = insert(tree, key);
}

void BalancedTree::remove(int key) {
	tree = remove(tree, key);
}

int BalancedTree::rank(int key) {
	return rank(tree, key) + 1; //ע��+1
}

int BalancedTree::select(int rank) {
	return select(tree, rank - 1); //ע��rank-1
}

int BalancedTree::pre(int key) { //ǰ��
	int r = rank(tree, key); //key������
	return select(tree, r - 1); //key��ǰ��һ����
}

int BalancedTree::next(int key) {
	int r = rankNext(tree, key); //key�ĺ�̵�����
	return select(tree, r); //key�ĺ��
}

int main() {
	BalancedTree bt;
	int n;
	scanf("%d", &n);
	int opt, x;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &opt, &x);
		switch (opt) {
		case 1: bt.insert(x); break;
		case 2: bt.remove(x); break;
		case 3: printf("%d\n", bt.rank(x)); break;
		case 4: printf("%d\n", bt.select(x)); break;
		case 5: printf("%d\n", bt.pre(x)); break;
		case 6: printf("%d\n", bt.next(x)); break;
		default:break;
		}
	}
	return 0;
}
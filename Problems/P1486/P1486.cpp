#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

class Cashier {
public:

	Cashier(int min);
	~Cashier();

	void insert(int salary); //I
	void increase(int salary_increment); //A 
	void decrease(int salary_decrement); //S
	int select(int k); //F

private:
	//SBT��
	typedef struct TNode {
		int key; //BST��keyֵ�����ڴ�����keyΪ����
		struct TNode * left;
		struct TNode * right;
		size_t size; //���������SBT����sizeά��ƽ��
		TNode(int key) : key(key), left(NULL), right(NULL), size(1) {}
	} *Tree;

	size_t getSize(Tree tree) {
		return tree ? tree->size : 0;
	}

	Tree leftRotate(Tree tree); //����
	Tree rightRotate(Tree tree); //����

	Tree maintain(Tree tree); //ά��ƽ��
	Tree maintainLeft(Tree tree); //ά��ƽ��--�������ĺ��ӵ�size������������size
	Tree maintainRight(Tree tree); //ά��ƽ��--�������ĺ��ӵ�size������������size

	Tree insert(Tree tree, int key); //����
	int select(Tree tree, int rank); //��tree���ҵ�����rank�Ľ�㣬����rank������keyС�ڸý���key�����ظý���key
	Tree remove(Tree tree, int key); //ɾ�����

	void deleteTree(Tree tree); //ɾ����

private:
	Tree tree; //ƽ����
	size_t remove_num; //�뿪��Ա��������tree��ɾ���Ľ����
	int min; //��С����
	queue<Tree> q; //����
};

Cashier::Cashier(int min) : tree(NULL), remove_num(0), min(min) {

}

Cashier::~Cashier() {
	deleteTree(tree);
	queue<Tree>().swap(q);
	printf("%d\n", remove_num); //����뿪��Ա����
}

void Cashier::insert(int salary) {
	if (salary >= min) 
		tree = insert(tree, salary);
	//else remove_num++; // "���ĳ��Ա���ĳ�ʼ���ʵ�����͹��ʱ�׼,��ô�����������Ĵ���"
}

void Cashier::increase(int salary_increment) {
	//����tree��ÿ��������ӹ���
	if (tree == NULL) return;
	q.push(tree);
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		t->key += salary_increment;
		if (t->left) q.push(t->left);
		if (t->right) q.push(t->right);
	}
}

void Cashier::decrease(int salary_decrement) {
	//����tree��ÿ�������ٹ��ʣ������ٺ�Ĺ��ʵ���min������vector��¼���������ɾ��
	if (tree == NULL) return;
	vector<int> v;
	q.push(tree);
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		t->key -= salary_decrement;
		if (t->key < min) {
			v.push_back(t->key);
		}
		if (t->left) q.push(t->left);
		if (t->right) q.push(t->right);
	}
	for (int key : v) {
		tree = remove(tree, key); //ɾ�����
	}
	remove_num += v.size(); //�뿪Ա����������
	v.clear();
}

int Cashier::select(int k) {
	//��ѯ��k��
	if (tree == NULL) return -1;
	if (tree->size >= k)
		return select(tree, tree->size - k); //��ѯ��(tree->size - k)��������С�Ľ��
	else return -1;
}

/*-------------------------SBT��-------------------------*/

Cashier::Tree Cashier::leftRotate(Tree tree) {
	Tree k = tree->right;
	tree->right = k->left;
	k->left = tree;
	tree->size = getSize(tree->left) + getSize(tree->right) + 1;
	k->size =tree->size + getSize(k->right) + 1;
	return k;
}

Cashier::Tree Cashier::rightRotate(Tree tree) {
	Tree k = tree->left;
	tree->left = k->right;
	k->right = tree;
	tree->size = getSize(tree->left) + getSize(tree->right) + 1;
	k->size = getSize(k->left)+ tree->size + 1;
	return k;
}

Cashier::Tree Cashier::maintain(Tree tree) {
	tree = maintainLeft(tree);
	return maintainRight(tree);
}

Cashier::Tree Cashier::maintainLeft(Tree tree) {
	if (tree == NULL || tree->left == NULL) return tree;
	if (tree->left->left && tree->left->left->size > getSize(tree->right)) {
		//����������������size������������size
		tree = rightRotate(tree);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	else if (tree->left->right && tree->left->right->size > getSize(tree->right)) {
		//����������������size������������size
		tree->left = leftRotate(tree->left);
		tree = rightRotate(tree);
		tree->left = maintain(tree->left);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	return tree;
}

Cashier::Tree Cashier::maintainRight(Tree tree) {
	if (tree == NULL || tree->right == NULL) return tree;
	if (tree->right->right && tree->right->right->size > getSize(tree->left)) {
		//����������������size������������size
		tree = leftRotate(tree);
		tree->left = maintain(tree->left);
		tree = maintain(tree);
	}
	else if (tree->right->left && tree->right->left->size > getSize(tree->left)) {
		//����������������size������������size
		tree->right = rightRotate(tree->right);
		tree = leftRotate(tree);
		tree->left = maintain(tree->left);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	return tree;
}

Cashier::Tree Cashier::insert(Tree tree, int key) {
	if (tree == NULL) {
		return new TNode(key);
	}
	tree->size++;
	if (key < tree->key) {
		tree->left = insert(tree->left, key);
		tree = maintainLeft(tree); //��������������Ҫ�ж��������ĺ��ӵ�size�Ƿ������������size
	}
	else {
		tree->right = insert(tree->right, key);
		tree = maintainRight(tree); //��������������Ҫ�ж��������ĺ��ӵ�size�Ƿ������������size
	}
	return tree;
}

int Cashier::select(Tree tree, int rank) {
	if (tree == NULL) return 0;
	size_t left_size = getSize(tree->left);
	if (rank == left_size) {
		return tree->key;
	}
	else if (rank < left_size) {
		return select(tree->left, rank);
	}
	else {
		return select(tree->right, rank - left_size - 1);
	}
}

Cashier::Tree Cashier::remove(Tree tree, int key) {
	if (tree == NULL) return NULL;
	tree->size--;
	if (key == tree->key) {
		if (tree->left && tree->right) { //������������ΪNULL
			//�������������Ĵ���tree
			Tree left_max = tree->left;
			while (left_max->right) left_max = left_max->right;
			tree->key = left_max->key;
			tree->left = remove(tree->left, left_max->key);
			tree = maintainRight(tree); //����������ɾ��������Ҫ�ж��������ĺ��ӵ�size�Ƿ������������size
		}
		else {
			Tree tmp = tree;
			tree = tree->left ? tree->left : tree->right;
			delete tmp;
		}
	}
	else if (key < tree->key) {
		tree->left = remove(tree->left, key);
		tree = maintainRight(tree); //����������ɾ��������Ҫ�ж��������ĺ��ӵ�size�Ƿ������������size
	}
	else {
		tree->right = remove(tree->right, key);
		tree = maintainLeft(tree); //����������ɾ��������Ҫ�ж��������ĺ��ӵ�size�Ƿ������������size
	}
	return tree;
}

void Cashier::deleteTree(Tree tree) {
	if (tree == NULL) return;
	//�ݹ�ɾ��
	deleteTree(tree->left);
	deleteTree(tree->right);
	delete tree;
}

int main() {
	int n, min;
	scanf("%d %d", &n, &min);
	Cashier cashier(min);
	char cmd; int k;
	for (int i = 0; i < n * 2; i++) { //ѭ��n*2�β���������������
		scanf("%c", &cmd);
		scanf("%d", &k);
		switch (cmd) {
		case 'I' : cashier.insert(k); break;
		case 'A': cashier.increase(k); break;
		case 'S': cashier.decrease(k); break;
		case 'F': {
			int salary = cashier.select(k);
			printf("%d\n", salary);
			break;
		}
		default: break;
		}
	}
	//����������������뿪��Ա������
	return 0;
}
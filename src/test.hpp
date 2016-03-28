#ifndef TEST_HPP
#define	TEST_HPP
#include "serverResource.hpp"
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>
#include <bitset>
void rotate(std::vector<std::vector<string>>& vec)
{
	for (int layer = 0; layer < 6 / 2; ++layer)
	{
		int first = layer;
		int last = 6 - 1 - layer;
		for (int i = first; i < last; ++i)
		{
			/*int offset = i - first;
			string top = vec[first][i];
			vec[first][i] = vec[last - offset][first];
			vec[last - offset][first] = vec[last][last - offset];
			vec[last][last - offset] = vec[i][last];
			vec[i][last] = top;*/
			string top = vec[first][i];
			vec[first][i] = vec[last - i][first];
			vec[last - i][first] = vec[last][last - i];
			vec[last][last - i] = vec[i][last];
			vec[i][last] = top;
		}
	}
}
void print(std::vector<std::vector<string>> vec)
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}
void test()
{
	std::vector<std::vector<string>> vec(6);
	for (int i = 0; i < 6; ++i)
		vec[i].resize(6);
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
			vec[i][j] = boost::lexical_cast<string>(i)+boost::lexical_cast<string>(j);
	}
	print(vec);
	rotate(vec);
	cout << "==================================" << endl;
	print(vec);

	

}

class tree
{	
public:
	tree(int data) :data(data), left(nullptr), right(nullptr)
	{}
	int data;
	boost::shared_ptr<tree> left;
	boost::shared_ptr<tree> right;
};
bool covers(boost::shared_ptr<tree> root, boost::shared_ptr<tree> p)
{
	if (root == nullptr) return false;
	if (root == p) return true;
	return covers(root->left, p) || covers(root->right, p);
}
boost::shared_ptr<tree> common_ancestor_helper(boost::shared_ptr<tree> root, boost::shared_ptr<tree> p, boost::shared_ptr<tree> q)
{
	if (root == nullptr) return nullptr;
	if (root == p || root == q) return root;
	bool p_in_left = covers(root->left, p);
	bool q_in_left = covers(root->left, q);

	if (p_in_left != q_in_left) return root;
	else
	{
		boost::shared_ptr<tree> child = p_in_left ? root->left : root->right;
		return common_ancestor_helper(child, p, q);
	}
}
boost::shared_ptr<tree> common_ancestor(boost::shared_ptr<tree> root, boost::shared_ptr<tree> p, boost::shared_ptr<tree> q)
{
	if (!covers(root, p) || !covers(root, q))
		return nullptr;
	return common_ancestor_helper(root, p, q);
}
void mid_travel(boost::shared_ptr<tree> root)
{
	if (root == nullptr)
	{
		cout << "root is nullptr" << endl;
	}
	else
	{
		mid_travel(root->left);
		cout << root->data << endl;
		mid_travel(root->right);
	}
}
void test_tree()
{
	//中序遍历为：123654
	boost::shared_ptr<tree> node1 = boost::shared_ptr<tree>(new tree(1));
	boost::shared_ptr<tree> node3 = boost::shared_ptr<tree>(new tree(3));
	boost::shared_ptr<tree> node4 = boost::shared_ptr<tree>(new tree(4));
	
	boost::shared_ptr<tree> node2 = boost::shared_ptr<tree>(new tree(2));
	node2->left = node1;
	node2->right = node3;
	boost::shared_ptr<tree> node6 = boost::shared_ptr<tree>(new tree(6));
	node6->left = node2;
	boost::shared_ptr<tree> node5 = boost::shared_ptr<tree>(new tree(5));
	node6->right = node5;
	node5->right = node4;

	mid_travel(node6);
	boost::shared_ptr<tree> test1=common_ancestor(node6, node1, node3);
	cout << test1->data << endl;
	boost::shared_ptr<tree> test2=common_ancestor(node6, node3, node4);
	cout << test2->data << endl;
	boost::shared_ptr<tree> test3 = common_ancestor(node6, node4, node5);
	cout << test3->data << endl;
	boost::shared_ptr<tree> test4 = common_ancestor(node6, node2, node3);
	cout << test4->data << endl;
}
int length(int x)
{
	int ret = 0;
	while(x > 0)
	{
		ret++;
		x=x >> 1;
		//cout << __LINE__ << ":"<<x << endl;
	}
	return ret;
}
void merge_bit(int n, int m, int j, int i)
{
	int space = j - i + 1;
	int len = length(m);
	/*int min = len <space ? len : space;
	cout << "len:" << len << endl;
	cout << "min:" << min << endl;*/
	int mask = 0;
	for (int i = 0; i < space; ++i)
		mask += (i +1)* 2;
	n &= ~mask;
	cout << "n:" << hex << n << endl;
	int temp = m << (j-len+1);
	cout << "temp:" << hex << temp << endl;
	cout << hex << n + temp << endl;
}
int update_bit(int n, int m, int i, int j)
{
	int all = ~0;
	int left = all << (j + 1);
	int right = ((1 << i) - 1);
	int mask = left | right;
	int clear = n&mask;
	int shift = m << i;
	return clear | shift;
}
void test_merge_bit()
{
	//01101100 010 3 1 结果输出100
	//merge_bit(108, 2, 3, 1);
	merge_bit(0x400, 0x13, 6, 2);
	cout << hex << update_bit(0x400, 0x13, 2, 6) << endl;
}
void test_bit_set()
{
	auto str1 = "0011";
	auto str2 = "0110";
	bitset<10> one(str1);
	bitset<10> two(str2);
	auto three = one&two;
	cout << three << endl;
	three <<= 4;
	cout << three << endl;
}


#endif	/* PAYPAL_HPP */


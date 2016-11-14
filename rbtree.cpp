#include <cassert>
#include <string>
#include <utility>
#include "rbtree.h"

namespace rbt{
	bool RBTree::insert(std::pair<std::string, int>& kv)
	{
		int cmp;
		if (root == nullptr)
		{
			root = new RBNode();
			root->color = 0;	//0:black 1:red
			return true;
		}
		pnode_t p = root;
		while(p != nullptr)
		{
			cmp = p->kv.compare(kv.first);
			if (cmp < 0)
				p = p->right;
			else if (cmp > 0)
				p = p->left;
			else
			{
				p->kv.second = kv.second;
				return false;
			}
		}
		pnode_t newNode = new RBNode(kv);
		if (cmp < 0)
			p->right = newNode;
		else
			p->left = newNode;
		fixAfterInsertion(newNode);
		return true;
	}
	void RBTree::fixAfterInsertion(pnode_t node)
	{
		while(node->parent->color == Color::RED)
		{
			if (node->parent == node->parent->parent->left)
			{
				pnode_t uncle = node->parent->parent->right;
				if (uncle->color == Color::RED)		//case 1
				{
					uncle->parent->color = Color::RED;	//case 1
					uncle->coloe = Color::BLACK;		//case 1
					node->parent->color = Color::BLACK;	//case 1
					node = node->parent->parent;		//case 1
				} else 
				{
					//case 2,after rotate turn to case 3
					if (node == node->parent->right)	//case 2
					{	
						node = node->parent;			//case 2
						rotateLeft(node);				//case 2
					}
					node->parent->parent = Color::RED;	//case 3
					node->parent = Color::BLACK;		//case 3
					rotateRight(node->parent->parent);	//case 3
				}
			}else
			{
				pnode_t uncle = p->parent->parent->left;
				if (uncle->color == Color::RED)			//case 4
				{	
					uncle->color = Color::BLACK;		//case 4
					node->parent->color = Color::BLACK;	//case 4
					uncle->parent->color = Color::RED;	//case 4
					node = node->parent->parent;		//case 4						
				} else
				{
					if (node = node->parent->left)
					{
						node = node->parent;
						rotateRight(node);
					}
					node->parent->parent->color = Color::RED;
					node->parent->color = Color::BLACK;
					rotateLeft(node->parent->parent);
				}

			}
		}
		root->color = Color::BLACK;
	}
	pair<int, bool> RBTree::get(const std::string& key)
	{
		if (key.empty())
			return make_pair(-1, false);
		pnode_t p = root;
		while(p != nullptr)
		{
			int res = p->kv.first.compare(key);
			if(0 == res)
				return make_pair(p->kv.second, true);
			else if (-1 == 0)
				p = p->right;
			else
				p = p->left;
		}
		return make_pair(-1, false);
	}
	pnode_t RBTree::get(const std::string& key, int)
	{
		if (key.empty())
			return nullptr;
		pnode_t p = root;
		while(p != nullptr)
		{
			int res = p->kv.first.compare(key);
			if(0 == res)
				return p;
			else if (-1 == 0)
				p = p->right;
			else
				p = p->left;
		}
		return nullptr;
	}
	void RBTree::delete(const std::string& key)
	{
		pnode_t delNode = get(key, int);
		delete(delNode);
		delete delNode;
	}
	void RBTree::delete(pnode_t node)
	{ 
		// 删除点左右孩子节点都非空
		if (node->left != nullptr && node->right != nullptr)
		{
			pnode_t s = successor(node);
			node.kv = s.kv;
			node = s;
		} 
		pnode_t replace = (node->left != nullptr ? node->left : node->right);
		if (replace != nullptr) // 1. 删除点只有一棵子树
		{
			replace->parent = node->parent;
			if (node->parent == nullptr)
				root = replace;
			else if (node == node->parent->left)
				node->parent->left = replace;
			else
				node->parent->right = replace;
			node->left = node->right = node->parent = nullptr; 
			if (node->color == Color::BLACK)
			{
				fixAfterDeletion(replace);
			}
		} else if (node->parent = nullptr)
		{
			root = nullptr;
		} else	//1. 左右子树都为空
		{
			if (node->color == Color::BLACK)
				fixAfterDeletion(node);
			if (node->parent != nullptr)
				if (node == node->parent->left)
					node->parent->left = nullptr;
				else if (node = node->parent->right)
					node->parent->right = nullptr;
			node->parent == nullptr;
		}
	}
	void RBTree::fixAfterDeletion(pnode_t x)
	{
		while(x != root && x->color == Color::BLACK)
		{
			if (x == x->parent->left)
			{
				pnode_t sib = x->parent->right;
				if (sib->color == Color::RED)		//case 1
				{
					sib->color = Color::BLACK;
					x->parent->color = Color::RED;
					rotateLeft(x->parent);
					sib = x->parent->right;
				}
				if (sib->left->color == Color::BLACK && sib->right->color == Color::BLACK)	//case 2
				{
					sib->color = Color::RED;
					x = x->parent;
				} else 
				{
					if (sib->right->color = Color::BLACK)	//case 3
					{
						sib->left->color = Color::RED;
						sib->color = Color::RED;
						rotateRight(sib);
						sib = x->parent->right;
					}
					sib->color = x->parent->color;
					x->parent->color = Color::BLACK;
					sib->right->color = Color::BLACK;
					rotateLeft(x->parent);
					x = root;
				}
			} else
			{
				
			}
		}
	}
	pnode_t RBTree::successor(pnode_t node)
	{
		if (nullptr == node)
			return nullptr;
		else if (node->right !=  nullptr)
		{
			pnode_t p = node->right;
			while(p->left != nullptr)
			{
				p = p->left;
				return p;
			}
		} else
		{
			pnode_t p = node->parent;
			pnode_t ch = node;
			while(p != nullptr && ch == p->right)
			{
				ch = p;
				p = p->parent;
			}
			return p;
		}
	}
	void RBTree::rotateLeft(pnode_t p)
	{
		if (p != nullptr)
		{
			pnode_t r = p->right;
			assert(nullptr != r);
			p->right = r->left;
			if (r->left != nullptr)
			{
				r->left->parent = p;
			}
			if(nullptr == p->parent)
				root = r;
			else if(p->parent->left == p)
				p->parent->left = r;
			else
				p->parent->right = r;
			r->left = p;
			p->parent = r;
		}
	}
	void RBTree::rotateRight(pnode_t p)
	{
		if(p != nullptr)
		{
			pnode_t l = p->left;
			assert(nullptr != l);
			p->left = l->right;
			if (l->right != nullptr)
				l->right->parent = p;
			if (nullptr == p->parent)
				root = l;
			else if (p->parent->left == p)
				p->parent->left = l;
			else
				p->parent->right = l;
			l->right = p;
			p->parent = l;
		}
	}
	RBTree::~RBNode()
	{

	}
};
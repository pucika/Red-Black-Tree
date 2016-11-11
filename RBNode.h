#include <cassert>
#include <string>
#include <utility>
#include "rbtree.h"

namespace rbg{
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
		
	}
	pair<int, bool> RBTree::get(const std::string& key)
	{
		if (k.empty())
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
	bool RBTree::remove()
	{

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
};
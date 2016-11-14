#pragma once
#include <utility>
#include <string>
namespace rbt{
	enum class Color {BLACK, RED};

	struct RBNode
	{
		RBNode():parent(nullptr), left(nullptr), right(nullptr)
			color(Color::RED)
		{}
		RBNode(std::pair<std::string, int>& kv)kv(kv)
		{}
		RBNode* parent;
		RBNode* left;
		RBNode* right;
		std::pair<std::string, int> kv;
		Color color;
	};
	
	typedef node_t RBNode;
	typedef pnode_t RBNode*;

	class RBTree{
	public:
		RBTree():root(nullptr)
		{}
		bool insert(const std::pair<std::string, int>& kv);
		pnode_t get();
		void delete(const std::string& key);
		~RBTree();
	private:
		pnode_t root;
		int size = 0;
	private:
		void rotateLeft(pnode_t );
		void rotateRight(pnode_t );
		void fixAfterInsertion(pnode_t node);
		void fixAfterDeletion(pnode_t node);
	};
}
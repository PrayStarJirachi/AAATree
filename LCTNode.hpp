#ifndef SJTU_LCTNODE_HPP
#define SJTU_LCTNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxTree;

template<class T, class A, class M>
class LCTree;

template<class T, class A, class M>
class LCTNode : public TNode<T, A, M>{
friend class AuxTree<T, A, M>;
friend class LCTree<T, A, M>;
private:
	AuxTree<T, A, M> subtree;
	LCTNode *child[2], *father;
	T tagTree, tagChain, sumChain, sumTree, data;
	bool haveTagTree, haveTagChain, reverse;
	size_t sizeChain, sizeTree;

	void makeTagChain(const T &value);
	void makeTagTree(const T &value);

public:
	const size_t id;

	LCTNode(const size_t &id);

	void pushTagTree();
	void pushTagChain();
	void update();

};


#include "source/LCTNode.cpp"

template<class T, class A, class M>
LCTNode<T, A, M>::LCTNode(const size_t &id) : id(id) {
}

template<class T, class A, class M>
void LCTNode<T, A, M>::makeTagChain(const T &value) {
	if (!haveTagChain) {
		tagChain = value;
		haveTagChain = true;
	} else {
		tagChain = add(tagChain, value);
	}
	data = add(data, value);
	sumChain = add(sumChain, mult(sizeChain, value));
}

template<class T, class A, class M>
void LCTNode<T, A, M>::makeTagTree(const T &value) {
	if (!haveTagTree) {
		tagTree = value;
		haveTagTree = true;
	} else {
		tagTree = add(tagTree, value);
	}
	sumTree = add(sumTree, mult(sizeTree + sizeChain, value));
	subtree.root.makeTagTree(value);
}

template<class T, class A, class M>
void LCTNode<T, A, M>::pushTagChain() {
	if (reverse) {
		std::swap(child[0], child[1]);
		if (child[0] != nullptr) {
			child[0] -> reverse ^= 1;
		}
		if (child[1] != nullptr) {
			child[1] -> reverse ^= 1;
		}
		reverse = false;
	}
	if (haveTagChain) {
		if (child[0] != nullptr) {
			child[0] -> makeTagChain(tagChain);
		}
		if (child[1] != nullptr) {
			child[1] -> makeTagChain(tagChain);
		}
		haveTagChain = false;
	}
}

template<class T, class A, class M>
void LCTNode<T, A, M>::pushTagTree() {
	if (haveTagTree) {
		subtree.root -> makeTagChain(tagTree);
		if (child[1] != nullptr) {
			child[1] -> makeTagTree(tagTree);
		}
		haveTagTree = false;
	}
}

template<class T, class A, class M>
void LCTNode<T, A, M>::update() {
	sizeChain = 1;
	sizeTree = subtree.root.size;
	sumTree = subtree.root.sum;
	sumChain = data;
	if (child[0] != nullptr) {
		sumChain = add(sumChain, child[0] -> sumChain);
		sumTree = add(sumTree, child[0] -> sumTree);
		sizeChain += child[0] -> sizeChain;
		sizeTree += child[0] -> sizeTree;
	}
	if (child[1] != nullptr) {
		sumChain = add(sumChain, child[1] -> sumChain);
		sumTree = add(sumTree, child[1] -> sumTree);
		sizeChain += child[1] -> sizeChain;
		sizeTree += child[1] -> sizeTree;
	}
}

}

#include "AuxTree.hpp"

#endif

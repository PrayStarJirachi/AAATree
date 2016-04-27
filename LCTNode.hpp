#ifndef SJTU_LCTNODE_HPP
#define SJTU_LCTNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxTree;

template<class T, class A, class M>
class LCTree;

template<class T, class A, class M>
class AuxNode;

template<class T, class A, class M>
class LCTNode : public TNode<T, A, M>{
friend class AuxTree<T, A, M>;
friend class LCTree<T, A, M>;
friend class AuxNode<T, A, M>;
private:
	AuxTree<T, A, M> subtree;
	LCTNode *child[2], *father;
	T tagTree, tagChain, sumChain, sumTree, data;
	bool haveTagTree, haveTagChain, reverse;
	size_t sizeChain, sizeTree;

	void makeTagChain(const T &value);
	void makeTagTree(const T &value);
	void makeSwap();

public:
	const size_t id;

	LCTNode(const size_t &id, const T &value);

	void pushTagTree();
	void pushTagChain();
	void update();

};


#include "source/LCTNode.cpp"

template<class T, class A, class M>
LCTNode<T, A, M>::LCTNode(const size_t &id, const T &value) : id(id), data(value), sizeTree(0), sizeChain(0),
	                                                          tagTree(T()), sumChain(T()), tagChain(T()), sumTree(T())
{
	father = child[0] = child[1] = nullptr;
	haveTagTree = haveTagChain = reverse = false;
}

template<class T, class A, class M>
void LCTNode<T, A, M>::makeTagChain(const T &value) {
	if (!haveTagChain) {
		tagChain = value;
		haveTagChain = true;
	} else {
		tagChain = this -> add(tagChain, value);
	}
	data = this -> add(data, value);
	sumChain = this -> add(sumChain, this -> mult(sizeChain, value));
}

template<class T, class A, class M>
void LCTNode<T, A, M>::makeTagTree(const T &value) {
	if (!haveTagTree) {
		tagTree = value;
		haveTagTree = true;
	} else {
		tagTree = this -> add(tagTree, value);
	}
	data = this -> add(data, value);
	sumChain = this -> add(sumChain, value);
	sumTree = this -> add(sumTree, this -> mult(sizeTree, value));
	subtree.makeDelta(value);
}

template<class T, class A, class M>
void LCTNode<T, A, M>::makeSwap() {
	reverse ^= 1;
	std::swap(child[0], child[1]);
}

template<class T, class A, class M>
void LCTNode<T, A, M>::pushTagChain() {
	if (reverse) {
		if (child[0] != nullptr) {
			child[0] -> makeSwap();
		}
		if (child[1] != nullptr) {
			child[1] -> makeSwap();
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
	if (haveTagTree) {
		//subtree.makeDelta(tagTree);
		if (child[0] != nullptr) {
			child[0] -> makeTagTree(tagTree);
		}
		if (child[1] != nullptr) {
			child[1] -> makeTagTree(tagTree);
		}
		haveTagTree = false;
	}
}

template<class T, class A, class M>
void LCTNode<T, A, M>::pushTagTree() {
	if (reverse) {
		if (child[0] != nullptr) {
			child[0] -> makeSwap();
		}
		if (child[1] != nullptr) {
			child[1] -> makeSwap();
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
	if (haveTagTree) {
		//subtree.makeDelta(tagTree);
		if (child[0] != nullptr) {
			child[0] -> makeTagTree(tagTree);
		}
		if (child[1] != nullptr) {
			child[1] -> makeTagTree(tagTree);
		}
		haveTagTree = false;
	}
}

template<class T, class A, class M>
void LCTNode<T, A, M>::update() {
	sizeChain = 1;
	sizeTree = subtree.getSize();
	sumTree = subtree.getSum();
	sumChain = data;
	if (child[0] != nullptr) {
		sumChain = this -> add(sumChain, child[0] -> sumChain);
		sizeChain += child[0] -> sizeChain;
		sizeTree += child[0] -> sizeTree;
		sumTree = this -> add(sumTree, child[0] -> sumTree);
	}
	if (child[1] != nullptr) {
		sumChain = this -> add(sumChain, child[1] -> sumChain);
		sizeChain += child[1] -> sizeChain;
		sizeTree += child[1] -> sizeTree;
		sumTree = this -> add(sumTree, child[1] -> sumTree);
	}
}

}

#include "AuxTree.hpp"

#endif

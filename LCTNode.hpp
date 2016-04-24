#ifndef SJTU_LCTNODE_HPP
#define SJTU_LCTNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxTree;

template<class T, class A, class M>
class LCTNode : public TNode<T, A, M>{
friend class AuxTree<T, A, M>;
private:
	LCTNode *child[2], *father;
	T tagTree, tagChain;
	bool haveTagTree, haveTagChain, reverse;
	AuxTree<T, A, M> subtree;

public:
	const size_t id;

	LCTNode(const size_t &id);

	void pushTagSubTree();
	void pushTagChain();
	void update();

};

#include "source/LCTNode.cpp"

}

#endif

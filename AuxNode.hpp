#ifndef SJTU_AUXNODE_HPP
#define SJTU_AUXNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxTree;

template<class T, class A, class M>
class LCTNode;

template<class T, class A, class M>
class AuxNode : TNode<T, A, M>{
friend class AuxTree<T, A, M>;
friend class LCTNode<T, A, M>;
private:
	int rnd;
	T tagTree, sum;
	size_t size;
	bool haveTagTree;
	AuxNode *child[2], *father;
	LCTNode<T, A, M> *data;
	void makeTagTree(const T &value);

public:
	void pushTagTree();
	void update();
	AuxNode(LCTNode<T, A, M> *data, int Rnd) : tagTree(), size(0), 
	                                           sum(), data(data), rnd(Rnd)
	{
		father = child[0] = child[1] = nullptr;
		haveTagTree = false;
	}
	int getrand() const {return rnd;}

};

#include "source/AuxNode.cpp"

}

#endif

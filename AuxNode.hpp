#ifndef SJTU_AUXNODE_HPP
#define SJTU_AUXNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxTree;

template<class T, class A, class M>
class AuxNode : TNode<T, A, M>{
friend class AuxTree<T, A, M>;
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
	AuxNode(LCTNode<T, A, M> *data, int Rnd) : TNode<T, A, M>(), tagTree(), data(data), rnd(Rnd) {
		child[0] = child[1] = nullptr;
	}
	int getrand() const {return rnd;}

};

#include "source/AuxNode.cpp"

}

#endif

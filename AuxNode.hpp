#ifndef SJTU_AUXNODE_HPP
#define SJTU_AUXNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxNode : TNode<T, A, M>{
private:
	T tagTree;
	int key, rnd;
	AuxNode *ls, *rs;
public:
	void pushdown();
	void update();
	AuxNode(int Key, int Rnd) : tagTree(), key(Key), rnd(Rnd), ls(NULL), rs(NULL) {}
	int getkey() const {return key;}
	int getrand() const {return key;}
};

#include "source/AuxNode.cpp"

}

#endif

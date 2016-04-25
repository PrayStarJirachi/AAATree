#ifndef SJTU_AUXNODE_HPP
#define SJTU_AUXNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxNode : TNode<T, A, M>{
private:
	T tagTree;
<<<<<<< HEAD
	bool haveTagTree;
	AuxNode *child[2], *father;
	void makeTagTree(const T &value);

=======
	int key, rnd;
	AuxNode *ls, *rs;
>>>>>>> lwher
public:
	void pushTagTree();
	void update();
	AuxNode(int Key, int Rnd) : TNode<T, A, M>(), tagTree(), key(Key), rnd(Rnd), ls(NULL), rs(NULL) {}
	int getkey() const {return key;}
	int getrand() const {return key;}
};

#include "source/AuxNode.cpp"

}

#endif

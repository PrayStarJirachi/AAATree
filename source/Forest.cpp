#ifdef SJTU_FOREST_HPP

#ifndef SJTU_FOREST_CPP
#define SJTU_FOREST_CPP

template<class T, class A, class M>
Forest<T, A, M>::Forest() : size(0) {
}

template<class T, class A, class M>
Forest<T, A, M>::~Forest() {
	// TODO
}

template<class T, class A, class M>
Forest<T, A, M>::Node::Node(LCTNode<T, A, M> *rhs) : p(rhs) {
}

template<class T, class A, class M>
typename Forest<T, A, M>::Node Forest<T, A, M>::createTree(const T &value) {
	LCTNode<T, A, M> *ret = new LCTNode<T, A, M>(++size, value);
	return Forest<T, A, M>::Node(ret);
}

template<class T, class A, class M>
void Forest<T, A, M>::setRoot(const Forest<T, A, M>::Node &u) {
	this -> setRoot(u.p);
}

template<class T, class A, class M>
void Forest<T, A, M>::link(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	LCTree<T, A, M>::link(u.p, v.p);
}

template<class T, class A, class M>
void Forest<T, A, M>::cut(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	this -> cut(u.p, v.p);
}

template<class T, class A, class M>
void Forest<T, A, M>::modify(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v, const T &value) {
	this -> modifyChain(u.p, v.p, value);
}

template<class T, class A, class M>
void Forest<T, A, M>::modify(const Forest<T, A, M>::Node &u, const T &value) {
	this -> modifySubTree(u.p, value);
}

template<class T, class A, class M>
T Forest<T, A, M>::query(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	return this -> queryChain(u.p, v.p);
}

template<class T, class A, class M>
T Forest<T, A, M>::query(const Forest<T, A, M>::Node &u) {
	return this -> queryChain(u.p);
}

#endif

#endif

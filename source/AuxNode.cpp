#ifdef SJTU_AUXNODE_HPP

#ifndef SJTU_AUXNODE_CPP
#define SJTU_AUXNODE_CPP

template<class T, class A, class M>
void AuxNode<T, A, M>::makeTagTree(const T &value) {
	if (!haveTagTree) {
		tagTree = value;
	} else {
		tagTree = add(tagTree, value);
	}
	haveTagTree = true;
	sum = add(data, mult(size, sum));
}

template<class T, class A, class M>
void AuxNode<T, A, M>::tagTreeDown() {
	if (haveTagTree) {
		haveTagTree = false;
		if (child[0] != nullptr) {
			child[0] -> makeDelta(tagTree);
		}
		if (child[1] != nullptr) {
			child[1] -> makeDelta(tagTree);
		}
	}
}

template<class T, class A, class M>
void AuxNode<T, A, M>::update() {
	size = 1;
	sum = data;
	if (child[0] != nullptr) {
		size += child[0] -> size;
		sum = add(sum, child[0] -> sum);
	}
	if (child[1] != nullptr) {
		size += child[1] -> size;
		sum = add(sum, child[1] -> sum);
	}
}

#endif

#endif

#ifdef SJTU_AUXTREE_HPP

#ifndef SJTU_AUXTREE_CPP
#define SJTU_AUXTREE_CPP

// pay attention to srand(timd(NULL)) !!!

template<class T, class A, class M>
void AuxTree<T, A, M> :: LL(AuxNode<T, A, M>* &t){
	AuxNode<T, A, M>* k = t -> rs;
	k -> downpush();
	t -> rs = k -> ls; 
	k -> ls = t;
	t -> update();
	k -> update();
	t = k;
}

template<class T, class A, class M>	
void AuxTree<T, A, M> :: RR(AuxNode<T, A, M>* &t){
	AuxNode<T, A, M>* k = t -> ls;
	k -> downpush();
	t -> ls = k -> rs;
	k -> rs = t;
	t -> update();
	k -> update();
	t = k;
}

template<class T, class A, class M>
AuxNode<T, A, M>* AuxTree<T, A, M> :: Treap_find(const int &key, AuxNode<T, A, M>* t) {
	if(t == NULL) return NULL;
	t -> pushdown();
	if(key < (t -> getkey())) return Treap_find(key, t -> ls); else
	if(key > (t -> getkey())) return Treap_find(key, t -> rs); else
	return t;
}

template<class T, class A, class M>
AuxNode<T, A, M>* AuxTree<T, A, M> :: find(const AuxNode<T, A, M> &rhs) {
	int Key = rhs.getkey();
	return Treap_find(Key, root);
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: Treap_Insert(const AuxNode<T, A, M> &rhs, AuxNode<T, A, M>* &t) {
	if(t == NULL){
		t = new AuxNode<T, A, M>(rhs.getkey(), rand());
		return;
	}
	t -> downpush();
	if(rhs.getkey() < (t -> getkey())){
		Treap_Insert(rhs, t -> ls);
		if((t -> ls -> getrand()) < (t -> getrand())) RR(t);
	}
	else{
		Treap_Insert(rhs, t -> rs);
		if((t -> rs -> getrand()) < (t -> getrand())) LL(t);
	}
	t -> update();
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: insert(const AuxNode<T, A, M> &rhs) {
	if(find(rhs) != NULL) throw "This ID exist!";
	Treap_Insert(rhs, root);
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: Treap_Delete(const AuxNode<T, A, M> &rhs, AuxNode<T, A, M>* &t) {
	t -> downpush();
	if((t -> getkey()) == (rhs.getkey())){
		if(t -> ls == NULL || t -> rs == NULL){
			AuxNode<T, A, M>* k = t;
			if(t -> ls != NULL)
				t = t -> ls;
			else 
				t = t -> rs;
			delete k;
		}
		else{
			if((t -> ls -> getrand()) < t -> rs -> getrand()){
				RR(t); 
				Treap_Delete(rhs, t -> rs);
				update(t);
			}
			else{
				LL(t);
				Treap_Delete(rhs, t -> ls);
				update(t);
			}
		}
		return;
	}
	if((rhs.getkey()) < (t -> getkey())) 
		Treap_Delete(rhs, t -> ls);
	else 
		Treap_Delete(rhs, t -> rs);
	update(t);
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: erase(const AuxNode<T, A, M> &rhs) {
	if(find(rhs) == NULL) throw "This ID doesn't exist!";
	Treap_Delete(rhs, root);
}

#endif

#endif

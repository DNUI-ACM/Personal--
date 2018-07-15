#ifndef _ZJQ_LIST_H_
#define _ZJQ_LIST_H_

namespace lis{

	template<typename T>

	class list{

		private:

			struct Node{

				Node() : pre(nullptr) , next(nullptr) , data(0) {}

				T data;
				Node *pre , *next;
			};

		public:

			size_t length;
			Node *start;
			Node *over;

			using p_node = Node*;
			using size_type = size_t;

			p_node nullnode;

			class iterator{

				public:

					p_node no;

					iterator(p_node p = nullptr) : no(p) {}

					bool operator !=(const iterator& it) const { return no != it.no; }
					bool operator ==(const iterator& it) const { return no == it.no; }

					iterator operator ++() { no = no->next; return no; }
					iterator operator --() { no = no->pre; return no; }

					iterator operator ++(int) { iterator temp = no; no = no->next; return temp; }
					iterator operator --(int) { iterator temp = no; no = no->pre; return temp; }

					iterator operator + (size_type n) {
						p_node tno = no;
						for (size_type i = 0; i < n; ++i){
							tno = tno->next;
						}
						return tno;
					}
					iterator operator - (size_type n) {
						p_node tno = no;
						for (size_type i = 0; i < n; ++i){
							tno = tno->pre;
						}
						return tno;
					}

					iterator operator += (size_type n) {
						for (size_type i = 0; i < n; ++i){
							no = no->next;
						}
						return no;
					}
					iterator operator -= (size_type n) {
						for (size_type i = 0; i < n; ++i){
							no = no->pre;
						}
						return no;
					}

					T& operator *() { return no->data; }

			};

			class reverse_iterator{

				public:

					p_node no;

					reverse_iterator(p_node p = nullptr) : no(p) {}

					bool operator !=(const reverse_iterator& it) const { return no != it.no; }
					bool operator ==(const reverse_iterator& it) const { return no == it.no; }

					reverse_iterator operator ++() { no = no->pre; return no; }
					reverse_iterator operator --() { no = no->next; return no; }

					reverse_iterator operator ++(int) { reverse_iterator temp = no; no = no->pre; return temp; }
					reverse_iterator operator --(int) { reverse_iterator temp = no; no = no->next; return temp; }

					reverse_iterator operator + (size_type n) {
						p_node tno = no;
						for (size_type i = 0; i < n; ++i){
							tno = tno->pre;
						}
						return tno;
					}
					reverse_iterator operator - (size_type n) {
						p_node tno = no;
						for (size_type i = 0; i < n; ++i){
							tno = tno->next;
						}
						return tno;
					}
					
					reverse_iterator operator += (size_type n) {
						for (size_type i = 0; i < n; ++i){
							no = no->pre;
						}
						return no;
					}
					reverse_iterator operator -= (size_type n) {
						for (size_type i = 0; i < n; ++i){
							no = no->next;
						}
						return no;
					}

					T& operator *() { return no->data; }

			};

			class const_iterator{

				public:

					p_node no;

					const_iterator(p_node p = nullptr) : no(p) {}

					bool operator !=(const_iterator& it) const { return no != it.no; }
					bool operator ==(const_iterator& it) const { return no == it.no; }

					const_iterator operator ++() { no = no->next; return no; }
					const_iterator operator --() { no = no->pre; return no; }

					const_iterator operator ++(int) { const_iterator temp = no; no = no->next; return temp; }
					const_iterator operator --(int) { const_iterator temp = no; no = no->pre; return temp; }

					const_iterator operator + (size_type n) {
						p_node tno = no;
						for (size_type i = 0; i < n; ++i){
							tno = tno->next;
						}
						return tno;
					}
					const_iterator operator - (size_type n) {
						p_node tno = no;
						for (size_type i = 0; i < n; ++i){
							tno = tno->pre;
						}
						return tno;
					}

					const_iterator operator += (size_type n) {
						for (size_type i = 0; i < n; ++i){
							no = no->next;
						}
						return no;
					}
					const_iterator operator -= (size_type n) {
						for (size_type i = 0; i < n; ++i){
							no = no->pre;
						}
						return no;
					}

					const T& operator *() const { return no->data; }

			};

			class const_reverse_iterator{

				public:

					p_node no;

					const_reverse_iterator(p_node p = nullptr) : no(p) {}

					bool operator !=(const_reverse_iterator& it) const { return no != it.no; }
					bool operator ==(const_reverse_iterator& it) const { return no == it.no; }

					const_reverse_iterator operator ++() { no = no->pre; return no; }
					const_reverse_iterator operator --() { no = no->next; return no; }

					const_reverse_iterator operator ++(int) { reverse_iterator temp = no; no = no->pre; return temp; }
					const_reverse_iterator operator --(int) { reverse_iterator temp = no; no = no->next; return temp; }

					const_reverse_iterator operator + (size_type n) {
						p_node tno = no;
						for (size_type i = 0; i < n; ++i){
							tno = tno->pre;
						}
						return tno;
					}
					const_reverse_iterator operator - (size_type n) {
						p_node tno = no;
						for (size_type i = 0; i < n; ++i){
							tno = tno->next;
						}
						return tno;
					}
					
					const_reverse_iterator operator += (size_type n) {
						for (size_type i = 0; i < n; ++i){
							no = no->pre;
						}
						return no;
					}
					const_reverse_iterator operator -= (size_type n) {
						for (size_type i = 0; i < n; ++i){
							no = no->next;
						}
						return no;
					}

					const T& operator *() const { return no->data; }

			};

			list() : nullnode(new Node()) , length(0)  , start(nullptr) , over(nullptr) {}
			list(size_type n , const T& val) : list() {
				for (size_type i = 0; i < n; ++i){
					push_back(val);
				}
			}
			list(iterator a , iterator z) : list() {
				for(iterator it = a; it != z; ++it){
					push_back(*it);
				}
			}
			list(list<T>& l) : list() {
				for(iterator it = l.begin(); it != l.end(); ++it){
					push_back(*it);
				}
			}

			~list() { clear(); delete nullnode; }

			iterator begin() const { return start; }
			iterator end() const { return over->next; }
			const_iterator cbegin() const { return start; }
			const_iterator cend() const { return over->next; }
			reverse_iterator rbegin() const { return over; }
			reverse_iterator rend() const { return start->pre; }
			const_reverse_iterator crbegin() const { return over; }
			const_reverse_iterator crend() const { return start->pre; }
			bool empty() { return !length; }
			size_type size() const { return length; }
			T& front() { return start->data; }
			T& back() { return over->data; }
			void assign(size_type n ,const T& val);
			void push_front(const T& val);
			void push_back(const T& val);
			void pop_front();
			void pop_back();
			void insert(iterator it , const T& val);
			void insert(iterator it , size_type n , const T& val);
			iterator erase(iterator it);
			iterator erase(iterator a , iterator z);
			void resize(size_type n);
			void reverse();
			void swap(list<T>& l);
			void sort();
			void clear();

		private:

			p_node merge_sort(p_node a);
			p_node merge(p_node a , p_node b);

	};

	template<typename T>
	inline void list<T>::assign(size_type n ,const T& val){
		for (size_type i = 0; i < n; ++i){
			push_back(val);
		}
	}

	template<typename T>
	inline void list<T>::push_front(const T& val){
		p_node node = new Node();
		node->data = val;
		if (length == 0){
			start = node;
			over = node;
			node->pre = nullnode;
			node->next = nullnode;
			nullnode->pre = node;
			nullnode->next = node;
			++length;
			return;
		}
		start->pre = node;
		node->next = start;
		start = node;
		node->pre = nullnode;
		nullnode->next = node;
		++length;
	}

	template<typename T>
	inline void list<T>::push_back(const T& val){
		p_node node = new Node();
		if (length == 0){
			push_front(val);
			return;
		}
		over->next = node;
		node->pre = over;
		over = node;
		node->data = val;
		node->next = nullnode;
		nullnode->pre = node;
		++length;
	}

	template<typename T>
	inline void list<T>::pop_front(){
		if (length == 1){
			delete start;
			start = nullptr;
			over = nullptr;
			length = 0;
			return;
		}
		p_node t = start;
		start = start->next;
		start->pre = nullnode;
		delete t;
		--length;
	}

	template<typename T>
	inline void list<T>::pop_back(){
		if (length == 1){
			pop_front();
			return;
		}
		p_node t = over;
		over = over->pre;
		over->next = nullnode;
		delete t;
		--length;
	}

	template<typename T>
	inline void list<T>::insert(iterator it , const T& val){
		if (it == begin()){
			push_front(val);
			return;
		}
		else if(it == end()){
			push_back(val);
			return;
		}
		p_node node = new Node();
		node->data = val;
		it.no->pre->next = node;
		node->pre = it.no->pre;
		node->next = it.no;
		it.no->pre = node;
		++length;
	}

	template<typename T>
	inline void list<T>::insert(iterator it , size_type n , const T& val){
		for(size_type i = 0; i < n; ++i){
			insert(it , val);
		}
	}

	template<typename T>
	inline typename list<T>::iterator list<T>::erase(iterator it){
		if(it == end())
			return it;
		else if (it == begin()){
			pop_front();
			return begin();
		}
		else if(it - 1 == end()){
			pop_back();
			return end();
		}
		p_node t = it.no;
		it.no->pre->next = it.no->next;
		it.no->next->pre = it.no->pre;
		delete t;
		--length;
		return t->next;
	}

	template<typename T>
	inline typename list<T>::iterator list<T>::erase(iterator a , iterator z){
		for(iterator it = a; it != z; ++it){
			erase(it);
		}
		return z;
	}

	template<typename T>
	inline void list<T>::resize(size_type n){
		if(n < length){
			for (size_type i = 0; i < length - n; ++i){
				pop_back();
			}
		}
		else if(n > length){
			for (size_type i = 0; i < n - length; ++i){
				push_back(0);
			}
		}
	}

	template<typename T>
	inline void list<T>::reverse(){
		p_node i = start , j = over->next;
		while(i != j){
			p_node temp = i->next;
			i->next = i->pre;
			i->pre = temp;
			i = temp;
		}
		p_node temp = over;
		over = start;
		start = temp;
	}
	template<typename T>
	inline void list<T>::swap(list<T>& l){
		p_node tp = this->start;
		this->start = l.start;
		l.start = tp;
		tp = this->over;
		this->over = l.over;
		l.over = tp;
		size_type tl = this->length;
		this->length = l.length;
		l.length = tl;
	}

	template<typename T>
	void list<T>::sort(){
		nullnode->pre = nullptr;
		nullnode->next = nullptr;
		start->pre = nullptr;
		over->next = nullptr;
		start = merge_sort(start);
		p_node temp = start;
		while(temp->next){
			temp = temp->next;
		}
		over = temp;
		nullnode->next = start;
		nullnode->pre = over;
		start->pre = nullnode;
		over->next = nullnode;
	}

	template<typename T>
	typename list<T>::p_node list<T>::merge_sort(p_node h){
		if (!h || !h->next){
			return h;
		}
		p_node a = h , b = h , p = nullptr;
		if (a && a->next){
			p = a;
			a = a->next;
			b = b->next->next;
		}
		p->next->pre = nullptr;
		p->next = nullptr;
		p_node lh = merge_sort(h);
		p_node rh = merge_sort(a);
		return merge(lh , rh);
	}

	template<typename T>
	typename list<T>::p_node list<T>::merge(p_node a , p_node b){
		p_node sk = nullptr , rk = nullptr;
		if (a->data <= b->data){
			sk = a;
			rk = a;
			a = a->next;
		}
		else{
			sk = b;
			rk = b;
			b = b->next;
		}
		while(a && b){
			if (a->data <= b->data){
				rk->next = a;
				a->pre = rk;
				rk = rk->next;
				a = a->next;
			}
			else{
				rk->next = b;
				b->pre = rk;
				rk = rk->next;
				b = b->next;
			}
		}
		if (a){
			rk->next = a;
			a->pre = rk;
		}
		else{
			rk->next = b;
			b->pre = rk;
		}
		return sk;
	}

	template<typename T>
	inline void list<T>::clear(){
		for (size_type i = 0; i < length; ++i){
			pop_back();
		}
	}

}

#endif

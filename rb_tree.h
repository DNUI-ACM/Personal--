#ifndef _ZJQ_RB_TREE_H_
#define _ZJQ_RE_TREE_H_

#include <iostream>
using namespace std;

namespace rbt{

	template<typename Key , typename Val>
	class map{

		private:

			enum color_type { red , black };

			struct rbnode{

				rbnode() : left(nullptr) , right(nullptr) , parent(nullptr) {}

				color_type color;
				rbnode* left;
				rbnode* right;
				rbnode* parent;
				Val data;
				Key key;
			};

			rbnode* root;
			size_t length;

		public:

			rbnode* nullnode;

			using p_rbnode = rbnode*;
			using size_type = size_t;

			map() : nullnode(new rbnode()) , length(0) {
				root = nullnode;
				nullnode->left = root;
				nullnode->right = root;
				nullnode->parent = root;
				nullnode->color = black;
			}
			~map() { clear(); delete nullnode; }

			// class iterator{

			// 	private:

			// 		p_rbnode no;

			// 	public:

			// 		bool operator !=(const iterator& it) { return no != it.no; }
			// 		bool operator ==(const iterator& it) { return no == it.no; }

			// 		void plus(){
			// 			if (no->right != nullnode){
			// 				no = no->right;
			// 				while(no->left != nullnode){
			// 					no = no->left;
			// 				}
			// 			}
			// 			else{
			// 				p_rbnode y = no->parent;
			// 				while(no == y->right && y->parent != nullnode){
			// 					no = y;
			// 					y = y->parent;
			// 				}
			// 				if (y->parent != nullnode){
			// 					no = y;
			// 				}
			// 			}
			// 		}

			// 		p_rbnode operator ++() { plus(); return no; }

			// 		iterator(p_rbnode p = nullptr) : no(p) {}

			// 		Val& operator *() { return no->data; }
			// };

			Val operator [] (Key k_) { p_rbnode p = find(k_); return p->data; }

			// iterator begin(){
			// 	p_rbnode temp = root;
			// 	while(temp->left != nullnode){
			// 		temp = temp->left;
			// 	}
			// 	return temp;
			// }
			// iterator end(){
			// 	p_rbnode temp = root;
			// 	while(temp->right != nullnode){
			// 		temp = temp->right;
			// 	}
			// 	return temp->right;
			// }
			p_rbnode find(Key k_);
			void insert(const Key& k_ , const Val& v_);
			void insert_fixup(p_rbnode node);
			void erase(Key k_);
			void erase_fixup(p_rbnode node);
			void rotate_left(p_rbnode node);
			void rotate_right(p_rbnode node);
			p_rbnode findorder(p_rbnode node);
			bool empty() {return length == 0; }
			size_type size() { return length; }
			void print();
			void print(p_rbnode node);
			void clear();
	};

	template<typename Key , typename Val>
	inline typename map<Key , Val>::p_rbnode map<Key , Val>::find(Key k_){
		p_rbnode index = root;
		while(index != nullnode){
			if (k_ < index->key){
				index = index->left;
			}
			else if (k_ > index->key){
				index = index->right;
			}
			else{
				break;
			}
		}
		return index;
	}

	template<typename Key , typename Val>
	void map<Key , Val>::insert(const Key& k_ , const Val& v_){
		p_rbnode p = nullnode;
		p_rbnode index = root;
		while(index != nullnode){
			p = index;
			if (k_ < index->key){
				index = index->left;
			}
			else if (k_ > index->key){
				index = index->right;
			}
			else{
				return;
			}
		}
		p_rbnode node = new rbnode();
		node->key = k_;
		node->data = v_;
		node->color = red;
		node->left = nullnode;
		node->right = nullnode;
		if (p == nullnode){
			root = node;
			root->parent = nullnode;
			nullnode->left = root;
			nullnode->right = root;
			nullnode->parent = root;
		}
		else{
			if (k_ < p->key){
				p->left = node;
			}
			else{
				p->right = node;
			}
			node->parent = p;
		}
		insert_fixup(node);
		++length;
	}

	template<typename Key , typename Val>
	void map<Key , Val>::insert_fixup(p_rbnode node){
		while(node->parent->color == red){
			if (node->parent == node->parent->parent->left){
				p_rbnode uncle = node->parent->parent->right;
				if (uncle->color == red){
					node->parent->color = black;
					uncle->color = black;
					node->parent->parent->color = red;
					node = node->parent->parent;
				}
				else{
					if (node == node->parent->right){
						node = node->parent;
						rotate_left(node);
					}
					node->parent->color = black;
					node->parent->parent->color = red;
					rotate_right(node->parent->parent);
				}
			}
			else{
				p_rbnode uncle = node->parent->parent->left;
				if (uncle->color == red){
					node->parent->color = black;
					uncle->color = black;
					node->parent->parent->color = red;
					node = node->parent->parent;
				}
				else{
					if (node == node->parent->left){
						node = node->parent;
						rotate_right(node);
					}
					node->parent->color = black;
					node->parent->parent->color = red;
					rotate_left(node->parent->parent);
				}
			}
		}
		root->color = black;
	}

	template<typename Key , typename Val>
	void map<Key , Val>::erase(Key k_){
		p_rbnode node = find(k_);
		if (node == nullnode){
			return;
		}
		if (node->left != nullnode && node->right != nullnode){
			p_rbnode order = findorder(node);
			node->data = order->data;
			node->key = order->key;
			node = order;
		}
		p_rbnode node_child;
		if (node->left != nullnode){
			node_child = node->left;
		}
		else if (node->right != nullnode){
			node_child = node->right;
		}
		else{
			node_child = nullnode;
		}
		node_child->parent = node->parent;
		if (node->parent == nullnode){
			root = node_child;
			nullnode->left = root;
			nullnode->right = root;
			nullnode->parent = root;
		}
		else if (node == node->parent->left){
			node->parent->left = node_child;
		}
		else{
			node->parent->right = node_child;
		}
		if (node->color == black && length > 1){
			erase_fixup(node_child);
		}
		delete node;
		--length;
	}

	template<typename Key , typename Val>
	void map<Key , Val>::erase_fixup(p_rbnode node){
		while(node != root && node->color == black){
			if (node == node->parent->left){
				p_rbnode bro = node->parent->right;
				if (bro->color == red){
					color_type temp = bro->color;
					bro->color = node->parent->color;
					node->parent->color = temp;
					rotate_left(node->parent);
				}
				else{
					if (bro->left->color == black && bro->right->color == black){
						bro->color = red;
						node = node->parent;
					}
					else if (bro->left->color == red){
						bro->color = red;
						bro->left->color = black;
						rotate_right(bro);
					}
					bro->color = node->parent->color;
					node->parent->color = black;
					bro->right->color = black;
					rotate_left(node->parent);
				}
			}
			else{
				p_rbnode bro = node->parent->left;
				if (bro->color == red){
					color_type temp = bro->color;
					bro->color = node->parent->color;
					node->parent->color = temp;
					rotate_right(node->parent);	
				}
				else{
					if (bro->left->color == black && bro->right->color == black){
						bro->color = red;
						node = node->parent;
					}
					else if (bro->right->color == red){
						bro->color = red;
						bro->right->color = black;
						rotate_left(bro);
					}
					bro->color = node->parent->color;
					node->parent->color = black;
					bro->left->color = black;
					rotate_right(node->parent);
				}
			}
		}
		root->color = black;
	}
	
	template<typename Key , typename Val>
	inline void map<Key , Val>::rotate_left(p_rbnode node){
		if (node == nullnode || node->right == nullnode){
			return;
		}
		p_rbnode r = node->right;
		r->parent = node->parent;
		node->right = r->left;
		if (r->left != nullnode){
			r->left->parent = node;
		}
		if (node->parent == nullnode){
			root = r;
			nullnode->left = root;
			nullnode->right = root;
		}
		else{
			if (node == node->parent->left){
				node->parent->left = r;
			}
			else{
				node->parent->right = r;
			}
		}
		node->parent = r;
		r->left = node;
	}

	template<typename Key , typename Val>
	inline void map<Key , Val>::rotate_right(p_rbnode node){
		if (node == nullnode || node->left == nullnode){
			return;
		}
		p_rbnode l = node->left;
		l->parent = node->parent;
		node->left = l->right;
		if (l->right != nullnode){
			l->right->parent = node;
		}
		if (node->parent == nullnode){
			root = l;
			nullnode->left = root;
			nullnode->right = root;
		}
		else{
			if (node == node->parent->right){
				node->parent->right = l;
			}
			else{
				node->parent->left = l;
			}
		}
		node->parent = l;
		l->right = node;
	}
	template<typename Key , typename Val>
	inline typename map<Key , Val>::p_rbnode map<Key , Val>::findorder(p_rbnode node){
		if (node == nullnode){
			return nullnode;
		}
		p_rbnode result = node->right;
		while(result->left != nullnode){
			result = result->left;
		}
		return result;
	}


	template<typename Key , typename Val>
	inline void map<Key , Val>::clear(){
		while(root != nullnode){
			erase(root->key);
		}
	}

	template<typename Key , typename Val>
	inline void map<Key , Val>::print(){
		print(root);
	}

	template<typename Key , typename Val>
	inline void map<Key , Val>::print(p_rbnode node){
		if (node == nullnode){
			return;
		}
		print(node->left);
		cout << node->data << endl;
		print(node->right);
	}	
}

#endif
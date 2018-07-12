#ifndef _ZJQ_VECTOR_H_
#define _ZJQ_VECTOR_H_

namespace vec{

    const int LENGTH = 5;

    template <typename T>
    class vector{

        public:

            using iterator = T*;
            using const_iterator = const iterator;
            using size_type = size_t;

        private:

            iterator start;
            iterator finish;
            size_type end_of_storage;
            T *my_data;

        public:

            class reverse_iterator{

                private:

                    iterator ptr;

                public:

                    reverse_iterator(iterator p = nullptr) : ptr(p) {}

                    bool operator != (const reverse_iterator& it) { return ptr != it.ptr; }
                    bool operator == (const reverse_iterator& it) { return ptr == it.ptr; }
                    T& operator *() { return *ptr; }
                    
                    reverse_iterator operator ++() { return --ptr; }
                    reverse_iterator operator --() { return ++ptr; }

                    reverse_iterator operator ++(int) { reverse_iterator temp = ptr; --ptr; return temp; }
                    reverse_iterator operator --(int) { reverse_iterator temp = ptr; ++ptr; return temp; }

                    reverse_iterator operator + (size_type n) { return ptr - n; }
                    reverse_iterator operator - (size_type n) { return ptr + n; }

            };

            using  const_reverse_iterator = const reverse_iterator;

            vector() : end_of_storage(LENGTH) , my_data(new T[end_of_storage]) {
                start = my_data;
                finish = start;
            }
            vector(size_type n) : end_of_storage(n) , my_data(new T[end_of_storage]) {
                start = my_data;
                finish = start;
            }
            vector(size_type n , const T& val) : end_of_storage(n) , my_data(new T[end_of_storage]) {
                start = my_data;
                finish = start;
                assign(n , val);
            }
            vector(vector<T>& v) : end_of_storage(v.end_of_storage) , my_data(new T[end_of_storage]) {
                start = my_data;
                finish = start;
                space(v.my_data , v.size());
            }
            vector(iterator a , iterator z) : end_of_storage(z - a) , my_data(new T[end_of_storage]) {
                start = my_data;
                finish = start;
                space(a , z - a);
            }
            ~vector() { delete[] my_data; }

            T operator [] (size_type n) { return *(begin() + n); }

            iterator begin() const { return start; }
            iterator end() const { return finish; }
            iterator rbegin() const { return finish - 1; }
            iterator rend() const { return start - 1; }
            const_reverse_iterator crbegin() const { return finish - 1; }
            const_reverse_iterator crend() const { return start - 1; }
            const_iterator cbegin() const { return start; }
            const_iterator cend() const { return finish; }
            size_type size() { return size_type(end() - begin()); }
            size_type capacity() { return end_of_storage; }
            bool empty() { return begin() == end(); }
            T& front() { return *begin(); }
            T& back() { return *(end() - 1); }
            void assign(size_type n , const T& val);
            void reserve(size_type n);
            void resize(size_type n);
            void push_back(const T& val);
            void pop_back();
            void insert(iterator it , const T& val);
            void erase(iterator it);
            void clear();

        private:
            
            void space(T* arr , size_type n);

    };

    template<typename T>
    inline void vector<T>::space(T *arr , size_type n){
        for (size_type i = 0; i < n; ++i){
            my_data[i] = arr[i];
        }
        finish += n;
    }

    template <typename T>
    inline void vector<T>::assign(size_type n , const T& val){
        if(end_of_storage < n){
            while(end_of_storage < n){
                end_of_storage *= 2;
            }
            delete[] my_data;
            my_data = new T[end_of_storage];
        }
        for (size_type i = 0; i < n; ++i){
            my_data[i] = val;
        }
        finish += n;
    }

    template <typename T>
    inline void vector<T>::reserve(size_type n){
        if (n < end_of_storage){
            return;
        }
        T* temp = my_data;
        size_type s = size();
        my_data = new T[n];
        for (size_type i = 0; i < s; ++i){
            my_data[i] = temp[i];
        }
        delete[] temp;
        start = &my_data[0];
        finish  = start + s;
    }

    template <typename T>
    inline void vector<T>::resize(size_type n){
        if (size() > n){
            finish = start + n;
            return;
        }
        if (end_of_storage < n){
            reserve(n * 2 + 1);
        }
        size_type s = size();
        for (int i = 0; i < n - s; ++i){
            *(finish++) = 0;
        }
    }

    template <typename T>
    inline void vector<T>::push_back(const T& val){
        size_type s = size();
        if (s == end_of_storage){
            reserve(end_of_storage * 2 + 1);
        }
        my_data[s++] = val;
        ++finish;
    }

    template<typename T>
    inline void vector<T>::pop_back(){
        --finish;
    }

    template<typename T>
    inline void vector<T>::insert(iterator it , const T& val){
        size_type s = size();
        if (s == end_of_storage){
            reserve(end_of_storage * 2 + 1);
        }
        for (int i = 0; i < it - begin(); ++i){
            *(finish) = *(--finish);
        }
        *(finish) = val;
        finish += it - begin() + 1;
    }

    template<typename T>
    inline void vector<T>::erase(iterator it){
        --it;
        while(it != finish){
            *it = *(it + 1);
            ++it;
        }
        --finish;
    }
    
    template<typename T>
    inline void vector<T>::clear(){
        finish = start;
    }
}

#endif
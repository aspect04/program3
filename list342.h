#ifndef LIST342_H
#define LIST342_H

#include <string>
#include <iostream>
#include <fstream>

template<typename T>
class List342 {

    public:
        List342();
        List342(const List342<T>& other);
        ~List342();

        bool BuildList(std::string file_name);
        bool Insert(T* obj);
        bool Remove(T target, T& result);
        bool Peek(T target, T& result) const;
        int Size() const;
        void DeleteList();
        bool Merge(List342& list1);

        List342<T> operator+(const List342<T>& other) const;
        List342<T>& operator+=(const List342<T>& other);
        friend std::ostream& operator<<(std::ostream& os, const List342<T>& list);
        bool operator==(const List342<T>& other) const;
        bool operator!=(const List342<T>& other) const;
        List342<T>& operator=(const List342<T>& other);

    private:
        Node<T> *head_ = nullptr;
        Node<T> *tail_ = nullptr;


        struct Node {
            T *value;
            Node *next;
        };


};



#endif //LIST342_H

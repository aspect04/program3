#include "List342.h"

template<type T>

List342::List342() {
    size = 0;
}
List342::List342(const List342<T>& other);
~List342::List342();

bool List342::BuildList(std::string file_name);
bool List342::Insert(T* obj) {
    Node* n = new Node<T>(obj);
    tail_ = n;
    n->next = nullptr;
}
bool List342::Remove(T target, T& result);
bool List342::Peek(T target, T& result) const;
int List342::Size() const;
void List342::DeleteList();
bool List342::Merge(List342& list1);

List342<T> List342::operator+(const List342<T>& other) const;
List342<T>& List342::operator+=(const List342<T>& other);
friend std::ostream& operator<<(std::ostream& os, const List342<T>& list);
bool List342::operator==(const List342<T>& other) const;
bool List342::operator!=(const List342<T>& other) const;
List342<T>& List342::operator=(const List342<T>& other);
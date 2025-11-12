// css 342 - data structures
// list342: a templated sorted linked list implementation
// maintains items in sorted order with no duplicates allowed

#ifndef LIST342_H
#define LIST342_H

#include <fstream>
#include <iostream>
#include <string>

// node structure for the linked list
// contains a pointer to data and pointer to next node
template<typename T>
struct Node {
  T* value;
  Node* next = nullptr;
};

// list342 class: a sorted, singly-linked list that maintains unique elements
// the list is always kept in sorted order (ascending)
// duplicate elements are not allowed
// template parameter t must support operators: <, >, ==, !=, <<, >>
template<typename T>
class List342 {
 public:
  // constructors and destructor

  // default constructor - creates an empty list
  List342();

  // copy constructor - creates a deep copy of another list
  List342(const List342<T>& other);

  // destructor - deallocates all nodes and data
  ~List342();

  // core list operations

  // builds a list from a file
  // opens the file, reads objects, and inserts them in sorted order
  // duplicates in the file are automatically rejected
  // returns true if file was opened successfully, false otherwise
  bool BuildList(std::string file_name);

  // inserts an object into the list in sorted position
  // creates a copy of the object to store in the list
  // returns true if inserted successfully, false if duplicate
  bool Insert(T* obj);

  // removes target item from list and returns it via result parameter
  // returns true if item was found and removed, false otherwise
  bool Remove(T target, T& result);

  // finds target item without removing it, returns via result parameter
  // returns true if item was found, false otherwise
  bool Peek(T target, T& result) const;

  // returns the number of items in the list
  int Size() const;

  // removes all items from list and deallocates all memory
  // this includes both the nodes and the data they point to
  void DeleteList();

  // merges another list into this one without allocating new memory
  // reuses nodes from list1, which becomes empty after the merge
  // duplicates are not inserted
  // returns true on success, false if merging with self
  bool Merge(List342& list1);

  // operator overloads

  // addition operator - creates new list with elements from both lists
  List342<T> operator+(const List342<T>& other) const;

  // addition assignment - adds elements from other list to this list
  List342<T>& operator+=(const List342<T>& other);

  // equality comparison - checks if two lists have identical elements
  bool operator==(const List342<T>& other) const;

  // inequality comparison
  bool operator!=(const List342<T>& other) const;

  // assignment operator - creates deep copy of another list
  List342<T>& operator=(const List342<T>& other);

  // stream insertion operator - outputs all list elements
  // no extra spaces, tabs, or newlines are added
  // defined inline to avoid template linkage issues
  friend std::ostream& operator<<(std::ostream& os, const List342<T>& list) {
    Node<T>* current = list.head_;
    while (current != nullptr) {
      os << *(current->value);
      current = current->next;
    }
    return os;
  }

 private:
  Node<T>* head_;  // pointer to first node in list
  Node<T>* tail_;  // pointer to last node in list
  int size_;       // number of elements in list
};

//------------------------------------------------------------------------------
// implementation
//------------------------------------------------------------------------------

// default constructor
template<typename T>
List342<T>::List342() {
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

// copy constructor
template<typename T>
List342<T>::List342(const List342<T>& other) {
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;

  // copy all elements from other list using insert
  Node<T>* current = other.head_;
  while (current != nullptr) {
    Insert(current->value);
    current = current->next;
  }
}

// destructor
template<typename T>
List342<T>::~List342() {
  DeleteList();
}

// insert an object in sorted order
template<typename T>
bool List342<T>::Insert(T* obj) {
  if (obj == nullptr) {
    return false;
  }

  // create a copy of the object to store
  T* new_data = new T(*obj);

  // create new node
  Node<T>* new_node = new Node<T>();
  new_node->value = new_data;
  new_node->next = nullptr;

  // check if list empty
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
    size_++;
    return true;
  }

  // check if insert at beginning
  if (*new_data < *(head_->value)) {
    new_node->next = head_;
    head_ = new_node;
    size_++;
    return true;
  }

  // check if duplicates at head
  if (*new_data == *(head_->value)) {
    delete new_data;
    delete new_node;
    return false;
  }

  // find where to insert obj in list
  Node<T>* current = head_;
  while (current->next != nullptr && *(current->next->value) < *new_data) {
    current = current->next;
  }

  // check for duplicates
  if (current->next != nullptr && *(current->next->value) == *new_data) {
    delete new_data;
    delete new_node;
    return false;
  }

  // insert after current
  new_node->next = current->next;
  current->next = new_node;

  // update tail if inserting at end
  if (new_node->next == nullptr) {
    tail_ = new_node;
  }

  size_++;
  return true;
}

// remove target item from list and return item removed to result parameter
template<typename T>
bool List342<T>::Remove(T target, T& result) {
  if (head_ == nullptr) {
    return false;
  }

  // check if target is at head
  if (*(head_->value) == target) {
    result = *(head_->value);
    Node<T>* temp = head_;
    head_ = head_->next;

    // update tail if list becomes empty
    if (head_ == nullptr) {
      tail_ = nullptr;
    }

    delete temp->value;
    delete temp;
    size_--;
    return true;
  }

  // search rest of list
  Node<T>* current = head_;
  while (current->next != nullptr) {
    if (*(current->next->value) == target) {
      result = *(current->next->value);
      Node<T>* temp = current->next;
      current->next = temp->next;

      // update tail if removing last node
      if (temp == tail_) {
        tail_ = current;
      }

      delete temp->value;
      delete temp;
      size_--;
      return true;
    }
    current = current->next;
  }

  return false;
}

// peek at target item without removing
template<typename T>
bool List342<T>::Peek(T target, T& result) const {
  Node<T>* current = head_;
  while (current != nullptr) {
    if (*(current->value) == target) {
      result = *(current->value);
      return true;
    }
    current = current->next;
  }
  return false;
}

// return the number of items in list
template<typename T>
int List342<T>::Size() const {
  return size_;
}

// delete all items and deallocate memory
template<typename T>
void List342<T>::DeleteList() {
  while (head_ != nullptr) {
    Node<T>* temp = head_;
    head_ = head_->next;
    delete temp->value;  // deallocate data
    delete temp;         // deallocate node
  }
  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

// merge another list into this one
template<typename T>
bool List342<T>::Merge(List342& list1) {
  // cannot merge with self
  if (this == &list1) {
    return false;
  }

  // if list1 is empty, nothing to merge
  if (list1.head_ == nullptr) {
    return true;
  }

  // process each node from list1
  while (list1.head_ != nullptr) {
    Node<T>* node_to_insert = list1.head_;
    list1.head_ = list1.head_->next;
    node_to_insert->next = nullptr;

    // check for duplicate before inserting
    bool is_duplicate = false;
    Node<T>* current = head_;
    while (current != nullptr) {
      if (*(current->value) == *(node_to_insert->value)) {
        is_duplicate = true;
        break;
      }
      current = current->next;
    }

    if (is_duplicate) {
      // delete duplicate node and its data
      delete node_to_insert->value;
      delete node_to_insert;
      list1.size_--;
      continue;
    }

    // insert node in sorted position
    if (head_ == nullptr || *(node_to_insert->value) < *(head_->value)) {
      // insert at beginning
      node_to_insert->next = head_;
      head_ = node_to_insert;
      if (tail_ == nullptr) {
        tail_ = node_to_insert;
      }
    } else {
      // find insertion point
      current = head_;
      while (current->next != nullptr &&
             *(current->next->value) < *(node_to_insert->value)) {
        current = current->next;
      }

      node_to_insert->next = current->next;
      current->next = node_to_insert;

      if (node_to_insert->next == nullptr) {
        tail_ = node_to_insert;
      }
    }

    size_++;
    list1.size_--;
  }

  // clear list1
  list1.head_ = nullptr;
  list1.tail_ = nullptr;
  list1.size_ = 0;

  return true;
}

// build list from file
template<typename T>
bool List342<T>::BuildList(std::string file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    return false;
  }

  T* temp = new T();
  while (file >> *temp) {
    Insert(temp);
    temp = new T();
  }
  delete temp;  // delete the last unused object

  file.close();
  return true;
}

// addition operator - create new list with combined elements
template<typename T>
List342<T> List342<T>::operator+(const List342<T>& other) const {
  List342<T> result(*this);      // copy current list
  List342<T> other_copy(other);  // copy other list
  result.Merge(other_copy);
  return result;
}

// addition assignment operator
template<typename T>
List342<T>& List342<T>::operator+=(const List342<T>& other) {
  if (this == &other) {
    return *this;
  }

  List342<T> other_copy(other);
  Merge(other_copy);
  return *this;
}

// equality operator
template<typename T>
bool List342<T>::operator==(const List342<T>& other) const {
  if (size_ != other.size_) {
    return false;
  }

  Node<T>* current1 = head_;
  Node<T>* current2 = other.head_;

  while (current1 != nullptr && current2 != nullptr) {
    if (*(current1->value) != *(current2->value)) {
      return false;
    }
    current1 = current1->next;
    current2 = current2->next;
  }

  return true;
}

// inequality operator
template<typename T>
bool List342<T>::operator!=(const List342<T>& other) const {
  return !(*this == other);
}

// assignment operator - deep copy
template<typename T>
List342<T>& List342<T>::operator=(const List342<T>& other) {
  if (this == &other) {
    return *this;
  }

  // delete current list
  DeleteList();

  // copy from other list
  Node<T>* current = other.head_;
  while (current != nullptr) {
    Insert(current->value);
    current = current->next;
  }

  return *this;
}

#endif  // LIST342_H

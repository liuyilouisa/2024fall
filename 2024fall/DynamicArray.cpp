//
// Created by 13584 on 2024/9/23.
//
#include <iostream>
#include <string>
namespace my_dynamic_array {
class array {
 private:
  int* value;
  int size;
  int capacity;
 public:
  array(): size(0), capacity(1){
    value = new int[capacity];
  };
  ~array(){
    delete[]value;
  }
  void resize(){
    if (size >= capacity){
      int newCapacity = 2*capacity;
      int* newValue = new int[newCapacity];
      for (int i = 0; i < size; ++i) {
        newValue[i] = value[i];
      }
      delete[]value;
      value = newValue;
      capacity = newCapacity;
    }
    if (size < capacity/2){
      int newCapacity = capacity/2;
      int* newValue = new int[newCapacity];
      for (int i = 0; i < size; ++i) {
        newValue[i] = value[i];
      }
      delete[]value;
      value = newValue;
      capacity = newCapacity;
    }
  }
  void append(int x){
    resize();
    if (capacity>size){
      value[size] = x;
      size++;
    }
  };
  void set(int i, int x){
    if(0<=i && i<capacity){ value[i] = x; }
  };
  void erase(int i){
    if(0<=i && i<size){
      int* newValue = new int[capacity];
      for (int j = 0; j < i; ++j) {
        newValue[j] = value[j];
      }
      for (int j = i+1; j < size; ++j) {
        newValue[j-1] = value[j];
      }
      delete[]value;
      value = newValue;
      size--;
      resize();
    }
  };
  int get(int x){return value[x];}
  int _size(){return size;}
  int _capacity(){return capacity;}
  void print(){
    if (size==0){ return;}
    for (int i = 0; i < size; ++i) {
      std::cout<<value[i]<<" ";
    }
    std::cout<<std::endl;
  }
};
}

int main() {
  my_dynamic_array::array arr;
  std::string command;
  while (std::cin >> command) {
    if (command == "append") {
      int value;
      std::cin >> value;
      arr.append(value);
    } else if (command == "print") {
      arr.print();
    } else if (command == "erase") {
      size_t index;
      std::cin >> index;
      arr.erase(index);
    } else if (command == "get") {
      size_t index;
      std::cin >> index;
      std::cout << arr.get(index) << std::endl;
    } else if (command == "set") {
      int index;
      int x;
      std::cin >> index >> x;
      arr.set(index, x);
    }else if (command == "size") {
      std::cout << arr._size() << std::endl;
    } else if (command == "capacity") {
      std::cout << arr._capacity() << std::endl;
    } else {
      std::cout << "Unknown command" << std::endl;
    }
  }
  return 0;
}
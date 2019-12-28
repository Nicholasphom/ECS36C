#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
 }

void PriorityQueue::insert(KeyValuePair kv) {
	// TODO: complete this function
  if(nodes_.size() - 1 <= size_) {
  nodes_.push_back(kv);
} else {
  nodes_.at(size_ + 1) = kv; // will add size if there is not enough space
}

  ++size_;
  heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
	// TODO: complete this function
  KeyValuePair  getMin = nodes_[ROOT];
  return getMin;
}

KeyValuePair PriorityQueue::removeMin() {
	// TODO: complete this function
  KeyValuePair Minimum = nodes_[ROOT];
  removeNode(ROOT);
  return Minimum;
}

bool PriorityQueue::isEmpty() const {
	// TODO: complete this function
  if(nodes_.empty() == true) {
    return true;
  } else {
    return false;
  }
}

size_t PriorityQueue::size() const {
	// TODO: complete this function
  return size_;
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {
	// TODO: complete this function
  // when children are smaller than parent
  while(i >= 1 && nodes_[i] <=  nodes_[i/2] ) {
    std::swap(nodes_[i],nodes_[i/2]);
    i = i/2;
  }

}

void PriorityQueue::heapifyDown(size_t i) {
	// TODO: complete this function
 while(2*i < size()) {
  int minindex;
  if (2*i+1 < size() && nodes_[2*i+1] < nodes_[2*i]) {
    minindex = 2* i +1;
  } else {
    minindex = 2* i;
  }
  if(nodes_[i] < nodes_[2 * i]) {
    break;
  } else {
    std::swap(nodes_[i], nodes_[minindex]);
  }
  i = minindex;
 }

}

void PriorityQueue::removeNode(size_t i) {
	// TODO: complete this function
  if(i == size()) { //last node of heap
    nodes_.pop_back(); 
  } else {
    std::swap(nodes_[i],nodes_[size()]);
    nodes_.pop_back();
    heapifyDown(i);
  }
  --size_;

}

Key PriorityQueue::getKey(size_t i) {
	// TODO: complete this function
  KeyValuePair k = nodes_[i];
  return k.first;
}

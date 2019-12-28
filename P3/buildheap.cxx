#include<iostream>
#include "json.hpp"
#include "priorityqueue.h"
#include<fstream>
void buildheap(std::string filename);
int main(int argc, char** argv) {
	std::string s1 = argv[1];
	std::cout << "Hello\n";
	buildheap(s1);


}
void buildheap(std::string filename) {
	PriorityQueue K(0);
	std::ifstream heapfile;
	nlohmann::json heap;
	heapfile.open(filename.c_str());
	if(heapfile.fail()) {

	}
	if (heapfile.is_open()) {
		heapfile >> heap;
	}
	
	for(auto keyitr = heap.begin(); keyitr.key() != "metadata"; keyitr++) {
		
		for(auto dataitr = heap[keyitr.key()].begin(); dataitr != heap[keyitr.key()].end();dataitr++) {
			

		}
		if (heap[keyitr.key()]["operation"] == "insert") {
				//std::cout << "Insert detected\n";
				K.insert(static_cast<Key>(heap[keyitr.key()]["key"]));
				
				
				//std::cout << "Key:" << key << std::endl;
			}
		if (heap[keyitr.key()]["operation"] == "removeMin") {
				K.removeMin();
			}

	}
	heap = K.JSON();
	std::cout << heap.dump(2);
	
}


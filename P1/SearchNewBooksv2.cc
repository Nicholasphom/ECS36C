#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <sstream>
#include<cstdlib>
#include<chrono> //NOLINT (build/c++11)
#include<algorithm>
// class for book to store isbn and condition
class book {	 public:
    int isbn;
    std::string condition;
void setisbn(int n) {
    isbn = n;
}
void setcondition(std::string str1) {
    condition = str1;
}
int getisbn() {
    return isbn;
}
std::string getcond() {
    return condition;
}
void print() {
	std::cout << "ISBN:"<< isbn << " Type: "<< condition << std::endl;
}
};
std::ostream &operator<<(std::ostream &output, std::vector<book> v);
bool readfile(std::string str, std::vector<book> &v);
bool compare(book i, book j);
bool linearsearch(std::vector<book> v, int target);
bool binarysearch(std::vector<book> v, int target);
void writeresult(std::string filename, double time, int c);
int main(int argc, char* argv[]) {
// strings to pass file name arguments to readfile
    std::string s1, s2, s3;
    std::vector<book>Newbook;
    std::vector<book>Requests;
    int choice = 0;
    s1 = argv[1];
    s2 = argv[2];
    s3 = argv[3];
    readfile(s1, Newbook);
    readfile(s2, Requests);
    std::cout << Newbook << std::endl;
    std::cout << "Enter 1. binary search 2. linear search " << std::endl;
    std::cin >> choice;
    while ((choice != 1 && choice != 2) || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        std::cerr << "Try again " << std::endl;
        std::cin >> choice;
    }
    auto start = std::chrono::high_resolution_clock::now();
    switch (choice) {
case 1:
    std::sort(Newbook.begin(), Newbook.end()-1, compare);
    std::cout << Newbook << std::endl;
for (int i = 0; i< Requests.size() ; i++) {
        if (binarysearch(Newbook, Requests[i].getisbn()) == true) {
            std::cout << "Book ISBN: " << Requests[i].getisbn();
            std::cout << " found" << std::endl;
        } else {
            std::cout << "Book with ISBN: " << Requests[i].getisbn();
            std::cout << " Not found" << std::endl;
        }
    }
        break;
case 2:
    for (int j = 0; j< Requests.size(); j++) {
            if (linearsearch(Newbook, Requests[j].getisbn()) == true) {
                std::cout << "ISBN : " << Requests[j].getisbn();
                std::cout << " found "<< std::endl;
            } else {
                std::cout << "ISBN: " << Requests[j].getisbn();
                std::cout << " not found" << std::endl;
            }
    }
    break;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration<double, std::micro>(finish-start).count();
    std::cout << "total cpu time: " << elapsed_us;
    std::cout << " microseconds " << " writing to " << argv[3] << std::endl;
    writeresult(s3, elapsed_us, choice);
    return 0;
}
bool readfile(std::string str, std::vector<book> &v) {
    std::ifstream ifs;
    ifs.open(str.c_str());
    std::string inc;   // incoming data from file
    int ibn;
    if (ifs.fail()) {
        std::cout << "Error in opening: "<< str << std::endl;
        return false;
    }
    while (!ifs.eof()) {
        book *bp;
        getline(ifs, inc, ',');
        bp = new book;
        ibn = atoi(inc.c_str());
        bp->setisbn(ibn);
        getline(ifs, inc);
        bp->setcondition(inc);
        v.push_back(*bp);
    }
    ifs.close();
}
bool compare(book i, book j) {
    if (i.getisbn() < j.getisbn()) {
        return true;
    }
}
bool binarysearch(std::vector<book> v, int target) {
    int hi, lo, mid;
    hi = v.size()-1;
    std::cout << "size of array: " << v.size() << std::endl;
    lo = 0;
    while (lo <= hi) {
        mid = (hi + lo)/2;
        if (target == v[mid].getisbn()) {
            return true;
        } else if (target < v[mid].getisbn()) {
            hi = mid -1;
        } else {
            lo = mid +1;
        }
    }
    return false;
}
bool linearsearch(std::vector<book> v, int target) {
    for (int i = 0; i< v.size()-1; i++) {
        if (v[i].getisbn() == target) {
            return true;
        }
    }
    return false;
}
std::ostream &operator<<(std::ostream &output, std::vector<book> v) {
    for (int i = 0; i < v.size()-1; i++) {
        std::cout << "Isbn:" <<v[i].getisbn() << std::endl;
        std::cout << "Condition: " << v[i].getcond() << std::endl;
    }
    return output;
}
void writeresult(std::string filename, double time, int c) {
    std::ofstream resultstream;
    resultstream.open(filename);
    if (resultstream.fail()) {
        std::cerr << "Error in opening file" << std::endl;
    }
    resultstream << "Cpu time: " << time << " choice : " << c << std::endl;
}

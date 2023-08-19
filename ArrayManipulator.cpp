#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>



class ArrayTransformer {
protected:
    std::ifstream fin;

public:
    ArrayTransformer(std::string pathToFile) {
        fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        std::cout << "start of ArrayTransf\n";
        fin.open(pathToFile);
    }

    virtual ~ArrayTransformer() {
        fin.close();
    }

public:
    virtual std::vector<int> nextTransform() = 0;
    
    void displayArr(std::vector<int>& arr);
    void bubbleSort(std::vector<int>& arr);
    void revBubbleSort(std::vector<int>& arr);
    std::vector<int> findIntersection(const std::vector<int>& arr1, const std::vector<int>& arr2, const std::vector<int>& arr3  = {});
    std::vector<int> createSortedReverseUnique(const std::vector<int>& arr1, const std::vector<int>& arr2, const std::vector<int>& arr3);

    bool contains(const std::vector<int>& arr, int num);
    
};


class ReadData: public ArrayTransformer {
public: 
    ReadData(std::string pathToFile) : ArrayTransformer(pathToFile) {}

    std::vector<int> nextTransform() override {

        try {
            std::vector<int> arr;

            if (fin.eof()) {
                return arr;
            }

            std::string line;
            std::string strNum;
            std::getline(fin, line);    
            std::cout << "read line: " << line << '\n';

            for(size_t i = 0; i < line.size(); ++i) {
                if(line[i] != ',' && line[i] != ' ' && i < line.size()) {
                    strNum += line[i];
                }
                else if (!strNum.empty()) {
                    int num = std::stoi(strNum);
                    arr.push_back(num);
                    strNum.clear();
                }
            }

            if (!strNum.empty()) {
                int num = std::stoi(strNum);
                arr.push_back(num);
                strNum.clear();
            }

            return arr;
    } 
    catch (const std::exception& ex) {
        std::cout << ex.what() << '\n';
        std::cout << "Error\n";
    }
    }
};



int main() {
    std::string path = "./myFile";

    ReadData manipulateArr(path);

    std::vector<int> arr1 = manipulateArr.nextTransform();
    std::vector<int> arr2 = manipulateArr.nextTransform();
    std::vector<int> arr3 = manipulateArr.nextTransform();
    
    std::cout << std::endl;

    manipulateArr.bubbleSort(arr1);
    manipulateArr.displayArr(arr1);
    manipulateArr.bubbleSort(arr2);
    manipulateArr.displayArr(arr2);
    manipulateArr.displayArr(arr3);
    
    std::cout << std::endl;

    std::vector<int> intersection  = manipulateArr.findIntersection(arr1, arr2, arr3);
    std::vector<int> intersection2 = manipulateArr.findIntersection(arr1, arr3);

    manipulateArr.displayArr(intersection);
    manipulateArr.displayArr(intersection2);

    std::cout << std::endl;

    std::vector<int> reverseUnique = manipulateArr.createSortedReverseUnique(arr1, arr2, arr3);

    manipulateArr.displayArr(reverseUnique);
    
    return 0;
}






void ArrayTransformer::displayArr(std::vector<int>& arr) {
    for (int i : arr) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}


void ArrayTransformer::bubbleSort(std::vector<int>& arr) { 
    int temp;
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void ArrayTransformer::revBubbleSort(std::vector<int>& arr) { 
    int temp;
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] < arr[j + 1]) { 
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


bool ArrayTransformer::contains(const std::vector<int>& arr, int num) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == num) {
            return true;
        }
    }
    return false;
}


std::vector<int> ArrayTransformer::findIntersection(const std::vector<int>& arr1, const std::vector<int>& arr2, const std::vector<int>& arr3) {
    std::vector<int> intersection;

    for (int num : arr1) {
        if (contains(arr2, num)) {
            if (arr3.empty() || contains(arr3, num)) {
                intersection.push_back(num);
            }
        }
    }

    return intersection;
}


std::vector<int> ArrayTransformer::createSortedReverseUnique(const std::vector<int>& arr1, const std::vector<int>& arr2, const std::vector<int>& arr3) {
    std::vector<int> reverseUnique;

    for (int num : arr1) {
        if (!contains(reverseUnique, num)) {
            reverseUnique.push_back(num);
        }
    }
    for (int num : arr2) {
        if (!contains(reverseUnique, num)) {
            reverseUnique.push_back(num);
        }
    }
    for (int num : arr3) {
        if (!contains(reverseUnique, num)) {
            reverseUnique.push_back(num);
        }
    }

    revBubbleSort(reverseUnique);

    return reverseUnique;
}
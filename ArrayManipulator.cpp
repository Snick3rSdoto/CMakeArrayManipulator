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

    virtual std::vector<int> nextTransform() = 0;
};


class VectorTransformer: public ArrayTransformer {
public: 
    VectorTransformer(std::string pathToFile) : ArrayTransformer(pathToFile) {}

    std::vector<int> nextTransform() override 
    {
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



void displayArr(std::vector<int>& arr) {
    for (int i : arr) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

void bubbleSort(std::vector<int>& arr) { 
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

void revBubbleSort(std::vector<int>& arr) { 
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

bool contains(const std::vector<int>& arr, int num) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == num) {
            return true;
        }
    }
    return false;
}

std::vector<int> findIntersection(const std::vector<int>& arr1, const std::vector<int>& arr2, const std::vector<int>& arr3 = {}) {
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

std::vector<int> createSortedReverseUnique(const std::vector<int>& arr1, const std::vector<int>& arr2, const std::vector<int>& arr3) {
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


int main() {
    std::string path = "./myFile";

    VectorTransformer vTrans(path);
    std::vector<int> arr1 = vTrans.nextTransform();
    std::vector<int> arr2 = vTrans.nextTransform();
    std::vector<int> arr3 = vTrans.nextTransform();

    std::cout << std::endl;

    bubbleSort(arr1);
    displayArr(arr1);
    bubbleSort(arr2);
    displayArr(arr2);
    displayArr(arr3);
    
    std::cout << std::endl;

    std::vector<int> intersection  = findIntersection(arr1, arr2, arr3);
    std::vector<int> intersection2 = findIntersection(arr1, arr3);

    displayArr(intersection);
    displayArr(intersection2);

    std::cout << std::endl;

    std::vector<int> reverseUnique = createSortedReverseUnique(arr1, arr2, arr3);

    displayArr(reverseUnique);
    
    return 0;
}
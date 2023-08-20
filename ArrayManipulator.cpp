#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

template <typename Iterable>

class ArrayTransformer {
protected:
    std::ifstream fin;

public:
    ArrayTransformer(std::string pathToFile) {
        fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        fin.open(pathToFile);
    }

    virtual ~ArrayTransformer() {
        fin.close();
    }

public:
    virtual Iterable nextTransform() = 0;

    template <typename T>
    void displayArr(const T& arr);
    template <typename T>
    void bubbleSort(T& arr);
    template <typename T>
    void revBubbleSort(T& arr);
    template <typename T>
    T findIntersection(const T& arr1, const T& arr2, const T& arr3 = {});
    template <typename T>
    T createSortedReverseUnique(const T& arr1, const T& arr2, const T& arr3); 
    template <typename T>
    bool contains(const T& arr, int num);
};

template <typename Trd>

class ReadData: public ArrayTransformer<Trd> {
public: 
    ReadData(std::string pathToFile) : ArrayTransformer<Trd>(pathToFile) {}
    
    Trd nextTransform() {

        try {
            Trd arr;

            if (this->fin.eof()) {
                return arr;
            }

            std::string line;
            std::string strNum;
            std::getline(this->fin, line);    
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

    ReadData<std::vector<int>> manipulateArr(path);

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


template <typename Iterable>
template <typename T>
void ArrayTransformer<Iterable>::displayArr(const T& arr) {
    for (const auto& i : arr) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}


template <typename Iterable>
template <typename T>
void ArrayTransformer<Iterable>::bubbleSort(T& arr) {
        for (auto it = std::begin(arr); it != std::end(arr); ++it) {
            for (auto inner = it; inner != std::end(arr); ++inner) {
                if (*it > *inner) {
                    std::swap(*it, *inner);
                }
            }
        }
    }


template <typename Iterable>
template <typename T>
void ArrayTransformer<Iterable>::revBubbleSort(T& arr) {
    for (auto it = std::begin(arr); it != std::end(arr); ++it) {
        for (auto inner = it; inner != std::end(arr); ++inner) {
            if (*it < *inner) {
                std::swap(*it, *inner);
            }
        }
    }
}

template <typename Iterable>
template <typename T>
bool ArrayTransformer<Iterable>::contains(const T& arr, int num) {
    for (const auto& element : arr) {
        if (element == num) {
            return true;
        }
    }
    return false;
}

template <typename Iterable>
template <typename T>
T ArrayTransformer<Iterable>::findIntersection(const T& arr1, const T& arr2, const T& arr3) {
    T intersection;

    for (int num : arr1) {
        if (contains(arr2, num)) {
            if (arr3.empty() || contains(arr3, num)) {
                intersection.push_back(num);
            }
        }
    }
    return intersection;
}

    template <typename Iterable>
    template <typename T>
    T ArrayTransformer<Iterable>::createSortedReverseUnique(const T& arr1, const T& arr2, const T& arr3) {
        T reverseUnique;

        for (const auto& arr : {arr1, arr2, arr3}) {
            for (const auto& num : arr) {
                if (std::find(reverseUnique.begin(), reverseUnique.end(), num) == reverseUnique.end()) {
                  reverseUnique.push_back(num);
            }
        }
    }
        revBubbleSort(reverseUnique);
        return reverseUnique;
    }
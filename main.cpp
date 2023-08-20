#include <iostream>
#include <vector>
#include <list>
#include "ArrayTransformer.cpp"


int main() {
    std::string path = "./myFile";

    ReadData<std::list<int>> manipulateArr(path);

    std::list<int> arr1 = manipulateArr.nextTransform();
    std::list<int> arr2 = manipulateArr.nextTransform();
    std::list<int> arr3 = manipulateArr.nextTransform();

    std::cout << std::endl;

    manipulateArr.bubbleSort(arr1);
    manipulateArr.displayArr(arr1);
    manipulateArr.bubbleSort(arr2);
    manipulateArr.displayArr(arr2);
    manipulateArr.displayArr(arr3);
    
    std::cout << std::endl;
    
    std::list<int> intersection  = manipulateArr.findIntersection(arr1, arr2, arr3);
    std::list<int> intersection2 = manipulateArr.findIntersection(arr1, arr3);

    manipulateArr.displayArr(intersection);
    manipulateArr.displayArr(intersection2);

    std::cout << std::endl;

    std::list<int> reverseUnique = manipulateArr.createSortedReverseUnique(arr1, arr2, arr3);

    manipulateArr.displayArr(reverseUnique);
    
        return 0;
    }



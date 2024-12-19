#include <iostream>
#include <vector>

class HeapSorter {
public:
    explicit HeapSorter(std::vector<int>& data) : data(data) {}

    void sort() {
        buildHeap();
        for (size_t i = data.size() - 1; i > 0; --i) {
            swap(0, i);
            heapify(0, i);
        }
    }

    void print() const {
        for (const int& value : data) {
            std::cout << value << std::endl;
        }
    }

private:
    std::vector<int>& data;

    void swap(size_t a, size_t b) {
        int tmp = data[a];
        data[a] = data[b];
        data[b] = tmp;
    }

    void heapify(size_t i, size_t heapSize) {
        const size_t left = 2 * i + 1;
        const size_t right = 2 * i + 2;
        size_t largest = i;

        if (left < heapSize && data[left] > data[largest]) {
            largest = left;
        }

        if (right < heapSize && data[right] > data[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(i, largest);
            heapify(largest, heapSize);
        }
    }

    void buildHeap() {
        for (size_t i = data.size() / 2; i > 0; --i) {
            heapify(i - 1, data.size());
        }
    }
};

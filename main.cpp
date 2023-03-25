#include <vector>
#include <iostream>

int findMaxPrefix(const std::vector<int> &vec) {
    std::vector<int> sums(vec.size() + 1);
    sums[0] = 0;
    int maxPref = 0;
    for (size_t i = 1; i < sums.size(); i++) {
        sums[i] = sums[i - 1] + vec[i - 1];
        if (sums[i] > maxPref)
            maxPref = sums[i];
    }
    return maxPref;
}

int maxConsecutiveElements(std::vector<int> &vec) {
    int maxConsEls = 0;
    int currMax;
    for (size_t i = 0; i < vec.size(); i += currMax) {
        currMax = 1;
        for (size_t j = i + 1; j < vec.size(); j++) {
            if (vec[i] == vec[j])
                currMax++;
            else if (currMax > maxConsEls)
                maxConsEls = currMax;
        }
    }
    return maxConsEls;
}

int main() {
    std::vector<int> vec1, vec2;
    uint32_t n{};
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    while (true) {
        std::cout << "введите размерность вектора (для выхода 0): ";
        std::cin >> n;
        if(n == 0)
            break;
        vec1.resize(n, 1);
        vec2.resize(n);
        auto t1 = high_resolution_clock::now();
        std::copy(vec1.begin(), vec1.end(), vec2.begin());
        auto t2 = high_resolution_clock::now();
        auto ms_int = duration_cast<std::chrono::microseconds>(t2 - t1);
        std::cout << "copy " << ms_int.count() << "mks, размер " <<  n <<"\n";
        t1 = high_resolution_clock::now();
        std::memcpy(vec2.data(), vec1.data(), vec1.size()* sizeof(vec1[0]));
        t2 = high_resolution_clock::now();
        ms_int = duration_cast<std::chrono::microseconds>(t2 - t1);
        std::cout << "memcpy " << ms_int.count() << "mks, размер " <<  n <<"\n";
        t1 = high_resolution_clock::now();
        for (uint32_t i = 0; i < n; ++i) {
            vec1[i] = static_cast<int>(random());
            vec2[i] = static_cast<int>(random());
        }
        t2 = high_resolution_clock::now();
        ms_int = duration_cast<std::chrono::microseconds>(t2 - t1);
        std::cout << "for loop random init " << ms_int.count() << "mks, размер " <<  n <<"\n";

        t1 = high_resolution_clock::now();
        std::for_each(vec1.begin(), vec1.end(), [](auto& val){val = random();});
        std::for_each(vec2.begin(), vec2.end(), [](auto& val){val = random();});
        t2 = high_resolution_clock::now();
        ms_int = duration_cast<std::chrono::microseconds>(t2 - t1);
        std::cout << "for_each random init " << ms_int.count() << "mks, размер " <<  n <<"\n";

        t1 = high_resolution_clock::now();
        auto maxPrefix = findMaxPrefix(vec1);
        t2 = high_resolution_clock::now();
        ms_int = duration_cast<std::chrono::microseconds>(t2 - t1);
        std::cout << "findMaxPrefix = "<< maxPrefix <<", время "<< ms_int.count() << "mks, размер " <<  n <<"\n";

        t1 = high_resolution_clock::now();
        auto maxConsElems = maxConsecutiveElements(vec2);
        t2 = high_resolution_clock::now();
        ms_int = duration_cast<std::chrono::microseconds>(t2 - t1);
        std::cout << "maxConsecutiveElements = "<< maxConsElems<<", время " << ms_int.count() << "mks, размер " <<  n <<"\n";
    }
}
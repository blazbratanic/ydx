/*
1. The complexity increases by ~1000^2 log(1000) 
2. The complexity increases by ~1000^2 
3. The complexity increases by ~1000 log(1000) 
*/

// O (n^2 log n)
// If size of n is increased by 1000 times, the complexity increases by ~1000^2 log(1000) 
double sum1(std::vector& v)
{    
    // O(1)
    if (v.empty()) {
        return 0.0;
    }
    // O(n)
    for(size_t i = 0; i < v.size() - 1; ++i) {
        // O(n log n)
        std::sort(v.begin()+i, v.end());
        // O(1)
        v[i+1] += v[i];
    }
    // O(1)
    return v.back();
}
 
// O(n^2)
// If size of n is increased by 1000 times, the complexity increases by ~1000^2 
double sum2(std::vector& v)
{    
    // O(1)
    if (v.empty()) {
        return 0.0;
    }
    // O(N)
    for(size_t i = 0; i < v.size() - 1; ++i) {
        // O(n)
        std::partial_sort(v.begin() + i, v.begin() + i + 2, v.end());
        // O(1)
        v[i+1] += v[i];
    }
    // O(1)
    return v.back();
}
 
// O(n log n)
// If size of n is increased by 1000 times, the complexity increases by ~1000 log(1000)
double sum3(std::vector& v)
{    
    // O(n log n) assuming container v is not sorted
    std::multiset set(v.begin(), v.end());

    // O(n), because in each iteration one element is erased from the container
    while (set.size() > 1) {
        // O(1)
        std::multiset::const_iterator itA = set.begin();
        // O(1)
        std::multiset::const_iterator itB = ++set.begin();
        // O(1)
        double c = *itA + *itB;
        // O(log n)
        set.erase(itA, itB);        
        // O(log n)
        set.insert(c);
    }
    // O(1)
    return !set.empty() ? *set.begin() 
                        : 0.0;
}

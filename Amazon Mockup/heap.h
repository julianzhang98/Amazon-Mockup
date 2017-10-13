#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{

public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below
    void trickleUp(int i);
    void trickleDown(int i);

    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    // You complete.
    keyToLocation_.insert(std::make_pair(item, store_.size()));

    std::pair<double, T> temp = std::make_pair(priority, item);

    store_.push_back(temp);

    trickleUp(store_.size()-1);

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete

    int index = keyToLocation_[item]; // index of item in array
    
    store_[index].first = priority; // use that index to update priority

    trickleUp(index); // because priority has decreased so go up

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    // You complete

    return store_[0].second;

}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    // You complete

    keyToLocation_.erase(store_[0].second); // removing from map

    if(store_.size() == 1) {
        store_.pop_back();
        return;
    }
    store_[0] = store_[store_.size()-1]; // set first to last
    keyToLocation_[store_[0].second] = 0;

    store_.pop_back(); // pop last

    trickleDown(0);


}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}


template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(int i) {

    // parent = (i-1)/m_
    
    if (i == 0) {
        // if it's already the top node
        return;
    }

    // if this is less than its parent
    if (c_(store_[i].first, store_[(i-1)/m_].first)) {
        // move it up and recurse
        std::pair<double, T> temp = store_[i];
        store_[i] = store_[(i-1)/m_];
        store_[(i-1)/m_] = temp;

        // after swap

        keyToLocation_[store_[i].second] = i;
        keyToLocation_[store_[(i-1)/m_].second] = (i-1)/m_;

        trickleUp((i-1)/m_);
    }

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleDown(int i) {

    // children = 2p+1 or 2p+2 or ... or 2p+m_

    int firstChildIndex = m_ * i + 1;

    // find smallest child
    int minIndex = i;

    for (int j = 0; j < m_; j++) {
        // might be out of bounds
        int thisIndex = firstChildIndex+j;
        if (thisIndex >= store_.size()) {
            break;
        }

        if (c_(store_[thisIndex].first, store_[minIndex].first)) {
            minIndex = thisIndex;
        }

    }

    if (minIndex == i) {
        // if this node is smaller than all its children
        return;
    }

    // recurse after switching places
    std::pair<double, T> temp = store_[i];
    store_[i] = store_[minIndex];
    store_[minIndex] = temp;

    // after swap
   
    keyToLocation_[store_[i].second] = i;
    keyToLocation_[store_[minIndex].second] = minIndex;

    trickleDown(minIndex);


}

#endif
#include "MemoryBlock.h"
#include <stdexcept>

MemoryBlock::MemoryBlock(size_t size) 
    : size(size), refCount(0), data(new int[size]()) {
}
MemoryBlock::~MemoryBlock() {
    delete[] data;
}
MemoryBlock::MemoryBlock(const MemoryBlock& other) 
    : size(other.size), refCount(0), data(new int[other.size]) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}
MemoryBlock& MemoryBlock::operator=(const MemoryBlock& other) {
    if (this != &other) {
        delete[] data; 
        size = other.size;
        refCount = 0; 
        data = new int[size]; 
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i]; 
        }
    }
    return *this;
}
MemoryBlock::MemoryBlock(MemoryBlock&& other) noexcept
    : size(other.size), refCount(other.refCount), data(other.data) {
    
    other.size = 0;
    other.refCount = 0;
    other.data = nullptr;
}
MemoryBlock& MemoryBlock::operator=(MemoryBlock&& other) noexcept {
    if (this != &other) {
        delete[] data; 
        size = other.size;
        refCount = other.refCount;
        data = other.data; 
        other.size = 0;
        other.refCount = 0;
        other.data = nullptr;
    }
    return *this;
}
int MemoryBlock::readFromBlock(std::size_t offset) const {
    if (offset >= size) {
        throw std::out_of_range("Offset is out of bounds");
    }
    return data[offset];
}
void MemoryBlock::writeToBlock(std::size_t offset, int value) {
    if (offset >= size) {
        throw std::out_of_range("Offset is out of bounds");
    }
    data[offset] = value;
}
void MemoryBlock::acquire() {
    ++refCount;
}
IdleAction MemoryBlock::release() {
    if (refCount > 0) {
        --refCount;
    }
    if (refCount == 0) {
        return onLastRelease();
    }
    return IdleAction::KeepCached;
}   



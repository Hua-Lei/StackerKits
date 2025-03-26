#include "nextbag.h"

NextBag::NextBag() {
    AddBag();
}

void NextBag::AddBag() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(RandomBag.begin(),RandomBag.end(),g);
    for(auto i : RandomBag) {
        currentBag.enqueue(i);
    }
}

PieceType NextBag::dequeue() {
    if(currentBag.size()<=7) {
        AddBag();
    }
    return currentBag.dequeue();
}
PieceType NextBag::at(int n) {
    return currentBag[n];
}

void NextBag::refresh() {
    currentBag.clear();
    AddBag();
}

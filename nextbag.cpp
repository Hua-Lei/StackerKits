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
    if(currentBag.isEmpty()) {
        AddBag();
    }
    return currentBag.dequeue();
}

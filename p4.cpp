#include <iostream>
using namespace std;

class TrieNode
{
public:

    bool hasEnded;
    char letter;
    int frequency;
    TrieNode *childrenArray[26];

    TrieNode(char ch)
    {
        ch = letter;
        for (int i = 0; i < 26; i++)
        {
            childrenArray[i] = NULL;
        }
        hasEnded = false;
    }
};

class minHeapNode
{
public:

    TrieNode *root;
    int freq;
    char *word;
    minHeapNode()
    {
        root = nullptr;
        freq = 0;
        word = nullptr;
    }
};

class minHeap
{
    public:

    minHeapNode *toStore;
    int size; // number of slots filled in minheap
    int minHeapCapacity;

    minHeap(int cap)
    {
        toStore = new minHeapNode[minHeapCapacity];
        size = 0;
        minHeapCapacity = cap;
;
    }
};

int main(void)
{
}
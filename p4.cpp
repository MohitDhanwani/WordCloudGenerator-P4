#include <iostream>
#include <string.h>
#include <unordered_set>
#include <cctype>

using namespace std;
class TrieNode
{
public:
    bool hasEnded;
    int MinheapIndex;
    int frequency;
    TrieNode *childrenArray[26];

    TrieNode()
    {
        MinheapIndex = -1;
        for (int i = 0; i < 26; i++)
        {
            childrenArray[i] = NULL;
        }
        hasEnded = false;
    }
};

class MinHeapNode
{
public:
    TrieNode *root;
    int freq;
    char *word;
    MinHeapNode()
    {
        root = nullptr;
        freq = 0;
        word = nullptr;
    }
};

class MinHeap
{
public:
    MinHeapNode *toStore;
    int size; // number of slots filled in minheap
    int minHeapCapacity;

    MinHeap(int cap)
    {
        minHeapCapacity = cap;
        toStore = new MinHeapNode[minHeapCapacity];
        size = 0;
    }
};

void swapMinheapNodes(MinHeapNode *x, MinHeapNode *y)
{
    MinHeapNode temp = *x;
    *x = *y;
    *y = temp;
}

void minHeapify(MinHeap *minheap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minheap->size && minheap->toStore[left].freq < minheap->toStore[smallest].freq)
    {
        smallest = left;
    }

    if (right < minheap->size && minheap->toStore[right].freq < minheap->toStore[smallest].freq)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        minheap->toStore[smallest].root->MinheapIndex = index;
        minheap->toStore[index].root->MinheapIndex = smallest;

        swapMinheapNodes(&minheap->toStore[smallest], &minheap->toStore[index]);
        minHeapify(minheap, smallest);
    }
}

// a function to create minheap
void buildingMinHeap(MinHeap *minHeap)
{
    int n = minHeap->size - 1;

    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        minHeapify(minHeap, i);
    }
}

// to convert the given word into lower case
void tolowercase(char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        word[i] = tolower(word[i]);
    }
}

//to remove punctuation marks from the word
void removePunctuation(char *word)
{
    int len = strlen(word);
    int i = 0, j = 0;
    while (i < len)
    {
        if (!ispunct(word[i]))
        {
            word[j++] = word[i];
        }
        i++;
    }
    word[j] = '\0';
}

void insertInMinHeap(MinHeap *minheap, TrieNode **root, char *word)
{
    
    // word present in the heap so updating the frequency of the occurance of the word
    if ((*root)->MinheapIndex != -1)
    {
        (minheap->toStore[(*root)->MinheapIndex].freq)++;

        // checking the same for others!
        minHeapify(minheap, (*root)->MinheapIndex);
    }

    // if word is not present in the minheap

    // checking whether the minheap is empty or not
    else if (minheap->size < minheap->minHeapCapacity)
    {
        int count = minheap->size;

        minheap->toStore[count].freq = (*root)->frequency;

        minheap->toStore[count].word = new char[strlen(word) + 1];

        strcpy(minheap->toStore[count].word, word);

        minheap->toStore[count].root = *root;

        (*root)->MinheapIndex = minheap->size;

        ++(minheap->size);

        buildingMinHeap(minheap);
    }

    // case when minheap would be full and word is not present in it.

    else if ((*root)->frequency > minheap->toStore[0].freq)
    {

        minheap->toStore[0].root->MinheapIndex = -1;
        minheap->toStore[0].root = *root;
        minheap->toStore[0].root->MinheapIndex = 0;
        minheap->toStore[0].freq = (*root)->frequency;

        // delete previously allocated memory and
        delete[] minheap->toStore[0].word;
        minheap->toStore[0].word = new char[strlen(word) + 1];
        strcpy(minheap->toStore[0].word, word);

        minHeapify(minheap, 0);
    }
}

// some of the common word which is mostly repeated in any file
unordered_set<string> stopWords = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", 
    "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", 
    "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", 
    "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", 
    "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", 
    "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", 
    "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", 
    "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", 
    "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", 
    "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", 
    "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", 
    "than", "too", "very" , "can", "will", "just", "don", "should", "now" };

void insertUtil(TrieNode **root, MinHeap *minHeap, char *word, char *dupWord)
{
    tolowercase(word);
    removePunctuation(word);
    
    // Check if the word is a stop word,if it is then return
    if (stopWords.find(word) != stopWords.end())
    {
        return;
    }

    // base condition
    if (*root == NULL)
    {
        *root = new TrieNode();
    }
    // There are still more characters in word

    if (*word != '\0')
    {
        insertUtil(&((*root)->childrenArray[tolower(*word) - 97]), minHeap, word + 1, dupWord);
    }

    // The complete word is processed
    else
    {
        // word is already present, increase the frequency
        if ((*root)->hasEnded)
        {
            ++((*root)->frequency);
        }
        else
        {
            (*root)->hasEnded = 1;
            (*root)->frequency = 1;
        }
        insertInMinHeap(minHeap, root, dupWord);
    }
}

// add a word to Trie & min heap.

void insertTrieAndHeap(char *word, TrieNode **root, MinHeap *minHeap)
{
    insertUtil(root, minHeap, word, word);
}

void displayMinHeap(MinHeap *minHeap)
{
    for (int i = 0; i < minHeap->size; i++)
    {
        cout << minHeap->toStore[i].word << " -> " << minHeap->toStore[i].freq << endl;
    }
}

void displayMinHeapToFile(MinHeap *minHeap, FILE *outFile)
{
    for (int i = 0; i < minHeap->size; i++)
    {
        fprintf(outFile, "%s\n", minHeap->toStore[i].word);
    }
}

void printKMostFreq(FILE *fp, int k, FILE *outFile)
{
    // Create a Min Heap of Size k
    MinHeap *minHeap = new MinHeap(k);

    // Create an empty Trie
    TrieNode *root = NULL;

    // A buffer to store one word at a time
    char buffer[50];

    while (fscanf(fp, "%s", buffer) != EOF)
    {
        insertTrieAndHeap(buffer, &root, minHeap);
    }
    displayMinHeapToFile(minHeap, outFile);
    displayMinHeap(minHeap);
}

int main()
{

    cout << "Enter the number of words(most frequent) you want to display on the console: " << endl;
    int k;
    cin >> k;

    cout << "Enter number of files: " << endl;
    int N;
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        char filename[50]; // Buffer to store filename
        cout << "Enter the filename: " << endl;
        cin >> filename;

        FILE *fp = fopen(filename, "r");

        if (fp == NULL)
        {
            cout << "File" << filename << "doesn't exist" << endl;
            continue;
        }

        char outputFilename[50];
        sprintf(outputFilename, "output_%d.txt", i); 

        FILE *outFile = fopen("output.txt", "w");

        printKMostFreq(fp, k, outFile);
        fclose(fp);
        fclose(outFile);
    }

    return 0;
}
#include "Entry.h"

struct MinHeapNode {
	Entry element;
	struct MinHeapNode *left, *right;
};

struct MinHeap {
	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
	temp->left = temp->right = NULL;
	temp->element.setCharacter(data);
	temp->element.setCount(freq);
	return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)
{
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	if (left < minHeap->size && minHeap->array[left]->element.getCount() < minHeap->array[smallest]->element.getCount())
		smallest = left;
	if (right < minHeap->size && minHeap->array[right]->element.getCount() < minHeap->array[smallest]->element.getCount())
		smallest = right;
	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

int isSizeOne(struct MinHeap* minHeap) { return (minHeap->size == 1); }

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;
	while (i && minHeapNode->element.getCount() < minHeap->array[(i - 1) / 2]->element.getCount()) {
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)
{
	int n = minHeap->size - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

std::string getCode(int arr[], int n) {
	std::string code;
	for (int i = 0; i < n; ++i) {
		code = code + std::to_string(arr[i]);
	}
	return code;
}

int isLeaf(struct MinHeapNode* root) { return !(root->left) && !(root->right); }

struct MinHeap* createAndBuildMinHeap(std::vector<Entry> allChar)
{
	struct MinHeap* minHeap = createMinHeap(allChar.size());
	for (int i = 0; i < allChar.size(); ++i)
		minHeap->array[i] = newNode(allChar[i].getCharacter(), allChar[i].getCount());
	minHeap->size = allChar.size();
	buildMinHeap(minHeap);
	return minHeap;
}

struct MinHeapNode* buildHuffmanTree(std::vector<Entry> allChars)
{
	struct MinHeapNode *left, *right, *top;
	struct MinHeap* minHeap = createAndBuildMinHeap(allChars);
	while (!isSizeOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = newNode('$', left->element.getCount() + right->element.getCount());
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}

void getCodes(struct MinHeapNode* root, int arr[], int top, std::vector<CodeEntry>& codes )
{
	if (root->left) {
		arr[top] = 0;
		getCodes(root->left, arr, top + 1, codes);
	}

	if (root->right) {
		arr[top] = 1;
		getCodes(root->right, arr, top + 1, codes);
	}

	if (isLeaf(root)) {
		char c = root->element.getCharacter();
		std::string s = getCode(arr, top);
		codes.push_back(CodeEntry(c, s));
	}
}

void HuffmanCodes(std::vector<Entry> allChars, std::vector<CodeEntry>& codes)
{
	struct MinHeapNode* root = buildHuffmanTree(allChars);
	int arr[100], top = 0;
	getCodes(root, arr, top, codes);
} 
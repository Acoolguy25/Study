#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>


using namespace std;
#define COUNT 10


struct Node {
    int val;
    Node* left;
    Node* right;
    
    Node(int x) : val(x), left(nullptr), right(nullptr) {
        std::cout << "Node: " << x << std::endl;
    }
};

// Recursive function to build the tree
Node* buildTreeChatGPT(std::vector<int>& nums, int start, int end) {
    if (start > end) {
        return nullptr;
    }
    
    // If the current range has fewer than 3 elements, pick mid as root
    int size = end - start + 1;
    int rootIndex = (size >= 3) ? start + 2 : start + min(1, size - 1);
    
    Node* root = new Node(nums[rootIndex]);
    
    // Recursively build the left and right subtrees
    int leftSize = rootIndex - start - 1 + 1;
    if (leftSize > 1){
        root->left = new Node(nums[rootIndex - 1]);
    }
    if (leftSize > 2){
        root->left->left = new Node(nums[rootIndex - 2]);
    }
    //root->left = buildTree(nums, start, rootIndex - 1);
    root->right = buildTreeChatGPT(nums, rootIndex + 1, end);
    
    return root;
}
Node* buildTreeAnswerKey(vector<int> data, int start, int end){
    if (start > end) {
        return NULL;
    }
    if (end - start < 2){ // Size < 3
        int rootIndex = start;
        Node* newNode = new Node(data[rootIndex]);
        newNode->right = buildTreeAnswerKey(data, rootIndex + 1, end);
        return newNode;
    }
    else {
        int rootIndex = end - 2;
        Node* newNode = new Node(data[rootIndex]);
        newNode->right = buildTreeAnswerKey(data, rootIndex + 1, end);
        newNode->left = buildTreeAnswerKey(data, start, rootIndex - 1);
        return newNode;
    }
}

Node* buildTreeStudent(vector<int> data, int left, int right){
    int size = right - left + 1;
    if (size <= 0){
        return NULL;
    }
    int rootIndex = max(left, right - 2);
    Node* newNode = new Node(data[rootIndex]);
    newNode->left = buildTreeStudent(data, left, rootIndex - 1);
    newNode->right = buildTreeStudent(data, rootIndex + 1, right);
    return newNode;
}

Node* buildTreeIl(vector<int> data, int start, int end){
    if (start > end){
        return NULL;
    }
    Node* newNode;
    if (end - start < 2){
        int rootIndex = start;
        newNode = new Node(data[rootIndex]);
        newNode->right = buildTreeIl(data, rootIndex + 1, end);
    }
    else{
        int rootIndex = end - 2;
        newNode = new Node(data[rootIndex]);
        newNode->left = buildTreeIl(data, start, rootIndex - 1);
        newNode->right = buildTreeIl(data, rootIndex + 1, end);
    }
    return newNode;
}

Node* buildFullTreeStudent(int i, int n){
    if (n < i){
        return NULL;
    }
    Node* newNode = new Node(i);
    if (n!=i){
        newNode->left = new Node(i + 1);
    }
    newNode->right = buildFullTreeStudent(i+2, n);
    return newNode;
}

Node* buildFullTreeIl(int i, int n){
    Node* curr = new Node(i);
    if (i == n){
        return curr;
    }
    else if (i == n - 1){
        curr->left = new Node(i + 1);
    }
    else {
        curr->left = new Node(i + 1);
        curr->right = buildFullTreeIl(i + 2, n);
    }
    return curr;
}

Node* buildSideTree(vector<int> data, int left, int right){
    int size = right - left + 1;
    if (size <= 0){
        return NULL;
    }
    int rootIndex = min(right, left + 2);
    Node* newNode = new Node(data[rootIndex]);
    newNode->right = buildSideTree(data, rootIndex + 1, right);
    newNode->left = buildSideTree(data, left, rootIndex - 1);
    return newNode;
}

Node* buildDoubleSidedTree(int i, int n){
    if (n < i){
        return NULL;
    }
    Node* newNode = new Node(i);
    newNode->left = buildDoubleSidedTree(i + 2, n);
    newNode->right = buildDoubleSidedTree(i + 3, n);
    return newNode;
}

void buildBST(Node*& node, int data){
    if (!node){
        node = new Node(data);
        return;
    }
    if (data < node->val){
        buildBST(node->left, data);
    }
    else{
        buildBST(node->right, data);
    }
}
// Function to get the height of the tree
int getTreeHeight(Node* root) {
    if (!root) return 0;
    return 1 + std::max(getTreeHeight(root->left), getTreeHeight(root->right));
}

void printSubtree(Node* root, std::vector<std::string>& output, int left, int top, int curr_width) {
    if (!root) return;

    // Convert node value to string
    std::string nodeStr = std::to_string(root->val);
    
    // Calculate the center position for the current node
    int center = left + curr_width / 2;

    // Ensure we don't go out of bounds while writing the node
    if (center < output[top].length()) {
        for (size_t i = 0; i < nodeStr.length() && center + i < output[top].length(); i++)
            output[top][center + i] = nodeStr[i];
    }

    // Calculate branch and children positions
    int branchOffset = (curr_width + 1) / 4;

    // Left child
    if (root->left) {
        int branchPos = center - branchOffset;
        if (branchPos > 0 && top + 1 < output.size()) {
            output[top + 1][branchPos] = '/';
            for (int pos = center - 1; pos > branchPos; pos--)
                output[top][pos] = '_';
        }
        printSubtree(root->left, output, left, top + 2, curr_width / 2);
    }

    // Right child
    if (root->right) {
        int branchPos = center + branchOffset;
        if (branchPos < output[top + 1].length() && top + 1 < output.size()) {
            output[top + 1][branchPos] = '\\';
            for (int pos = center + 1; pos < branchPos; pos++)
                output[top][pos] = '_';
        }
        printSubtree(root->right, output, left + curr_width / 2 + 1, top + 2, curr_width / 2);
    }
}

void printTree(Node* root) {
    int height = getTreeHeight(root);
    int width = (1 << height) * 3;  // Set width dynamically based on tree height for ample spacing
    std::vector<std::string> output(height * 2, std::string(width, ' '));
    
    printSubtree(root, output, 0, 0, width);
    
    for (const auto& line : output)
        std::cout << line << std::endl;
}

int main() {
    int n = 8; // Number of elements
    Node* root;

    // Full Tree Test Case
    //std::vector<int> nums = {4, 2, 3, 5, 6, 7, 9};
    // Node* root = buildFullTreeStudent(0, n);
    // Tree Test Case
    //root = buildTreeIl(nums, 0, nums.size() - 1);

    // Side Tree Test Case
    std::vector<int> nums;
    for (int i = 1; i <= n; i++){
        nums.push_back(i);
    }
    root = buildSideTree(nums, 0, nums.size() - 1);

    // Build BST Test Case
    // for (auto num: nums){
    //     buildBST(root, num);
    // }

    // Build double sided tree
    // root = buildDoubleSidedTree(0, n);
    
    // Print out the tree
    std::cout << "Constructed Tree: " << std::endl;
    printTree(root);
    
    return 0;
}

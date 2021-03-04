#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <string.h>
#include <fstream>

std::map<char,std::string> codes;
class HuffmanCodes
{
 struct Node
 {
  char data;
  size_t freq;
  Node* left;
  Node* right;

  Node()
  {
    data = '\0';
    freq = 0;
  }
  Node(char data, size_t freq) : data(data),
                                 freq(freq),
                                 left(NULL),
                                 right(NULL)
                                 {}
 ~Node()
 {
   delete left;
   delete right;
 }
 };

 struct compare
 {
  bool operator()(Node* l, Node* r)
  {
    return (l->freq > r->freq);
  }
};

Node* top;

void printCode(Node* root, std::string str)
{
  if(root == NULL)
   return;

 if(root->data != '$')
 {
   std::cout << root->data << " : " << str << "\n";
 }
 printCode(root->left, str + "0");
 printCode(root->right, str + "1");
}

void storeCodes(Node* root, std::string str) 
{ 
    if (root==NULL) 
        return; 
    if (root->data != '$') 
        codes[root->data]=str; 
    storeCodes(root->left, str + "0"); 
    storeCodes(root->right, str + "1"); 
} 


public:
  HuffmanCodes() {}
  ~HuffmanCodes()
  {
    delete top;
  }
	void GenerateCode(const std::vector<char>& data, const std::vector<size_t>& freq)
  {
   Node* left;
   Node* right;

   std::priority_queue<Node*, std::vector<Node*>, compare > minHeap;

   for(size_t i = 0; i < data.size(); ++i)
   {
      minHeap.push(new Node(data[i], freq[i]));
   }

    while(minHeap.size() != 1)
    {
      left = minHeap.top();
      minHeap.pop();

      right = minHeap.top();
      minHeap.pop();

      top = new Node('$', left->freq + right->freq);
      top->left  = left;
      top->right = right;
      minHeap.push(top);
     }
    printCode(minHeap.top(), "");
   	storeCodes(minHeap.top(),"");
 }
};


int main()
{
  	std::string text;
	std::fstream f1,f2;
  	f1.open("input.txt");
  	f2.open("output.txt",std::ios::out);
  	map<char, char> bit;
  	std::string line;
	while (!f1.eof())
	{
		getline(f1, line);
		text += line;
	}
  	
  	
	  
	HuffmanCodes set1;
	
  	std::vector<char> inpdata;
  	std::vector<size_t> inpfreq;
  	std::map<char,size_t> letter_count;
	//std::string text="abc";
	std::string encoded;
	
	for(char c : text)
		letter_count[c]++;
	for(auto entry : letter_count){
		inpdata.push_back(entry.first);
		inpfreq.push_back(entry.second);	
	}
		
  	size_t size = inpdata.size();
  	set1.GenerateCode(inpdata, inpfreq);
  
	for(auto i: text)
		encoded += 	codes[i];
		
	std::cout << "\nEncoded Huffman data:\n" << encoded << std::endl; 
  	f2<<encoded;

  	
	f1.close();
	f2.close();
	
	
  	return 0;
 }

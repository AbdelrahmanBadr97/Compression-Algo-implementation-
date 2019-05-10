#include "huffman.h"

// Your implementations here


bool sortbysec(const Symbol &a, const Symbol &b)
{
	return (a.pro < b.pro);
}

float Huffman::compute_entropy(const vector<unsigned char>& msg, vector<Symbol>* prob) {

	set<unsigned char> Alphaset;

	//make set of values
	long double allchar = msg.size();
	for (int i = 0; i < msg.size(); i++)
		Alphaset.insert(msg[i]);


	//make pairs of values and thier probabilty
	for (std::set<unsigned char>::iterator it = Alphaset.begin(); it != Alphaset.end(); ++it) {
		int freq = std::count(msg.begin(), msg.end(), *it);
		Symbol temp;
		temp.pro = (double)(freq) /allchar;
		temp.val = *it;
		prob->push_back(temp);
	}
	reverse(prob->begin(), prob->end());
	float H = 0;
	//Calc Entropy
	for (std::vector<Symbol>::iterator it = (*prob).begin(); it != (*prob).end(); ++it) {
		H -= ((*it).pro)*log2(((*it).pro));

	}
	
	return H;

}

void Huffman::build_tree(const vector<Symbol>& prob) {
	//fill priority queue
	priority_queue<pair<double,Node*>> TQ;
	for (int i = 0; i < prob.size();i++) {
		Node* n=new Node;
		n->val=prob[i].val;
		n->prob = prob[i].pro;
		TQ.push(make_pair(-(prob[i]).pro,n));
	}

	// assume left is 0 and it is the small 
	pair<double,Node*>temp1;
	pair<double,Node*>temp2;
	while (TQ.size() != 1) {
		temp1=TQ.top();
		TQ.pop();
		temp2=TQ.top();
		TQ.pop();
		Node* parent=new Node;
		parent->left = temp1.second;
		parent->right = temp2.second;
		parent->val = -1;
		TQ.push(make_pair(temp1.first+temp2.first,parent));
	}

	tree=(TQ.top()).second;
	tableCode(tree, "");

}

int Huffman::encode(const vector<unsigned char>& msg,vector<unsigned int>* encoded_msg) {
	int Num_bits = 0; string code;
	for (int i = 0; i < msg.size(); i++) {
		code = "";
		for (int j = 0; j < Alphabet.size(); j++) {
			if (Alphabet[j].first == msg[i]) {
				code = Alphabet[j].second;
				Num_bits += code.size();
				break;

			}
		}
		//convert code to bits then to int 
		bitset<32>c(code);
		//add coded symbol
		encoded_msg->push_back((unsigned int)(c.to_ulong()));

	}
	//reverse vector because of push back
	reverse(encoded_msg->begin(),encoded_msg->end());
	sort(Alphabet.begin(), Alphabet.end());
	
	return Num_bits;
}
void Huffman::tableCode(Node* x, string Code)
{
	// search the tree for a value if found ,make found = true
	if (x->left==NULL && x->right==NULL) {
		Alphabet.push_back(make_pair(x->val, Code));
		return;
	}
	//if not found check for left child
	if (x->left != NULL ) {
		tableCode( x->left, Code+"0");
	}
	//if not found check for right child
	if (x->right != NULL) {
		tableCode( x->right, Code+"1");
	}

}
void Huffman::print_code_table(){
	for (int i = 0; i < Alphabet.size(); i++) {
		cout << Alphabet[i].first<< " ------ " << Alphabet[i].second << endl;
	}
}

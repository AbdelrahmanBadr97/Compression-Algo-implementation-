#include "huffman.h"

int main(int argc, char* argv[]) {
	Huffman A;
	string fileName = argv[0];
	string func = argv[1];
	string dif="";
	if (argc == 3)
	{
		dif = argv[2];
	}

	string phototype; int x, y, maxintensty,pixel;
	vector <unsigned char > pixels;
	vector<Symbol>*S=new vector <Symbol>;
	cin >> phototype;
	cin >> x >> y >> maxintensty;
	for (int i = 0; i < x; i++)
		for (int k = 0; k < y; k++) {
			cin >> pixel;
			pixels.push_back(pixel);
		}
	reverse(pixels.begin(), pixels.end());
  // read parameters here ...
	
		if (func == "-entropy") {
			float H=A.compute_entropy(pixels, S);
			cout << H;
		}
		else if (func == "-tree") {
			//built and print tree
			A.compute_entropy(pixels, S);
			A.build_tree(*S);
			A.print_code_table();


		}
		else if (func == "-encode" &&argc == 2)
		{
			// Huffman Code 
			vector<unsigned int>* encoded_msg = new vector <unsigned int>;
			A.compute_entropy(pixels, S);
			A.build_tree(*S);
			int NumofBits = A.encode(pixels,encoded_msg);
			cout << NumofBits << endl;
		
		}

		else if (func == "-encode" &&argc == 3) {
			
			// diff Huffman encode 
			vector <unsigned char > pixelsdiff;
			//calc the diffrenece 
			for (int i = 0; i < x; i++) {
				pixelsdiff.push_back(pixels[(i*y)]);
				for (int k = 1; k < y; k++) {
					pixelsdiff.push_back(pixels[(i*y) + k] - pixels[(i*y) + (k - 1)]);
				}
			}
			reverse(pixelsdiff.begin(), pixelsdiff.end());
			A.compute_entropy(pixelsdiff, S);
			A.build_tree(*S);
			vector<unsigned int>* encoded_msg = new vector <unsigned int>;
			//print Num of bite after encoding
			int NumofBits = A.encode(pixelsdiff, encoded_msg);
			cout << NumofBits << endl;

		}
		else { cout << "Wrong" << endl; }
 
  return 0;
}

#include "arithmetic.h"

string hex_str_to_bin_str(const string& hex);
const char* hex_char_to_bin(char c);
int main(int argc, char* argv[]) {
	Arithmetic A;
	string fileName = argv[0];
	string func = argv[1];
	string value = "";
	if (argc >2 )
	{
		value = argv[2];
	}
	

	// read parameters here ...

	if (func == "-bin_to_dec") {
		value.erase(0, 2);
		long double H = A.binary_to_decimal(hex_str_to_bin_str(value));
		cout << H;
	}
	else if (func == "-dec_to_bin") {
		string::size_type sz;     // alias of size_t
		double v = std::stod(value, &sz);
		string result = A.decimal_to_binary(v);
			cout << result;

	}
	else if (func == "-encode" )
	{
		string phototype; int x, y, maxintensty, pixel;
		vector <unsigned char > pixels;
		cin >> phototype;
		cin >> x >> y >> maxintensty;
		for (int i = 0; i < x; i++)
			for (int k = 0; k < y; k++) {
				cin >> pixel;
				pixels.push_back(pixel);
			}
		
		string::size_type sz;     // alias of size_t
		double v = std::stod(value, &sz);
		vector <bitset<32>> *encoded=new vector <bitset<32>>;

		int Num=A.encode(pixels, int(v), encoded);
		cout << Num << endl;
		cout << encoded->size()<<endl;
		/*for (int i = 0; i < encoded->size(); i++) {
			cout << (*(encoded))[i] << endl;
		}
		A.Write_Alph();*/
	}

	else if (func == "-decode" ) {

		string phototype = "P2"; int x, y, maxintensty; 
	 
		string temp; temp= argv[3];
		string::size_type sz;     // alias of size_t
		x = std::stod(temp, &sz);
		temp = argv[4];
		string::size_type sz1;     // alias of size_t
		y = std::stod(temp, &sz1);

		temp = argv[5];
		string::size_type sz2;     // alias of size_t
		maxintensty = std::stod(temp, &sz2);
		int dummy; cin >> dummy;
		int Num_tags; cin >> Num_tags;
		bitset<32> tag;
		vector <bitset<32>> tags;
		for (int i = 0; i < Num_tags; i++){
			   cin >> tag;
				tags.push_back(tag);
			}

		
	    A.Read_Alph();
		string::size_type sz3;     // alias of size_t
		int Num_sym_block = std::stod(value, &sz3);

		vector <unsigned char > *decodedmsg=new vector <unsigned char >;
         
		A.decode(tags, Num_sym_block, decodedmsg);
		int l = 0;
		cout << phototype << endl << x << " " << y << endl << maxintensty << endl;
		
		for (int i = 0; i < y; i++) {
			for (int k = 0; k <x; k++) {
				cout <<(int) (*decodedmsg)[i*x+k] << " ";
			}
			cout << endl;
		}
		A.Write_Alph();
	}
	else { cout << "Wrong" << endl; }

	return 0;
}
string hex_str_to_bin_str(const string& hex)
{
	// TODO use a loop from <algorithm> or smth
	string bin="";
	for (unsigned i = 0; i != hex.length(); ++i)
		bin += hex_char_to_bin(hex[i]);
	return bin;
}

const char* hex_char_to_bin(char c)
{
	// TODO handle default / error
	switch (toupper(c))
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	default:
		return "";
	}
}


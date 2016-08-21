#include "MyAPI.h"
#include "Node.h"
//#include "Huffman.h"
#include "Huffman2.h"
#include "File.h"

void preOrder(const vector<node> &v, int head) {
    v[head].print();
    if(v[head].left != -1)   preOrder(v, v[head].left);
    if(v[head].right != -1)   preOrder(v, v[head].right);
}

int main()
{
	Huffman2 h2;
	string read = readFile("file/origin.txt");      // 把文件读取进字符串中
	string zip = h2.encode(read);                   // 哈夫曼编码(压缩文件)
	writeFile("file/origin.r", zip);                 // 把编码好的字符串写进文件中
	string decode = h2.decode(zip);                 // 哈夫曼解码（解压文件）
	cout << (read == decode) << endl;               // 判断解码后的串是否和原来相等，即是否做到无损压缩
	writeFile("file/unpack.txt", decode);            // 把解码好的字符串写进文件中
	return 0;

	const string str = "abcdabcdabdabdabaa";        // 下面是单纯测试字符串的压缩和解压
	string test = "";

	for(int i = 1; i <= 6; ++i) {
		test += str;
		string en = h2.encode(test);
		string de = h2.decode(en);
		cout << en << "\nencode'size = " << en.size() << endl;
		cout << "h2 successful?: " << (de == test) << endl << endl << endl << endl;
	}
	return 0;
}

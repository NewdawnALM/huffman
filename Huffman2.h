#ifndef bigger_
#define bigger_

template<typename T>
struct bigger {
    bool operator() (const T &lhs, const T &rhs) const {
        return rhs < lhs;
    }
};

#endif

vector<node> tmp;

class Huffman2 {
	static vector<node> vec;			// 内部数据结构
	static int head;
public:
	Huffman2() { }
	static string encode(const string &oldString);			// 返回编码的字符串（带头信息的）
	static string decode(const string &encodeString);		// 返回解码的字符串
private:
	// 编码和解码都可以使用的公共函数
	static void createTree();
	static void load01(int head, string s);

	// 编码阶段的专属工具函数
	static void preTreatment(const string &oldString);
	static string makeHead();
	static string arrayToString(const string &Array01);

	// 解码阶段的专属工具函数
	static string stringToArray(const string &str);
	static pair<string, uint> headTreatment(const string &encodeString);
	static string searchNode(int head, char* &ptr);
};

vector<node> Huffman2::vec = vector<node>();
int Huffman2::head = 0;


// 对需要编码的字符串进行预处理，即统计出每个结点的频数存放进类内的 vec 中
void Huffman2::preTreatment(const string &oldString) {
	map<uchar, int> m;
	for(auto it = oldString.begin(); it != oldString.end();++it)
	//for(int i = 0; oldString[i] != '\0'; ++i)
		++m[uchar(*it)];
	vec.clear();
    for(auto it = m.begin(); it != m.end(); ++it)
        vec.push_back(node(it->first, it->second));
}

// 构造 huffman 树
void Huffman2::createTree() {
	int num = 0;
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        it->id = num++;
    }
    priority_queue<node, vector<node>, bigger<node> > q;
    for_each(vec.begin(), vec.end(), [&q](const node &n) {  q.push(n);  } );

    int times = vec.size();

	if(times == 1) {
		node top(vec[0].val - 1);
		top.id = num++;
		top.left = vec[0].id;

		q.push(top);
		vec.push_back(top);
	}

	else
    for(int i = 1; i < times; ++i) {
        node first = q.top();   q.pop();
        node second = q.top();  q.pop();
        
		node add(first.val + second.val);
        add.id = num++;
        add.left = first.id;
        add.right = second.id;

        q.push(add);
        vec.push_back(add);
    }
	head = q.top().id;
}

// 为构造好的 huffman 树编上 01 码
void Huffman2::load01(int head, string s) {
	if(vec[head].isleaf()) {
        vec[head].encode = s;
        return ;
    }
    if(vec[head].left != -1)	Huffman2::load01(vec[head].left, s + "0");
	if(vec[head].right != -1)	Huffman2::load01(vec[head].right, s + "1");
}

string Huffman2::arrayToString(const string &Array01) {
	int len = Array01.size();
	uchar ch = 0;
	string res = "";
	for(int i = 0; i < len; ++i) {
		if(i != 0 && ((i & 7) == 0)) {
			res += ch;
			ch = 0;
		}
		if(Array01[i] == '1')	ch |= 1 << (7 - (i & 7));
	}
	res += ch;
	return res;
}

string Huffman2::stringToArray(const string &str) {
	int len = str.size();
	string res = "";
	for(int i = 0; i < len; ++i) {
		for(int j = 7; j >= 0; --j)
			res += ((str[i] & (1 << j)) ? "1": "0");
	}
	return res;
}

// 返回包装好的头信息字符串
string Huffman2::makeHead() {
	auto uintToStr = [](uint x) -> string {			// 匿名函数，把 uint 转换成 4 个字节的字符串
		string res = "";
		for(int i = 3; i >= 0; --i)
			res += uchar((x >> (i << 3)) & 255);
		return res;
	};

	uint total = 0;					// 统计头信息的长度
    string charInfo = "";				// 头信息的字符串，每5个字节为一个单位，第1个字节记录字符值，后4个字节记录该字符出现的频数
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        if(it->isleaf() == false)   break;					// 因为叶子节点全都集中在前面，所以可以直接跳出
		++total;
        charInfo += it->key;
		charInfo += uintToStr(it->val);
    }
	return uintToStr(total) + charInfo;
}

// 主编码函数，调用前面几个工具函数
string Huffman2::encode(const string &oldString) {
	if(oldString == "")	  return "";

    preTreatment(oldString);
    createTree();
    load01(head, "");

	tmp = vec;

    map<uchar, string> m;
    for(int i = 0; i < vec.size(); ++i)
        if(vec[i].isleaf())   m[vec[i].key] = vec[i].encode;		// 存好每个字符对应的编码值

    string array01 = "";
    for(int i = 0; oldString[i] != '\0'; ++i)
		array01 += m[oldString[i]];					// 把原来字符串中的字符转换成对应的编码值

	string res = makeHead() + arrayToString(array01);
	return res;						// 最终返回的字符串为头信息长度+头信息+源字符串的编码
}


// 取出 encodeString 的头信息放进 vector<node> 中，并返回后面的编码字符串
pair<string, uint> Huffman2::headTreatment(const string &encodeString) {

	auto strToUint = [](uchar c1, uchar c2, uchar c3, uchar c4) -> uint {		// 匿名函数， 把 4 个字节的 uchar 转换成对应的 uint
		return (uint(c1) << 24) | (uint(c2) << 16) | (uint(c3) << 8) | uint(c4);
	};
	const string &en = encodeString;
	uint total = strToUint(en[0], en[1], en[2], en[3]);

	uint retLen = 0;
	vec.clear();
	for(uint i = 0; i < total; ++i) {
		uint key_id = 4 + i * 5;
		uchar key = en[key_id];
		uint val = strToUint(en[key_id + 1], en[key_id + 2], en[key_id + 3], en[key_id + 4]);
		retLen += val;
		vec.push_back(node(key, val));
	}
	return make_pair(en.substr(4 + total * 5), retLen);
}

// 根据 01 序列查找对应结点的字符值
string Huffman2::searchNode(int head, char* &ptr) {
    if(vec[head].isleaf())    return chtostr(vec[head].key);
    if(*ptr == '0')   return searchNode(vec[head].left, ++ptr);
    if(*ptr == '1')   return searchNode(vec[head].right, ++ptr);
}

// 主函数，返回解码后的字符串
string Huffman2::decode(const string &encodeString) {
	if(encodeString == "")	 return "";

	auto p = headTreatment(encodeString);
	string huffStr = p.first;
	uint len = p.second;

	createTree();
	load01(head, "");

	string array01 = stringToArray(huffStr);
    string res = "";

    char *ptr = &array01[0];
    while(*ptr != '\0') {
		res += searchNode(head, ptr);
		if(res.size() == len)	return res;
	}
}

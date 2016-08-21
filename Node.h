#ifndef Node_h
#define Node_h

const uchar specialKey = 3;			// 特殊字符用来作分隔标识

// 节点类
class node {
public:
    uchar key;
    uint val;
    int id;						// 存储在 vector 中的编号
    int left, right;			// 左右子结点在 vector 的编号
    string encode;				// 经过 huffman 编码后的 01 串
    void defaultInit()  {   id = 0;  left = right = -1;  encode = "";  }		// 用这个函数来实现VS不支持的类内初始化

    node(): key(specialKey), val(0)  {   defaultInit();   }
    node(int val): key(specialKey), val(val)  {   defaultInit();   }
    node(uchar key, int val): key(key), val(val)  {   defaultInit();   }

    bool operator < (const node &rhs) const {
        if(val == rhs.val)   return key < rhs.key;
        return val < rhs.val;
    }
	bool operator == (const node &rhs) const {
		return key == rhs.key && val == rhs.val && id == rhs.id
			&& left == rhs.left && right == rhs.right && encode == rhs.encode;
	}
    bool isleaf() const {   return left == -1 && right == -1;   }				// 判断是否是叶子节点的函数，很多地方需要用到
    void showKey() const {   printf("key = %c ",key);   }
    void showValue() const {   printf(" val = %d ",val);   }
    void showId() const {   printf(" id = %d ",id);   }
    void showLeft() const {   printf(" left = %d ",left);   }
    void showRight() const {   printf(" right = %d ",right);   }
    void showEncode() const {   printf(" encode = %s ", encode.c_str());   }
    void print() const ;
};

void node::print() const {
    showKey();
    showValue();
    showId();
    showLeft();
    showRight();
    showEncode();
    puts("");
}

#endif
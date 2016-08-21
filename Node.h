#ifndef Node_h
#define Node_h

const uchar specialKey = 3;			// �����ַ��������ָ���ʶ

// �ڵ���
class node {
public:
    uchar key;
    uint val;
    int id;						// �洢�� vector �еı��
    int left, right;			// �����ӽ���� vector �ı��
    string encode;				// ���� huffman ������ 01 ��
    void defaultInit()  {   id = 0;  left = right = -1;  encode = "";  }		// �����������ʵ��VS��֧�ֵ����ڳ�ʼ��

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
    bool isleaf() const {   return left == -1 && right == -1;   }				// �ж��Ƿ���Ҷ�ӽڵ�ĺ������ܶ�ط���Ҫ�õ�
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
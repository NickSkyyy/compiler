// correct check
const bool _T = True, _F = False;
const bool _12T = 1, _02F = 0;
const char _CH = 'a', _I2CH = 48;
const int _INT = 0, _CH2I = 'a', _F2I = False, _T2I = True;
const string _STR = "qixiaorui";

bool t = True, f = False, tf;
char ch = 'a', tch;
int dnum = 412, td;
int hnum = 0x14, th;    // 20
int onum = 010, to;     // 8
string str = "Hello World!", ts;

// wrong example
const int a = 1, s0 = "abc";        // 连续声明
const int b = 1, c = 2, s1 = "abc"; // 三次声明
const string s2 = 'c';              // 错误声明
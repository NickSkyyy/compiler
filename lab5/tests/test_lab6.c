// 1. CONST
const bool _T = True, _F = False;
const bool _12T = 1, _02F = 0;
const char _CH = 'a', _I2CH = 48;
const int _INT = 0, _CH2I = 'a', _F2I = False, _T2I = True;
const string _STR = "qixiaorui";

// wrong example
const int a = 1, s0 = "abc";         // 常量连续声明
const int b = 1, c0 = 2, s1 = "abc"; // 常量三次声明
const string s2 = 'c';               // 常量错误声明
string s3 = "abc", d = 3;            // 变量连续声明
string s4 = "aa", s5 = "bb", e = 4;  // 变量三次声明
char c1 = "test";                    // 变量错误声明

int main()
{
    // 2. VAR
    bool t = True, f = False, tf;
    char ch = 'a', tch;
    int dnum = 412, td;
    int hnum = 0x14, th;    // 20
    int onum = 010, to;     // 8
    int itest;
    string str = "Hello World!", ts;

    // 3.1 EASY EXP
    itest = td + th;
    itest = to - td;
    itest = th * to;
    itest = td / th;
    itest = to % td;
    itest += th;
    itest -= to;
    itest *= td;
    itest /= th;
    itest %= to;
}
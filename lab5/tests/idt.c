// correct check
const bool t = True, f = False;
const bool _12t = 1, _0tf = 0;
const char ch = 'a', i2ch = 48;
const int a = 0, ch2i = 'a', f2i = False, t2i = True;
const string s = "qixiaorui";

// wrong example
const int b = 1, ss = "abc";        // 连续声明
const int c = 1, d = 2, ss = "abc"; // 三次声明
const string s = 'c';               // 错误声明
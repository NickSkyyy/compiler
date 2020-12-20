/**
 * Test for comment block
 * 
 * @return nothing
 */
const bool FT = True;
const bool FF = False;
const char CHAR = ' ';
const int INT = 100;
const string STR = "qixiaorui";

bool ft = True;
bool ff = False;
char ch = 'a';
int dec = 0;      // a = 0(dec)
int oct = 010;    // b = 8(oct)
int hex = 0x10;   // c = 16(hex)
int noval;
string s = "qxr";

void check_void_nothing()
{

}

void check_void_semi()
{
    ;
}

int check_int_param(int d, int e)
{
    return d;
}

// Main func
int main()
{
    // basic alu
    noval = dec + oct;
    noval = dec - hex;
    noval = oct * hex;
    noval = oct / hex;
    noval = hex % dec;
    noval = +noval;
    noval = -noval;
    noval = (noval);
    noval += noval;
    noval -= noval;
    noval *= noval;
    noval /= noval;
    noval %= noval;

    // complex alu
    noval = dec + oct * hex;
    noval = noval + dec * oct + hex;
    noval = (dec - -oct) * hex;

    if (noval != 0)
    {
        int noval = 0;
    }   
    else if (noval == 1)
    {
        if (noval >= 1 && noval <= 1)
            return;
    }
    else if (dec || oct && hex)
    {
        putch('a');
        putch(ch);
        putint(noval);
        putint(12);
        noval = getint();
    }
    else
    {
        while (!(noval < 1) && !(noval > 1))
        {
            break;
        }
    }
    for (int i = 0; i < 10; i+=1)
    {
        if (!noval) continue;
    }
}
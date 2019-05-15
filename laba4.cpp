#include "pch.h"
#include <iostream>
#include<string>
#include<fstream>
#include <bitset>
#include <limits>
using namespace std;
using byte = unsigned char;
using bits_in_byte = bitset<size_t(8)>;
constexpr std::size_t BITS_PER_BYTE = std::numeric_limits<byte>::digits;
class archive
{
public:
void take(string zip, string input, string output);
private:
void archiving(string input, string output);
void unpack(string input, string output);
string bit(string input);
void debit(string c, string output);
string* resize(string *f, int d);
};
void archive::take(string zip, string input, string output)
{
//if (zip == "compress")
archiving(input, output);
//else
// unpack(input, output);
}
void archive::archiving(string input, string output)
{
int i = 0, j = 0, r = 0, lg, k, g = 4, h, s = 16;
string b, c, *t;
t = new string[s];
b = bit(input);
while (j < b.size())
{
for (k = i - 1; k > -1; k--)
{
string d;
lg = t[k].size();
for (int z = 0; z < lg; z++)
d += b[j + z];
if (d == t[k])
break;
}
if (k == -1)
lg = 0;
cout << " "<<lg << " ";
for (int z = 0; z < lg + BITS_PER_BYTE &&(z+j)<b.size(); z++)
{
t[i] += b[j + z];
}
cout << 'l';
k++;
for (int z = 0; z < g; z++)
{
h = k % 2;
k = k / 2;
if (h == 1)
c += '1';
else
c += '0';

}
r = r + g;
j =j +lg;
for (int z = 0; z < BITS_PER_BYTE; z++)
c+= b[j + z];
j = j+BITS_PER_BYTE;
r = r+BITS_PER_BYTE;
i++;
if (i == s)
{
t = resize(t, s);
g=g+1;
s = s * 2;
}
}
debit(c, output);
}
void archive::unpack(string input, string output)
{
string b;
b = bit(input);

debit(b, output);
}
string archive::bit(string input)
{
ifstream open(input);
char c;
string buffer = "";
while (!open.eof())
{
open.get(c);
buffer += bits_in_byte(byte(c)).to_string();
}
open.close();
return buffer;
}
void archive::debit(string bitel, string output)
{
while (bitel.size() % BITS_PER_BYTE)
bitel += '0';
ofstream file(output, ios::binary);

for (int i = 0; i < bitel.size(); i += BITS_PER_BYTE)
{
byte b = bits_in_byte(bitel.substr(i, BITS_PER_BYTE)).to_ulong();
file << b;
}
}
string* archive::resize(string *f, int d)
{
string *t = new string[2 * d];
for (int i = 0; i < d; i++)
t[i] = f[i];
delete[] f;
return t;
}
int main()
{
archive A;
string zip, input, output;
cin >> zip >> input >> output;
A.take(zip, input, output);
}

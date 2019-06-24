#include <iostream>
#include <string>
#include <fstream>
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

    if (zip == "--compress")
        archiving(input, output);
    if (zip == "--decompress")
        unpack(input, output);
}
void archive::archiving(string input, string output)
{
    int i = 0, j = 0, lg, k = 0, g = 4, h, s = 16, q = 0, r = 0;
    string b, c, *t;
    t = new string[s];
    b = bit(input);
    q = b.size();
    while (j < q)
    {
        for (k = i - 1; k > -1; k--)
        {
            string d;
            lg = t[k].size();
            for (int z = j; z < j + lg && (z < q); z++)
                d += b[z];
            if (d == t[k])
                break;
        }
        if (k == -1)
            lg = 0;
        for (int z = j; z < j + lg + BITS_PER_BYTE && z < q; z++)
        {
            t[i] += b[z];
        }
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
        for (int z = j + lg; z < j + lg + BITS_PER_BYTE && (z < q); z++)
        {
            c += b[z];
        }
        j = j + lg + BITS_PER_BYTE;
        i++;
        if (i == s)
        {
            t = resize(t, s);
            g = g + 1;
            s = s * 2;
        }
    }
    debit(c, output);
}
void archive::unpack(string input, string output)
{
    int i = 0, j = 0, g = 4, s = 16;
    long int p = 0;
    string b, c, *t;
    t = new string[s];
    b = bit(input);
    while (j < b.size())
    {
        if (b.size() - j < g)
            break;
        for (int z = 0, k = 1; z < g; z++)
        {
            int g = b[j + z] - '0';
            p = p + g * k;
            k = k * 2;
        }
        j = j + g;
        p--;
        if (p > -1)
        {
            for (int z = 0; z < t[p].size(); z++)
                t[i] += t[p][z];
        }

        for (int z = j; z < j + BITS_PER_BYTE && z < b.size(); z++)
        {
            t[i] += b[z];
        }
        for (int z = 0; z < t[i].size(); z++)
            c += t[i][z];
        j = j + BITS_PER_BYTE;
        i++;
        p = 0;
        if (i == s)
        {
            t = resize(t, s);
            g = g + 1;
            s = s * 2;
        }
    }
    debit(c, output);
}
string archive::bit(string input)
{

    ifstream open(input);
    char c;
    string buffer = "";
    open.get(c);
    while (!open.eof())
    {
        buffer += bits_in_byte(byte(c)).to_string();
        open.get(c);
    }
    open.close();
    return buffer;
}
void archive::debit(string bitel, string output)
{
    while (bitel.size() % BITS_PER_BYTE != 0)
        bitel += '0';
    ofstream file(output, ios::binary);
    int k = bitel.size();
    for (int i = 0; i < k; i += BITS_PER_BYTE)
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
int main(int argc, char const *argv[])
{
    archive A;
    if (argc < 4)
    {
        cout << "have not enought parameters..." << endl;
        return 0;
    }
    string parameter(argv[1]), input(argv[2]), output(argv[3]);
    cout << parameter << " " << input << " " << output << endl;
    A.take(parameter, input, output);

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#define write0 outfile.write((char*)(&zero),1);

const unsigned int magic_number = 0xbeeffeeb;
const unsigned int number_files = 2;
const unsigned char zero = 0;

int main()
{
    std::ofstream outfile ("filesystem",std::ofstream::binary);
    outfile.write((char*)(&magic_number),4);
    outfile.write((char*)(&number_files),4);
    for(int i = 0; i < 512 - 4 - 4;i += 1)
    {
        write0;
    }

    vector<string> files_names = {"file1.txt","file2.txt"};
    vector<string> files_data = {"this is the data of the first file","#include <iostream>\n\nusing namespace std;\n\nint main()\n{\n\treturn 0;\n}\n"};

    for(int i = 0; i < 2;i++)
    {
        string name = files_names.at(i);
        string data = files_data.at(i);
        outfile.write((char*)(name.c_str()),name.size());
        cout << name << endl;
        cout << data << endl; 
        for(int i = name.size(); i < 12;i++)
        {
            write0;
        }
        outfile.write((char*)(data.c_str()),data.size());
        for(int i = data.size(); i < 500;i++)
        {
            write0;
        }
    }

    return 0;
}


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int getNumberOfColumn(string s){
    int res = 1;
    if (s == "")
    {
        res = 0; return res;
    }
    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == ',') ++res;
    }
    return res;
}

int main(){
    string inputfile;
    cout << "\n\nThis program translating csv raw data file\nto LaTeX code of a table data\n\n";
    cout << "Current csv format:\n\t- multiple lines of number\n\t- separator: comma <,>\nPut your data in \"result.csv\" (same directory with this program file)\n";
    cout << "\npress Enter when ready\n";
    getline(cin, inputfile);
    ifstream inf; // inputfile
    ofstream ouf; // outputfile

    inf.open("result.csv");
    ouf.open("latexcode.txt");


    if (!inf.is_open()){
        cerr << "Error opening the file." << endl;
        return 1;
    }
    if (!ouf.is_open()){
        cerr << "Error opening the file." << endl;
        return 1;
    }
    string line;
    getline(inf, line);
    int cols = getNumberOfColumn(line);
    string tableColGen = "|";
    for (int i = 0; i < cols; ++i){
        tableColGen += "c|";
    }
    ouf << "\\begin{table}[h]\n\t\\begin{adjustwidth}{-4cm}{}\n\t\\centering\n\t\\begin{tabular}{" + tableColGen + "}";
    string result = "";
    ouf << "\n\t\t\%add your table's header here, below is sample header of 13 columns";
    ouf << "\n\t\t\\hline \\multirow{2}{*}{Header 1} & \\multirow{2}{*}{Header 2} & \\multirow{2}{*}{Header 3} & \\multirow{2}{*}{Header 4} & \\multicolumn{3}{c|}{Header 5} & \\multicolumn{3}{c|}{Header 6} & \\multicolumn{3}{c|}{Header 7}\\\\"
    << "\n\t\t\\cline{5-13}& & & &  sub 1 &  sub 2 &  sub 3 &  sub 4 &  sub 5 &  sub 6 &  sub 7 &  sub 8 &  sub 9 \\\\";
    do{
        string newline = "\n\t\t\\hline ";
        
        for (int i = 0; i < line.length(); ++i)
        {
            if (line[i] == ','){
                newline += " & ";
            }
            else{
                newline += line[i];
            }
        }
        newline += "\\\\";
        ouf << newline;
    }
    while (getline(inf, line));
    inf.close();
    ouf << "\n\t\t\\hline\n\t\\end{tabular}\n\t\\caption{}\n\t\\label{tab:example}\n\t\\end{adjustwidth}\n\\end{table}";
    cout << "\tLaTeX code file generated\n";
    cout << "\tpress Enter to exit\n";
    getline(cin,line);
    return 0;
}
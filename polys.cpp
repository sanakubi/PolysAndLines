#include <iostream>
#include <fstream>
#include <string>

#include "object.h"

using namespace std;

obj_point stxy(string str){ 
    obj_point rtn;

    rtn.x = stoi(str.substr(0, str.find(";")));
    rtn.y = stoi(str.substr(str.find(";") + 1, str.size()));

    return rtn;
}

int main()
{
    object treg;
    vector<obj_line_vec> lines;
 
    std::ifstream File;
    File.open("lines.txt", ios::in);

    string s_tmp;

    if (File.is_open()) {

        while (std::getline(File, s_tmp)) {
            
            if (s_tmp.size() > 2) {
                string first = s_tmp.substr(0, s_tmp.find(" ") );
                string second = s_tmp.substr(s_tmp.find(" ") + 1, s_tmp.find("\n") - 1);
                obj_line_vec temp;
                temp.start = stxy(first);
                //cout << temp.start << "; ";
                temp.end = stxy(second);
                //cout << temp.end << endl;
                lines.push_back(temp);

            }
        }

    } else { cout << "No file!"; }


    File.close();
    File.open("polys.txt", ios::in);

    s_tmp = "";

    if (File.is_open()) {

        std::getline(File, s_tmp);
        if (s_tmp.size() > 2) {
            bool out = 1;
            while (out) {
                string buffer = s_tmp.substr(0, s_tmp.find(" "));
                string buff = s_tmp.substr(s_tmp.find(" ") + 1, s_tmp.size());
                if (s_tmp == buff)  
                    out = 0;
                s_tmp = buff;
                treg.add_point(stxy(buffer));
            }
            treg.calcalte_object();
        }

    } else { cout << "No file!\n"; }
    
    ofstream fout("results.txt");
    fout << "";

    for (int i = 0; i < lines.size(); i++) {
        fout << to_string(treg.report(lines[i])) << "\n";
        cout << "Line: " << lines[i].start << "-" << lines[i].end << endl << endl;
    }

    fout.close();
}

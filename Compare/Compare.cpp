#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

void main() {
	std::ifstream in1, in2,ref;
	std::ofstream out;
	ref.open("input_paths.txt");
	out.open("resultOfCompare.txt");
	
	path dir1,dir2;
	ref >> dir1 >> dir2;
	out << "Comparison of " << dir1 << " and " << dir2 << " has been started!" << endl;
	out << "All values are shown which difference is greater 0.001" << endl;
	double epsilon = 1e-3;

	try
	{
		if (exists(dir1))
		{
			if (is_regular_file(dir1))
				cout << dir1 << " it is a file not a folder!! " << '\n';

			else if (is_directory(dir1))
			{
				for (directory_entry& x : directory_iterator(dir1)) {
					int n = 0;
					if (is_regular_file(x.path())) {
						path current_file = dir2;
						current_file.append(x.path().filename().c_str());
						if (exists(current_file)) {
							out << x.path().filename() << endl;
							in1.open((x.path()).c_str());
							in2.open(current_file.c_str());
							while (!in1.eof() && !in2.eof()) {
								n++;
								/*char s1[]="", s2[] = "";
								in1.getline(s1,16853);
								in2.getline(s2, 16853);*/
								string s1, s2;
								in1 >> s1;
								in2 >> s2;
								if(!s1.empty() && !s2.empty())
								if ((s1 != s2)&&(stod(s1) - stod(s2) > epsilon))
									out << ' ' << s1 << " || " << s2 << endl;
							}
							out << "End of file was found" << endl;
							out << endl;
							/*if (in1.eof() && !in2.eof())out << "End of file 1 was found" << endl;
							if (!in1.eof() && in2.eof())out << "End of file 2 was found" << endl;*/
						}
						else 
							out << "file " << current_file << " does not exist\n";
						
						cout << "    " << x.path().filename() << '\n';
					}
				}
			}
			else
				cout << dir1 << " exists, but is not a regular file or directory\n";
		}
		else
			cout << dir1 << " does not exist\n";
	}

	catch (const filesystem_error& ex)
	{
		cout << ex.what() << '\n';
	}
	out << "Well done!" << endl;

	out.close();
}
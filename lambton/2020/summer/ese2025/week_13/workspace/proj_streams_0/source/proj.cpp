/*
 * proj.cpp
 *
 *  Created on: Aug. 24, 2020
 *      Author: takis
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::flush;
using std::ofstream;
using std::ifstream;
using std::string;
using std::getline;
using std::istringstream;
using std::ostringstream;

ifstream& openInputFile(ifstream &in, const string &filename)
{
	in.close(); // close in case it was already open
	in.clear(); // clear any existing errors

	in.open(filename.c_str()); // note: filenames are "C-style" strings

	if (!in.good())
		cout << "error: cannot open file!" << endl;

	return in;
}

ofstream& openOutputFile(ofstream &out, const string &filename)
{
	out.close(); // close in case already opened
	out.clear(); // clear any existing errors

	out.open(filename.c_str(), ofstream::out);

	if (!out.good())
		cout << "error: cannot open file!" << endl;

	return out;
}

template<typename T>
void closeFile(T &file)
{
	file.close();
	return;
}

int main()
{
	// initialize: open input and output files
	string infilename = "text.txt";
	string outfilename = "processed.txt";
	ifstream infile;
	ofstream outfile;
	openInputFile(infile, infilename);
	openOutputFile(outfile, outfilename);

	// read in a line from the input file
	unsigned long linenumber = 0;
	string line, word;
	while (getline(infile, line))
	{
		// do per-line processing
		++linenumber;
		string::size_type len(0), maxlen(0);
		string maxword;
		istringstream stream_wordin(line);
		while (stream_wordin >> word)
		{
			len = word.size();
			if (len > maxlen)
			{
				maxlen = len;
				maxword.assign(word);
			}
		}

		// send processed line to output file
		ostringstream stream_lineout;
		stream_lineout << "longest word on line " << linenumber << ": "
				<< maxword << "\n";
		outfile << stream_lineout.str(); // send stream, converted to string, to outfile
	}

	// exit
	closeFile(outfile);
	closeFile(infile);

	return 0;
}


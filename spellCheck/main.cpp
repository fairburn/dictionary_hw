// Brandon Fairburn
// 905557875
// fairburn@vt.edu
// ECE 3574
// Homework 2
// September 21, 2012

#include "Dictionary.h"
using namespace std;

int main(int argc, char ** argv)
{
	if( argc != 3 )
	{
		cout << "Error: program takes 2 arguments" << endl;
		return 1;
	}
	
	QString filename;
	if( QString(argv[2]) == "british" )
		filename = "/usr/share/dict/british-english"; // path to british-english file 
	else if (QString(argv[2]) == "american" )
		filename = "/usr/share/dict/american-english"; // path to american-english file
	else
	{
		cout << "Error: language must be british or american." << endl;
		return 1;
	}
	
	Dictionary dict(filename);
	dict.setInputFile(argv[1]);
	dict.wordCount();
	
	QApplication app(argc, argv);
	dict.spellCheck(argv[1]);
	return app.exec();
	
}

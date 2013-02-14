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
	if( argc != 4 )
	{
		cout << "Error: program takes 3 arguments" << endl;
		return 1;
	}
	
	QString filename = argv[1];
	QString language;
	if( QString(argv[2]) == "british" )
		language = "/usr/share/dict/british-english"; // path to british-english file 
	else if (QString(argv[2]) == "american" )
		language = "/usr/share/dict/american-english"; // path to american-english file
	else
	{
		cout << "Error: language must be british or american." << endl;
		return 1;
	}
	
	Dictionary dict(language);
	dict.setInputFile(filename);
	dict.wordCount();
	
	QApplication app(argc, argv);
	dict.showWordCount(atoi(argv[3]));
	return app.exec();
	
}

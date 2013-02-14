// Brandon Fairburn
// 905557875
// fairburn@vt.edu
// ECE 3574
// Homework 2
// September 21, 2012

#include "Dictionary.h"

Dictionary::Dictionary(QString filename)
{
	// initialize dictionary
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QTextStream data(&file);
	
	// store words in a QHash
	while( true )
	{
		QString line = data.readLine();
		if( line.isNull() )
			break;
		
		// add word to dictionary hash
		// make lowercase to avoid capitalization errors
		dict[line.toLower()] = 0;
	}
	file.close();
	
	num_of_miss = 0;
}

Dictionary::~Dictionary(){}

void Dictionary::setInputFile(QString filename)
{
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QTextStream data(&file);
	
	while( true )
	{
		QString line = data.readLine();
		
		if( line.isNull() )
			break;
		
		if( line == "" )
			continue;
		
		else
		{
			QStringList chunks = line.split(" ");
			for( int i = 0; i < chunks.size(); i++ )
			{
				QString clean_word  = clean(chunks[i].toLower());
				words_from_file.append(clean_word);
			}
		}
	}
	file.close();
}

// Create hashes of misspelled and real words
// Also updates number of times the word is found in the file
void Dictionary::wordCount()
{
	for( int i = 0; i < words_from_file.size(); i++ )
	{
		QString word = words_from_file[i].toLower();
		bool in_dictionary = dict.contains(word);
		
		if( word == "" )
			continue;
		
		if( !in_dictionary ) // if word is misspelled
		{
			num_of_miss += 1;
			if( misspelled.contains(word) )
				misspelled[word] += 1;
			else
				misspelled[word] = 1;
		}
		
		else
		{
			if( words.contains(word) )
				words[word] += 1;
			else
				words[word] = 1;
		}
			
	}
	order();
	
}


QString Dictionary::clean(QString in)
{
	in.remove(QChar(','));
	in.remove(QChar('.'));
	in.remove(QChar('?'));
	in.remove(QChar('!'));
	in.remove(QChar('('));
	in.remove(QChar(')'));
	in.remove(QChar(':'));
	in.remove(QChar(';'));
	in.remove(QChar('\"'));
	
	return in;
}

void Dictionary::order()
{
	// most often used real words
	QList<int> values = words.values();
	qSort(values.begin(), values.end(), qGreater<int>());
	foreach( int val, values )
	{
		QList<QString> keys = words.keys(val);
		foreach( QString key, keys )
		{
			QPair<QString, int> item(key, val);
			if( most_used.contains(item) )
				continue;
			most_used.append(item);
		}
	}
	
	// most common misspelled words
	values = misspelled.values();
	qSort(values.begin(), values.end(), qGreater<int>());
	foreach( int val, values )
	{
		QList<QString> keys = misspelled.keys(val);
		foreach( QString key, keys )
		{
			QPair<QString, int> item(key, val);
			if( most_miss.contains(item) )
				continue;
			most_miss.append(item);
		}
	}
}


void Dictionary::spellCheck(QString filename)
{
	QTextEdit * textEdit = new QTextEdit;
	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
	QString out;
	while( true )
	{
		QString line = in.readLine();
		if( line.isNull() )
			break;
		
		QStringList chunks = line.split(" ");
		for( int i = 0; i < chunks.size(); i++ )
		{
			if( words.contains(clean(chunks[i].toLower())) )
				out.append(chunks[i] + " ");
			else
				out.append("<font color=\"red\">" + chunks[i] + "</font> ");
		}
		out.append("<br>");
	}
	textEdit->setHtml(out);
	textEdit->show();
	
	
}

void Dictionary::showWordCount(int num)
{
	QTextEdit * usedEdit = new QTextEdit;
	QTextEdit * missEdit = new QTextEdit;
	QString used(QString::number(num) + " most common words:<br>-------------<br>");
	QString miss(QString::number(num) + " most common misspelled words:<br>-------------<br>");
	for( int i = 0; i < num; i++ )
	{
		used.append(most_used[i].first + " : " + QString::number(most_used[i].second) + "<br>");
		miss.append(most_miss[i].first + " : " + QString::number(most_miss[i].second) + "<br>");
	}
	usedEdit->setHtml(used);
	usedEdit->show();
	
	missEdit->setHtml(miss);
	missEdit->show();
	
	
}










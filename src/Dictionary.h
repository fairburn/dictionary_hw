// Brandon Fairburn
// 905557875
// fairburn@vt.edu
// ECE 3574
// Homework 2
// September 21, 2012

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QtGui>
#include <QTextEdit>
#include <QString>
#include <QStringList>
#include <QList>
#include <QPair>
#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>

class Dictionary
{
public:
	Dictionary(QString filename);
	~Dictionary();
	
	void setInputFile(QString filename);
	void spellCheck(QString filename);
	void wordCount();
	void showWordCount(int num);
	
private:
	QHash<QString, int> dict; // all words in dictionary
	QHash<QString, int> misspelled; // misspelled words in file stored here
	QHash<QString, int> words; // real words in file stored here
	QList< QPair<QString, int> > most_miss; // most common misspelled words stored here
	QList< QPair<QString, int> > most_used; // most commonly found words stored here
	QStringList words_from_file;
	
	unsigned int num_of_miss;
	
	QString clean(QString in);
	void order();
};

#endif
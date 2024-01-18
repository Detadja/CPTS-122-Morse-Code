#include "header.h"

int main()
{
	ifstream infile("MorseTable.txt", ios::in);
	BST<char, string> Tree;

	char charac;
	string mors_cod, sentence, code;
	while (!infile.eof()) //Goes trhough the file until the end
	{
		infile >> charac;
		infile >> mors_cod;

		//cout << charac << endl << mors_cod << endl << endl;

		Tree.insert(charac, mors_cod);
	}

	cout << "The tree in order:" << endl;
	Tree.disp_tree();
	system("pause");
	system("cls");

	cout << "What message would like to convert into morse?\n";
	getline(cin, sentence);

	cout << endl << "The morse code version is:" << endl;
	Tree.convert(sentence, &code);

	infile.close();
	return 0;
}
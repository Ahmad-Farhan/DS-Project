#include "stddsdb.h"
#include <Windows.h>

int IndexingMenu(FieldTable*& Map)
{
	system("cls");

	int decision;

	for (int i = 0; i < 8; i++)
		cout << endl;

	cout << "\t\t\t\t\t Select Field For Indexing" << endl;
	cout << "\t\t\t\t\t -------------------------" << endl;

	for (int i = 0; i < Map->Total; i++)
		cout << "\t\t\t\t\t " << i + 1 << ". " << Map->Table[i] << endl;

	cout << endl << "\t\t\t\t\t Enter Decision : ";
	cin >> decision;



	if (decision >= 1 && decision <= Map->Total)
		return decision;
	else
	{
		while (decision < 1 && decision > Map->Total);
		{
			IndexingMenu(Map);
		}
	}
}



int TreeSelect()
{
	system("cls");

	for (int i = 0; i < 8; i++)
		cout << endl;

	int decision = 0;
	cout << "\t\t\t\t\t  Select the Tree " << endl
		<< "\t\t\t\t\t  --------------" << endl
		<< "\t\t\t\t\t  1. AVL Tree" << endl
		<< "\t\t\t\t\t  2. Red Black Tree" << endl
		<< "\t\t\t\t\t  3. B Tree" << endl;



	cout << endl << "\t\t\t\t\t Enter Decision : ";
	cin >> decision;


	if (decision >= 1 && decision <= 3)
		return decision;
	else
	{
		while (decision < 1 && decision > 3);
		{
			TreeSelect();
		}
	}
}

void welcome()
{
	for (int i = 0; i < 8; i++)
		cout << endl;

	cout << "\t\t\t\t\t _______________________" << endl;
	Sleep(300);
	cout << "\t\t\t\t\t W";
	Sleep(300);
	cout << "e";
	Sleep(300);
	cout << "l";
	Sleep(300);
	cout << "c";
	Sleep(300);
	cout << "o";
	Sleep(300);
	cout << "m";
	Sleep(300);
	cout << "e";
	Sleep(300);
	cout << " t";
	Sleep(300);
	cout << "o";
	Sleep(300);
	cout << " A";
	Sleep(300);
	cout << "H";
	Sleep(300);
	cout << "I";
	Sleep(300);
	cout << " D";
	Sleep(300);
	cout << "a";
	Sleep(300);
	cout << "t";
	Sleep(300);
	cout << "a";
	Sleep(300);
	cout << "Base" << endl;
	Sleep(300);

	cout << "\t\t\t\t\t -----------------------" << endl;

	Sleep(300);
	system("cls");

	return;
}

int Operations()
{
	system("cls");

	for (int i = 0; i < 8; i++)
		cout << endl;

	int decision = 0;
	cout << "\t\t\t\t\t    Operations " << endl
		<< "\t\t\t\t\t    ---------- " << endl
		<< "\t\t\t\t\t  1. Point Search" << endl
		<< "\t\t\t\t\t  2. Range Search" << endl
		<< "\t\t\t\t\t  3. Delete Field" << endl
		<< "\t\t\t\t\t  4. Update Field" << endl
		<< "\t\t\t\t\t  5. Where Clause" << endl
		<< "\t\t\t\t\t  6. Creater another Tree" << endl
		<< "\t\t\t\t\t  7. Exit" << endl;




	cout << endl << "\t\t\t\t\t Enter Decision : ";
	cin >> decision;


	if (decision >= 1 && decision <= 7)
		return decision;
	else
	{
		while (decision < 1 && decision > 7);
		{
			Operations();
		}
	}


}

int endOption()
{

	int endChoice;
	cout << endl << "\t\t\t\t\t 1. Continue";
	cout << endl << "\t\t\t\t\t 2. Terminate";

	cout << endl << endl << "\t\t\t\t\t Enter Decision : ";
	cin >> endChoice;

	return endChoice;
}

void menu()
{
	RBTree<Field<string>>* RTreeStr;
	RBTree<Field<double>>* RTreeFloat;

	BTree<Field<int>>* BTreeInt;
	BTree<Field<string>>* BTreeStr;


	AVLTree<Field<string>>* AVLStr;
	AVLTree<Field<double>>* AVLfloat;



	FieldTable* Map = GenerateFieldMap();
	int totalFchoices = Map->Total;
	cout << totalFchoices << endl;
	int FChoice = IndexingMenu(Map);


	int TChoice = TreeSelect();

	string fieldselected = Map->Table[FChoice - 1];


	int min, max, ps;
	int endChoice;
	string min2, max2, ps2;
	string id, oldval, newVal, input, upclaus;

	switch (TChoice)
	{

	case 1:

		for (int j = 0; j < totalFchoices; j++)
		{

			if (FChoice == j + 1)
				if (FChoice == 1 || FChoice == 2 || FChoice == 6 || FChoice == 7)
				{

					GenerateIndex(AVLfloat, fieldselected, 10);
					Sleep(700);

				OperationsMenu1:

					int oper = Operations();

					switch (oper)
					{
					case 1:
						cout << endl << "\t\t\t\t\t Input Id : ";
						cin >> ps;

						AVLfloat->Search(ps);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu1;
						else
							break;
					case 2:
						cout << endl << "\t\t\t\t\t Min Id : ";
						cin >> min;
						cout << endl << "\t\t\t\t\t Max Id : ";
						cin >> max;

						AVLfloat->RangeSearch(min, max);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu1;
						else
							break;
					case 3:

						cout << endl << "\t\t\t\t\t Delete Id: ";
						cin >> ps;

						AVLfloat->Delete(ps);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu1;
						else
							break;
					case 4:
						cout << endl << "\t\t\t\t\t Enter Id: ";
						cin >> id;
						cout << endl << "\t\t\t\t\t Old Value: ";
						cin >> oldval;
						cout << endl << "\t\t\t\t\t New Value: ";
						cin >> newVal;
						upclaus = id + "," + fieldselected + "," + oldval + "," + newVal;
						UpdateClause(AVLfloat, upclaus);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu1;
						else
							break;
					case 5:
						cout << endl << "\t\t\t\t\t Enter Command [Syntax Eg: point-search, Iowa where Deaths = 29600]: ";
						cin >> input;
						WhereClause(AVLfloat, input);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu1;
						else
							break;
					case 6:
						menu();
						break;
					case 7:

						break;
					default:
						cout << "\t\t\t\t\t Invalid Input!" << endl;
					}
				}
				else
				{
					GenerateIndex(AVLStr, fieldselected, 10);
					Sleep(700);

				OperationsMenu2:

					int oper = Operations();

					switch (oper)
					{
					case 1:
						cout << endl << "\t\t\t\t\t Input Id : ";
						cin >> ps2;

						AVLStr->Search(ps2);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu2;
						else
							break;
					case 2:
						cout << endl << "\t\t\t\t\t Min Id : ";
						cin >> min2;
						cout << endl << "\t\t\t\t\t Max Id : ";
						cin >> max2;

						AVLStr->RangeSearch(min2, max2);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu2;
						else
							break;
					case 3:

						cout << endl << "\t\t\t\t\t Delete Id: ";
						cin >> ps2;

						AVLStr->Delete(ps2);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu2;
						else
							break;
					case 4:
						cout << endl << "\t\t\t\t\t Enter Id: ";
						cin >> id;
						cout << endl << "\t\t\t\t\t Old Value: ";
						cin >> oldval;
						cout << endl << "\t\t\t\t\t New Value: ";
						cin >> newVal;
						upclaus = id + "," + fieldselected + "," + oldval + "," + newVal;
						UpdateClause(AVLStr, upclaus);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu2;
						else
							break;
					case 5:
						cout << endl << "\t\t\t\t\t Enter Command [Syntax Eg: point-search, Iowa where Deaths = 29600]: ";
						cin >> input;
						WhereClause(AVLStr, input);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu2;
						else
							break;
					case 6:
						menu();
						break;
					case 7:

						break;
					default:
						cout << "\t\t\t\t\t Invalid Input!" << endl;
					}

				}
		}

		break;
	case 2:
		for (int j = 0; j < totalFchoices; j++)
		{
			if (FChoice == j + 1)
				if (FChoice == 1 || FChoice == 2 || FChoice == 6 || FChoice == 7)
				{
					GenerateIndex(RTreeFloat, fieldselected, 10);
					Sleep(700);

				OperationsMenu3:

					int oper = Operations();

					switch (oper)
					{
					case 1:
						cout << endl << "\t\t\t\t\t Input Id : ";
						cin >> ps;

						RTreeFloat->Search(ps);

						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu3;
						else
							break;
					case 2:
						cout << endl << "\t\t\t\t\t Min Id : ";
						cin >> min;
						cout << endl << "\t\t\t\t\t Max Id : ";
						cin >> max;

						RTreeFloat->RangeSearch(min, max);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu3;
						else
							break;
					case 3:

						cout << endl << "\t\t\t\t\t Delete Id: ";
						cin >> ps;

						RTreeFloat->Delete(ps);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu3;
						else
							break;
					case 4:
						cout << endl << "\t\t\t\t\t Enter Id: ";
						cin >> id;
						cout << endl << "\t\t\t\t\t Old Value: ";
						cin >> oldval;
						cout << endl << "\t\t\t\t\t New Value: ";
						cin >> newVal;
						upclaus = id + "," + fieldselected + "," + oldval + "," + newVal;
						UpdateClause(RTreeFloat, upclaus);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu3;
						else
							break;
					case 5:
						cout << endl << "\t\t\t\t\t Enter Command [Syntax Eg: point-search, Iowa where Deaths = 29600]: ";
						cin >> input;
						WhereClause(RTreeFloat,input);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu3;
						else
							break;
					case 6:
						menu();
						break;
					case 7:

						break;
					default:
						cout << "\t\t\t\t\t Invalid Input!" << endl;
					}

				}
				else
				{
					GenerateIndex(RTreeStr, fieldselected, 10);
					Sleep(700);

				OperationsMenu4:

					int oper = Operations();

					switch (oper)
					{
					case 1:
						cout << endl << "\t\t\t\t\t Input Id : ";
						cin >> ps2;

						RTreeStr->Search(ps2);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu4;
						break;
					case 2:
						cout << endl << "\t\t\t\t\t Min Id : ";
						cin >> min2;
						cout << endl << "\t\t\t\t\t Max Id : ";
						cin >> max2;

						RTreeStr->RangeSearch(min2, max2);

						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu4;
						else
							break;
					case 3:

						cout << endl << "\t\t\t\t\t Delete Id: ";
						cin >> ps2;

						RTreeStr->Delete(ps2);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu4;
						else
							break;
					case 4:
						cout << endl << "\t\t\t\t\t Enter Id: ";
						cin >> id;
						cout << endl << "\t\t\t\t\t Old Value: ";
						cin >> oldval;
						cout << endl << "\t\t\t\t\t New Value: ";
						cin >> newVal;
						upclaus = id + "," + fieldselected + "," + oldval + "," + newVal;
						UpdateClause(RTreeStr, upclaus);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu4;
						else
							break;
					case 5:
						cout << endl << "\t\t\t\t\t Enter Command [Syntax Eg: point-search, Iowa where Deaths = 29600]: ";
						cin >> input;
						WhereClause(RTreeStr, input);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu4;
						else
							break;
					case 6:
						menu();
						break;
					case 7:

						break;
					default:
						cout << "\t\t\t\t\t Invalid Input!" << endl;
					}

				}
		}
		break;

	case 3:
		int dec;
		cout << endl << "\t\t\t\t\t Enter Order : ";
		cin >> dec;

		for (int j = 0; j < totalFchoices; j++)
		{
			if (FChoice == j + 1)
				if (FChoice == 1 || FChoice == 2 || FChoice == 6 || FChoice == 7)
				{
					GenerateIndex(BTreeInt, dec, fieldselected, 10);
					Sleep(700);

				OperationsMenu5:

					int oper = Operations();

					switch (oper)
					{
					case 1:
						cout << endl << "\t\t\t\t\t Input Id : ";
						cin >> ps;

						BTreeInt->Search(ps);

						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu5;
						else
							break;
					case 2:
						cout << endl << "\t\t\t\t\t Min Id : ";
						cin >> min;
						cout << endl << "\t\t\t\t\t Max Id : ";
						cin >> max;

						BTreeInt->RangeSearch(min, max);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu5;
						else
							break;
					case 3:

						cout << endl << "\t\t\t\t\t Delete Id: ";
						cin >> ps;

						BTreeInt->Delete(ps);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu5;
						else
							break;
					case 4:
						cout << endl << "\t\t\t\t\t Enter Id: ";
						cin >> id;
						cout << endl << "\t\t\t\t\t Old Value: ";
						cin >> oldval;
						cout << endl << "\t\t\t\t\t New Value: ";
						cin >> newVal;
						upclaus = id + "," + fieldselected + "," + oldval + "," + newVal;
						UpdateClause(BTreeInt, upclaus);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu5;
						else
							break;
					case 5:
						cout << endl << "\t\t\t\t\t Enter Command [Syntax Eg: point-search, Iowa where Deaths = 29600]: ";
						cin >> input;
						WhereClause(BTreeInt, input);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu5;
						else
							break;
					case 6:
						menu();
						break;
					case 7:

						break;
					default:
						cout << "\t\t\t\t\t Invalid Input!" << endl;
					}

				}
				else
				{
					GenerateIndex(BTreeStr, dec, fieldselected, 10);
					Sleep(700);

				OperationsMenu6:

					int oper = Operations();

					switch (oper)
					{
					case 1:
						cout << endl << "\t\t\t\t\t Input Id : ";
						cin >> ps2;

						BTreeStr->Search(ps2);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu6;
						else
							break;
					case 2:
						cout << endl << "\t\t\t\t\t Min Id : ";
						cin >> min;
						cout << endl << "\t\t\t\t\t Max Id : ";
						cin >> max;

						BTreeStr->RangeSearch(min2, max2);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu6;
						else
							break;
					case 3:

						cout << endl << "\t\t\t\t\t Delete Id: ";
						cin >> ps;

						BTreeStr->Delete(ps2);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu6;
						else
							break;
					case 4:
						cout << endl << "\t\t\t\t\t Enter Id: ";
						cin >> id;
						cout << endl << "\t\t\t\t\t Old Value: ";
						cin >> oldval;
						cout << endl << "\t\t\t\t\t New Value: ";
						cin >> newVal;
						upclaus = id + "," + fieldselected + "," + oldval + "," + newVal;
						UpdateClause(BTreeStr, upclaus);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu6;
						else
							break;
					case 5:
						cout << endl << "\t\t\t\t\t Enter Command [Syntax Eg: point-search, Iowa where Deaths = 29600]: ";
						cin >> input;
						WhereClause(BTreeStr,input);
						endChoice = endOption();

						if (endChoice == 1)
							goto OperationsMenu6;
						else
							break;
					case 6:
						menu();
						break;
					case 7:

						break;
					default:
						cout << "\t\t\t\t\t Invalid Input!" << endl;
					}

				}
		}
		break;
	default:
		cout << "\t\t\t\t\t Invalid Input!" << endl;
	}

	return;
}


int main()
{
	//BTree<Field<string>>* BITree;
	//GenerateIndex(BITree, 8, "State", 10);
	//WhereClause(BITree, string("point-search, Illinois where Deaths = 106872"));
	welcome();
	menu();

	return 0;
}
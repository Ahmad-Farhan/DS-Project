#pragma once
#include "RBTree.h"
#include "BTree.h"
#include "AVLTree.h"


//===============================================================//
//Searching Duplicates AVLTrees, RBTrees, BTrees
//===============================================================//

template<class data> inline Field<data>
SearchKeys(AVLNode<Field<data>>* Node, const string& OldVal, const int FieldNumber, const string& field, const string& DefinedBy)
{
	if (Node->Keys == nullptr || field == DefinedBy)
		return Node->Data;

	string Tuple = Node->Data.ReadTuple(), Record, CurrentVal;

	Field<data> curr = Node->Data;
	Tuple = curr.ReadTuple();
	CurrentVal = CurrFieldEntry(Tuple, FieldNumber);
	if (CompareStr(CurrentVal, OldVal))
		return curr;

	return Node->Keys->SearchFields(OldVal, FieldNumber);
}

template<class data> inline Field<data>
SearchKeys(RBNode<Field<data>>* Node, const string& OldVal, const int FieldNumber, const string& field, const string& DefinedBy)
{
	if (Node->Keys == nullptr || field == DefinedBy)
		return Node->Data;

	string Tuple = Node->Data.ReadTuple(), Record, CurrentVal;

	Field<data> curr = Node->Data;
	Tuple = curr.ReadTuple();
	CurrentVal = CurrFieldEntry(Tuple, FieldNumber);
	if (CompareStr(CurrentVal, OldVal))
		return curr;

	return Node->Keys->SearchFields(OldVal, FieldNumber);
}

template<class data> inline Field<data>
SearchKeys(BTNode<Field<data>>* Node, const string& OldVal, const int FieldNumber, const string& field, const data key,const string& DefinedBy)
{
	int index = 0;
	Field<data> curr = Node->Keys[0];
	string Tuple, Record, CurrentVal;

	for (index = 0; index < Node->KeyIndex; index++)
		if (Node->Keys[index] == key)
			break;

	if (Node->Links[index] == nullptr || field == DefinedBy)
	{
		Tuple = Node->Keys[index].ReadTuple();
		CurrentVal = CurrFieldEntry(Tuple, FieldNumber);
		if (CompareStr(CurrentVal, OldVal))
			return Node->Keys[index];
	}
	if (Node->Links[index] != nullptr)
		return Node->Links[index]->SearchFields(OldVal, FieldNumber);
	else return Field<data>();
}

inline Field<string>
SearchKeys(BTNode<Field<string>>* Node, const string& OldVal, const int FieldNumber, const string& field, const string key, const string& DefinedBy)
{
	int index = 0;
	Field<string> curr = Node->Keys[0];
	string Tuple, Record, CurrentVal;

	for (index = 0; index < Node->KeyIndex; index++)
		if (Node->Keys[index] == key)
			break;

	if (Node->Links[index] == nullptr || field == DefinedBy)
	{
		Tuple = Node->Keys[index].ReadTuple();
		CurrentVal = CurrFieldEntry(Tuple, FieldNumber);
		if (CompareStr(CurrentVal, OldVal))
			return Node->Keys[index];
	}
	if (Node->Links[index] != nullptr)
		return Node->Links[index]->SearchFields(OldVal, FieldNumber);
	else return Field<string>();
}

//===============================================================//
//Update Clauses AVLTrees, RBTrees, BTrees
//===============================================================//
string UpdateCurrVal(const string Currline, const string& NewVal, const int Fieldno)
{
	string result, LineData = " "; bool Quotation = false;
	for (int i = 0, index = 0; LineData != ""; i++)
	{
		LineData = CreateUpdateData(Currline, index);
		if (i == Fieldno - 1)
			result += NewVal + ",";
		else if
			(LineData == "") break;
		else
			result += LineData + ",";
	}
	result.pop_back();
	return result;
}

//AVLTree Update
template <class data>
void UpdateClause(AVLTree<Field<data>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string Dataline, filename, 
		key = GetData(clause, index),
		field = GetData(clause, index),
		OldValue = GetData(clause, index),
		NewValue = GetData(clause, index);

	AVLNode<Field<data>>* Tuple = Tree->Retrieve(ConvertFromStr<data>(key));
	if (Tuple == nullptr)
	{	cout << field << " : " << key << "Not Found Within Record" << endl; return;}

	filename = BasePath;
	filename += "1.csv";
	ifstream file(filename, ios::in);
	if (file.fail())
	{	cout << "Unable to Open file for Update" << endl; return;}

	getline(file, Dataline);
	file.close();
	FieldNumber = ExtractFieldNumber(Dataline, field);
	if (FieldNumber == -1)
	{	cout << "Invalid Field Defined for Update" << endl; return;}

	Field<data> Record = SearchKeys(Tuple, OldValue, FieldNumber, field, Tree->GetDefinedBy());
	if (Record == Field<data>()) { cout << "Tuple with " << field << " : " << OldValue << " Not Found" << endl; return; }
	Dataline = UpdateCurrVal(Record.ReadTuple(), NewValue, FieldNumber);
	Record.Overwrite(Dataline);
	Tree->SaveTree();

}

void UpdateClause(AVLTree<Field<string>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string Dataline, filename,
		key = GetData(clause, index),
		field = GetData(clause, index),
		OldValue = GetData(clause, index),
		NewValue = GetData(clause, index);

	AVLNode<Field<string>>* Tuple = Tree->Retrieve(key);
	if (Tuple == nullptr)
	{cout << field << " : " << key << "Not Found Within Record" << endl; return;}

	filename = BasePath;
	filename += "1.csv";
	ifstream file(filename, ios::in);
	if (file.fail())
	{
		cout << "Unable to Open file for Update" << endl; return;
	}

	getline(file, Dataline);
	file.close();
	FieldNumber = ExtractFieldNumber(Dataline, field);
	if (FieldNumber == -1)
	{	cout << "Invalid Field Defined for Update" << endl; return;}

	Field<string> Record = SearchKeys(Tuple, OldValue, FieldNumber, field, Tree->GetDefinedBy());
	if (Record == Field<string>()) { cout << "Tuple with " << field << " : " << OldValue << " Not Found" << endl; return; }
	Dataline = UpdateCurrVal(Record.ReadTuple(), NewValue, FieldNumber);
	Record.Overwrite(Dataline);
}

//RB Tree Update
 template <class data>
void UpdateClause(RBTree<Field<data>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string Dataline, filename,
		key = GetData(clause, index),
		field = GetData(clause, index),
		OldValue = GetData(clause, index),
		NewValue = GetData(clause, index);

	RBNode<Field<data>>* Tuple = Tree->Retrieve(ConvertFromStr<data>(key));
	if (Tuple == nullptr)
	{	cout << field << " : " << key << "Not Found Within Record" << endl; return;}

	filename = BasePath;
	filename += "1.csv";
	ifstream file(filename, ios::in);
	if (file.fail())
	{	cout << "Unable to Open file for Update" << endl; return;}

	getline(file, Dataline);
	file.close();
	FieldNumber = ExtractFieldNumber(Dataline, field);
	if (FieldNumber == -1)
	{	cout << "Invalid Field Defined for Update" << endl; return;}

	Field<data> Record = SearchKeys(Tuple, OldValue, FieldNumber, field, Tree->GetDefinedBy());
	if (Record == Field<data>()) { cout << "Tuple with " << field << " : " << OldValue << " Not Found" << endl; return; }
	Dataline = UpdateCurrVal(Record.ReadTuple(), NewValue, FieldNumber);
	Record.Overwrite(Dataline);
	Tree->SaveTree();

}

void UpdateClause(RBTree<Field<string>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string Dataline, filename,
		key = GetData(clause, index),
		field = GetData(clause, index),
		OldValue = GetData(clause, index),
		NewValue = GetData(clause, index);

	RBNode<Field<string>>* Tuple = Tree->Retrieve(key);
	if (Tuple == nullptr)
	{	cout << field << " : " << key << "Not Found Within Record" << endl; return;}

	filename = BasePath;
	filename += "1.csv";
	ifstream file(filename, ios::in);
	if (file.fail())
	{	cout << "Unable to Open file for Update" << endl; return;}

	getline(file, Dataline);
	file.close();
	FieldNumber = ExtractFieldNumber(Dataline, field);
	if (FieldNumber == -1)
	{
		cout << "Invalid Field Defined for Update" << endl; return;
	}

	Field<string> Record = SearchKeys(Tuple, OldValue, FieldNumber, field, Tree->GetDefinedBy());
	if (Record == Field<string>()) { cout << "Tuple with " << field << " : " << OldValue << " Not Found" << endl; return; }
	Dataline = UpdateCurrVal(Record.ReadTuple(), NewValue, FieldNumber);
	Record.Overwrite(Dataline);
}

//BTree Update
template <class data>
void UpdateClause(BTree<Field<data>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber, Tval;
	string Dataline, filename,
		key = GetData(clause, index),
		field = GetData(clause, index),
		OldValue = GetData(clause, index),
		NewValue = GetData(clause, index);

	BTNode<Field<data>>* Tuple = Tree->Retrieve(ConvertFromStr<data>(key));
	//BTNode<Field<string>>* Tuple = Tree->Retrieve(key, Tval); //Btree 2
	if (Tuple == nullptr)
	{	cout << field << " : " << key << "Not Found Within Record" << endl; return;}

	filename = BasePath;
	filename += "1.csv";
	ifstream file(filename, ios::in);
	if (file.fail())
	{	cout << "Unable to Open file for Update" << endl; return;}

	getline(file, Dataline);
	file.close();
	FieldNumber = ExtractFieldNumber(Dataline, field);
	if (FieldNumber == -1)
	{	cout << "Invalid Field Defined for Update" << endl; return;	}

	Field<data> Record = SearchKeys(Tuple, OldValue, FieldNumber, field, ConvertFromStr<data>(key),/*Tval,*/Tree->GetDefinedBy());
	if (Record == Field<data>()) { cout << "Tuple with " << key << " " << field << " : " << OldValue << " Not Found" << endl; return; }
	Dataline = UpdateCurrVal(Record.ReadTuple(), NewValue, FieldNumber);
	Record.Overwrite(Dataline);
	//Tree->SaveTree();

}

void UpdateClause(BTree<Field<string>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber, Tval=0;
	string Dataline, filename,
		key = GetData(clause, index),
		field = GetData(clause, index),
		OldValue = GetData(clause, index),
		NewValue = GetData(clause, index);

	BTNode<Field<string>>* Tuple = Tree->Retrieve(key); //Btree 1
	//BTNode<Field<string>>* Tuple = Tree->Retrieve(key, Tval); //Btree 2
	if (Tuple == nullptr)
	{	cout << field << " : " << key << "Not Found Within Record" << endl; return;}

	filename = BasePath;
	filename += "1.csv";
	ifstream file(filename, ios::in);
	if (file.fail())
	{	cout << "Unable to Open file for Update" << endl; return;}

	getline(file, Dataline);
	file.close();
	FieldNumber = ExtractFieldNumber(Dataline, field);
	if (FieldNumber == -1)
	{	cout << "Invalid Field Defined for Update" << endl; return;}

	Field<string> Record = SearchKeys(Tuple, OldValue, FieldNumber, field, key,/*Tval,*/Tree->GetDefinedBy());
	if (Record == Field<string>()) { cout << "Tuple with " << field << " : " << OldValue << " Not Found" << endl; return; }
	Dataline = UpdateCurrVal(Record.ReadTuple(), NewValue, FieldNumber);
	Record.Overwrite(Dataline);
}

//===============================================================//
//PointSearch AVLTrees, RBTrees, BTrees
//===============================================================//

//================ Point Search AVLTree ================//
template <class data>
void PointSearchAVLD(AVLTree <Field<data>>*& Tree, const string key, const string& field, const string specific)
{
	string Check, str = BasePath;
	str += "1.csv";
	ifstream file(str, ios::in);
	if (file.fail())
	{	cout << "Unable to Open file for Where Clause" << endl; return;}
	getline(file, str);
	file.close();

	data temp = ConvertFromStr<data>(key);
	int FieldNumber = ExtractFieldNumber(str, field);
	AVLNode<Field<data>>* curr = Tree->Retrieve(temp);
	str = curr->Data.ReadTuple();
	Check = CurrFieldEntry(str, FieldNumber);
	if (CompareStr(specific, Check))
		cout << curr->Data << endl;
	curr->DisplaySpKeys(specific, FieldNumber);
}

void PointSearchAVLS(AVLTree <Field<string>>*& Tree, const string key, const string& field, const string specific)
{
	string Check, str = BasePath;
	str += "1.csv";
	ifstream file(str, ios::in);
	if (file.fail())
	{
		cout << "Unable to Open file for Where Clause" << endl; return;
	}
	getline(file, str);
	file.close();

	int FieldNumber = ExtractFieldNumber(str, field);
	AVLNode<Field<string>>* curr = Tree->Retrieve(key);
	str = curr->Data.ReadTuple();
	Check = CurrFieldEntry(str, FieldNumber);
	if (CompareStr(specific, Check))
		cout << curr->Data << endl;
	curr->DisplaySpKeys(specific, FieldNumber);
}

//================ Point Search RBTree ================//
template <class data>
void PointSearchRBD(RBTree <Field<data>>*& Tree, const string key, const string& field, const string specific)
{
	string Check, str = BasePath;
	str += "1.csv";
	ifstream file(str, ios::in);
	if (file.fail())
	{
		cout << "Unable to Open file for Where Clause" << endl; return;
	}
	getline(file, str);
	file.close();

	data temp = ConvertFromStr<data>(key);
	int FieldNumber = ExtractFieldNumber(str, field);
	RBNode<Field<data>>* curr = Tree->Retrieve(temp);
	str = curr->Data.ReadTuple();
	Check = CurrFieldEntry(str, FieldNumber);
	if (CompareStr(specific, Check))
		cout << curr->Data << endl;
	curr->DisplaySpKeys(specific, FieldNumber);
}

void PointSearchRBS(RBTree <Field<string>>*& Tree, const string key, const string& field, const string specific)
{
	string Check, str = BasePath;
	str += "1.csv";
	ifstream file(str, ios::in);
	if (file.fail())
	{
		cout << "Unable to Open file for Where Clause" << endl; return;
	}
	getline(file, str);
	file.close();

	int FieldNumber = ExtractFieldNumber(str, field);
	RBNode<Field<string>>* curr = Tree->Retrieve(key);
	str = curr->Data.ReadTuple();
	Check = CurrFieldEntry(str, FieldNumber);
	if (CompareStr(specific, Check))
		cout << curr->Data << endl;
	curr->DisplaySpKeys(specific, FieldNumber);
}

//================ Point Search BTree ================//

template <class data>
const int GetBTNodeIndex(const BTNode<Field<data>>* Node , const string& key)
{
	data Val = ConvertFromStr<data>(key);
	for (int index = 0; index < Node->KeyIndex; index++)
		if (Node->Keys[index] == Val)
			return index;
}

const int GetBTNodeIndex(const BTNode<Field<string>>* Node, const string& key)
{
	for (int index = 0; index < Node->KeyIndex; index++)
		if (Node->Keys[index] == key)
			return index;
}

template <class data>
void PointSearchBTD(BTree<Field<data>>*& Tree, const string key, const string& field, const string specific)
{
	string Check, str = BasePath;
	str += "1.csv";
	ifstream file(str, ios::in);
	if (file.fail())
	{
		cout << "Unable to Open file for Where Clause" << endl; return;
	}
	getline(file, str);
	file.close();

	data temp = ConvertFromStr<data>(key);
	int FieldNumber = ExtractFieldNumber(str, field);
	BTNode<Field<data>>* curr = Tree->Retrieve(temp);
	int index = GetBTNodeIndex<data>(curr, key);
	str = curr->Keys[index].ReadTuple();
	Check = CurrFieldEntry(str, FieldNumber);
	if (CompareStr(specific, Check))
		cout << curr->Keys[index] << endl;
	if(curr->Links[index] != nullptr)
		curr->Links[index]->DisplaySpFields(specific, FieldNumber);
}

void PointSearchBTS(BTree<Field<string>>*& Tree, const string key, const string& field, const string specific)
{
	string Check, str = BasePath;
	str += "1.csv";
	ifstream file(str, ios::in);
	if (file.fail())
	{
		cout << "Unable to Open file for Where Clause" << endl; return;
	}
	getline(file, str);
	file.close();

	int FieldNumber = ExtractFieldNumber(str, field);
	BTNode<Field<string>>* curr = Tree->Retrieve(key);
	int index = GetBTNodeIndex<string>(curr, key);
	str = curr->Keys[index].ReadTuple();
	Check = CurrFieldEntry(str, FieldNumber);
	if (CompareStr(specific, Check))
		cout << curr->Keys[index] << endl;
	if (curr->Links[index] != nullptr)
		curr->Links[index]->DisplaySpFields(specific, FieldNumber);
}

//===============================================================//
//Where Clauses AVLTrees, RBTrees, BTrees
//===============================================================//

//================ Where Clause RBTree ================//

template <class data>
void WhereClause(AVLTree<Field<data>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string operation = GetData(clause, index), field, Specific, key;
	field = GetWhereData(clause, index);
	key = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	for (int i = 0; i < 3; i++)
		Specific = GetWhereData(clause, index);

	if (CompareStr(operation, "point-search"))
		PointSearchAVLD(Tree, key, field, Specific);
	else cout << "Operation " << operation << " Unavailable" << endl;
}

void WhereClause(AVLTree<Field<string>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string operation = GetData(clause, index), field, Specific, key;
	field = GetWhereData(clause, index);
	key = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	for (int i = 0; i < 3; i++)
		Specific = GetWhereData(clause, index);

	if (CompareStr(operation, "point-search"))
		PointSearchAVLS(Tree, key, field, Specific);
	else cout << "Operation " << operation << " Unavailable" << endl;
}

//================ Where Clause RBTree ================//
template <class data>
void WhereClause(RBTree<Field<data>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string operation = GetData(clause, index), field, Specific, key;
	field = GetWhereData(clause, index);
	key = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	for (int i = 0; i < 3; i++)
		Specific = GetWhereData(clause, index);

	if (CompareStr(operation, "point-search"))
		PointSearchRBD(Tree, key, field, Specific);
	else cout << "Operation " << operation << " Unavailable" << endl;
}

void WhereClause(RBTree<Field<string>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string operation = GetData(clause, index), field, Specific, key;
	field = GetWhereData(clause, index);
	key = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	for (int i = 0; i < 3; i++)
		Specific = GetWhereData(clause, index);

	if (CompareStr(operation, "point-search"))
		PointSearchRBS(Tree, key, field, Specific);
	else cout << "Operation " << operation << " Unavailable" << endl;
}

//================ Where Clause BTree ================//
template <class data>
void WhereClause(BTree<Field<data>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string operation = GetData(clause, index), field, Specific, key;
	field = GetWhereData(clause, index);
	key = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	for (int i = 0; i < 3; i++)
		Specific = GetWhereData(clause, index);

	if (CompareStr(operation, "point-search"))
		PointSearchBTD(Tree, key, field, Specific);
	else cout << "Operation " << operation << " Unavailable" << endl;
}

void WhereClause(BTree<Field<string>>*& Tree, const string& clause)
{
	int index = 0, FieldNumber;
	string operation = GetData(clause, index), field, Specific, key;
	field = GetWhereData(clause, index);
	key = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	field = GetWhereData(clause, index);
	for (int i = 0; i < 3; i++)
		Specific = GetWhereData(clause, index);

	if (CompareStr(operation, "point-search"))
		PointSearchBTS(Tree, key, field, Specific);
	else cout << "Operation " << operation << " Unavailable" << endl;
}
//===============================================================//
//Index Generators AVLTrees, RBTrees, BTrees
//===============================================================//

//Generates AVLTree Index
template <class datatype>
void GenerateIndex(AVLTree<Field<datatype>>*& Tree, const string required, const int TotalFiles)
{
	ifstream file;
	int DataOffset, CommaCount = 0;
	Tree = new AVLTree<Field<datatype>>(required);
	string FileNo = "0", Extension = ".csv", Filename, Dataline;

	file.open("IndexTrees/AVLTree_" + required + ".csv");
	if (!file.fail()) 	if (!file.fail()) {file.close();
	cout << endl << "\t\t\t\t Tree Already Created with the Given Index..." << endl;
	Tree->LoadTree(); return;}

	for (int FileCount = 0; FileCount < TotalFiles; FileCount++)
	{
		IncrementFileNumber(FileNo);
		Filename = BasePath;
		Filename += FileNo + Extension;

		file.open(Filename, ios::in);
		if (file.fail())
		{
			cout << "Unable to Open File :" << Filename << endl;
			return;
		}
		getline(file, Dataline);
		CommaCount = ExtractFieldNumber(Dataline, required);

		DataOffset = 1;
		while (!file.eof())
		{
			getline(file, Dataline);
			if (!IsEmpty(Dataline))
			Tree->Insert(GetDesiredField<datatype>(Dataline, DataOffset++, FileNo, CommaCount, datatype()));
		}
		file.close();
	}
	cout << endl << "\t\t\t\t\t Index Generated..." << endl;

	Tree->SaveTree();

	cout << "\t\t\t\t\t Tree Saved..." << endl;
}

//Generates RBTree Index
template <class datatype>
void GenerateIndex(RBTree<Field<datatype>>*& Tree, const string required, const int TotalFiles)
{
	ifstream file;
	int DataOffset, CommaCount = 0;
	Tree = new RBTree<Field<datatype>>(required);
	string FileNo = "0", Extension = ".csv", Filename, Dataline;

	file.open("IndexTrees/RBTree_" + required + ".csv");
	if (!file.fail()) 	if (!file.fail()) {file.close();
	cout << endl << "\t\t\t\t Tree Already Created with the Given Index..." << endl;
	Tree->LoadTree(); return;}

	for (int FileCount = 0; FileCount < TotalFiles; FileCount++)
	{
		IncrementFileNumber(FileNo);
		Filename = BasePath;
		Filename += FileNo + Extension;

		file.open(Filename, ios::in);
		if (file.fail())
		{
			cout << "Unable to Open File :" << Filename << endl;
			return;
		}
		getline(file, Dataline);
		CommaCount = ExtractFieldNumber(Dataline, required);

		DataOffset = 1;
		while (!file.eof())
		{
			getline(file, Dataline);
			if (!IsEmpty(Dataline))
			Tree->Insert(GetDesiredField<datatype>(Dataline, DataOffset++, FileNo, CommaCount, datatype()));
		}
		file.close();
	}
	cout << endl << "\t\t\t\t\t Index Generated..." << endl;

	Tree->SaveTree();

	cout << "\t\t\t\t\t Tree Saved..." << endl;
}

//Generates BTree Index
template <class datatype>
void GenerateIndex(BTree<Field<datatype>>*& Tree, const int Order,const string required, const int TotalFiles)
{
	ifstream file;
	int DataOffset, CommaCount = 0;
	Tree = new BTree<Field<datatype>>(Order,required);
	string FileNo = "0", Extension = ".csv", Filename, Dataline;

	file.open("IndexTrees/BTree_" + required + ".csv");
	if (!file.fail()) 	if (!file.fail()) { file.close();
	cout << endl << "\t\t\t\t Tree Already Created with the Given Index..."<< endl;
	Tree->LoadTree();return;}

	for (int FileCount = 0; FileCount < TotalFiles; FileCount++)
	{
		IncrementFileNumber(FileNo);
		Filename = BasePath;
		Filename += FileNo + Extension;

		file.open(Filename, ios::in);
		if (file.fail())
		{
			cout << "Unable to Open File :" << Filename << endl;
			return;
		}
		getline(file, Dataline);
		CommaCount = ExtractFieldNumber(Dataline, required);

		DataOffset = 1;
		while (!file.eof())
		{
			getline(file, Dataline);
			Tree->Insert(GetDesiredField<datatype>(Dataline, DataOffset++, FileNo, CommaCount, datatype()));
		}
		file.close();
	}
	cout << endl << "\t\t\t\t\t Index Generated..." << endl;

	Tree->SaveTree();

	cout << "\t\t\t\t\t Tree Saved..." << endl;
}

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#define BasePath "DataFiles/NCHS_-_Leading_Causes_of_Death__United_States_";


void GotoLine(fstream& file, const int lineno)
{
	string str;
	file._Seekbeg;
	for (int i = 0; i < lineno; i++)
		getline(file, str);
}

bool IsEmpty(const string& str)
{
	int len = str.length();
	for (int i = 0; i < len-1 && i < 5; i++)
		if (str[i] != ' ')
			return false;
	return true;
}

void AppendClearStr(string& str, const int times)
{
	for (int i = 0; i < times; i++)
		str += " ";
}

template <class data >
class Field {
public:
	data Data;
	string fileNo;
	int lineNo;

	Field() : lineNo(-1), fileNo(""), Data(data()){}
	Field(const data val, const int Ln = -1, const string fn = "") : lineNo(Ln), fileNo(fn), Data(val){}
	Field(const Field<data>& Other) : lineNo(Other.lineNo), fileNo(Other.fileNo), Data(Other.Data) {}

	void operator=(const Field& Other)
	{
		Data = Other.Data;
		fileNo = Other.fileNo;
		lineNo = Other.lineNo;
	}
	bool operator>(const Field& Other) const
	{
		return this->Data > Other.Data;
	}
	bool operator<(const Field& Other) const
	{
		return this->Data < Other.Data;
	}
	bool operator==(const Field& Other) const
	{
		return this->Data == Other.Data;
	}
	bool operator<=(const Field& Other) const
	{
		return this->Data <= Other.Data;
	}
	bool operator>=(const Field& Other) const
	{
		return this->Data >= Other.Data;
	}
	bool MatchAll(const Field<data>& Other) const
	{
		return (this->Data == Other->Data &&
			this->fileNo == Other->fileNo &&
			this->LineNo == Other->LineNo);
	}
	string ClearString(const int index)
	{
		string res;
		for (int i = 0; i < index; i++)
			res += ' ';
		return res;
	}
	void Overwrite(string NewValue = "")
	{
		int LineSize, LineStart;
		string Dataline, filename = BasePath;
		filename += fileNo + ".csv";
		fstream file(filename, ios::in | ios::out);

		if (file.fail()) { cout << "Unable to Open File for Overwriting\n"; return; }

		GotoLine(file, lineNo);
		LineStart = file.tellp();
		getline(file, Dataline);
		LineSize = Dataline.size();

		if (NewValue == "") NewValue = ClearString(LineSize);
		if (NewValue.size() < LineSize) AppendClearStr(NewValue, LineSize - NewValue.size());

		file.seekp(LineStart);
		file.write(NewValue.c_str(), NewValue.size());

		file.close();
	}
	string ReadTuple()
	{
		string Dataline, filename = BasePath;
		filename += fileNo + ".csv";

		fstream file(filename, ios::in);
		if (file.fail())
		{
			cout << "Unable to Open File for Tuple Reading : " << filename << endl;
			return "";
		}

		GotoLine(file, lineNo);
		getline(file, Dataline);
		file.close();
		return Dataline;
	}
};

template <class data>
void ReadData(const Field<data>& Res, string& str)
{
	string Dataline,
		filename = "DataFiles/NCHS_-_Leading_Causes_of_Death__United_States_" + Res.fileNo + ".csv";

	fstream file(filename, ios::in);
	if (file.fail())
	{
		cout << "Unable to Open File : " << filename << endl;
		return;
	}

	GotoLine(file, Res.lineNo);
	getline(file, str);
	file.close();
}

string GetData(string line, int& index)
{
	string res;
	bool Quotation = false;

	if (index >= line.length())
		return "";
	while (line[index] != '\0' && line[index] != '\n' && index < line.length())
	{
		if (line[index] == ',' && !Quotation) break;
		else if (line[index] == '\"' && !Quotation) Quotation = true;
		else if (line[index] == '\"' && Quotation) Quotation = false;
		else res += line[index];
		index++;
	}

	index++;
	return res;
}

template <class data>
ostream& operator<<(ostream& output, const Field<data>& Res)
{
	//cout << Res.Data;
	//return output;

	string res;
	ReadData(Res, res);

	if (IsEmpty(res))
	{	cout << "Record Not Found\n"; return output;}

	int index = 0;
	string str = GetData(res, index);
	output << "ID : " << str << "\n";
	str = GetData(res, index);
	output << "Year : " << str << "\n";
	str = GetData(res, index);
	output << "113 Cause-Name : " << str << "\n";
	str = GetData(res, index);
	output << "Cause Name : " << str << "\n";
	str = GetData(res, index);
	output << "State : " << str << "\n";
	str = GetData(res, index);
	output << "Deaths : " << str << "\n";
	str = GetData(res, index);
	output << "Age-adjusted Death Rate : " << str << "\n";

	return output;
}

class FieldTable {
public:
	int Total;
	string* Table;
	FieldTable() { Total = 0; Table = nullptr; }
	FieldTable(const string& line, const int count) : Total(count)
	{
		Table = new string[Total];
		for (int i = 0, index = 0; i < count; i++)
			Table[i] = GetData(line, index);
	}
	FieldTable(const FieldTable& Other)
	{
		this->Total = Other.Total;
		Table = new string[Total];
		for (int i = 0; i < Total; i++)
			Table[i] = Other.Table[i];
	}
	const string operator=(const int i)
	{	return Table[i];}
	void DisplayTable()
	{
		for (int i = 0; i < Total; i++)
			cout << Table[i] << endl;
	}
};

const int TotalFields(const string& str)
{
	int count = 1;
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] == ',') count++;
	return count++;
}

FieldTable* GenerateFieldMap()
{
	string filename = BasePath;
	fstream file(filename + "1.csv", ios::in);
	getline(file, filename);
	FieldTable* Table = new FieldTable(filename, TotalFields(filename));
	file.close();
	return Table;
}

string GetWhereData(string line, int& index)
{
	string res;
	bool Quotation = false;

	if (index >= line.length())
		return "";
	while (line[index] != '\0' && line[index] != '\n' && index < line.length())
	{
		if (line[index] == ',' && !Quotation) break;
		else if (line[index] == ' ') break;
		else if (line[index] == '=') break;
		else if (line[index] == '\"' && !Quotation) Quotation = true;
		else if (line[index] == '\"' && Quotation) Quotation = false;
		else res += line[index];
		index++;
	}

	index++;
	return res;
}

string CreateUpdateData(string line, int& index)
{
	string res;
	bool Quotation = false;

	if (index >= line.length())
		return "";
	while (line[index] != '\0' && line[index] != '\n' && index < line.length())
	{
		if (line[index] == ',' && !Quotation) break;
		else if (line[index] == '\"' && !Quotation) { Quotation = true; res += line[index]; }
		else if (line[index] == '\"' && Quotation) { Quotation = false; res += line[index]; }
		else res += line[index];
		index++;
	}

	index++;
	return res;
}
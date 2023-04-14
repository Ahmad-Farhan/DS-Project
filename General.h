#pragma once
#include "Datafield.h"

string RevString(const string& str)
{
	string res;
	for (int i = str.length() - 1; i >= 0; i--)
		res += str[i];
	return res;
}

const int StrToInt(string& str)
{
	int res = 0;
	for (int i = 0; i < str.length(); i++)
		res = (res * 10) + (str[i] - 48);
	str = "";
	return res;
}

const string IntToStr(int Num)
{
	string res;
	while (Num != 0)
	{
		res += (Num % 10) + 48;
		Num /= 10;
	}
	return RevString(res);
}

const string FloatToStr(double Val)
{
	int Num = Val;
	string res;
	while (Num != 0)
	{
		res += (Num % 10) + 48;
		Num /= 10;
	}
	if (Val == double(Num))
		return RevString(res);
	
	res += '.' + ((Val - double(Num)) * 10) + 48;
	return RevString(res);
}

const int pow(const int Val, int times)
{
	int res = Val;
	while (times-- != 0)
		res *= Val;
	return res;
}

const double StrToFloat(string& str)
{
	int index;
	double res = 0;
	for (index = 0; index < str.length() && str[index] != '.'; index++)
		res = (res * 10) + (str[index] - 48);
	
	if (str[index] == '.')
		for (int i = 1; index < str.length(); i++)
			res += (str[index++] - 48) / pow(10, i);

	str = "";
	return res;
}

void IncrementFileNumber(string& Fn)
{
	int Num = StrToInt(Fn);
	Num++;
	Fn = IntToStr(Num);
}

bool CompareStr(const string& str1, const string& str2)
{
	if (str1.length() != str2.length())
		return false;

	int size = str1.length();
	for (int i = 0; i < size; i++)
		if (str1[i] != str2[i])
			return false;
	return true;
}

bool IsString(const string& str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] == ' ')
			return true;
	return false;
}

template <class data>
const data ConvertFromStr(const string& str)
{
	stringstream ss(str);
	data Num;
	ss >> Num;
	return Num;
}

template <class data>
const string ConvertToStr(const data num)
{
	stringstream ss;
	ss << num;
	string strNum = ss.str();
	return strNum;
}

template <class data>
const Field<data> GetDesiredField(string line, const int lineNo, const string FileNo, const int CommaCount, const data)
{
	string Id; bool Quotation = false;
	for (int i = 0, count = 0; line[i] != '\0'; i++)
		if (line[i] == ',' && !Quotation)
			if (++count == CommaCount) break;
			else Id = "";
		else if (line[i] == '\"' && !Quotation) Quotation = true;
		else if (line[i] == '\"' && Quotation) Quotation = false;
		else Id += line[i];
	
	const Field<data> Node(ConvertFromStr<data>(Id), lineNo, FileNo);
	return Node;
}

template <class data>
const Field<string> GetDesiredField(string line, const int lineNo, const string FileNo, const int CommaCount, const string)
{
	string Id; bool Quotation = false;
	for (int i = 0, count = 0; line[i] != '\0'; i++)
		if (line[i] == ',' && !Quotation)
			if (++count == CommaCount) break;
			else Id = "";
		else if (line[i] == '\"' && !Quotation) Quotation = true;
		else if (line[i] == '\"' && Quotation) Quotation = false;
		else Id += line[i];

	const Field<string> Node(Id, lineNo, FileNo);
	return Node;
}

string CurrFieldEntry(string line, const int CommaCount)
{
	string Id; bool Quotation = false;
	for (int i = 0, count = 0; line[i] != '\0'; i++)
		if (line[i] == ',' && !Quotation)
			if (++count == CommaCount) break;
			else Id = "";
		else if (line[i] == '\"' && !Quotation) Quotation = true;
		else if (line[i] == '\"' && Quotation) Quotation = false;
		else Id += line[i];

	return Id;
}

template<class data>
std::string CreateRecord(const Field<data>& Node)
{
	std::string res = ConvertToStr(Node.Data) + ',' + Node.fileNo + ',' + ConvertToStr(Node.lineNo) + '\n';
	return res;
}

std::string CreateRecord(const Field<string>& Node)
{
	std::string res = Node.Data + ',' + Node.fileNo + ',' + ConvertToStr(Node.lineNo) + '\n';
	return res;
}

Field<string> CreateLoadNode(const string& Dataline, const string& type)
{
	int index = 0;
	string KeyVal = GetData(Dataline, index);
	string Fileno = GetData(Dataline, index);
	string lineNo = GetData(Dataline, index);
	const Field<string> Node(KeyVal, StrToInt(lineNo), Fileno);
	return Node;
}

template <class data>
Field<data> CreateLoadNode(const string& Dataline, const data& type)
{
	int index = 0;
	string KeyVal = GetData(Dataline, index);
	string Fileno = GetData(Dataline, index);
	string lineNo = GetData(Dataline, index);
	const Field<data> Node(ConvertFromStr<data>(KeyVal), StrToInt(lineNo), Fileno);
	return Node;
}

const int ExtractFieldNumber(const string& Dataline, const string& required)
{
	int index = 0;
	string test;
	for (int count = 0; index < Dataline.length(); count++)
	{
		test = GetData(Dataline, index);
		if (CompareStr(test, required))
			return ++count;
	}
	return (-1);
}
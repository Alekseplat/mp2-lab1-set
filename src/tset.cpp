// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField((s.MaxPower))
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0) throw - 4;
	if (Elem < MaxPower) return BitField.GetBit(Elem);
	return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem > MaxPower) throw - 5;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 || Elem > MaxPower) throw - 5;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this == &s) return *this;
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower && BitField == s.BitField) return 1;
	return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower && BitField == s.BitField) return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	if (MaxPower > s.MaxPower)
	{
		TBitField _check_(MaxPower);
		for (int i = 0; i < MaxPower; i++)
		{
			if (IsMember(i) || s.IsMember(i))
				_check_.SetBit(i);
		}
		return _check_;
	}
	TBitField _check_(s.MaxPower);
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (IsMember(i) || s.IsMember(i))
			_check_.SetBit(i);
	}
	return _check_;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem > MaxPower) throw - 5;
	TBitField _check_(BitField);
	_check_.SetBit(Elem);
	return _check_;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 || Elem > MaxPower) throw - 5;
	TBitField _check_(BitField);
	_check_.ClrBit(Elem);
	return _check_;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	if (MaxPower > s.MaxPower)
	{
		TBitField _check_(MaxPower);
		for (int i = 0; i < MaxPower; i++)
		{
			if (IsMember(i) && s.IsMember(i))
				_check_.SetBit(i);
		}
		return _check_;
	}
	TBitField _check_(s.MaxPower);
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (IsMember(i) && s.IsMember(i))
			_check_.SetBit(i);
	}
	return _check_;
}

TSet TSet::operator~(void) // дополнение
{

	TBitField _check_(BitField);
	_check_ = ~_check_;
	return _check_;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	cin >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << s.BitField;
	return ostr;
}

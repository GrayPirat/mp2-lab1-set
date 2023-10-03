// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля

#include <iostream>
#include "tbitfield.h"
#include "tset.h"

struct OutIndException {
    int a;
};

TSet::TSet(size_t mp) : bitField(mp) {
    maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : bitField(s.bitField) {
    maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : bitField(bf) {}

TSet::operator TBitField()
{
    return TBitField(1);
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return maxPower;
}

bool TSet::isMember(const uint elem) const // элемент множества?
{
    if (bitField.getBit(elem))
        return true;
    return false;
}

void TSet::insElem(const uint elem) // включение элемента множества
{
    bitField.setBit(elem);
}

void TSet::delElem(const uint elem) // исключение элемента множества
{
    bitField.clrBit(elem);
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (this != &s) {
        TBitField nul(s.maxPower);
        maxPower = s.maxPower;
        bitField = bitField & nul;
        for (int i = 0; i < maxPower; i++) {
            if (s.bitField.getBit(i)) {
                bitField.setBit(i);
            }
        }
    }
    return *this;
}

bool TSet::operator==(const TSet& s) const // сравнение
{
    if (maxPower == s.maxPower) {
        for (int i = 0; i < maxPower; i++) {
            if (bitField.getBit(i) != s.bitField.getBit(i)) {
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

bool TSet::operator!=(const TSet& s) const // сравнение
{
    if (this == &s) {
        return false;
    }
    return true;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    if (maxPower > s.maxPower) {
        bitField = bitField | s.bitField;
        return *this;
    }
    else {
        maxPower = s.maxPower;
        bitField = bitField | s.bitField;
        return *this;
    }
    /*if (maxPower == s.maxPower) {
        TSet temp(s.maxPower);
        maxPower = s.maxPower;
        for (int i = 0; i < s.maxPower; i++) {
            if (bitField.getBit(i) || s.bitField.getBit(i)) {
                temp.bitField.setBit(i);
            }
        }
        return temp;
    }
    else {
        if (maxPower > s.maxPower) {
            TSet temp(maxPower);
            //maxPower = s.maxPower;
            for (int i = 0; i < s.maxPower; i++) {
                if (bitField.getBit(i) || s.bitField.getBit(i)) {
                    temp.bitField.setBit(i);
                }
            }
            for (int i = s.maxPower; i < maxPower; i++) {
                if (bitField.getBit(i))
                    temp.bitField.setBit(i);
            }
            return temp;
        }
        else {
            TSet temp(s.maxPower);
            //maxPower = s.maxPower;
            for (int i = 0; i < maxPower; i++) {
                if (bitField.getBit(i) || s.bitField.getBit(i)) {
                    temp.bitField.setBit(i);
                }
            }
            for (int i = maxPower; i < s.maxPower; i++) {
                if (s.bitField.getBit(i))
                    temp.bitField.setBit(i);
            }
            return temp;
        }
    }*/
}

TSet TSet::operator+(const uint elem) // объединение с элементом
{
    if (elem > maxPower - 1) {
        throw OutIndException();
    }
    insElem(elem);
    return *this;

}

TSet TSet::operator-(const uint elem) // разность с элементом
{
    if (elem > maxPower - 1) {
        throw OutIndException();
    }
    delElem(elem);
    return *this;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    if (maxPower > s.maxPower) {
        TSet temp(s.maxPower);
        temp.maxPower = maxPower;
        temp.bitField = bitField & s.bitField;
        return temp;
    }
    else {
        TSet temp(maxPower);
        temp.maxPower = s.maxPower;
        temp.bitField = bitField & s.bitField;
        return temp;
    }
}

TSet TSet::operator~() // дополнение
{
    TSet temp(maxPower);
    for (int i = 0; i < maxPower; i++) {
        if (!isMember(i)) {
            temp.insElem(i);
        }
    }
    return temp;
}

// перегрузка ввода/вывода
std::istream& operator>>(std::istream& istr, TSet& s) // ввод
{
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s) // вывод
{
    return ostr;
}

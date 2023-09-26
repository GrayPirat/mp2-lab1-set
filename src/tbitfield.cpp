// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"

struct OutOfIndException {
    int a;
};

TBitField::TBitField(size_t len)
{
    bitLen = len;
    if (len == 0) {
        memLen = 0;
    }
    else {
        bitLen% sizik == 0 ? memLen = bitLen / sizik : memLen = bitLen / sizik + 1;
    }
    
    pMem = new uint[memLen];
    for (size_t i = 0; i < memLen; i++) {
        pMem[i] = pMem[i] & 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    //delete[] pMem;
    memLen = bf.memLen;
    bitLen = bf.bitLen;
    pMem = new uint[memLen];
    for (size_t i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    return n/sizik;
}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    uint a = 0;
    return a|(1<<(n%sizik));
}

// доступ к битам битового поля
uint TBitField::getLength() const // получить длину (к-во битов)
{
    return bitLen;
}

size_t TBitField::getNumBytes() const // получить количество байт выделенной памяти
{
    return memLen * sizeof(uint);
}

void TBitField::setBit(const size_t n) // установить бит
{
    if (n > bitLen) {
        throw OutOfIndException();
    }
    else {
        pMem[getIndex(n)] |= getMask(n);
    }
}

void TBitField::clrBit(const size_t n) // очистить бит
{
    if (n > bitLen) {
        throw OutOfIndException();
    }
    else {
        pMem[getIndex(n)] &= ~(getMask(n));
    }
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    if (n > bitLen) {
        throw OutOfIndException();
    }
    else {
        bool isbit = (getMask(n)) & pMem[getIndex(n)];
        return isbit;
    }
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    delete pMem;
    memLen = bf.memLen;
    bitLen = bf.bitLen;
    pMem = new uint(bf.memLen);
    for (int i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bitLen == bf.bitLen) {
        for (int i = 0; i < memLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
    /*if (bitLen == bf.bitLen) {
        for (int i = 0; i < memLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                return true;
            }
        }
        return false;
    }
    return true;*/
    if (*this == bf) {
        return false;
    }
    return true;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (bitLen == bf.bitLen) {
        TBitField temp(bitLen);
        for (int i = 0; i < memLen - 1; i++) {
            temp.pMem[i] = pMem[i] | bf.pMem[i];
        }
        for (int i = sizik * (memLen - 1); i < bitLen; i++) {
            if (getBit(i) || bf.getBit(i)) {
                temp.setBit(i);
            }
        }
        return temp;
    }
    else {
        if (bitLen > bf.bitLen) {
            TBitField temp(bitLen);
            for (int i = 0; i < bf.memLen; i++) {
                temp.pMem[i] = pMem[i] | bf.pMem[i];
            }
            for (int i = sizik * (bf.memLen - 1); i < bf.bitLen; i++) {
                if (getBit(i) || bf.getBit(i)) {
                    temp.setBit(i);
                }
            }
            for (int i = bf.bitLen; i < bitLen; i++) {
                if (getBit(i)) {
                    temp.setBit(i);
                }
            }
            return temp;
        }
        else {
            TBitField temp(bf.bitLen);
            for (int i = 0; i < memLen; i++) {
                temp.pMem[i] = pMem[i] | bf.pMem[i];
            }
            for (int i = sizik * (memLen - 1); i < bitLen; i++) {
                if (getBit(i) || bf.getBit(i)) {
                    temp.setBit(i);
                }
            }
            for (int i = bitLen; i < bf.bitLen; i++) {
                if (getBit(i)) {
                    temp.setBit(i);
                }
            }
            return temp;
        }
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (bitLen == bf.bitLen) {
        TBitField temp(bitLen);
        for (int i = 0; i < memLen - 1; i++) {
            temp.pMem[i] = pMem[i] & bf.pMem[i];
        }
        for (int i = sizik * (memLen - 1); i < bitLen; i++) {
            if (getBit(i) && bf.getBit(i)) {
                temp.setBit(i);
            }
        }
        return temp;
    }
    else {
        if (bitLen > bf.bitLen) {
            TBitField temp(bitLen);
            for (int i = 0; i < bf.memLen; i++) {
                temp.pMem[i] = pMem[i] & bf.pMem[i];
            }
            for (int i = sizik * (bf.memLen - 1); i < bf.bitLen; i++) {
                if (getBit(i) && bf.getBit(i)) {
                    temp.setBit(i);
                }
            }
            return temp;
        }
        else {
            TBitField temp(bf.bitLen);
            for (int i = 0; i < memLen; i++) {
                temp.pMem[i] = pMem[i] & bf.pMem[i];
            }
            for (int i = sizik * (memLen - 1); i < bitLen; i++) {
                if (getBit(i) && bf.getBit(i)) {
                    temp.setBit(i);
                }
            }
            return temp;
        }
    }
}

TBitField TBitField::operator~() // отрицание
{
    TBitField temp(memLen);
    for (int i = 0; i < memLen - 1; i++) {
        temp.pMem[i] = ~(pMem[i]);
    }
    for (int i = sizik * (memLen - 1); i < bitLen; i++) {
        if (getBit(i)==0) {
            temp.setBit(i);
        }
    }
    return temp;
}

TBitField::~TBitField()
{
    delete[] pMem;
}

// ввод/вывод
std::istream &operator>>(std::istream &istr, TBitField &bf) // ввод
{
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
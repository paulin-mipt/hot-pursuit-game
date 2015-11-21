#pragma once
#include "stdafx.h"
#include <vector>


const int DEFAULT_SIZE_X = 20;
const int DEFAULT_SIZE_Y = 15;
const int DEFAULT_COLORS_NUMBER = 4;


enum BType {
    BNone,
    BRoad,
    BTree,
    BWall,
    BStart
};


class CMap {
public:
    CMap();
    ~CMap();

    const std::vector< std::vector<int> >& GetNumbers();
    int GetX();
    int GetY();

    //������ ��������� ������ � ������������ (i, j)
    void ClickCell( int i, int j );
    void ClickCell( int i, int j, BType bType );
    //�������� �����
    void RestartMap();
    //������������� ������� ����
    void SetSize( int x, int y );

    void LoadMapFromFile( std::ifstream& );
    void SaveMapToFile( std::ofstream& );

private:
    std::vector< std::vector<int> > numbers;
    int sizeX;
    int sizeY;
    int colorsNumber;
};

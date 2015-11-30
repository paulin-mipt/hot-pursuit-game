#pragma once
#include "stdafx.h"
#include <vector>


const int DEFAULT_SIZE_X = 20;
const int DEFAULT_SIZE_Y = 15;
const int DEFAULT_COLORS_NUMBER = 3;


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

    std::list<std::array<int, 2>> StartLinePoints() { return startLinePoints; }

private:
    std::vector< std::vector<int> > numbers;
    std::list<std::array<int, 2>> startLinePoints;
    int sizeX;
    int sizeY;
    int colorsNumber;
};

#pragma once
#include <iostream>
#include <fstream>


class Util
{
private:
    static int finalScore;
    static std::string fileLocation;
public:
    static void SetFinalScore(int score);

    static int GetFinalScore();

    static std::string ToStringFixedLength(int value, int digits = 3);

    static std::string ConvertShipTexture(int textr);

    static std::string ConvertLifeTexture(int textr);

    static std::string ConvertBulletTexture(int textr);
    
    static void SaveHighScore(int value);

    static int GetHighScore();

    static int shipColor;
};
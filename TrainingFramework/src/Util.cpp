#include "Util.h"

int Util::finalScore;
int Util::shipColor;
std::string Util::fileLocation = "meta.txt";

void Util::SetFinalScore(int score)
{
	Util::finalScore = score;
}

int Util::GetFinalScore()
{
    return finalScore;
}

std::string Util::ToStringFixedLength(int value, int digits)
{
    unsigned int uvalue = value;
    if (value < 0) {
        uvalue = -uvalue;
    }
    std::string result;
    while (digits-- > 0) {
        result += ('0' + uvalue % 10);
        uvalue /= 10;
    }
    if (value < 0) {
        result += '-';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string Util::ConvertShipTexture(int textr)
{
    if (textr == 0)
        return "playerShip3_blue";
    if (textr == 1)
        return "playerShip3_red";
    if (textr == 2)
        return "playerShip3_green";
    if (textr == 3)
        return "playerShip3_orange";
}

std::string Util::ConvertLifeTexture(int textr)
{
    if (textr == 0)
        return "playerLife3_blue";
    if (textr == 1)
        return "playerLife3_red";
    if (textr == 2)
        return "playerLife3_green";
    if (textr == 3)
        return "playerLife3_orange";
}

std::string Util::ConvertBulletTexture(int textr)
{
    if (textr == 0)
        return "laserBlue02";
    if (textr == 1)
        return "laserRed02";
    if (textr == 2)
        return "laserGreen04";
    if (textr == 3)
        return "laserRed02";
}

void Util::SaveHighScore(int value)
{
    std::ofstream wf(fileLocation);
    if (!wf)
    {
        std::cout << "Cannot open file!" << std::endl;
        return;
    }

    wf << value;
    wf.close();

    if (!wf.good()) {
        std::cout << "Error occurred at writing time!" << std::endl;
        return;
    }
}

int Util::GetHighScore()
{
    std::ifstream rf(fileLocation);
    if (!rf) {
        std::cout << "Cannot open file!" << std::endl;
        return 0;
    }

    int score = 0;
    rf >> score;
    return score;
}
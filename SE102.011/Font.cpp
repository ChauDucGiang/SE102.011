#include "Font.h"

void CFont::Render() {
    int aniId = -1;
    switch (num) {
    case 0:
        aniId = ID_ANI_0;
        break;
    case 1:
        aniId = ID_ANI_1;
        break;
    case 2:
        aniId = ID_ANI_2;
        break;
    case 3:
        aniId = ID_ANI_3;
        break;
    case 4:
        aniId = ID_ANI_4;
        break;
    case 5:
        aniId = ID_ANI_5;
        break;
    case 6:
        aniId = ID_ANI_6;
        break;
    case 7:
        aniId = ID_ANI_7;
        break;
    case 8:
        aniId = ID_ANI_8;
        break;
    default:
        aniId = ID_ANI_9;
    }
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

std::vector<int> CFont::GetDigits(int num) {
    std::vector<int> digits;
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
}

void CFont::DrawNumber(int num, float startX, float startY) {
    std::vector<int> digits = GetDigits(num);
    for (int digit : digits) {
        //new CFont(startX, startY, digit);
    }
}


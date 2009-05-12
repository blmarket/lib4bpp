#include "TrueSight.h"

void TrueSight::CalcClipArea(const Line &wall)
{
    Vector2 vec1,vec2;
    vec1 = wall.s - m_Viewer;
    vec2 = wall.e - m_Viewer;

    float ang1 = vec1.angle(),ang2 = vec2.angle();
    vec1.normalize();
    vec2.normalize();

    Vector2 far1,far2;
    far1 = m_Viewer + vec1 * m_SightRadius;
    far2 = m_Viewer + vec2 * m_SightRadius;
}

int main(void)
{
    return 0;
}

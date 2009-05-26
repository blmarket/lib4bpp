using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace DxLib
{
    public class Shadow
    {
        struct Wall
        {
            int wallid; // 실제 wall의 element 번호? 쯤이라고 생각해.
            float dist; // wall이 존재하는 거리
            float angle; // wall의 각도            
        }

        List<Wall> m_Walls = new List<Wall>();

        public Shadow()
        {
        }

        void addit(float d1, float a1, float d2, float a2)
        {
        }

        public void AddWall(Vector2 p1, Vector2 p2)
        {
            double angle1, angle2;
            angle1 = Math.Atan2(p1.Y, p1.X);
            angle2 = Math.Atan2(p2.Y, p1.Y);
            double adiff = angle2 - angle1;
            if (adiff < 0) adiff += Math.PI * 2.0;
            if (adiff > Math.PI)
            {
                Vector2 tmp = p2; p2 = p1; p1 = tmp;
                double tmp2 = angle1; angle1 = angle2; angle2 = tmp2;
            }
            if (angle1 < 0) angle1 += Math.PI * 2.0;
            if (angle2 < 0) angle2 += Math.PI * 2.0;
            if (angle2 < angle1)
            {
                float tmp = (p1.X * p2.Y - p1.Y * p2.X) / (p2.Y - p1.Y);
                addit(tmp, 0.0f, p2.Length(), (float)angle2);
                addit(p1.Length(), (float)angle1, tmp, (float)Math.PI * 2.0f);
            }
        }
    }
}

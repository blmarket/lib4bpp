using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace DxLib
{
    namespace Geometry2D
    {
        /// <summary>
        /// Ax + By = C 형식의 Line을 표현
        /// </summary>
        struct Line
        {
            /// <summary>
            ///  두 개의 점으로부터 Line을 생성. p1과 p2는 직선을 지나는 두개의 점
            /// </summary>
            public Line(Vector2 p1, Vector2 p2)
            {
                A = p2.Y - p1.Y;
                B = p1.X - p2.X;
                C = p1.X * p2.Y - p1.Y * p2.X;
            }

            /// <summary>
            /// (0,0)을 지나고 각도 angle인 직선과 교차하는 점을 return함.
            /// </summary>
            public Vector2 GetIntersection(double angle)
            {
                float a = (float)Math.Cos(angle);
                float b = (float)Math.Sin(angle);
                return new Vector2((a * C) / (A * a + B * b), (b * C) / (A * a + B * b));
            }

            float A, B, C;
        }
    }
}

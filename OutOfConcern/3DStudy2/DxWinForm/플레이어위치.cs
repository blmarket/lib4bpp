using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Text;
using Microsoft.DirectX.Direct3D;
using Microsoft.DirectX;

namespace DxLib
{
    public class 플레이어위치
    {
        public 플레이어위치()
        {
        }

        public Matrix getWorldMatrix()
        {
            return Matrix.Translation(pos.X,0,pos.Y);
        }

        public Matrix getShadowWorldMatrix()
        {
            Matrix shadow = Matrix.Identity;
            shadow.M22 = 0;
            shadow.M24 = -0.99999f;

            return Matrix.Translation(pos.X, 0, pos.Y) * shadow;
        }

        public override string ToString()
        {
            return base.ToString() + " X : " + pos.X + " Y : " + pos.Y;
        }

        public Vector2 pos = new Vector2();
    }

    public class 커서위치
    {
        public 커서위치() { }

        public Point m_MousePoint;
        public Rectangle m_ClientRectangle;

        public override string ToString()
        {
            return base.ToString() + " X : " + m_MousePoint.X + " Y : " + m_MousePoint.Y;
        }
    }
}
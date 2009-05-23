using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX.Direct3D;
using Microsoft.DirectX;

namespace DxLib
{
    public class 플레이어위치
    {
        public 플레이어위치()
        {
            pos.X = 3.0f;
        }

        public Matrix getWorldMatrix()
        {
            return Matrix.Translation(pos.X,0,pos.Y);
        }

        public override string ToString()
        {
            return base.ToString() + "\nX : " + pos.X + " Y : " + pos.Y;
        }

        public Vector2 pos = new Vector2();
    }
}

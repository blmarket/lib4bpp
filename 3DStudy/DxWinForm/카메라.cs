using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace DxLib
{
    public class 카메라
    {
        public override string ToString()
        {
            return base.ToString() + "(" + m_Position.ToString() + ")";
        }

        public string getPicking(Point pos, Rectangle rt)
        {
            Vector3 v = new Vector3(0, 0, 1);
            v.X = (((((pos.X - rt.Left) * 2.0f / rt.Right) - 1.0f)) - m_Projection.M31) / m_Projection.M11;
            v.Y = ((-(((pos.Y - rt.Top) * 2.0f / rt.Bottom) - 1.0f)) - m_Projection.M32) / m_Projection.M22;
            Matrix inv = Matrix.Invert(m_View);

            Vector3 orig, dir;
            orig = new Vector3(inv.M41, inv.M42, inv.M43);
            dir = new Vector3(
                v.X * inv.M11 + v.Y * inv.M21 + v.Z * inv.M31,
                v.X * inv.M12 + v.Y * inv.M22 + v.Z * inv.M32,
                v.X * inv.M13 + v.Y * inv.M23 + v.Z * inv.M33);

            return v.ToString() + orig + dir;
        }

        public 카메라()
        {
            m_View = Matrix.LookAtLH(new Vector3(5, 15, -5), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
            m_Projection = Matrix.PerspectiveFovLH((float)Math.PI / 4, 1.0f, 0.1f, 100.0f);
        }

        public Matrix m_World
        {
            get
            {
                return m_Position.getWorldMatrix();
            }
        }

        public Matrix m_ShadowWorld
        {
            get
            {
                return m_Position.getShadowWorldMatrix();
            }
        }

        public Matrix m_View;
        public Matrix m_Projection;

        public 플레이어위치 m_Position = new 플레이어위치();
    }
}

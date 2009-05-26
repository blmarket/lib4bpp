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

        public Vector2 getPicking(Point pos, Viewport Viewport)
        {
            Vector3 v1 = new Vector3(pos.X, pos.Y, 1);
            Vector3 v2 = new Vector3(pos.X, pos.Y, 0);
            v1.Unproject(Viewport, m_Projection, m_View, Matrix.Identity);
            v2.Unproject(Viewport, m_Projection, m_View, Matrix.Identity);
            Vector3 v3 = v2 - v1;
            v3.Scale(1.0f/v3.Y);
            Vector3 v4 = v1 - v3 * v1.Y; // Y 값이 0이 되는 방정식 계산.

            return new Vector2(v4.X, v4.Z);
        }

        public 카메라()
        {
            m_View = Matrix.LookAtLH(new Vector3(5, 15, -5), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
            m_Projection = Matrix.PerspectiveFovLH((float)Math.PI / 4, 1.0f, 0.1f, 100.0f);
            m_Projection = Matrix.OrthoLH(5, 5, 0.1f, 100.0f);
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

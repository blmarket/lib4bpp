using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

        public string getPIcking(Vector2 pos)
        {
            Vector4 vec1 = new Vector4(pos.X, pos.Y, 0.1f, 1.0f);
            Vector4 vec2 = new Vector4(pos.X, pos.Y, 100.0f, 1.0f);
            Matrix ViewProjection = m_View * m_Projection;
            Matrix invViewProjection = Matrix.Invert(m_View * m_Projection);
            vec1.Transform(invViewProjection);
            vec1.Scale(1.0f / vec1.W);
            vec2.Transform(invViewProjection);
            vec2.Scale(1.0f / vec2.W);
            Vector2 vec3 = new Vector2();
            float zdiff = vec2.Z - vec1.Z;
            float xdiff = vec2.X - vec1.X;
            float ydiff = vec2.Y - vec1.Y;
            vec3.X = vec1.X - (xdiff / zdiff) * vec1.Z;
            vec3.Y = vec1.Y - (ydiff / zdiff) * vec1.Z;
            return vec1.ToString() + vec2 + vec3;
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

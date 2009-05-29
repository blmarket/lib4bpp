﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Drawing;
using DxLib.Geometry2D;

namespace DxLib
{
    public class Shadow2
    {
        public List<Vector2[]> m_Walls = new List<Vector2[]>();

        public Shadow2()
        {
        }

        public void clear()
        {
            m_Walls.Clear();
        }

        void addit(Vector2 p1, Vector2 p2)
        {
            Vector2[] Boundary = new Vector2[4] {
                new Vector2(3,3),
                new Vector2(-3,3),
                new Vector2(-3,-3),
                new Vector2(3,-3),
            };

            float a1 = (float)Math.Atan2(p1.Y, p1.X); 
            if (a1 < 0) a1 += (float)Math.PI * 2;
            float a2 = (float)Math.Atan2(p2.Y, p2.X);
            if (a2 < 0) a2 += (float)Math.PI * 2;
            DxLib.Geometry2D.Line line = new DxLib.Geometry2D.Line(p1,p2);

            int cnt = 2;
            for (int i = 0; i < 4; i++)
            {
                float angle = (float)Math.Atan2(Boundary[i].Y, Boundary[i].X);
                if (angle < 0) angle += (float)Math.PI * 2;
                if (a1 < angle && angle < a2)
                {
                    cnt++;
                }
            }

            Vector2[] Walls = new Vector2[cnt];
            Walls[0] = p1;
            Walls[cnt - 1] = p2;
            cnt = 1;
            for (int i = 0; i < 4; i++)
            {
                float angle = (float)Math.Atan2(Boundary[i].Y, Boundary[i].X);
                if (angle < 0) angle += (float)Math.PI * 2;
                if (a1 < angle && angle < a2)
                {
                    Walls[cnt] = line.GetIntersection(angle);
                    cnt++;
                }
            }

            m_Walls.Add(Walls);
        }

        public void AddWall(Vector2 p1, Vector2 p2)
        {
            double angle1, angle2;
            angle1 = Math.Atan2(p1.Y, p1.X);
            angle2 = Math.Atan2(p2.Y, p2.X);
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
                DxLib.Geometry2D.Line line = new DxLib.Geometry2D.Line(p1, p2);
                Vector2 tmp = line.GetIntersection(0.0);
                addit(tmp, p2);
                addit(p1, tmp);
            }
            else
            {
                addit(p1, p2);
            }
        }

        public override string ToString()
        {
            return base.ToString();
        }

        private VertexBuffer m_VB = null;
        public int m_VertexCount = 0;

        public VertexBuffer BuildShadowVertex(Device dx_device, Vector2 ViewerPos)
        {
            int vc = 0;
            foreach (Vector2[] w in m_Walls)
            {
                for (int i = 0; i < w.Count() - 1; i++)
                {
                    vc += 2;
                }
            }

            if (m_VB != null) m_VB.Dispose();
            m_VB = new VertexBuffer(typeof(CustomVertex.PositionColored), vc * 3, dx_device, Usage.None,
                CustomVertex.PositionColored.Format, Pool.Managed);

            m_VertexCount = vc * 3;

            CustomVertex.PositionColored[] array = (CustomVertex.PositionColored[])m_VB.Lock(0, LockFlags.None);

            for (int i = 0; i < vc * 3; i++)
                array[i].Color = Color.Black.ToArgb();

            vc = 0;
            foreach (Vector2[] w in m_Walls)
            {
                for (int i = 0; i < w.Count() - 1; i++)
                {
                    Vector2 tmp = w[i], tmp2 = w[i + 1];
                    tmp.Normalize(); tmp.Scale(25);
                    tmp2.Normalize(); tmp2.Scale(25);

                    array[vc].X = w[i].X;
                    array[vc].Y = 0;
                    array[vc].Z = w[i].Y;
                    vc++;

                    array[vc].X = w[i + 1].X;
                    array[vc].Y = 0;
                    array[vc].Z = w[i + 1].Y;
                    vc++;

                    array[vc].X = tmp.X;
                    array[vc].Y = 0;
                    array[vc].Z = tmp.Y;
                    vc++;

                    array[vc].X = w[i + 1].X;
                    array[vc].Y = 0;
                    array[vc].Z = w[i + 1].Y;
                    vc++;

                    array[vc].X = tmp2.X;
                    array[vc].Y = 0;
                    array[vc].Z = tmp2.Y;
                    vc++;

                    array[vc].X = tmp.X;
                    array[vc].Y = 0;
                    array[vc].Z = tmp.Y;
                    vc++;
                }
            }
            m_VB.Unlock();
            return m_VB;
        }
    }
}

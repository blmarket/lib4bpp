using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace DxLib
{
    public class Shadow
    {
        public struct Wall
        {
            public Wall(int wd, float d, float a)
            {
                wallid = wd;
                dist = d;
                angle = a;
            }

            public float x 
            { 
                get 
                {
                    return (float)Math.Cos(angle) * dist;
                }
            }

            public float y
            {
                get 
                {
                    return (float)Math.Sin(angle) * dist;
                }
            }

            public int wallid; // 실제 wall의 element 번호? 쯤이라고 생각해.
            public float dist; // wall이 존재하는 거리
            public float angle; // wall의 각도            

            public override string ToString()
            {
                return "" + dist + "+" + angle;
            }
        }

        public List<Wall[]> m_Walls = new List<Wall[]>();

        public Shadow()
        {
        }

        public void clear()
        {
            m_Walls.Clear();
        }

        Vector2 FromAngDist(float angle, float dist)
        {
            return new Vector2(dist * (float)Math.Cos(angle), dist * (float)Math.Sin(angle));
        }

        float getdistforangle(Wall w1, Wall w2, float angle)
        {
            Vector2 v1 = FromAngDist(w1.angle - angle, w1.dist);
            Vector2 v2 = FromAngDist(w2.angle - angle, w2.dist);
            return getinetersecty0(v1, v2);
        }

        void addit(float d1, float a1, float d2, float a2)
        {
            Vector2[] Boundary = new Vector2[4] {
                new Vector2(3,3),
                new Vector2(-3,3),
                new Vector2(-3,-3),
                new Vector2(3,-3),
            };

            int cnt = 2;
            for (int i = 0; i < 4; i++)
            {
                float angle = (float)Math.Atan2(Boundary[i].Y, Boundary[i].X);
                if (a1 < angle && angle < a2)
                {
                    cnt++;
                }
            }

            Wall[] Walls = new Wall[cnt];
            Walls[0] = new Wall(0, d1, a1);
            Walls[cnt-1] = new Wall(0, d2, a2);
            cnt=1;
            for (int i = 0; i < 4; i++)
            {
                float angle = (float)Math.Atan2(Boundary[i].Y, Boundary[i].X);
                if (a1 < angle && angle < a2)
                {
                    float dist = getdistforangle(Walls[0], Walls[Walls.Count()-1], angle);
                    Walls[cnt] = new Wall(0, dist, angle);
                    cnt++;
                }
            }

            m_Walls.Add(Walls);
        }

        float getinetersecty0(Vector2 p1, Vector2 p2)
        {
            return (p1.X * p2.Y - p1.Y * p2.X) / (p2.Y - p1.Y);
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
                float tmp = getinetersecty0(p1, p2);
                addit(tmp, 0.0f, p2.Length(), (float)angle2);
                addit(p1.Length(), (float)angle1, tmp, (float)Math.PI * 2.0f);
            }
            else
            {
                addit(p1.Length(), (float)angle1, p2.Length(), (float)angle2);
            }
        }

        public override string ToString()
        {
            string ret = "";
            for (int i = 0; i < m_Walls.Count; i++)
            {
                ret += m_Walls[i].ToString() + "\n";
            }
            return base.ToString() + ret;
        }

        private VertexBuffer m_VB = null;
        public int m_VertexCount = 0;

        public VertexBuffer BuildShadowVertex(Device dx_device)
        {
            int vc = 0;
            foreach (Wall[] w in m_Walls)
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
            foreach (Wall[] w in m_Walls)
            {
                for (int i = 0; i < w.Count() - 1; i++)
                {
                    Wall tmp = w[i], tmp2 = w[i + 1];
                    tmp.dist += 25;
                    tmp2.dist += 25;

                    array[vc].X = w[i].x;
                    array[vc].Y = 0;
                    array[vc].Z = w[i].y;
                    vc++;

                    array[vc].X = w[i+1].x;
                    array[vc].Y = 0;
                    array[vc].Z = w[i+1].y;
                    vc++;

                    array[vc].X = tmp.x;
                    array[vc].Y = 0;
                    array[vc].Z = tmp.y;
                    vc++;

                    array[vc].X = w[i+1].x;
                    array[vc].Y = 0;
                    array[vc].Z = w[i+1].y;
                    vc++;

                    array[vc].X = tmp2.x;
                    array[vc].Y = 0;
                    array[vc].Z = tmp2.y;
                    vc++;

                    array[vc].X = tmp.x;
                    array[vc].Y = 0;
                    array[vc].Z = tmp.y;
                    vc++;
                }
            }
            m_VB.Unlock();
            return m_VB;
        }
    }
}

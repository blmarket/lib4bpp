using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace DxLib
{
    public class WallHide
    {
        public WallHide(Device dx_device)
        {
        }

        public static WallHide CreateRandomWalls(Device dx_device, int cnt, float minx, float maxx, float miny, float maxy)
        {
            WallHide ret = new WallHide(dx_device);
            Random rand = new Random();

            Vector2[] boundary = new Vector2[4] { 
                    new Vector2(minx,miny),
                    new Vector2(minx,maxy),
                    new Vector2(maxx,miny),
                    new Vector2(maxx,maxy),
                };

            for (int i = 0; i < cnt; i++)
            {
                Vector2 p1, p2;
                p1.X = (float)rand.NextDouble() * (maxx - minx) + minx;
                p1.Y = (float)rand.NextDouble() * (maxy - miny) + miny;
                p2.X = (float)rand.NextDouble() * (maxx - minx) + minx;
                p2.Y = (float)rand.NextDouble() * (maxy - miny) + miny;
                ret.AddWall(p1, p2);
                ret.m_shadow.AddWall(p1, p2);
            }

            return ret;
        }

        public static void test(Device dx_device)
        {
            WallHide wh = new WallHide(dx_device);
            wh.AddWall(new Vector2(0, 0), new Vector2(5, 5));
            wh.AddWall(new Vector2(0, 5), new Vector2(5, 0));
            wh.AddWall(new Vector2(0, 0), new Vector2(5, 0));
            wh.AddWall(new Vector2(0, 5), new Vector2(5, 5));
            wh.AddWall(new Vector2(2.5f, 0), new Vector2(2.5f, 5));
        }

        public void BuildVertexBuffer(Device dx_device, Vector2 ViewerPos)
        {
            // 보이지 않는 벽들을 가려야 할 필요가 있다.
            if (m_VB != null)
            {
                m_VB.Dispose();
                m_VB = null;
            }

            List<Geometry2D.LineSegment> lines = new List<DxLib.Geometry2D.LineSegment>();

            foreach (Geometry2D.LineSegment line in m_Walls)
            {
                Vector2 p1 = line.p1;
                Vector2 p2 = line.p2;
                double angle1, angle2;

                p1 -= ViewerPos;
                p2 -= ViewerPos;

                angle1 = Math.Atan2(p1.Y, p1.X);
                angle2 = Math.Atan2(p2.Y, p2.X);
                double adiff = angle2 - angle1;
                if (adiff < 0) adiff += Math.PI * 2;

                if (adiff > Math.PI)
                {
                    adiff = angle1; angle1 = angle2; angle2 = adiff;
                    Vector2 p = p1; p1 = p2; p2 = p;
                }

                Geometry2D.LineSegment ll = new DxLib.Geometry2D.LineSegment(p1,p2);

                if (angle1 > angle2)
                {
                    Vector2 p;
                    ll.GetIntersect(Math.PI, out p);
                    Geometry2D.LineSegment l1 = new DxLib.Geometry2D.LineSegment(p1, p);
                    Geometry2D.LineSegment l2 = new DxLib.Geometry2D.LineSegment(p, p2);
                    lines.Add(l1);
                    lines.Add(l2);
                }
                else
                {
                    lines.Add(ll);
                }
            }

            lines.Sort(
                delegate(Geometry2D.LineSegment l1, Geometry2D.LineSegment l2)
                {
                    return l1.Angle1.CompareTo(l2.Angle1);
                });

            m_nPrimitives = lines.Count * 2;
            m_VB = new VertexBuffer(typeof(CustomVertex.PositionColored), m_nPrimitives * 3, dx_device, Usage.None,
                CustomVertex.PositionColored.Format, Pool.Default);

            CustomVertex.PositionColored[] array = (CustomVertex.PositionColored[])m_VB.Lock(0, LockFlags.None);
            for (int i = 0; i < lines.Count(); i++)
            {
                int color = Color.Red.ToArgb();
                array[i * 6] = new CustomVertex.PositionColored(lines[i].p1.X, 0, lines[i].p1.Y, color);
                array[i * 6 + 1] = new CustomVertex.PositionColored(lines[i].p1.X, 1, lines[i].p1.Y, color);
                array[i * 6 + 2] = new CustomVertex.PositionColored(lines[i].p2.X, 0, lines[i].p2.Y, color);
                array[i * 6 + 3] = new CustomVertex.PositionColored(lines[i].p1.X, 1, lines[i].p1.Y, color);
                array[i * 6 + 4] = new CustomVertex.PositionColored(lines[i].p2.X, 0, lines[i].p2.Y, color);
                array[i * 6 + 5] = new CustomVertex.PositionColored(lines[i].p2.X, 1, lines[i].p2.Y, color);
            }
            m_VB.Unlock();
        }

        public void render(Device dx_device)
        {
            dx_device.SetStreamSource(0, m_VB, 0);
            dx_device.DrawPrimitives(PrimitiveType.TriangleList, 0, m_nPrimitives);
        }

        /// <summary>
        /// 벽을 추가한다. 모든 벽들이 서로 intersect하게 되는 일이 없도록 벽을 쪼갠다.
        /// </summary>
        public void AddWall(Vector2 p1, Vector2 p2)
        {
            AddWallInternal(p1, p2);
            m_shadow.AddWall(p1, p2);
        }

        private void AddWallInternal(Vector2 p1, Vector2 p2)
        {
            Geometry2D.LineSegment line = new DxLib.Geometry2D.LineSegment(p1, p2);
            foreach (Geometry2D.LineSegment w in m_Walls)
            {
                Vector2 ptr;
                if (line.intersect(w, out ptr))
                {
                    AddWallInternal(p1, ptr);
                    AddWallInternal(ptr, p2);
                    return;
                }
            }
            m_Walls.Add(line);
        }

        public List<Geometry2D.LineSegment> m_Walls = new List<DxLib.Geometry2D.LineSegment>();
        public Shadow3 m_shadow = new Shadow3();
        public VertexBuffer m_VB = null;
        public int m_nPrimitives = 0;
    }
}
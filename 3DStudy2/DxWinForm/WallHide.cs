using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace DxLib
{
    public class WallHide
    {
        public static WallHide CreateRandomWalls(Device dx_device, int cnt, float minx, float maxx, float miny, float maxy)
        {
            WallHide ret = new WallHide();
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

        public static void test()
        {
            WallHide wh = new WallHide();
            wh.AddWall(new Vector2(0, 0), new Vector2(5, 5));
            wh.AddWall(new Vector2(0, 5), new Vector2(5, 0));
            wh.AddWall(new Vector2(0, 0), new Vector2(5, 0));
            wh.AddWall(new Vector2(0, 5), new Vector2(5, 5));
            wh.AddWall(new Vector2(2.5f, 0), new Vector2(2.5f, 5));
        }

        public void BuildVertexBuffer(Device dx_device)
        {
            m_Walls.Sort(
                delegate(Geometry2D.LineSegment l1, Geometry2D.LineSegment l2)
                {
                    return l1.Angle1.CompareTo(l2.Angle1);
                });

            for (int i = 0; i < m_Walls.Count(); i++)
            {
            }
        }

        public void render(Device dx_device)
        {
        }

        /// <summary>
        /// 벽을 추가한다. 모든 벽들이 서로 intersect하게 되는 일이 없도록 벽을 쪼갠다.
        /// </summary>
        public void AddWall(Vector2 p1, Vector2 p2)
        {
            Geometry2D.LineSegment line = new DxLib.Geometry2D.LineSegment(p1, p2);
            foreach (Geometry2D.LineSegment w in m_Walls)
            {
                Vector2 ptr;
                if (line.intersect(w, out ptr))
                {
                    AddWall(p1, ptr);
                    AddWall(ptr, p2);
                    return;
                }
            }
            m_Walls.Add(line);
        }

        public List<Geometry2D.LineSegment> m_Walls = new List<DxLib.Geometry2D.LineSegment>();
        public Shadow3 m_shadow = new Shadow3();
    }
}
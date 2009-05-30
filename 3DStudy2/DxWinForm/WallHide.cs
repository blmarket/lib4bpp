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
        public static void test()
        {
            WallHide wh = new WallHide();
            wh.AddWall(new Vector2(0, 0), new Vector2(5, 5));
            wh.AddWall(new Vector2(0, 5), new Vector2(5, 0));
        }

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

        public List<Geometry2D.LineSegment> m_Walls;
    }
}
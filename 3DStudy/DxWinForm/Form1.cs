using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace DxWinForm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void InitObjects()
        {
            VertexBuffers.LargeGround ground = new VertexBuffers.LargeGround(dx_device);
            m_Objects.Add(ground);

            VertexBuffers.MyBillBoard bill = new VertexBuffers.MyBillBoard(dx_device);
            m_Objects.Add(bill);

            VertexBuffers.SmallGround sground = new VertexBuffers.SmallGround(dx_device);
            m_Objects.Add(sground);

            VertexBuffers.ShadowFullScreen shadows = new VertexBuffers.ShadowFullScreen(dx_device, 500, 500);
            m_Objects.Add(shadows);

            VertexBuffers.Walls walls = VertexBuffers.Walls.CreateRandomWalls(dx_device, 5, -3, 3, -3, 3);
            m_Objects.Add(walls);            

            m_Mesh = Mesh.Teapot(dx_device);
            Bitmap Bits = new Bitmap(512,512);
            Graphics g = Graphics.FromImage(Bits);
            Pen pen = new Pen(Color.Magenta);
            pen.Width = 5.0f;
            g.Clear(Color.White);
            g.DrawRectangle(pen, 50, 50, 100, 100);
            Bits.Save("test.bmp");
            m_Tex = TextureLoader.FromFile(dx_device, "test.bmp");
//            System.IO.Stream infile = new System.IO.FileStream("test.bmp",System.IO.FileMode.Open);
//            m_Tex = Texture.FromStream(dx_device, infile, Usage.None, Pool.Default);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            PresentParameters pp = new PresentParameters();

            pp.Windowed = true;
            pp.SwapEffect = SwapEffect.Discard;
            pp.BackBufferFormat = Format.Unknown;
            pp.EnableAutoDepthStencil = true;
            pp.AutoDepthStencilFormat = DepthFormat.D24S8;

            try
            {
                dx_device = new Device(0, DeviceType.Hardware, this, CreateFlags.SoftwareVertexProcessing, pp);
                dx_device.RenderState.CullMode = Cull.None;
                dx_device.RenderState.ColorVertex = true;
                dx_device.RenderState.Lighting = false;
                dx_device.RenderState.FillMode = FillMode.Solid;
                dx_device.RenderState.ZBufferEnable = true;
                dx_device.RenderState.StencilEnable = true;
                dx_device.RenderState.ReferenceStencil = 0;
                dx_device.RenderState.StencilPass = StencilOperation.Increment;
                dx_device.RenderState.AlphaBlendEnable = true;

                InitObjects();
            }
            catch (DirectXException ee)
            {
                // do nothing.
                MessageBox.Show("NO");
                throw ee;
            }
        }

        private void Render2()
        {
            dx_device.Clear(ClearFlags.Target | ClearFlags.ZBuffer | ClearFlags.Stencil, Color.Blue, 1.0f, 0);
            dx_device.BeginScene();

            Matrix matWorld, matView, matProj;
            matWorld = matView = matProj = Matrix.Identity;
            matView = Matrix.LookAtLH(new Vector3(5, 5, -5), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
            matProj = Matrix.PerspectiveFovLH((float)Math.PI / 4, 1.0f, 0.1f, 100.0f);
            dx_device.SetTransform(TransformType.World, matWorld);
            dx_device.SetTransform(TransformType.View, matView);
            dx_device.SetTransform(TransformType.Projection, matProj);

            m_Objects[4].render(dx_device);

            dx_device.EndScene();
            dx_device.Present();
        }

        private void Render1()
        {
            dx_device.Clear(ClearFlags.Target | ClearFlags.ZBuffer | ClearFlags.Stencil, Color.Blue, 1.0f, 0);

            dx_device.BeginScene();
            dx_device.SetTexture(0, m_Tex);

            matWorld = matView = matProj = Matrix.Identity;
            matWorld = m_position.getWorldMatrix();
            matView = Matrix.LookAtLH(new Vector3(5, 15, -5), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
            matProj = Matrix.PerspectiveFovLH((float)Math.PI / 4, 1.0f, 0.1f, 100.0f);
            dx_device.SetTransform(TransformType.World, matWorld);
            dx_device.SetTransform(TransformType.View, matView);
            dx_device.SetTransform(TransformType.Projection, matProj);

            // 원래 객체를 그린다.
            dx_device.RenderState.ShadeMode = ShadeMode.Gouraud;
            dx_device.RenderState.CullMode = Cull.None;
            dx_device.RenderState.ZBufferWriteEnable = true;
            dx_device.RenderState.StencilEnable = false;
            dx_device.RenderState.AlphaBlendEnable = false;
//            m_Objects[4].render(dx_device);

            // 그림자 영역을 그린다.
            dx_device.RenderState.ZBufferWriteEnable = false;
            dx_device.RenderState.StencilEnable = true;
            dx_device.RenderState.ShadeMode = ShadeMode.Flat;
            dx_device.RenderState.StencilFunction = Compare.Always;
            dx_device.RenderState.StencilZBufferFail = StencilOperation.Keep;
            dx_device.RenderState.StencilFail = StencilOperation.Keep;
            dx_device.RenderState.ReferenceStencil = 1;
            dx_device.RenderState.StencilMask = -1;
            dx_device.RenderState.StencilWriteMask = -1;
            dx_device.RenderState.StencilPass = StencilOperation.Increment;
            dx_device.RenderState.AlphaBlendEnable = true;
            dx_device.RenderState.SourceBlend = Blend.Zero;
            dx_device.RenderState.DestinationBlend = Blend.One;

            dx_device.Transform.World = m_position.getShadowWorldMatrix();
            m_Objects[4].render(dx_device);
            dx_device.Transform.World = m_position.getWorldMatrix();

            // 원래 객체를 그린다.
            dx_device.RenderState.ShadeMode = ShadeMode.Gouraud;
            dx_device.RenderState.CullMode = Cull.None;
            dx_device.RenderState.ZBufferWriteEnable = true;
            dx_device.RenderState.StencilEnable = false;
            dx_device.RenderState.AlphaBlendEnable = false;
            m_Objects[0].render(dx_device);
            m_Objects[1].render(dx_device);
            m_Objects[4].render(dx_device);


            // 그림자에 해당하는 부분을 다시 그린다.
            dx_device.RenderState.ZBufferEnable = true;
            dx_device.RenderState.ZBufferWriteEnable = false;
            dx_device.RenderState.StencilEnable = true;
            dx_device.RenderState.AlphaBlendEnable = true;
            dx_device.RenderState.SourceBlend = Blend.SourceAlpha;
            dx_device.RenderState.DestinationBlend = Blend.InvSourceAlpha;

            dx_device.TextureState[0].ColorArgument1 = TextureArgument.TextureColor;
            dx_device.TextureState[0].ColorArgument2 = TextureArgument.Constant;
            dx_device.TextureState[0].ColorOperation = TextureOperation.SelectArg2;
            dx_device.TextureState[0].AlphaArgument1 = TextureArgument.TextureColor;
            dx_device.TextureState[0].AlphaArgument2 = TextureArgument.Diffuse;
            dx_device.TextureState[0].AlphaOperation = TextureOperation.Modulate;

            dx_device.RenderState.ReferenceStencil = 1;
            dx_device.RenderState.StencilFunction = Compare.LessEqual;
            dx_device.RenderState.StencilPass = StencilOperation.Keep;

            m_Objects[0].render(dx_device);

            dx_device.TextureState[0].ColorArgument1 = TextureArgument.TextureColor;
            dx_device.TextureState[0].ColorArgument2 = TextureArgument.Diffuse;
            dx_device.TextureState[0].ColorOperation = TextureOperation.Modulate;
            dx_device.TextureState[0].AlphaArgument1 = TextureArgument.TextureColor;
            dx_device.TextureState[0].AlphaArgument2 = TextureArgument.Diffuse;
            dx_device.TextureState[0].AlphaOperation = TextureOperation.Modulate;
            
            dx_device.RenderState.ShadeMode = ShadeMode.Gouraud;
            dx_device.RenderState.CullMode = Cull.None;
            dx_device.RenderState.ZBufferWriteEnable = true;
            dx_device.RenderState.StencilEnable = false;
            dx_device.RenderState.AlphaBlendEnable = false;

            FontDescription desc = new FontDescription();
            Microsoft.DirectX.Direct3D.Font fnt = new Microsoft.DirectX.Direct3D.Font(dx_device, desc);            

            fnt.DrawText(null, m_position.ToString(), new Point(5, 5), Color.White);
 
            dx_device.EndScene();

            dx_device.Present();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Render1();
        }

        public DxLib.플레이어위치 m_position = new DxLib.플레이어위치();
        private Device dx_device = null;
        private List<VertexBuffers.DrawItem> m_Objects = new List<VertexBuffers.DrawItem>();
        private Mesh m_Mesh = null;
        private Texture m_Tex = null;
        public Matrix matWorld, matView, matProj;

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if(m_Tex != null) m_Tex.Dispose();
            m_Mesh.Dispose();           
            dx_device.Dispose();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            float value = 1.0f;
            if (e.Control) value *= 10;
            switch (e.KeyCode)
            {
                case Keys.Up:
                    m_position.pos.Y -= value;
                    break;
                case Keys.Down:
                    m_position.pos.Y += value;
                    break;
                case Keys.Left:
                    m_position.pos.X += value;
                    break;
                case Keys.Right:
                    m_position.pos.X -= value;
                    break;
            }
            Render1();
        }
    }

    namespace VertexBuffers
    {
        public abstract class DrawItem
        {
            public abstract void render(Device dx_device);
        }

        public class DrawVertexBuffer : DrawItem
        {
            public VertexBuffer m_VB;
            public int m_nPrimitives;

            public override void render(Device dx_device)
            {
                dx_device.SetStreamSource(0, m_VB, 0);
                dx_device.VertexFormat = m_VB.Description.VertexFormat;
                dx_device.DrawPrimitives(PrimitiveType.TriangleList, 0, m_nPrimitives);
            }
        }

        public class LargeGround : DrawVertexBuffer
        {
            public LargeGround(Device dx_device)
            {
                m_VB = new VertexBuffer(typeof(CustomVertex.PositionTextured), 6, dx_device, Usage.WriteOnly, CustomVertex.PositionTextured.Format,
                    Pool.Default);
                m_VB.Created += new EventHandler(this.OnCreateVertexBuffer);
                m_nPrimitives = 2;
                OnCreateVertexBuffer(m_VB, null);
            }

            public void OnCreateVertexBuffer(object sender, EventArgs e)
            {
                CustomVertex.PositionTextured[] points = new CustomVertex.PositionTextured[4]
                {
                    new CustomVertex.PositionTextured(-3,0,-3,0,0),
                    new CustomVertex.PositionTextured(-3,0,3,0,1),
                    new CustomVertex.PositionTextured(3,0,3,1,1),
                    new CustomVertex.PositionTextured(3,0,-3,1,0),
                };

                CustomVertex.PositionTextured[] vertices = new CustomVertex.PositionTextured[6]
                {
                    points[0],
                    points[1],
                    points[2],
                    points[0],
                    points[2],
                    points[3],
                };

                VertexBuffer vb = (VertexBuffer)sender;
                vb.SetData((object)vertices, 0, LockFlags.None);
            }
        }

        public class MyBillBoard : DrawVertexBuffer
        {
            public void OnCreateBillBoard(object sender, EventArgs e)
            {
                CustomVertex.TransformedColored[] points = new CustomVertex.TransformedColored[4]
                {
                    new CustomVertex.TransformedColored(5,5,0,1,Color.FromArgb(50,Color.Blue).ToArgb()),
                    new CustomVertex.TransformedColored(5,105,0,1,Color.FromArgb(50,Color.Magenta).ToArgb()),
                    new CustomVertex.TransformedColored(105,5,0,1,Color.FromArgb(50,Color.MediumBlue).ToArgb()),
                    new CustomVertex.TransformedColored(105,105,0,1,Color.FromArgb(50,Color.Linen).ToArgb()),
                };

                CustomVertex.TransformedColored[] vertices = new CustomVertex.TransformedColored[6]
                {
                    points[0],
                    points[1],
                    points[3],
                    points[0],
                    points[2],
                    points[3],
                };

                VertexBuffer vb = (VertexBuffer)sender;
                vb.SetData((object)vertices, 0, LockFlags.None);
            }

            public MyBillBoard(Device dx_device)
            {
                m_VB = new VertexBuffer(
                    typeof(CustomVertex.TransformedColored),
                    6,
                    dx_device,
                    Usage.WriteOnly,
                    CustomVertex.TransformedColored.Format,
                    Pool.Default);

                m_nPrimitives = 2;

                m_VB.Created += new EventHandler(this.OnCreateBillBoard);
                OnCreateBillBoard(m_VB, null);
            }
        }

        public class SmallGround : DrawVertexBuffer
        {
            public SmallGround(Device dx_device)
            {
                m_VB = new VertexBuffer(typeof(CustomVertex.PositionColored), 6, dx_device, Usage.WriteOnly, CustomVertex.PositionColored.Format,
                    Pool.Default);
                m_nPrimitives = 2;
                m_VB.Created += new EventHandler(this.OnCreateVertexBuffer);
                OnCreateVertexBuffer(m_VB, null);
            }

            public void OnCreateVertexBuffer(object sender, EventArgs e)
            {
                Color gray = Color.FromArgb(50, Color.Black);

                CustomVertex.PositionColored[] points = new CustomVertex.PositionColored[4]
                {
                    new CustomVertex.PositionColored(-1,0,-1,gray.ToArgb()),
                    new CustomVertex.PositionColored(-1,0,1,gray.ToArgb()),
                    new CustomVertex.PositionColored(1,0,1,gray.ToArgb()),
                    new CustomVertex.PositionColored(1,0,-1,gray.ToArgb()),
                };

                CustomVertex.PositionColored[] vertices = new CustomVertex.PositionColored[6]
                {
                    points[0],
                    points[1],
                    points[2],
                    points[0],
                    points[2],
                    points[3],
                };

                VertexBuffer vb = (VertexBuffer)sender;
                vb.SetData((object)vertices, 0, LockFlags.None);
            }
        }

        public class Wall : DrawVertexBuffer
        {
            public Wall(Device dx_device,Vector2 p1,Vector2 p2,float height,Vector2[] boundary)
            {
                m_VB = new VertexBuffer(typeof(CustomVertex.PositionColored), 6, dx_device, Usage.WriteOnly, CustomVertex.PositionColored.Format,
                    Pool.Default);
                this.p1 = p1;
                this.p2 = p2;
                this.height = height;
                m_VB.Created += new EventHandler(this.OnCreateVertexBuffer);
                m_nPrimitives = 2;
                OnCreateVertexBuffer(m_VB, null);
            }

            public void OnCreateVertexBuffer(object sender, EventArgs e)
            {
                CustomVertex.PositionColored[] points = new CustomVertex.PositionColored[4]
                {
                    new CustomVertex.PositionColored(p1.X,0,p1.Y,Color.Red.ToArgb()),
                    new CustomVertex.PositionColored(p1.X,height,p1.Y,Color.Red.ToArgb()),
                    new CustomVertex.PositionColored(p2.X,0,p2.Y,Color.Red.ToArgb()),
                    new CustomVertex.PositionColored(p2.X,height,p2.Y,Color.Red.ToArgb()),
                };

                CustomVertex.PositionColored[] vertices = new CustomVertex.PositionColored[6]
                {
                    points[0],
                    points[1],
                    points[3],
                    points[0],
                    points[3],
                    points[2],
                };

                VertexBuffer vb = (VertexBuffer)sender;
                vb.SetData((object)vertices, 0, LockFlags.None);
            }

            private Vector2 p1, p2;
            private float height;
        }

        public class Walls : DrawItem
        {
            public void AddWall(Device dx_device, Vector2 p1, Vector2 p2, Vector2[] boundary)
            {
                AddWall(dx_device, p1, p2, 0.8f, boundary);
            }

            public void AddWall(Device dx_device,Vector2 p1, Vector2 p2, float height, Vector2[] boundary)
            {
                Wall tmp = new Wall(dx_device, p1, p2, height, boundary);
                m_List.Add(tmp);
            }

            public override void render(Device dx_device)
            {
                foreach (Wall w in m_List)
                {
                    w.render(dx_device);
                }
            }

            public static Walls CreateRandomWalls(Device dx_device, int cnt, float minx, float maxx, float miny, float maxy)
            {
                Walls ret = new Walls();
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
                    ret.AddWall(dx_device, p1, p2, boundary);
                }

                return ret;
            }

            private List<Wall> m_List = new List<Wall>();
        }

        public class ShadowFullScreen : DrawVertexBuffer
        {
            public ShadowFullScreen(Device dx_device,float sx,float sy)
            {
                m_VB = new VertexBuffer(typeof(CustomVertex.TransformedColored), 6, dx_device, Usage.WriteOnly, CustomVertex.TransformedColored.Format,
                    Pool.Default);
                this.sx = sx;
                this.sy = sy;
                m_VB.Created += new EventHandler(this.OnCreateVertexBuffer);
                m_nPrimitives = 2;
                OnCreateVertexBuffer(m_VB, null);
            }

            public void OnCreateVertexBuffer(object sender, EventArgs e)
            {
                Color gray = Color.FromArgb(127, Color.Black);

                CustomVertex.TransformedColored[] points = new CustomVertex.TransformedColored[4]
                {
                    new CustomVertex.TransformedColored(0,0,0,1,gray.ToArgb()),
                    new CustomVertex.TransformedColored(0,sy,0,1,gray.ToArgb()),
                    new CustomVertex.TransformedColored(sx,0,0,1,gray.ToArgb()),
                    new CustomVertex.TransformedColored(sx,sy,0,1,gray.ToArgb()),
                };

                CustomVertex.TransformedColored[] vertices = new CustomVertex.TransformedColored[6]
                {
                    points[0],
                    points[1],
                    points[3],
                    points[0],
                    points[2],
                    points[3],
                };

                VertexBuffer vb = (VertexBuffer)sender;
                vb.SetData((object)vertices, 0, LockFlags.None);
            }

            private float sx, sy;
        }
    }
}

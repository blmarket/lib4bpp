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

        public void OnCreateVertexBuffer(object sender, EventArgs e)
        {
            CustomVertex.PositionColored[] points = new CustomVertex.PositionColored[4]
            {
                new CustomVertex.PositionColored(-3,0,-3,Color.White.ToArgb()),
                new CustomVertex.PositionColored(-3,0,3,Color.White.ToArgb()),
                new CustomVertex.PositionColored(3,0,3,Color.White.ToArgb()),
                new CustomVertex.PositionColored(3,0,-3,Color.White.ToArgb()),
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
            vb.SetData((object)vertices,0,LockFlags.None);
        }

        private void InitObjects()
        {
            m_VB = new VertexBuffer(typeof(CustomVertex.PositionColored), 6, dx_device, Usage.WriteOnly, CustomVertex.PositionColored.Format,
                Pool.Default);
            m_VB.Created += new EventHandler(this.OnCreateVertexBuffer);
            OnCreateVertexBuffer(m_VB, null);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            PresentParameters pp = new PresentParameters();

            pp.Windowed = true;
            pp.SwapEffect = SwapEffect.Discard;
            try
            {
                dx_device = new Device(0, DeviceType.Hardware, this, CreateFlags.SoftwareVertexProcessing, pp);
                dx_device.RenderState.CullMode = Cull.None;
                dx_device.RenderState.ColorVertex = true;
                dx_device.RenderState.Lighting = false;
                dx_device.RenderState.FillMode = FillMode.Solid;

                InitObjects();
            }
            catch (DirectXException)
            {
                // do nothing.
            }
        }

        private Device dx_device = null;
        private VertexBuffer m_VB = null;

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            dx_device.Clear(ClearFlags.Target, Color.Black.ToArgb(), 1.0f, 0);

            dx_device.BeginScene();
            dx_device.SetStreamSource(0, m_VB, 0);
            dx_device.VertexFormat = m_VB.Description.VertexFormat;

            Matrix matWorld, matView, matProj;
            matWorld = matView = matProj = Matrix.Identity;
            matView = Matrix.LookAtLH(new Vector3(5, 5, -5), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
            matProj = Matrix.PerspectiveFovLH((float)Math.PI / 4, 1.0f, 0.1f, 100.0f);
            dx_device.SetTransform(TransformType.World, matWorld);
            dx_device.SetTransform(TransformType.View, matView);
            dx_device.SetTransform(TransformType.Projection, matProj);

            dx_device.DrawPrimitives(PrimitiveType.TriangleList, 0, 2);
            dx_device.EndScene();

            dx_device.Present();
        }
    }
}

﻿using System;
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
            vb.SetData((object)vertices,0,LockFlags.None);
        }

        public void OnCreateBillBoard(object sender, EventArgs e)
        {
            CustomVertex.TransformedTextured[] points = new CustomVertex.TransformedTextured[4]
            {
                new CustomVertex.TransformedTextured(5,5,0,1,0,0),
                new CustomVertex.TransformedTextured(5,105,0,1,0,1),
                new CustomVertex.TransformedTextured(105,5,0,1,1,0),
                new CustomVertex.TransformedTextured(105,105,0,1,1,1),
            };

            CustomVertex.TransformedTextured[] vertices = new CustomVertex.TransformedTextured[6]
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

        private void InitObjects()
        {
            VertexBuffer VB = new VertexBuffer(typeof(CustomVertex.PositionTextured), 6, dx_device, Usage.WriteOnly, CustomVertex.PositionTextured.Format,
                Pool.Default);
            VB.Created += new EventHandler(this.OnCreateVertexBuffer);
            OnCreateVertexBuffer(VB, null);
            m_Objects.Add(new KeyValuePair<int, VertexBuffer>(2, VB));

            VB = new VertexBuffer(
                typeof(CustomVertex.TransformedTextured), 
                6, 
                dx_device, 
                Usage.WriteOnly, 
                CustomVertex.TransformedTextured.Format, 
                Pool.Default);

            VB.Created += new EventHandler(this.OnCreateBillBoard);
            OnCreateBillBoard(VB, null);
            m_Objects.Add(new KeyValuePair<int, VertexBuffer>(2, VB));                

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
            pp.EnableAutoDepthStencil = true;
            pp.AutoDepthStencilFormat = DepthFormat.D16;
            try
            {
                dx_device = new Device(0, DeviceType.Hardware, this, CreateFlags.SoftwareVertexProcessing, pp);
                dx_device.RenderState.CullMode = Cull.None;
                dx_device.RenderState.ColorVertex = true;
                dx_device.RenderState.Lighting = false;
                dx_device.RenderState.FillMode = FillMode.Solid;
/*                dx_device.RenderState.StencilEnable = true;
                dx_device.RenderState.ReferenceStencil = 0;
                dx_device.RenderState.StencilPass = StencilOperation.Increment;*/

                InitObjects();
            }
            catch (DirectXException ee)
            {
                // do nothing.
                MessageBox.Show("NO");
                throw ee;
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            dx_device.Clear(ClearFlags.Target, Color.Black, 1.0f, 0);

            dx_device.BeginScene();
            dx_device.SetTexture(0, m_Tex);

            Matrix matWorld, matView, matProj;
            matWorld = matView = matProj = Matrix.Identity;
            matView = Matrix.LookAtLH(new Vector3(5, 5, -5), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
            matProj = Matrix.PerspectiveFovLH((float)Math.PI / 4, 1.0f, 0.1f, 100.0f);
            dx_device.SetTransform(TransformType.World, matWorld);
            dx_device.SetTransform(TransformType.View, matView);
            dx_device.SetTransform(TransformType.Projection, matProj);

            foreach (KeyValuePair<int, VertexBuffer> p in m_Objects)
            {
                dx_device.SetStreamSource(0, p.Value, 0);
                dx_device.VertexFormat = p.Value.Description.VertexFormat;
                dx_device.DrawPrimitives(PrimitiveType.TriangleList, 0, p.Key);
            }

            dx_device.EndScene();

            dx_device.Present();
        }

        private Device dx_device = null;
        private List<KeyValuePair<int, VertexBuffer>> m_Objects = new List<KeyValuePair<int, VertexBuffer>>();
        private Mesh m_Mesh = null;
        private Texture m_Tex = null;

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if(m_Tex != null) m_Tex.Dispose();
            foreach (KeyValuePair<int, VertexBuffer> p in m_Objects)
            {
                p.Value.Dispose();
            }
            m_Mesh.Dispose();           
            dx_device.Dispose();
        }
    }
}

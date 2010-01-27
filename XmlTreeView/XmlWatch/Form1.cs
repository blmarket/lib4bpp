using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.IO;

namespace XmlWatch
{
    public partial class XmlWatch : Form
    {
        public XmlWatch()
        {
            InitializeComponent();
            this.SetStyle(
              ControlStyles.AllPaintingInWmPaint |
              ControlStyles.UserPaint |
              ControlStyles.DoubleBuffer, true);
        }

        private void AddNode(XmlNode inXmlNode, TreeNode inTreeNode)
        {
            XmlNode xNode;
            TreeNode tNode;
            XmlNodeList nodeList;
            int i;

            // Loop through the XML nodes until the leaf is reached.
            // Add the nodes to the TreeView during the looping process.
            if (inXmlNode.HasChildNodes)
            {
                nodeList = inXmlNode.ChildNodes;
                for (i = 0; i <= nodeList.Count - 1; i++)
                {
                    xNode = inXmlNode.ChildNodes[i];
                    inTreeNode.Nodes.Add(new TreeNode(xNode.Name));
                    tNode = inTreeNode.Nodes[i];
                    AddNode(xNode, tNode);
                }
            }
            else
            {
                // Here you need to pull the data from the XmlNode based on the
                // type of node, whether attribute values are required, and so forth.
                inTreeNode.Text = (inXmlNode.OuterXml).Trim();
            }
        }

        private bool UpdateNode(XmlNode elem, TreeNodeCollection col)
        {
            bool changed = false;
            if(col.Count > elem.ChildNodes.Count)
            {
                col.Clear();
            }

            for(int i=0;i<elem.ChildNodes.Count;i++)
            {
                XmlNode cnode = elem.ChildNodes[i];
                string text;
                if (cnode.HasChildNodes)
                {
                    text = cnode.Name;
                }
                else
                {
                    text = cnode.OuterXml.Trim();
                }

                if(col.Count <= i)
                {
                    col.Add(text);
                    col[i].BackColor = Color.Red;
                    changed = true;
                }
                else
                {
                    if(col[i].Text != text)
                    {
                        col[i].Text = text;
                        col[i].BackColor = Color.Red;
                        changed = true;
                    }
                }
                if(UpdateNode(cnode, col[i].Nodes))
                {
                    col[i].BackColor = Color.Red;
                    changed = true;
                }
            }
            return changed;
        }

        private void LoadXML(XmlDocument dom)
        {
            UpdateNode(dom.DocumentElement, treeView1.Nodes);
        }

        public void ExplicitUpdate(XmlDocument xml)
        {
            LoadXML(xml);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Timer tt = new Timer();
            // color update interval in millisec. modify to change color animation interval.
            tt.Interval = 50;
            tt.Tick += delegate(object obj, EventArgs ee)
            {
                // traverse all nodes to update color.
                Traverse(treeView1.Nodes);
            };
            tt.Start();

            tt = new Timer();
            // Watch interval in millisec. modify here to change watch interval.
            tt.Interval = 1000;
            tt.Tick += delegate(object obj, EventArgs ee)
            {
                // Get New XML. Modify here to 
                Program.XmlSupplier.Execute(new UpdateDelegate(ExplicitUpdate));
            };
            tt.Start();
        }

        public int min(int a, int b)
        {
            if (a < b) return a;
            return b;
        }

        private void Traverse(TreeNode node)
        {
            Color curColor = node.BackColor;
            if (curColor.ToArgb() == -1) // it's white
            {
                // do nothing.
            }
            else
            {
                curColor = Color.FromArgb(min(255, curColor.R + 10), min(255, curColor.G + 10), min(255, curColor.B + 10));
                node.BackColor = curColor;
            }

            // traverse childs.
            foreach (TreeNode cnode in node.Nodes)
            {
                Traverse(cnode);
            }
        }

        private void Traverse(TreeNodeCollection col)
        {
            // traverse all
            foreach(TreeNode cnode in col)
            {
                Traverse(cnode);
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace XmlTreeView
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
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

        private void LoadXML(string filename)
        {
            try
            {
                XmlDocument dom = new XmlDocument();
                dom.Load(filename);

                UpdateNode(dom.DocumentElement, treeView1.Nodes);
/*

                treeView1.Nodes.Clear();
                treeView1.Nodes.Add(new TreeNode(dom.DocumentElement.Name));
                TreeNode tNode = new TreeNode();
                tNode = treeView1.Nodes[0];

                AddNode(dom.DocumentElement, tNode);
 */
//                treeView1.ExpandAll();
            }
            catch (Exception E)
            {
                MessageBox.Show(E.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            LoadXML("Sample.XML");
        }

        Color[] avails = new Color[] {
            Color.Aqua, Color.Red, Color.Beige, Color.Bisque, Color.Black, Color.BlanchedAlmond, Color.Blue, Color.BlueViolet, Color.BurlyWood
        };
        static Random Picker = new Random();

        private void Form1_Load(object sender, EventArgs e)
        {
            Timer tt = new Timer();
            tt.Interval = 50;
            tt.Tick += new EventHandler(tt_Tick);
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
            if (curColor.ToArgb() == -1)
            {
                //               node.BackColor = Color.FromKnownColor((KnownColor)(Picker.Next(175)));
            }
            else
            {
                curColor = Color.FromArgb(min(255, curColor.R + 10), min(255, curColor.G + 10), min(255, curColor.B + 10));
                node.BackColor = curColor;
            }
            foreach (TreeNode cnode in node.Nodes)
            {
                Traverse(cnode);
            }
        }

        private void Traverse(TreeNodeCollection col)
        {
            foreach(TreeNode cnode in col)
            {
                Traverse(cnode);
            }
        }

        void tt_Tick(object sender, EventArgs e)
        {
            Traverse(treeView1.Nodes);
        }
    }
}

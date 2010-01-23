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

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                XmlDocument dom = new XmlDocument();
                dom.Load("Sample.XML");

                treeView1.Nodes.Clear();
                treeView1.Nodes.Add(new TreeNode(dom.DocumentElement.Name));
                TreeNode tNode = new TreeNode();
                tNode = treeView1.Nodes[0];

                AddNode(dom.DocumentElement, tNode);
                treeView1.ExpandAll();
            }
            catch (Exception E)
            {
                MessageBox.Show(E.Message);
            }
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

        Color[] avails = new Color[] {
            Color.Aqua, Color.Red, Color.Beige, Color.Bisque, Color.Black, Color.BlanchedAlmond, Color.Blue, Color.BlueViolet, Color.BurlyWood
        };
        static Random Picker = new Random();

        private void Form1_Load(object sender, EventArgs e)
        {
            Timer tt = new Timer();
            tt.Interval = 2000;
            tt.Tick += new EventHandler(tt_Tick);
            tt.Start();
        }

        private void Traverse(TreeNode node)
        {
            node.BackColor = avails[Picker.Next(avails.Length)];
            foreach (TreeNode cnode in node.Nodes)
            {
                Traverse(cnode);
            }
        }

        void tt_Tick(object sender, EventArgs e)
        {
            Traverse(treeView1.Nodes[0]);
        }
    }
}

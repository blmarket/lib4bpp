using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;

namespace XmlTreeView
{
    public delegate void UpdateDelegate(XmlDocument xmldoc);

    interface ISubject
    {
        void Execute(UpdateDelegate Updater);
    }

    public abstract class SimpleSubject : ISubject
    {
        #region ISubject 멤버
        public void Execute(UpdateDelegate Updater)
        {
            XmlDocument doc = Run();
            Updater(doc);
        }
        #endregion

        public abstract XmlDocument Run();
    }

    public class SimpleTest : SimpleSubject
    {
        private int count = 0;

        public override XmlDocument Run()
        {
            XmlDocument doc = new XmlDocument();
            doc.LoadXml("<xml><child>It is test</child><child2>" + count + "</child2></xml>");
            count += 1;
            return doc;
        }
    }

    public class FileReadSubject : SimpleSubject
    {
        string m_filename;
        public FileReadSubject(string filename)
        {
            m_filename = filename;
        }

        public override XmlDocument Run()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(m_filename);
            return doc;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;

namespace XmlWatch
{
    /// <summary>
    /// When you execute this with suffice xmldoc, UI applies this.
    /// </summary>
    /// <param name="xmldoc">XML Document which you want to update</param>
    public delegate void UpdateDelegate(XmlDocument xmldoc);

    interface ISubject
    {
        void Execute(UpdateDelegate Updater);
    }

    /// <summary>
    /// SimpleSubject is Wrapper Class of ISubject.
    /// It uses simple call-return method instead of execute-callback method.
    /// </summary>
    public abstract class SimpleSubject : ISubject
    {
        #region ISubject Member
        public void Execute(UpdateDelegate Updater)
        {
            XmlDocument doc = Run();
            Updater(doc);
        }
        #endregion

        /// <summary>
        /// Make a Xml Document to watch.
        /// </summary>
        /// <returns>Xml Document</returns>
        public abstract XmlDocument Run();
    }

    /// <summary>
    /// Simple Example XML Subject Class
    /// </summary>
    public class SimpleTest : SimpleSubject
    {
        private int count = 0;

        /// <summary>
        /// It creates simple XML Document.
        /// </summary>
        /// <returns>Created XML Document</returns>
        public override XmlDocument Run()
        {
            XmlDocument doc = new XmlDocument();
            doc.LoadXml("<xml><child>It is test</child><child2>" + count + "</child2></xml>");
            count += 1;
            return doc;
        }
    }

    /// <summary>
    /// Simple Example Periodic XML File Reader Class
    /// </summary>
    public class FileReadSubject : SimpleSubject
    {
        string m_filename;

        /// <summary>
        /// Initializer with filename
        /// </summary>
        /// <param name="filename">XML file name to watch</param>
        public FileReadSubject(string filename)
        {
            m_filename = filename;
        }

        /// <summary>
        /// It returns parsed XML Document from file
        /// </summary>
        /// <returns>parsed XML Document</returns>
        public override XmlDocument Run()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(m_filename);
            return doc;
        }
    }
}

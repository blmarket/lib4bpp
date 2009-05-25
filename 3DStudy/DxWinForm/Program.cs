using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace DxWinForm
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            m_Form = new Form1();
            Application.Idle += new EventHandler(Application_Idle);
            Application.Run(m_Form);
        }

        static void Application_Idle(object sender, EventArgs e)
        {
            m_Form.Idle();
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }

        private static Form1 m_Form = null;
    }
}

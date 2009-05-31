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
            DxLib.WallHide.test();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            m_Form = new Form1();
            Application.Idle += new EventHandler(Application_Idle);
            m_Form.Show();
            while (m_Form.Created)
            {
                m_Form.Idle();
                Application.DoEvents();
            }
//            Application.Run(m_Form);
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

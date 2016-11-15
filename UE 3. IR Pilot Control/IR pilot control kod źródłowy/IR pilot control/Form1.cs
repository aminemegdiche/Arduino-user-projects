using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WindowsInput;
using System.IO;

namespace IR_pilot_control
{
    public partial class Form1 : Form
    {
        string URL = Application.StartupPath;

        public Form1()
        {
            InitializeComponent();

            LoadConfig();
            
        }

        void LoadConfig()
        {
            string element;
            string[] elements, elements2;

            if (File.Exists(URL + @"/config.IR"))
            {
                try
                {
                    StreamReader streamReader = new StreamReader(URL + @"/config.IR");
                    element = streamReader.ReadToEnd();
                    streamReader.Close();

                    elements = element.Split('\x0001');

                    for (int i = 0; i < elements.Length; i++)
                    {
                        elements2 = elements[i].Split('\n');

                        dataGridView1.Rows.Add(elements2[0],
                                               elements2[1],
                                               elements2[2],
                                               elements2[3]
                                               );
                    } 
                }
                catch{}
            }
        }


        private void btnStart_Click(object sender, EventArgs e)
        {
            btnStart.Enabled = false;
            btnStop.Enabled = true;
            gbConfig.Enabled = false;
            try
            {
                serialPort1.PortName = txtPortName.Text;
                serialPort1.BaudRate = Convert.ToInt16(txtBaudRate.Text);
                serialPort1.Open();

                if (cbDoubleClicked.Checked == true)
                    serialPort1.Write("T");
                else if (cbDoubleClicked.Checked == false)
                    serialPort1.Write("F");
            }
            catch 
            {
                MessageBox.Show("Port Name does not exist \nor the Baud Rate is incorrect.");
                btnStop_Click(sender, e);
            }

        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            btnStart.Enabled = true;
            btnStop.Enabled = false;
            gbConfig.Enabled = true;
            try
            {
                serialPort1.Close();
            }
            catch
            {
                MessageBox.Show("error serialPort1.Close();");
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string line = serialPort1.ReadLine();
            this.BeginInvoke(new LineReceivedEvent(LineReceived), line);
        }

        private delegate void LineReceivedEvent(string line);

        private void LineReceived(string line)
        {
            if (symulate(line) == false) 
            {
                txtSecondClick.Text = txtFirstClick.Text;
                txtFirstClick.Text = line;
            }

            txtConsol.SelectionStart = txtConsol.Text.Length;

            txtConsol.Text += line + "\n";

            txtConsol.SelectionStart = txtConsol.Text.Length;
            txtConsol.ScrollToCaret();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                if (cbDoubleClicked.Checked == true)
                    serialPort1.Write("T");
                else if (cbDoubleClicked.Checked == false)
                    serialPort1.Write("F");
            }

            if (cbDoubleClicked.Checked == true)
            {
                lblSecondClick.Enabled = true;
                txtSecondClick.Enabled = true;
            }
            else if (cbDoubleClicked.Checked == false)
            {
                lblSecondClick.Enabled = false;
                txtSecondClick.Enabled = false;
            }

            
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (txtFirstClick.Text != "" &&
                txtSecondClick.Text != "" &&
                txtKeyPress.Text != "")
            {
                addHex();
            }
        }

        private bool symulate(string keyID)
        {
            string s1, s2;

            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                s1 = dataGridView1.Rows[i].Cells[0].Value.ToString();
                s2 = dataGridView1.Rows[i].Cells[1].Value.ToString();

                if ((s1 == keyID) || (s2 == keyID))
                {
                    encodingKeys(dataGridView1.Rows[i].Cells[3].Value.ToString());
                    return true;
                }
            }
            return false;
        }

        void encodingKeys(string keys)
        {
            string[] key = keys.Split('|');
            for (int i = 0; i < key.Length-1; i++)
            {
                if (key[i] == "^")
                    InputSimulator.SimulateKeyDown(VirtualKeyCode.CONTROL);
                else if (key[i] == "+")
                    InputSimulator.SimulateKeyDown(VirtualKeyCode.SHIFT);
            }

            SendKeys.SendWait(key[key.Length - 1]);

            for (int i = 0; i < key.Length - 1; i++)
            {
                if (key[i] == "^")
                    InputSimulator.SimulateKeyUp(VirtualKeyCode.CONTROL);
                else if (key[i] == "+")
                    InputSimulator.SimulateKeyUp(VirtualKeyCode.SHIFT);
            }
        }

        string codingKey()
        {

            string keys = "";

            if (cbCtrl.Checked == true)
                keys += "^|";
            if (cbShift.Checked == true)
                keys += "+|";
            if (cbAlt.Checked == true)
                keys += "%";

            keys += txtKeyPress.Text;

            return keys;
        }

        string codingViev()
        {
            string keys = "";

            if (cbCtrl.Checked == true)
                keys += "CTRL + ";
            if (cbShift.Checked == true)
                keys += "SHIFT + ";
            if (cbAlt.Checked == true)
                keys += "ALT + ";

            keys += txtKeyPress.Text;

            return keys;
        }

        void addHex()
        {
            if (cbDoubleClicked.Checked == true)
            {
                dataGridView1.Rows.Add( txtFirstClick.Text,
                                        txtSecondClick.Text,
                                        codingViev(),
                                        codingKey()
                                        );
            }
            else
            {
                dataGridView1.Rows.Add( txtFirstClick.Text,
                                        txtFirstClick.Text,
                                        codingViev(),
                                        codingKey()
                                        );
            }
            
        }

        private void dataGridView1_CellContentDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            int id = dataGridView1.CurrentCellAddress.Y;
            dataGridView1.Rows.RemoveAt(id);
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            string save = "";

            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                if(i > 0)
                    save += "\n\x0001";

                save += dataGridView1.Rows[i].Cells[0].Value + "\n";
                save += dataGridView1.Rows[i].Cells[1].Value + "\n";
                save += dataGridView1.Rows[i].Cells[2].Value + "\n";
                save += dataGridView1.Rows[i].Cells[3].Value;
            }

            using (FileStream fs = File.Create(URL + @"\config.IR"))
            {
                Byte[] info = new UTF8Encoding(true).GetBytes(save);
                fs.Write(info, 0, info.Length);
            }

            
        }

        bool cancel = true;

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
            e.Cancel = cancel;
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            cancel = false;
            Application.Exit();
        }

        

        
    }
}

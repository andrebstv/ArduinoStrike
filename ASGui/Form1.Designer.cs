namespace WinFormsApp1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            button1 = new Button();
            button2 = new Button();
            abreConfig = new OpenFileDialog();
            panel1 = new Panel();
            txtLog = new TextBox();
            button3 = new Button();
            button4 = new Button();
            notifyIcon1 = new NotifyIcon(components);
            panel1.SuspendLayout();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(12, 572);
            button1.Name = "button1";
            button1.Size = new Size(75, 42);
            button1.TabIndex = 0;
            button1.Text = "Lê Config";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(93, 572);
            button2.Name = "button2";
            button2.Size = new Size(75, 42);
            button2.TabIndex = 1;
            button2.Text = "Escreve Config";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // abreConfig
            // 
            abreConfig.Filter = "Arquivos de Config.|*.json";
            abreConfig.InitialDirectory = "C:\\Diversos\\Arduino Strike\\ArduinoStrike\\ArduinoStrike\\x64\\Release";
            // 
            // panel1
            // 
            panel1.Controls.Add(txtLog);
            panel1.Location = new Point(12, 12);
            panel1.Name = "panel1";
            panel1.Size = new Size(407, 554);
            panel1.TabIndex = 2;
            // 
            // txtLog
            // 
            txtLog.Location = new Point(3, 3);
            txtLog.Multiline = true;
            txtLog.Name = "txtLog";
            txtLog.Size = new Size(401, 548);
            txtLog.TabIndex = 0;
            txtLog.Visible = false;
            // 
            // button3
            // 
            button3.Location = new Point(250, 572);
            button3.Name = "button3";
            button3.Size = new Size(75, 42);
            button3.TabIndex = 3;
            button3.Text = "Roda Processo";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // button4
            // 
            button4.Location = new Point(331, 572);
            button4.Name = "button4";
            button4.Size = new Size(75, 42);
            button4.TabIndex = 4;
            button4.Text = "Para Processo";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click;
            // 
            // notifyIcon1
            // 
            notifyIcon1.Icon = (Icon)resources.GetObject("notifyIcon1.Icon");
            notifyIcon1.Text = "Arduino Strike";
            notifyIcon1.Visible = true;
            notifyIcon1.MouseDoubleClick += notifyIcon1_MouseDoubleClick;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(431, 640);
            Controls.Add(button4);
            Controls.Add(button3);
            Controls.Add(panel1);
            Controls.Add(button2);
            Controls.Add(button1);
            Icon = (Icon)resources.GetObject("$this.Icon");
            MaximizeBox = false;
            Name = "Form1";
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Arduino Strike Gui";
            FormClosing += Form1_FormClosing;
            Load += Form1_Load;
            Resize += Form1_Resize;
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private Button button1;
        private Button button2;
        private OpenFileDialog abreConfig;
        private Panel panel1;
        private Button button3;
        private Button button4;
        private TextBox txtLog;
        private NotifyIcon notifyIcon1;
    }
}

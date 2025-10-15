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
            bt_le_config = new Button();
            bt_escreve_config = new Button();
            abreConfig = new OpenFileDialog();
            panel1 = new Panel();
            txtLog = new TextBox();
            bt_roda_processo = new Button();
            bt_para_processo = new Button();
            notifyIcon1 = new NotifyIcon(components);
            contextMenuStrip1 = new ContextMenuStrip(components);
            ativaOProcessoToolStripMenuItem = new ToolStripMenuItem();
            mataOProcessoToolStripMenuItem = new ToolStripMenuItem();
            ativaBTimerToolStripMenuItem = new ToolStripMenuItem();
            fechaOAppToolStripMenuItem = new ToolStripMenuItem();
            bt_bomb = new Button();
            panel1.SuspendLayout();
            contextMenuStrip1.SuspendLayout();
            SuspendLayout();
            // 
            // bt_le_config
            // 
            bt_le_config.Location = new Point(12, 572);
            bt_le_config.Name = "bt_le_config";
            bt_le_config.Size = new Size(75, 42);
            bt_le_config.TabIndex = 0;
            bt_le_config.Text = "Lê Config";
            bt_le_config.UseVisualStyleBackColor = true;
            bt_le_config.Click += button1_Click;
            // 
            // bt_escreve_config
            // 
            bt_escreve_config.Location = new Point(93, 572);
            bt_escreve_config.Name = "bt_escreve_config";
            bt_escreve_config.Size = new Size(75, 42);
            bt_escreve_config.TabIndex = 1;
            bt_escreve_config.Text = "Escreve Config";
            bt_escreve_config.UseVisualStyleBackColor = true;
            bt_escreve_config.Click += button2_Click;
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
            // 
            // bt_roda_processo
            // 
            bt_roda_processo.Location = new Point(250, 572);
            bt_roda_processo.Name = "bt_roda_processo";
            bt_roda_processo.Size = new Size(75, 42);
            bt_roda_processo.TabIndex = 3;
            bt_roda_processo.Text = "Roda Processo";
            bt_roda_processo.UseVisualStyleBackColor = true;
            bt_roda_processo.Click += button3_Click;
            // 
            // bt_para_processo
            // 
            bt_para_processo.Location = new Point(331, 572);
            bt_para_processo.Name = "bt_para_processo";
            bt_para_processo.Size = new Size(75, 42);
            bt_para_processo.TabIndex = 4;
            bt_para_processo.Text = "Para Processo";
            bt_para_processo.UseVisualStyleBackColor = true;
            bt_para_processo.Click += button4_Click;
            // 
            // notifyIcon1
            // 
            notifyIcon1.ContextMenuStrip = contextMenuStrip1;
            notifyIcon1.Icon = (Icon)resources.GetObject("notifyIcon1.Icon");
            notifyIcon1.Text = "Arduino Strike";
            notifyIcon1.Visible = true;
            notifyIcon1.MouseDoubleClick += notifyIcon1_MouseDoubleClick;
            // 
            // contextMenuStrip1
            // 
            contextMenuStrip1.Items.AddRange(new ToolStripItem[] { ativaOProcessoToolStripMenuItem, mataOProcessoToolStripMenuItem, ativaBTimerToolStripMenuItem, fechaOAppToolStripMenuItem });
            contextMenuStrip1.Name = "contextMenuStrip1";
            contextMenuStrip1.Size = new Size(162, 92);
            // 
            // ativaOProcessoToolStripMenuItem
            // 
            ativaOProcessoToolStripMenuItem.Name = "ativaOProcessoToolStripMenuItem";
            ativaOProcessoToolStripMenuItem.Size = new Size(161, 22);
            ativaOProcessoToolStripMenuItem.Text = "Ativa o processo";
            ativaOProcessoToolStripMenuItem.Click += ativaOProcessoToolStripMenuItem_Click;
            // 
            // mataOProcessoToolStripMenuItem
            // 
            mataOProcessoToolStripMenuItem.Name = "mataOProcessoToolStripMenuItem";
            mataOProcessoToolStripMenuItem.Size = new Size(161, 22);
            mataOProcessoToolStripMenuItem.Text = "Mata o processo";
            mataOProcessoToolStripMenuItem.Click += mataOProcessoToolStripMenuItem_Click;
            // 
            // ativaBTimerToolStripMenuItem
            // 
            ativaBTimerToolStripMenuItem.Name = "ativaBTimerToolStripMenuItem";
            ativaBTimerToolStripMenuItem.Size = new Size(161, 22);
            ativaBTimerToolStripMenuItem.Text = "Ativa BTimer";
            // 
            // fechaOAppToolStripMenuItem
            // 
            fechaOAppToolStripMenuItem.Name = "fechaOAppToolStripMenuItem";
            fechaOAppToolStripMenuItem.Size = new Size(161, 22);
            fechaOAppToolStripMenuItem.Text = "Fecha o app";
            fechaOAppToolStripMenuItem.Click += fechaOAppToolStripMenuItem_Click;
            // 
            // bt_bomb
            // 
            bt_bomb.Location = new Point(174, 572);
            bt_bomb.Name = "bt_bomb";
            bt_bomb.Size = new Size(70, 42);
            bt_bomb.TabIndex = 5;
            bt_bomb.Text = "Bomb\r\nTimer";
            bt_bomb.UseVisualStyleBackColor = true;
            bt_bomb.Click += bt_bomb_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(431, 640);
            Controls.Add(bt_bomb);
            Controls.Add(bt_para_processo);
            Controls.Add(bt_roda_processo);
            Controls.Add(panel1);
            Controls.Add(bt_escreve_config);
            Controls.Add(bt_le_config);
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
            contextMenuStrip1.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private Button bt_le_config;
        private Button bt_escreve_config;
        private OpenFileDialog abreConfig;
        private Panel panel1;
        private Button bt_roda_processo;
        private Button bt_para_processo;
        private TextBox txtLog;
        private NotifyIcon notifyIcon1;
        private Button bt_bomb;
        private ContextMenuStrip contextMenuStrip1;
        private ToolStripMenuItem ativaOProcessoToolStripMenuItem;
        private ToolStripMenuItem mataOProcessoToolStripMenuItem;
        private ToolStripMenuItem ativaBTimerToolStripMenuItem;
        private ToolStripMenuItem fechaOAppToolStripMenuItem;
    }
}

using System.Diagnostics;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Windows.Forms;
using System.Diagnostics;
using System.Windows;
using System.Runtime.InteropServices;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private string caminhoArquivo; // para guardar o JSON que foi aberto
        private JsonObject jsonObj; // armazenar o JSON carregado
        public class Config
        {
            public int ak47Key { get; set; }
            public int augKey { get; set; }
            public int autoAcceptKey { get; set; }
            public bool bhop { get; set; }
            public int colorBotKey { get; set; }
            public int colorThreshold { get; set; }
            public int confirmationKey { get; set; }
            public int famasKey { get; set; }
            public bool fastReload { get; set; }
            public int galilKey { get; set; }
            public int m4a1Key { get; set; }
            public int m4a4Key { get; set; }
            public int offKey { get; set; }
            public bool rapidFire { get; set; }
            public double sensitivity { get; set; }
            public int sgKey { get; set; }
            public int umpKey { get; set; }
            public double zoomSensitivity { get; set; }
        }

        // Importações do Windows API
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool AttachConsole(uint dwProcessId);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool FreeConsole();

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool SetConsoleCtrlHandler(ConsoleCtrlDelegate HandlerRoutine, bool Add);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool GenerateConsoleCtrlEvent(uint dwCtrlEvent, uint dwProcessGroupId);

        delegate bool ConsoleCtrlDelegate(uint CtrlType);

        const uint CTRL_C_EVENT = 0;


        private void button1_Click(object sender, EventArgs e)
        {
            // Abre o diálogo
            if (abreConfig.ShowDialog() == DialogResult.OK)
            {
                // Pega o arquivo selecionado
                string caminho = abreConfig.FileName;
                caminhoArquivo = abreConfig.FileName;
                string configuracoes = File.ReadAllText(abreConfig.FileName);

                Config config = JsonSerializer.Deserialize<Config>(configuracoes);
                // Exibe no TextBox
                //textBox1.Text = caminho;

                string json = File.ReadAllText(abreConfig.FileName);
                jsonObj = JsonNode.Parse(json).AsObject();

                // Limpa controles antigos
                panel1.Controls.Clear();

                panel1.Controls.Clear();
                int y = 10;

                foreach (var kv in jsonObj)
                {
                    Label lbl = new Label();
                    lbl.Text = kv.Key;
                    lbl.Left = 10;
                    lbl.Top = y;
                    lbl.Width = 100;

                    TextBox txt = new TextBox();
                    txt.Left = 120;
                    txt.Top = y;
                    txt.Width = 200;
                    txt.Text = kv.Value?.ToString();
                    txt.Name = "txt_" + kv.Key;

                    panel1.Controls.Add(lbl);
                    panel1.Controls.Add(txt);

                    y += 30;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (jsonObj == null)
            {
                MessageBox.Show("Nenhum JSON aberto.");
                return;
            }

            // Atualiza valores no JsonObject
            foreach (Control c in panel1.Controls)
            {
                if (c is TextBox txt)
                {
                    string key = txt.Name.Replace("txt_", "");
                    string valor = txt.Text;

                    if (int.TryParse(valor, NumberStyles.Integer, CultureInfo.InvariantCulture, out int i))
                        jsonObj[key] = i;
                    else if (double.TryParse(valor, NumberStyles.Float, CultureInfo.InvariantCulture, out double d))
                        jsonObj[key] = d;
                    else if (bool.TryParse(valor, out bool b))
                        jsonObj[key] = b;
                    else
                        jsonObj[key] = valor; // mantém string
                }
            }
            // Salva formatado
            File.WriteAllText(caminhoArquivo, jsonObj.ToJsonString(new JsonSerializerOptions { WriteIndented = true }));

            MessageBox.Show("Arquivo atualizado com sucesso!");
        }
        Process backend;
        private void button3_Click(object sender, EventArgs e)
        {
            string exePath = @"C:\Diversos\Arduino Strike\ArduinoStrike\ArduinoStrike\x64\Release\ArduinoStrike.exe";

            backend = new Process();
            backend.StartInfo.FileName = exePath;

            // Extrai automaticamente o diretório do executável
            backend.StartInfo.WorkingDirectory = Path.GetDirectoryName(exePath);
            backend.StartInfo.RedirectStandardOutput = true;
            backend.StartInfo.RedirectStandardError = true;
            backend.StartInfo.UseShellExecute = false;
            backend.StartInfo.CreateNoWindow = true;
            backend.OutputDataReceived += Backend_OutputDataReceived;
            backend.ErrorDataReceived += Backend_OutputDataReceived;
            backend.Start();
            backend.BeginOutputReadLine();
            backend.BeginErrorReadLine();
            txtLog.Visible = true;
        }
        private void Backend_OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            if (!string.IsNullOrEmpty(e.Data))
            {
                // Para Windows Forms:
                if (txtLog.InvokeRequired)
                {
                    txtLog.Invoke(new Action(() =>
                    {
                        txtLog.AppendText(e.Data + Environment.NewLine);
                        txtLog.SelectionStart = txtLog.Text.Length;
                        txtLog.ScrollToCaret();

                        if (e.Data.Contains("Console mode set"))
                        {
                            // Extraia o título se possível do log anterior
                        }
                    }));
                }
                else
                {
                    txtLog.AppendText(e.Data + Environment.NewLine);
                    txtLog.SelectionStart = txtLog.Text.Length;
                    txtLog.ScrollToCaret();
                }
            }
        }
        private void KillZXXCProcesses()
        {
            try
            {
                // Encontra TODOS os processos que começam com "ZXXC"
                var zxxcProcesses = Process.GetProcesses()
                    .Where(p =>
                    {
                        try
                        {
                            return p.ProcessName.StartsWith("ZXXZ", StringComparison.OrdinalIgnoreCase);
                        }
                        catch
                        {
                            return false;
                        }
                    })
                    .ToList();

                txtLog.Invoke(new Action(() =>
                {
                    txtLog.AppendText($"Encontrados {zxxcProcesses.Count} processo(s) ZXXZ\n");
                }));

                foreach (var proc in zxxcProcesses)
                {
                    try
                    {
                        txtLog.Invoke(new Action(() =>
                        {
                            txtLog.AppendText($"Enviando Ctrl+C para {proc.ProcessName} (ID: {proc.Id})\n");
                        }));

                        if (SendCtrlC(proc))
                        {
                            if (proc.WaitForExit(5000))
                            {
                                txtLog.Invoke(new Action(() =>
                                {
                                    txtLog.AppendText($"{proc.ProcessName} encerrado com sucesso\n");
                                }));
                            }
                            else
                            {
                                txtLog.Invoke(new Action(() =>
                                {
                                    txtLog.AppendText($"{proc.ProcessName} timeout, forçando kill\n");
                                }));
                                proc.Kill();
                            }
                        }
                        else
                        {
                            txtLog.Invoke(new Action(() =>
                            {
                                txtLog.AppendText($"Falha Ctrl+C em {proc.ProcessName}, forçando kill\n");
                            }));
                            proc.Kill();
                        }
                    }
                    catch (Exception ex)
                    {
                        txtLog.Invoke(new Action(() =>
                        {
                            txtLog.AppendText($"Erro em {proc.ProcessName}: {ex.Message}\n");
                        }));
                    }
                }

                backend?.Dispose();
            }
            catch (Exception ex)
            {
                txtLog.Invoke(new Action(() =>
                {
                    txtLog.AppendText($"Erro geral: {ex.Message}\n");
                }));
            }
        }

        private bool SendCtrlC(Process process)
        {
            try
            {
                FreeConsole();

                if (AttachConsole((uint)process.Id))
                {
                    SetConsoleCtrlHandler(null, true);
                    bool result = GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
                    Thread.Sleep(100);
                    FreeConsole();
                    SetConsoleCtrlHandler(null, false);
                    return result;
                }

                return false;
            }
            catch
            {
                return false;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            KillZXXCProcesses();
            //txtLog.Visible = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            KillZXXCProcesses();
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            // Restaura o form ao dar duplo clique no ícone
            this.Show();
            this.WindowState = FormWindowState.Normal;
            this.Activate();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            // Quando minimizar, esconde o form e mostra só no tray
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.Hide();
                notifyIcon1.Visible = true;
                notifyIcon1.ShowBalloonTip(1000, "Minimizado", "O aplicativo está rodando na bandeja", ToolTipIcon.Info);
            }
        }
    }
}

using System;
using System.Diagnostics; // Usaremos o Stopwatch para um timer preciso
using System.Numerics;
using ClickableTransparentOverlay;
using ImGuiNET;

namespace BombTimer
{
    public class Renderer : Overlay
    {
        // --- Variáveis de Controle do Timer ---
        public bool bombPlanted = false;
        private int initialTimeToBlow = 40; // Tempo inicial em segundos
        private float timeRemaining;       // Tempo restante em segundos (usar float para mais precisão)
        private Stopwatch stopwatch = new Stopwatch();

        // --- Variáveis de Configuração da UI ---
        private Vector4 redColor = new Vector4(1.0f, 0.0f, 0.0f, 0.85f); // Vermelho com um pouco de transparência
        private Vector4 whiteColor = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);
        private Vector2 windowSize = new Vector2(300, 150); // Aumentei o tamanho para acomodar texto grande
        private bool isRunning = true; // Flag para controlar o loop principal

        // Construtor foi limpo, pois a classe base já cuida do contexto ImGui.
        public Renderer() : base() { }

        // Método para "plantar a bomba" e iniciar o timer
        public void PlantBomb()
        {
            if (!bombPlanted)
            {
                bombPlanted = true;
                timeRemaining = initialTimeToBlow;
                stopwatch.Restart(); // Reinicia e começa a contar o tempo
            }
        }

        protected override void Render()
        {
            if (!isRunning) return;

            // --- Lógica do Timer ---
            if (bombPlanted)
            {
                // Calcula o tempo restante
                timeRemaining = initialTimeToBlow - (float)stopwatch.Elapsed.TotalSeconds;

                // Se o tempo acabar, reseta o estado
                if (timeRemaining <= 0)
                {
                    timeRemaining = 0;
                    bombPlanted = false;
                    stopwatch.Stop();
                }
            }

            // --- Renderização da Janela ImGui ---

            // Define o estilo da janela
            ImGui.PushStyleColor(ImGuiCol.WindowBg, redColor);
            ImGui.PushStyleColor(ImGuiCol.Text, whiteColor);
            ImGui.PushStyleVar(ImGuiStyleVar.WindowRounding, 10.0f); // Adiciona cantos arredondados

            // Pega o tamanho da tela para posicionar a janela
            var displaySize = ImGui.GetIO().DisplaySize;

            // --- POSICIONAMENTO ---
            // Para posicionar no centro da tela:
            var windowPos = new Vector2((displaySize.X - windowSize.X) * 0.5f, (displaySize.Y - windowSize.Y) * 0.5f);

            // Para posicionar no canto superior direito:
            // var windowPos = new Vector2(displaySize.X - windowSize.X - 10, 10);

            // Para posicionar no centro inferior:
            // var windowPos = new Vector2((displaySize.X - windowSize.X) * 0.5f, displaySize.Y - windowSize.Y - 20);

            ImGui.SetNextWindowSize(windowSize);
            ImGui.SetNextWindowPos(windowPos);

            // Flags para criar uma janela simples, sem bordas, título ou interações
            var flags = ImGuiWindowFlags.NoTitleBar |
                        ImGuiWindowFlags.NoResize |
                        ImGuiWindowFlags.NoMove |
                        ImGuiWindowFlags.NoScrollbar |
                        ImGuiWindowFlags.NoCollapse |
                        ImGuiWindowFlags.NoSavedSettings;

            if (ImGui.Begin("Bomb Timer Overlay", flags))
            {
                // Aumenta o tamanho da fonte DENTRO desta janela
                ImGui.SetWindowFontScale(5.0f);

                // Define o texto a ser exibido
                string textToShow;
                if (bombPlanted)
                {
                    // Formata o tempo para mostrar uma casa decimal
                    textToShow = $"{timeRemaining:F1}";
                }
                else
                {
                    textToShow = "Waiting...";
                }

                // --- FORMATAÇÃO (Centralização do Texto) ---

                // 1. Calcula o tamanho que o texto ocupará na tela
                var textSize = ImGui.CalcTextSize(textToShow);

                // 2. Calcula a posição horizontal para centralizar
                var textPosX = (windowSize.X - textSize.X) * 0.5f;

                // 3. Calcula a posição vertical para centralizar
                var textPosY = (windowSize.Y - textSize.Y) * 0.5f;

                // 4. Move o "cursor" de renderização para a posição calculada
                ImGui.SetCursorPos(new Vector2(textPosX, textPosY));

                // 5. Renderiza o texto
                ImGui.Text(textToShow);

                ImGui.End();
            }

            // Restaura os estilos
            ImGui.PopStyleColor(2);
            ImGui.PopStyleVar(1);
        }
    }
}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using ClickableTransparentOverlay;
using ImGuiNET;


namespace BombTimer
{
    public class Renderer : Overlay
    {
        private Vector4 redColor = new Vector4(1, 0, 0, 1);
        public bool bombPlanted = false;
        public int timeToBlow = -1;
        private bool isRunning = true;

        // Criar contexto no construtor
        public Renderer()
        {
            ImGui.CreateContext();
        }

        protected override void Dispose(bool disposing)
        {
            ImGui.DestroyContext();
            base.Dispose(disposing);
        }

        protected override void Render()
        {
            if (!isRunning) return;

            // Estilos
            ImGui.PushStyleColor(ImGuiCol.WindowBg, new Vector4(1, 0, 0, 1)); // fundo vermelho
            ImGui.PushStyleColor(ImGuiCol.Text, new Vector4(1, 1, 1, 1));     // texto branco

            var displaySize = ImGui.GetIO().DisplaySize;
            var windowSize = new Vector2(200, 100);

            // Posiciona a janela ImGui (não o overlay)
            //ImGui.SetNextWindowPos(new Vector2(displaySize.X - windowSize.X - 10, 10), ImGuiCond.Always);
            //ImGui.SetNextWindowPos(new System.Numerics.Vector2(10, Engine.Instance.GetScreenHeight() - size.Y - 10), ImGuiCond.Once);
            ImGui.SetNextWindowSize(windowSize, ImGuiCond.Always);
            //ImGui.Posi

            var flags = ImGuiWindowFlags.NoTitleBar | ImGuiWindowFlags.NoResize |
                        ImGuiWindowFlags.NoMove | ImGuiWindowFlags.NoScrollbar |
                        ImGuiWindowFlags.NoCollapse | ImGuiWindowFlags.NoSavedSettings;

            ImGui.Begin("Timer", flags);

            // Usar SetWindowFontScale ao invés de FontGlobalScale
            ImGui.SetWindowFontScale(3.0f);

            if (bombPlanted)
            {
                ImGui.Text($"{timeToBlow} s");
            }
            else
            {
                ImGui.Text("Waiting...");
            }

            ImGui.End();

            // Restaura estilos
            ImGui.PopStyleColor(2);
        }
    }
}


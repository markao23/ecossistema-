#include "Mapa.h"
#include "Animal.h"
#include <raylib.h>
#include <iostream>
#include <ctime>
#include <memory>

int main() {
    srand(time(nullptr));

    const int Widith = 1024;
    const int Height = 768;
    InitWindow(Widith, Height, "Ecossistema em 3D");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 15.0f, 12.0f, 15.0f }; // Câmera no alto, olhando na diagonal
    camera.target = (Vector3){ 5.0f, 0.0f, 5.0f };      // Ponto central do mapa (foco)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Eixo Y é o "teto"
    camera.fovy = 45.0f;                                // Campo de visão
    camera.projection = CAMERA_PERSPECTIVE;

    Mapa ecossitema(10, 10);
    ecossitema.adicionarAnimal(std::make_shared<Animal>("Lobo", 5, 5));
    ecossitema.adicionarAnimal(std::make_shared<Animal>("Coelho", 2, 8));

    SetTargetFPS(60);
    int frameCounter = 0;

    while (!WindowShouldClose())
    {
        frameCounter++;
        if (frameCounter >= 60)
        {
            ecossitema.atualizarTurno();
            frameCounter = 0;
        }
        if (!ecossitema.getAnimais().empty())
        {
            float centroX = 0.0f, centroY = 0.0f;

            for (const auto& animal : ecossitema.getAnimais()) {
                centroX += animal->x;
                centroY += animal->y;
            }
            centroX /= ecossitema.getAnimais().size();
            centroY /= ecossitema.getAnimais().size();

            camera.target = (Vector3){ centroX, 0.0f, centroY };
            camera.position = (Vector3){ centroX + 15.0f, 12.0f, centroY + 15.0f };
        }
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawGrid(20, 1.0f);
                    for (const auto& animal : ecossitema.getAnimais()) {
                        Vector3 pos = { (float)animal->x, 0.5f, (float)animal->y };
                        Color color = (animal->especie == "Lobo") ? RED : BLUE;

                        DrawSphere(pos, 0.4f, color);

                        Vector3 posCabeca = { pos.x, pos.y + 0.3f, pos.z + 0.2f };
                        DrawSphere(posCabeca, 0.25f, color);
                    }
            EndMode3D();
            DrawFPS(10, 10);
            DrawText("Lobo: Vermelho | Coelho: Azul", 10, 40, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
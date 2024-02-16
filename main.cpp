#include <stdio.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "dark/style_dark.h"

#include <string> 

#define MAX_COLUMNS 20

static void Button001(bool &windowActiv);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 1000;
    int screenHeight = 600;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Example Window");
    GuiLoadStyleDark();

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    bool WindowBox000Active = false;
    bool DropdownBox002EditMode = false;
    int DropdownBox002Active = 0;
    int ListView004ScrollIndex = 0;
    int ListView004Active = 0;
    //----------------------------------------------------------------------------------

    // SetTargetFPS(120);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------
        Camera camera = {0};
        camera.position = Vector3{4.0f, 3.0f, 4.0f};
        camera.target = Vector3{0.0f, 1.8f, 0.0f};
        camera.up = Vector3{0.0f, 1.0f, 0.0f};
        camera.fovy = 60.0f;
        camera.projection = CAMERA_ORTHOGRAPHIC;

        // Generates some random columns
        float heights[MAX_COLUMNS] = {0.0f};
        Vector3 positions[MAX_COLUMNS] = {0};
        Color colors[MAX_COLUMNS] = {0};

        for (int i = 0; i < MAX_COLUMNS; i++)
        {
            heights[i] = static_cast<float>(GetRandomValue(1, 12));
            positions[i] = Vector3{static_cast<float>(GetRandomValue(-15, 15)), heights[i] / 2, static_cast<float>(GetRandomValue(-15, 15))};
            colors[i] = Color{static_cast<unsigned char>(GetRandomValue(20, 255)), static_cast<unsigned char>(GetRandomValue(10, 55)), 30, 255};
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        BeginMode3D(camera);

        DrawPlane(Vector3{0.0f, 0.0f, 0.0f}, Vector2{32.0f, 32.0f}, LIGHTGRAY); // Draw ground
        DrawCube(Vector3{-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, BLUE);         // Draw a blue wall
        DrawCube(Vector3{16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIME);          // Draw a green wall
        DrawCube(Vector3{0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, GOLD);          // Draw a yellow wall

        // Draw some cubes around
        for (int i = 0; i < MAX_COLUMNS; i++)
        {
            DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
            DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
        }

        EndMode3D();

        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        if (DropdownBox002EditMode)
            GuiLock();

        if (GuiButton(Rectangle{float(GetScreenWidth() / 2) - 60, float(GetScreenHeight() / 2) - 12, 120, 24}, "A BUTTON"))
            Button001(WindowBox000Active);

        if (WindowBox000Active)
        {
            WindowBox000Active = !GuiWindowBox(Rectangle{280, 120, 480, 344}, "#198# SAMPLE TEXT");

            GuiStatusBar(Rectangle{280, 440, 120, 24}, "SAMPLE TEXT");
            GuiListView(Rectangle{552, 280, 120, 72}, "ONE;TWO;THREE", &ListView004ScrollIndex, &ListView004Active);
            if (GuiDropdownBox(Rectangle{328, 272, 120, 24}, "ONE;TWO;THREE", &DropdownBox002Active, DropdownBox002EditMode))
                DropdownBox002EditMode = !DropdownBox002EditMode;
        }

        GuiUnlock();
        //----------------------------------------------------------------------------------
        std::string fpsText = "FPS: " + std::to_string(GetFPS());
        GuiStatusBar(Rectangle{0, (float)GetScreenHeight() - 20, (float)GetScreenWidth(), 20}, fpsText.c_str());
        //DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
static void Button001(bool &windowActiv)
{
    // TODO: Implement control logic
    windowActiv = !windowActiv;
}

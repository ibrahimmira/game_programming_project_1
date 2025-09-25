/**
* Author: Ibrahim Mira
* Assignment: Simple 2D Scene
* Date due: 2025-09-27, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "CS3113/cs3113.h"


// Global Constants
constexpr int   SCREEN_WIDTH  = 1600,
                SCREEN_HEIGHT = 900,
                FPS           = 60,
                SIZE          = 300;

constexpr char    BG_COLOUR[] = "#710000ff";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
constexpr Vector2 BASE_SIZE   = { (float) SIZE, (float) SIZE };

constexpr Vector2 REGERA_SIZE  = { (float) 1200, (float) 673 };
constexpr Vector2 FLASH_SIZE   = { (float) 1024, (float) 1202 };
constexpr Vector2 CAMERA_SIZE  = { (float) 965, (float) 723 };

constexpr char REGERA[]  = "assets/regera.png";
constexpr char FLASH[]  = "assets/flash.png";
constexpr char CAMERA[]  = "assets/camera.png";

// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gScaleFactor   = SIZE,
          gAngle         = 0.0f,
          gPulseTime     = 0.0f;
Vector2   gPosition      = ORIGIN;
Vector2   gScale         = CAMERA_SIZE;
float     gPreviousTicks = 0.0f;

Texture2D gTexture;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures");

    gTexture = LoadTexture(CAMERA);

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    // Nothing to update
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    // Whole texture (UV coordinates)
    Rectangle textureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gTexture.width),
        static_cast<float>(gTexture.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        gPosition.x,
        gPosition.y,
        static_cast<float>(gScale.x),
        static_cast<float>(gScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 objectOrigin = {
        static_cast<float>(gScale.x) / 2.0f,
        static_cast<float>(gScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        gTexture, 
        textureArea, 
        destinationArea, 
        objectOrigin, 
        gAngle, 
        WHITE
    );

    EndDrawing();
}

void shutdown() { CloseWindow(); }

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}


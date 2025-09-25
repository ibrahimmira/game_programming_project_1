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
constexpr Vector2 FLASH_SIZE   = { (float) 512, (float) 601 };
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

Vector2   gFlashScale    = FLASH_SIZE;
Vector2   gRegeraScale   = REGERA_SIZE;
Vector2   gCameraScale   = CAMERA_SIZE;

Vector2   gScale         = BASE_SIZE;
float     gPreviousTicks = 0.0f;

Texture2D gTextureFLASH;
Texture2D gTextureREGERA;
Texture2D gTextureCAMERA;

// Function Declarations
void drawFlash();
void drawRegera();
void drawCamera();
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void drawFlash() {
    
    // Whole texture (UV coordinates)
    Rectangle FlashTextureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gTextureFLASH.width),
        static_cast<float>(gTextureFLASH.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle FlashDestinationArea = {
        gPosition.x,
        gPosition.y,
        static_cast<float>(gFlashScale.x),
        static_cast<float>(gFlashScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 FlashObjectOrigin = {
        static_cast<float>(gFlashScale.x) / 2.0f,
        static_cast<float>(gFlashScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        gTextureFLASH, 
        FlashTextureArea, 
        FlashDestinationArea, 
        FlashObjectOrigin, 
        gAngle, 
        WHITE
    );
}

void drawRegera() {
    
    // Whole texture (UV coordinates)
    Rectangle RegeraTextureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gTextureREGERA.width),
        static_cast<float>(gTextureREGERA.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle RegeraDestinationArea = {
        gPosition.x,
        gPosition.y,
        static_cast<float>(gRegeraScale.x),
        static_cast<float>(gRegeraScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 RegeraObjectOrigin = {
        static_cast<float>(gRegeraScale.x) / 2.0f,
        static_cast<float>(gRegeraScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        gTextureREGERA, 
        RegeraTextureArea, 
        RegeraDestinationArea, 
        RegeraObjectOrigin, 
        gAngle, 
        WHITE
    );
}

void drawCamera() {
    
    // Whole texture (UV coordinates)
    Rectangle CameraTextureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(gTextureCAMERA.width),
        static_cast<float>(gTextureCAMERA.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle CameraDestinationArea = {
        gPosition.x,
        gPosition.y,
        static_cast<float>(gCameraScale.x),
        static_cast<float>(gCameraScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 CameraObjectOrigin = {
        static_cast<float>(gCameraScale.x) / 2.0f,
        static_cast<float>(gCameraScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        gTextureCAMERA, 
        CameraTextureArea, 
        CameraDestinationArea, 
        CameraObjectOrigin, 
        gAngle, 
        WHITE
    );
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures");

    gTextureFLASH  = LoadTexture(FLASH);
    gTextureREGERA = LoadTexture(REGERA);
    gTextureCAMERA = LoadTexture(CAMERA);

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

    drawFlash();
    drawRegera();
    drawCamera();

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


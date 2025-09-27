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
#include "math.h"

// Global Constants
constexpr int   SCREEN_WIDTH  = 1366,
                SCREEN_HEIGHT = 768,
                FPS           = 60,
                SIZE          = 300,
                BG_COUNT      = 5;

constexpr Vector2   REGERA_SIZE  = { (float) 1200, (float) 673 },
                    FLASH_SIZE   = { (float) 512, (float) 601 },
                    CAMERA_SIZE  = { (float) 965, (float) 723 };

constexpr char REGERA[]  = "assets/regera.png";
constexpr char FLASH[]  = "assets/flash.png";
constexpr char CAMERA[]  = "assets/camera.png";

const char* BG_PALETTE[] = {
    "#710000ff", 
    "#2a0033ff", 
    "#001d4dff", 
    "#004d26ff", 
    "#4d2a00ff"  
};

constexpr float FLASH_MIN_FACTOR = 1.0f / 12.0f,
                FLASH_MAX_FACTOR = 1.5f,
                FLASH_GROWTH_K   = 0.9f,
                FLASH_BASE_SPEED = 120.0f,
                FLASH_BOB_AMP    = 40.0f,
                FLASH_BOB_FREQ   = 3.0f,

                REGERA_ANGULAR_SPEED = 0.6f,
                REGERA_ELLIPSE_RADIUSX = 80.0F,
                REGERA_ELLIPSE_RADIUSY = 30.0F,

                CAMERA_ORBIT_SPEED = 1.1F,
                CAMERA_ORBIT_RADIUSX = 330.0F,
                CAMERA_ORBIT_RADIUSY = 190.0F;

// Global Variables
AppStatus   gAppStatus     = RUNNING;

float       gFlashTime     = 0.0f,
            gAngle         = 0.0f,
            gPulseTime     = 0.0f,
            gCameraAngle   = 0.0f,
            gPreviousTicks = 0.0f;

Vector2     gFlashScale    = { FLASH_SIZE.x * FLASH_MIN_FACTOR, FLASH_SIZE.y * FLASH_MIN_FACTOR },
            gRegeraScale   = { REGERA_SIZE.x / 2.0f, REGERA_SIZE.y / 2.0f },
            gCameraScale   = { CAMERA_SIZE.x / 9.0f, CAMERA_SIZE.y / 9.0f },

            gFlashPosition = { gFlashScale.x / 2.0f, SCREEN_HEIGHT - gFlashScale.y / 2.0f },
            
            gRegeraBasePosition = { SCREEN_WIDTH / 2.0f - 250.0f, SCREEN_HEIGHT / 2.0f - 150.0f },
            gRegeraPosition = { gRegeraScale.x / 2.0f, gRegeraScale.y / 2.0f },

            gCameraPosition = { SCREEN_WIDTH - gCameraScale.x / 2.0f, gCameraScale.y / 2.0f };
            
int         gBgIndex = 0;

Texture2D   gTextureFLASH;
Texture2D   gTextureREGERA;
Texture2D   gTextureCAMERA;

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
        gFlashPosition.x,
        gFlashPosition.y,
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
        gRegeraPosition.x,
        gRegeraPosition.y,
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
        gCameraPosition.x,
        gCameraPosition.y,
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
        gCameraAngle, 
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

    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    gPulseTime += 1.0f * deltaTime;

    // Flash Animation
    gFlashTime += deltaTime;

    float growth = expf(FLASH_GROWTH_K * gFlashTime),
          factor = FLASH_MIN_FACTOR * growth,
          speed = FLASH_BASE_SPEED * growth;

    if (factor > FLASH_MAX_FACTOR) factor = FLASH_MAX_FACTOR;

    gFlashScale.x = FLASH_SIZE.x * factor;
    gFlashScale.y = FLASH_SIZE.y * factor;

    gFlashPosition.x += speed * deltaTime;
    gFlashPosition.y = SCREEN_HEIGHT - gFlashScale.y * 0.5f
                       - FLASH_BOB_AMP * sinf(gPulseTime * FLASH_BOB_FREQ);

    // Extra Credit
    if (gFlashPosition.x - gFlashScale.x * 0.5f > SCREEN_WIDTH) {
        gBgIndex = (gBgIndex + 1) % BG_COUNT;

        gFlashTime = 0.0f;
        gFlashScale.x = FLASH_SIZE.x * FLASH_MIN_FACTOR;
        gFlashScale.y = FLASH_SIZE.y * FLASH_MIN_FACTOR;
        gFlashPosition.x = gFlashScale.x * 0.5f;
        gFlashPosition.y = SCREEN_HEIGHT - gFlashScale.y * 0.5f;
    }
    
    // ٍRegera Animation
    gRegeraPosition.x = gRegeraBasePosition.x + REGERA_ELLIPSE_RADIUSX * cosf(REGERA_ANGULAR_SPEED * gPulseTime);
    gRegeraPosition.y = gRegeraBasePosition.y + REGERA_ELLIPSE_RADIUSY * sinf(2.0f * REGERA_ANGULAR_SPEED * gPulseTime);
    
    // Camera Animation (follows the Regera)
    float theta = CAMERA_ORBIT_SPEED * gPulseTime;

    gCameraPosition.x = gRegeraPosition.x + CAMERA_ORBIT_RADIUSX * cosf(theta);
    gCameraPosition.y = gRegeraPosition.y + CAMERA_ORBIT_RADIUSY * sinf(theta);

    gCameraAngle = 10.0f * sinf(theta);
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_PALETTE[gBgIndex]));

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

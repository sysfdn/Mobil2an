#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "class/Terrains.hpp"
#include "class/Car.hpp"
#include "class/functions.hpp"
#include <iostream>

// Constants
GLdouble WIDTH = 640;
GLdouble HEIGHT = 800;
GLdouble pixel = 100;

Terrains *terrains = new Terrains();
Car *cars0 = new Car("red");
Car *cars1 = new Car("purple");
Car *cars2 = new Car("purple");
Car *cars3 = new Car("purple");

char programName[] = "Mobil2an";
int FPS = 60;
int GAMESTATE = 0;
int score = 0;
int highScore = 0;
bool gameOver = false;
double speed = 0.5;

double lane = 30;
double positiion = 100;
double lane_1 = 50;
double positiion_1 = 125;
double lane_2 = 70;
double positiion_2 = 150;

void init()
{
    glOrtho(0, pixel, 0, pixel, -1, 1);
}

void mainMenu()
{
    drawBox(25, 80, 75, 85, 238, 238, 238);
    drawText("Mobil2an Geming", GLUT_BITMAP_HELVETICA_18, 40, 81, 43, 51, 95);

    drawBox(25, 40, 75, 50, 0, 0, 0);
    drawText("Press S to Start", GLUT_BITMAP_HELVETICA_18, 30, 41, 43, 51, 95);
    drawText("Press X to Exit", GLUT_BITMAP_HELVETICA_18, 30, 45, 43, 51, 95);
}

void setOtherCar()
{
    cars1->OtherRespawn(lane, positiion);
    cars2->OtherRespawn(lane_1, positiion_1);
    cars3->OtherRespawn(lane_2, positiion_2);

    positiion -= speed;
    positiion_1 -= speed;
    positiion_2 -= speed;
    if (positiion <= -10)
    {
        positiion = 100;
        lane = 25 + (std::rand() % (70 - 25 + 1));
        score += 1;
    }
    if (positiion_1 <= -10)
    {
        positiion_1 = 100;
        lane_1 = 25 + (std::rand() % (70 - 25 + 1));
        score += 1;
    }

    if (positiion_2 <= -10)
    {
        positiion_2 = 100;
        lane_2 = 25 + (std::rand() % (70 - 25 + 1));
        score += 1;
    }
    if (score % 2 == 1)
    {
        speed += 0.0001;
    }

    if ((abs(cars0->car_x - lane) < 6) && (positiion <= 10))
    {
        GAMESTATE = 0;
    }
    else if ((abs(cars0->car_x - lane_1) < 6) && (positiion_1 <= 10))
    {
        GAMESTATE = 0;
    }
    else if ((abs(cars0->car_x - lane_2) < 6) && (positiion_2 <= 10))
    {
        GAMESTATE = 0;
    }

    if (GAMESTATE == 0)
    {
        lane = 30;
        positiion = 100;
        lane_1 = 50;
        positiion_1 = 125;
        lane_2 = 70;
        positiion_2 = 150;
        speed = 0.5;
        if (score >= highScore)
        {
            highScore = score;
        }
        score = 0;
    }
}

void onGame()
{
    setOtherCar();
    cars0->Respawn();

    if (highScore)
    {
        char text_highscore[20];
        sprintf(text_highscore, "HighScore: %i", highScore);
        drawText(text_highscore, GLUT_BITMAP_HELVETICA_18, 0, 96, 238, 238, 238);
    }
    char text_score[20];
    sprintf(text_score, "Score: %i", score);
    drawText(text_score, GLUT_BITMAP_HELVETICA_18, 0, 93, 238, 238, 238);

    char text_fps[10] = "Speed:";
    drawText(text_fps, GLUT_BITMAP_HELVETICA_18, 0, 90, 238, 238, 238);

    char text_speed[20];
    sprintf(text_speed, "%f km/s", speed * 100);
    drawText(text_speed, GLUT_BITMAP_HELVETICA_18, 0, 87, 238, 238, 238);
}

void gameState()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.098, 0.584, 0.611, 0);
    terrains->drawStreet();
    if (GAMESTATE == 1)
    {
        onGame();
    }
    else
    {
        mainMenu();
    }
    glFlush();
}

void onMainMenu(unsigned char key, int x, int y)
{
    if (key == 's' || key == 'S')
    {
        GAMESTATE = 1;
    }
    else if (key == 'x' || key == 'X')
    {
        exit(0);
    }
}

void onKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        cars0->car_x += 1;
    }
    if (key == GLUT_KEY_LEFT)
    {
        cars0->car_x -= 1;
    }
    if (key == GLUT_KEY_UP)
    {
    }

    if (cars0->car_x <= 22)
    {
        cars0->car_x = 22;
    }
    if (cars0->car_x >= 71)
    {
        cars0->car_x = 71;
    }
}

void Timer(int value)
{
    glutTimerFunc(1000 / FPS, Timer, value);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow(programName);
    init();
    glutSpecialFunc(onKeyboard);
    glutKeyboardFunc(onMainMenu);
    glutDisplayFunc(gameState);
    Timer(0);
    glutMainLoop();
    return 0;
}
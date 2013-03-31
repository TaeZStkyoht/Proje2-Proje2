/***********
Oguzhan Turk
040080232
***********/

#include<math.h>

#include<GL/glut.h>

#define PI 3.14159265

GLfloat player1X=-0.95, player1Y=0, player1Z=0, player2X=0.95, player2Y=0, player2Z=0, ballX=0, ballY=0, ballZ=0;
GLint direction=1;
GLdouble angle=90, ballSpeed=0.006;

void Display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix(); /* 1. oyuncu cubugu */
	glColor3f(1, 1, 1);
	glTranslatef(player1X, player1Y, player1Z);
	glRectf(-.01, -.2, .01, .2);
	glPopMatrix();
	glPushMatrix(); /* 2. oyuncu cubugu */
	glColor3f(1, 1, 1);
	glTranslatef(player2X, player2Y, player2Z);
	glRectf(-.01, -.2, .01, .2);
	glPopMatrix();
	glPushMatrix(); /* Top */
	glColor3f(direction==1?1:0, direction==2?1:0, !direction?1:0);
	glTranslatef(ballX, ballY, ballZ);
	if(direction==1){ /* Yon saga ise */
		ballX+=ballSpeed;
		ballY+=(ballSpeed*cos(angle*PI/180)/sin(angle*PI/360));
		if(ballX>=player2X-0.025 && ballY<=player2Y+0.225 && ballY>=player2Y-0.225){ /* x ekseninde yon degistir */
			direction=0;
			angle=90-(ballY-player2Y)*45/0.225;
		}
		else if(ballY>=0.99 || ballY<=-0.99) angle*=-1; /* y ekseninde yon degistir */
		else if(ballX>player2X+0.02) direction=2; /* Topu durdur */
	}
	else if(!direction){ /* Yon sola ise */
		ballX-=ballSpeed;
		ballY+=(ballSpeed*cos(angle*PI/180)/sin(angle*PI/360));
		if(ballX<=player1X+0.025 && ballY<=player1Y+0.225 && ballY>=player1Y-0.225){ /* x ekseninde yon degistir */
			direction=1;
			angle=90-(ballY-player1Y)*45/0.225;
		}
		else if(ballY>=0.99 || ballY<=-0.99) angle*=-1; /* y ekseninde yon degistir */
		else if(ballX<player1X-0.02) direction=2; /* Topu durdur */
	}
	glRectf(-.01, -.01, .01, .01);
	glPopMatrix();
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y){
   switch(key){
   case 27: /* Cikis */
	   exit(0);
	   break;
   case 's': /* 1. oyuncu icin asagi tusu */
   case 'S':
	   if(player1Y>-0.78) player1Y-=0.025;
	   break;
   case 'w': /* 1. oyuncu icin yukari tusu */
   case 'W':
	   if(player1Y<0.78) player1Y+=0.025;
	   break;
   case 'r': /* Albastan */
   case 'R':
	   player1X=-0.95;
	   player1Y=0;
	   player1Z=0;
	   player2X=0.95;
	   player2Y=0;
	   player2Z=0;
	   ballX=0;
	   ballY=0;
	   ballZ=0;
	   direction=1;
	   angle=90;
	   ballSpeed=0.006;
	   break;
   }
}

void SpecialKeyboard(int key, int x, int y){
   switch(key){
   case GLUT_KEY_DOWN: /* 2. oyuncu icin asagi tusu */
	   if(player2Y>-0.78) player2Y-=0.025;
	   break;
   case GLUT_KEY_UP: /* 2. oyuncu icin yukari tusu */
	   if(player2Y<0.78) player2Y+=0.025;
	   break;
   }
}

void Reshape(int width, int height){
    GLfloat fAspect;
    if(height==0) height=1;
    glViewport(0, 0, width, height);
    fAspect = (GLfloat)width/(GLfloat)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Timer(int value){
	ballSpeed+=0.000001; /* Top zamanla hizlanir */
	glutPostRedisplay();
	glutTimerFunc(15, Timer, 1);
}

void Init(){
	glClearColor(0, 0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_PROJECTION);
}


int main(int argc, char *argv[]){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutCreateWindow("Pong");

    Init();
    glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	Timer(0);

    glutMainLoop();

    return 0;
}

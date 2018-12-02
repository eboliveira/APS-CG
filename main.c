#include <GL/glut.h>

int ball1_center[3] = {-2,-2,0};
int ball5_center[3]= {2,-2,0};
int rotate_vector[3] = {0,0,0};

void iluminacao(){
    //define a posição e parâmetros da luz 0
    float position[4] = {5.0f, 5.0f, 5.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //ativando luz ambiente global
    float global_ambient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    //ativa a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(1, 1, 1, //posição da câmera
              0.0, 0.0, 0.0, //para onde a câmera aponta
              0.0, 1.0, 0.0); //vetor viewup
    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);

    iluminacao();
    return 0;
}



void display(){
    //limpa o buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //define material da superfície
    float kd[4] = {0.65f, 0.65f, 0.0f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    //define que a matrix é a a model view
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4);
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        //ball 1 lines
        glVertex3f(-2,-1.5,0);
        glVertex3f(-2,3,-2);

        glVertex3f(-2,-1.5,0);
        glVertex3f(-2,3,2);

        //ball 2 lines
        glVertex3f(-1,-1.5,0);
        glVertex3f(-1,3,-2);

        glVertex3f(-1,-1.5,0);
        glVertex3f(-1,3,2);

        //ball 3 lines
        glVertex3f(0,-1.5,0);
        glVertex3f(0,3,-2);

        glVertex3f(0,-1.5,0);
        glVertex3f(0,3,2);

        //ball 4 lines
        glVertex3f(1,-1.5,0);
        glVertex3f(1,3,-2);

        glVertex3f(1,-1.5,0);
        glVertex3f(1,3,2);

        //ball 5 lines
        glVertex3f(2,-1.5,0);
        glVertex3f(2,3,2);

        glVertex3f(2,-1.5,0);
        glVertex3f(2,3,-2);
    glEnd();
    glLineWidth(10);
    glBegin(GL_LINES);
        //bars
        glVertex3f(-2,3,-2);
        glVertex3f(3,3,-2);

        glVertex3f(-2,3,2);
        glVertex3f(3,3,2);

        //support 1
        glVertex3f(-2,3,-2);
        glVertex3f(-2,6,0);

        glVertex3f(-2,6,0);
        glVertex3f(-2,3,2);

        glVertex3f(-2,3,-2);
        glVertex3f(-2,3,2);

        //support 2
        glVertex3f(3,3,-2);
        glVertex3f(3,6,0);

        glVertex3f(3,6,0);
        glVertex3f(3,3,2);

        glVertex3f(3,3,-2);
        glVertex3f(3,3,2);
    glEnd();

    glPushMatrix();
        glTranslatef(-2,-2,0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1,-2,0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,-2,0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1,-2,0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(ball5_center[0],ball5_center[1],0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();

    //força o desenho das primitivas
    glutSwapBuffers();
}

void Timer(int value){
    ball5_center[0]+=0.1;
    ball5_center[1]+=0.1;
    glutPostRedisplay();
    glutTimerFunc(1000, Timer, 1);
}

int main(int argc, char** argv){
    glutInit(&argc,argv);                           //inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);    //configura o modo de display
    glutInitWindowPosition(200,0);                  //seta a posição inicial da janela
    glutInitWindowSize(400,400);                    //configura a largura e altura da janela de exibição
    glutCreateWindow("Exemplo 4 - Propriedades da Superficie");                 //cria a janela de exibição
    // glutTimerFunc(1000, Timer, 1);
    init();                                         //executa função de inicialização
    glutDisplayFunc(display);
    glutMainLoop();                                  //mostre tudo e espere
    return 0;

}

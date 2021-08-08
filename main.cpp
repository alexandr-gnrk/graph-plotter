#include <iostream>
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>
#include <cmath>

using namespace std;

#define PI 3.14159265358979323846
#define WIDTH 700
#define HEIGHT 700
#define NUM_DVS 250
#define MAX_STR_LEN 256
#define	MAX_VIEW 3
#define FONT_1 GLUT_BITMAP_8_BY_13
#define FONT_2 GLUT_BITMAP_HELVETICA_10
#define A 4


inline void ColorDefault();
inline void DrawRectangle(double x1, double y1, double x2, double y2);
inline void PosDefault();
void IntToStr(int number, char *string);
void Calculation();
double Max(double x, double y);
void RenderScene(void);
void ChangeSize(int w, int h);
void MouseButton(int button, int state, int x, int y);
void MouseMove(int x, int y);
void RenderBitmapString(double x, double y, double z, void *font, char *string);


double x_min = -20, x_max = 20;
double fi_min = 0, fi_max = 2 * PI;
double max_arg, argument, scale, scale_sep, dx, dfi, y_min = 0, y_max = 0, x, y;
double cx[NUM_DVS], cy[NUM_DVS];
double rx[2], ry[2];
double x_1, y_1, x_2, y_2;
int pressed = 0; 


int main(int argc, char **argv)
{
	// инициализация
	glutInit(&argc, argv);
	Calculation();
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Graph plotter");
 

	glutDisplayFunc(RenderScene);				// регистрация обратных вызовов

	glutMouseFunc(MouseButton);					// изменение масштаба
	glutMotionFunc(MouseMove);
 	glutIdleFunc(RenderScene);
	glutReshapeFunc(ChangeSize);				// Новая функция изменения размеров окна
	
	glutMainLoop();								// Основной цикл GLUT
 
	return 0;
}


inline void ColorDefault()
{
	glColor3ub(255, 255, 255);
}


void Calculation()
{
	int i;
	double ro;
	dx = (x_max - x_min) / (NUM_DVS - 1.0);		// вычисление изменения аргумента
	
	i = 0;										// вычисление функции на заданом отрезке
	for (argument = x_min; argument <= x_max; argument += dx) {
		cx[i] = argument;
		cy[i] = cos(argument); 						// функция
		if (cy[i] > y_max) {
			y_max = cy[i];
		}
		if (cy[i] < y_min) {
			y_min = cy[i];
		}
		i++;
	}

	// dfi = (fi_max - fi_min) / (NUM_DVS - 1.0);		// вычисление изменения аргумента
	
	// i = 0;										// вычисление функции на заданом отрезке
	// for (argument = fi_min; argument <= fi_max; argument += dfi) {
	// 	ro = A * sqrt(cos(2 * argument));
	// 	cx[i] = ro * cos(argument);
	// 	cy[i] = ro * sin(argument); 						// функция
	// 	if (cy[i] > y_max) {
	// 		y_max = cy[i];
	// 	}
	// 	if (cy[i] < y_min) {
	// 		y_min = cy[i];
	// 	}
	// 	i++;
	// }

	rx[0] = x_1 * x_max;
	ry[0] = cos(rx[0]);
	rx[1] = x_2 * x_max;
	ry[1] = cos(rx[1]);


	max_arg = Max(Max(-x_min, x_max), Max(-y_min, y_max));
	scale_sep = round(max_arg / 8);				// вычисление масштаба графика
	scale = 1 / max_arg;
	if (scale_sep == 0) {
		cout << "The scopes are too small" << endl;
		exit(1);
	}
}


double Max(double x, double y)
{
	if (x > y) {
		return x;
	}
	return y;
}


void RenderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(33, 33, 33);
	glBegin(GL_QUADS);
		glVertex3d(-100.0, -100.0, -1.0);
		glVertex3d(-100.0, 100.0, -1.0);
		glVertex3d(100.0, 100.0, -1.0);
		glVertex3d(100.0, -100.0, -1.0);
	glEnd();
	ColorDefault();

	glColor3ub(180, 180, 180);
	glBegin(GL_LINES);
		
		glVertex3d(0.0, -100.0, -1.0);			// оси OX и OY соответственно
		glVertex3d(0.0, 100.0, -1.0);
		glVertex3d(-100.0, 0.0, -1.0);
		glVertex3d(100.0, 0.0, -1.0);
		
		glVertex3d(1.0, 0.0, -1.0);				// направление оси OX
		glVertex3d(0.97, -0.015, -1.0);
		glVertex3d(0.97, 0.015, -1.0);
		glVertex3d(1.0, 0.0, -1.0);
		
		glVertex3d(0.0, 1.0, -1.0);				// направление оси OY
		glVertex3d(-0.015, 0.97, -1.0);
		glVertex3d(0.015, 0.97, -1.0);
		glVertex3d(0.0, 1.0, -1.0);

	glEnd();
	ColorDefault();



	

	double cod;									// масштабные обозначения
	glBegin(GL_LINES);
		for (cod = scale; cod < MAX_VIEW; cod += scale) {
			
			glColor3ub(50, 50, 50);
			glVertex3d(cod, 100.0, -1.0);
			glVertex3d(cod, -100.0, -1.0);

			glVertex3d(-cod, 100.0, -1.0);
			glVertex3d(-cod, -100.0, -1.0);

			glVertex3d(100.0, cod, -1.0);
			glVertex3d(-100.0, cod, -1.0);

			glVertex3d(100.0, -cod, -1.0);
			glVertex3d(-100.0, -cod, -1.0);  
		}
	glEnd();
	ColorDefault();

	glBegin(GL_LINES);
		for (cod = scale_sep * scale; cod < MAX_VIEW; cod += scale_sep * scale) {
			
			glColor3ub(80, 80, 80);
			glVertex3d(cod, 100.0, -1.0);
			glVertex3d(cod, -100.0, -1.0);

			glVertex3d(-cod, 100.0, -1.0);
			glVertex3d(-cod, -100.0, -1.0);

			glVertex3d(100.0, cod, -1.0);
			glVertex3d(-100.0, cod, -1.0);

			glVertex3d(100.0, -cod, -1.0);
			glVertex3d(-100.0, -cod, -1.0);


			glColor3ub(180, 180, 180);
			glVertex3d(cod, 0.01, -1.0);
			glVertex3d(cod, -0.01, -1.0);

			glVertex3d(-cod, 0.01, -1.0);
			glVertex3d(-cod, -0.01, -1.0);

			glVertex3d(0.01, cod, -1.0);
			glVertex3d(-0.01, cod, -1.0);

			glVertex3d(0.01, -cod, -1.0);
			glVertex3d(-0.01, -cod, -1.0);  
		}
	glEnd();
	ColorDefault();

	double num;
	glColor3ub(180, 180, 180);
	num = scale_sep;							// вывод масштаба в виде чисел
	cod = scale_sep * scale;
	while (cod < MAX_VIEW) {
		char str_num[MAX_STR_LEN];
		IntToStr(num, str_num);
		RenderBitmapString(cod + 0.01 , 0.015, -1.0, FONT_2, str_num);
		RenderBitmapString(0.015, cod + 0.01, -1.0, FONT_2, str_num);
		IntToStr(-num, str_num);

		RenderBitmapString(-cod + 0.01 , 0.015, -1.0, FONT_2, str_num);
		RenderBitmapString(0.015, -cod + 0.01, -1.0, FONT_2, str_num);
		cod += scale_sep * scale;
		num += scale_sep;
	}

	glColor3ub(100, 100, 100);
	RenderBitmapString(0.5, 0.95, -0.995, FONT_1, (char*) "Made by Honcharuk");
	RenderBitmapString(0.40, 0.90, -0.995, FONT_1, (char*) "p^2 - a^2 * cos(2 * u) = 0");
	ColorDefault();

	
	glBegin(GL_LINE_STRIP);						// 	рисование графика функции
		for (int i = 0; i < NUM_DVS - 1; i++) {
			glVertex3d(cx[i] * scale, cy[i] * scale, -1.0);
		}
	glEnd();

	DrawRectangle(x_1, y_1, x_2, y_2);
	

	glutSwapBuffers();
}


// функция изменение размеров окна
void ChangeSize(int w, int h)
{
	
	if(h == 0) {								// предупредим деление на ноль
		h = 1;									// если окно будет сильно "перетянуто"
	}

	double ratio = 1.0* w / h;
 
	glMatrixMode(GL_PROJECTION);				// используем матрицу проекции

	glLoadIdentity();							// Reset матрицы
 
	glViewport(0, 0, w, h);						// определяем окно просмотра
 
	gluPerspective(90, ratio, 0, 1000);			// установить корректную перспективу
 
	glMatrixMode(GL_MODELVIEW);					// вернуться к модели
}


inline void PosDefault()
{
	x_1 = y_1 = x_2 = y_2 = 0;
}


void MouseButton(int button, int state, int x, int y)
{
	switch (button) {
		case 4:
			if (state == GLUT_UP) {
				x_min -= 1;
				x_max += 1;
			}
			if (x_min > -8) { x_min = -8; }
			if (x_max < 8) { x_max = 8; }
			PosDefault();
			break;
		case 3:
			if (button == 3 && state == GLUT_UP) {
				x_min += 1;
				x_max -= 1;
			}
			if (x_min > -8) { x_min = -8; }
			if (x_max < 8) { x_max = 8; }
			PosDefault();
			break;
		case GLUT_LEFT_BUTTON:
			if (pressed == 0 && state == GLUT_DOWN) {
				x_1 = y_1 = x_2 = y_2 = 0;
				x_1 = (x - WIDTH / 2.0) / (WIDTH / 2.0);
				y_1 = -(y - HEIGHT / 2.0) / (WIDTH / 2.0);
				x_2 = x_1;
				y_2 = y_1;
				pressed = 1;
			}
			if (pressed == 1 && state == GLUT_UP) {
				x_2 = (x - WIDTH / 2.0) / (WIDTH / 2.0);
				y_2 = -(y - HEIGHT / 2.0) / (WIDTH / 2.0);
				pressed = 0;
			}
			break;
		default:
			PosDefault();
			break;
		}
	Calculation();
}


inline void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINE_STRIP);
		glVertex3d(x1, y1, -1.0);
		glVertex3d(x1, y2, -1.0);
		glVertex3d(x2, y2, -1.0);
		glVertex3d(x2, y1, -1.0);
		glVertex3d(x1, y1, -1.0);
	glEnd();
}


void MouseMove(int x, int y) {
	if (pressed == 1) {
 		x_2 = (x - WIDTH / 2.0) / (WIDTH / 2.0);
		y_2 = -(y - HEIGHT / 2.0) / (WIDTH / 2.0);
	}
}


// функция для вывоода текста на экран
void RenderBitmapString(double x, double y, double z, void *font, char *string)
{
	char *c;
	glRasterPos3d(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


// функция преобразующая целое число в строку
void IntToStr(int number, char *string)
{
	int is_negative = 0, amount_ch = 0;
	char temp_char;

	if (number < 0) {							// и делаем его положительным
		is_negative = 1;						// если число отрицательное фиксируем это
		number = abs(number);
	}
	else if (number == 0) {						// если число равно нулю
		string[0] = 0 + 48;						// записуем в строку ноль и выходим с функции
		string[1] = '\0';
		return;
	}

	while (number > 0) {						// записуем все цифры числа в строку
		amount_ch++;
		string[amount_ch - 1] = number % 10 + 48;
		number /= 10;
	}

	if (is_negative) {							// если число отрицатильное
		amount_ch++;							// добавляем в строку минус
		string[amount_ch - 1] = '-';
	}


	for (int i = 0; i < amount_ch / 2; i++) {
		temp_char = string[i];					// отражаем строку симетрично центру
		string[i] = string[amount_ch - 1 - i];
		string[amount_ch - 1 - i] = temp_char;
	}
	string[amount_ch] = '\0'; 
}
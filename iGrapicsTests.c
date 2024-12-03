#include <stdio.h>
#include <math.h>


typedef struct
{
	double p[2];
	double v[2];
	double m;
	double uk;
	double r;
	double color[3];
} 
object;


double Border[2][2];
double mapBorder[2][2];



const int perTeam = 5;
object objects[(5*2)+1];

int selectedPlayer = 0;
double powerX = 0, powerY = 0;
const double vMin = 0.2;




double measureDistance(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	double d = sqrt((dx*dx) + (dy*dy));
	return d;
}




void moveObjectsEx()
{
	double vx;
	double vy;
	double v;
	double ratio[2];
	for (int i = 0; i <= perTeam*2; i++)
	{
		vx = objects[i].v[0];
		vy = objects[i].v[1];
		v = sqrt((vx*vx) + (vy*vy));
		ratio[0] = abs(vx/v);
		ratio[1] = abs(vy/v);
		for (int j = 0; j < 2; j++)
		{
			if (abs(objects[i].v[j]) > vMin)
			{
				objects[i].p[j] += objects[i].v[j];
				if (objects[i].v[j] < 0) objects[i].v[j] += ratio[j] * objects[i].uk;
				else if (objects[i].v[j] > 0) objects[i].v[j] -= ratio[j] * objects[i].uk;
			}
		}
	}
}




void addFriction(object* player, int i)
{
	object p = *player;
	double vx = p.v[0];
	double vy = p.v[1];
	double v = sqrt((vx*vx) + (vy*vy));
	double ratio[2];
	ratio[0] = abs(vx/v);
	ratio[1] = abs(vy/v);

	if (p.v[i] < 0) (*player).v[i] += ratio[i] * p.uk;
	else if (p.v[i] > 0) (*player).v[i] -= ratio[i] * p.uk;
}

void moveObjects()
{
	for (int i = 0; i <= perTeam*2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (abs(objects[i].v[j]) > vMin)
			{
				objects[i].p[j] += objects[i].v[j];
				addFriction(&objects[i], j);
			}
		}
	}
}




void collisionWithBorder__Old()
{
	for (int i = 0; i <= perTeam*2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (objects[i].p[j] - objects[i].r <= Border[0][j])
			{
				objects[i].p[j] = Border[0][j] + objects[i].r;
				objects[i].v[j] *= -1;
			}
			else if (objects[i].p[j] + objects[i].r >= Border[1][j])
			{
				objects[i].p[j] = Border[1][j] - objects[i].r;
				objects[i].v[j] *= -1;
			}
		}
	}
}





void collisionWithBorder()
{
	for (int i = 0; i <= perTeam*2; i++)
	{
		double p[2];
		p[0] = objects[i].p[0];
		p[1] = objects[i].p[1];
		double r = objects[i].r;

		// Horizontal
		if (p[1] < mapBorder[1][2] && p[1] > mapBorder[1][1])
		{
			if (p[0] - r < mapBorder[0][0])
			{
				objects[i].p[0] = mapBorder[0][0] + r;
				objects[i].v[0] *= -1;
			}

			else if (p[0] + r > mapBorder[0][3])
			{
				objects[i].p[0] = mapBorder[0][3] - r;
				objects[i].v[0] *= -1;
			}
		}

		else if (p[1] < mapBorder[1][3] && p[1] > mapBorder[1][0])
		{
			if (p[0] - r < mapBorder[0][1])
			{
				objects[i].p[0] = mapBorder[0][1] + r;
				objects[i].v[0] *= -1;
			}

			else if (p[0] + r > mapBorder[0][2])
			{
				objects[i].p[0] = mapBorder[0][2] - r;
				objects[i].v[0] *= -1;
			}
		}


		// Vertical
		if (p[0] < mapBorder[0][2] && p[0] > mapBorder[0][1])
		{
			if (p[1] - r < mapBorder[1][0])
			{
				objects[i].p[1] = mapBorder[1][0] + r;
				objects[i].v[1] *= -1;
			}

			else if (p[1] + r > mapBorder[1][3])
			{
				objects[i].p[1] = mapBorder[1][3] - r;
				objects[i].v[1] *= -1;
			}
		}

		else if (p[0] < mapBorder[0][3] && p[0] > mapBorder[0][0])
		{
			if (p[1] - r < mapBorder[1][1])
			{
				objects[i].p[1] = mapBorder[1][1] + r;
				objects[i].v[1] *= -1;
			}

			else if (p[1] + r > mapBorder[1][2])
			{
				objects[i].p[1] = mapBorder[1][2] - r;
				objects[i].v[1] *= -1;
			}
		}
	}
}








void afterCollisionPosition(object* player1, object* player2, double d)
{
	object p1 = *player1;
	object p2 = *player2;

	double D = p1.r + p2.r;
	double dc = D - d;
	double dx = p2.p[0] - p1.p[0];
	double dy = p2.p[1] - p1.p[1];

	dx = ((dx * dc) / (2 * d)) + 0.001;
	dy = ((dy * dc) / (2 * d)) + 0.001;

	(*player1).p[0] -= dx;
	(*player1).p[1] -= dy;
	(*player2).p[0] += dx;
	(*player2).p[1] += dy;
}



int main()
{
	objects[1].p[0] = 15;
	objects[1].p[1] = 15;
	objects[2].p[0] = 20;
	objects[2].p[1] = 20;
	objects[1].r = objects[2].r = 5;

	double d = measureDistance(objects[1].p[0], objects[1].p[1], objects[2].p[0], objects[2].p[1]);

	afterCollisionPosition(&objects[1], &objects[2], d);

	double df = measureDistance(objects[1].p[0], objects[1].p[1], objects[2].p[0], objects[2].p[1]);

	printf("%lf -- %lf\n", d, df);

	return 0;
}





/*


*/
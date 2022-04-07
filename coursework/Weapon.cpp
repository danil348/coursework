#include "Weapon.h"

void Bullets::fly()
{
	Bx = screanW /2 + dist * cos(angle * M_PI / 180);
	By = screanH /2 + dist * -sin(angle * M_PI / 180);
	dist += 0.9f;
}

void Bullets::setAngl(int x, int y, int w, int h)
{
	x = x - w / 2;
	y = (h / 2 - y);
	screanW = w;
	screanH = h;
	angle = -int(atan2f(float(x), float(y)) * 180 / M_PI - 90) % 360;
	if (angle < 0) {
		angle = 270 + angle + 90;
	}
}

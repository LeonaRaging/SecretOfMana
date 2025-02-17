class vector2f 
{
public:
	vector2f(float p_x, float p_y):
		x(p_x), y(p_y) {}
	vector2f():
		x(0.0f), y(0.0f) {}
private:
	float x, y;
};
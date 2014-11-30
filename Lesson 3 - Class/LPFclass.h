class LPFclass
{
public:
	LPFclass();
	double LPFinput(double x);
	void LPFinput(double* x, int len);
private:
	double x2;
	double x1;
	double y2;
	double y1;
};

class LPFclass
{
public:
	LPFclass();
	double LPFinput(double x);
	void LPFinput(double* x, int len);
private:
	double x2; // x[n-2] (two inputs ago)
	double x1; // x[n-1] (last input)
	double y2; // y[n-2] (two outputs ago)
	double y1; // y[n-1] (last output)
};

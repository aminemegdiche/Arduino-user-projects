int const _pinsSize = 7;
int _pins[_pinsSize] = {3,5,6,9,10,11,13}; //piny PWM 
int stop = 1; //czy ma się zatrzymywać na moment na skrajnych diodach (1-nie,0-tak)
int _pause = 150; //czas wy�wietlania
int v[5] = {0,0,50,150,255}; //definicja mocy diod
int _power[_pinsSize][_pinsSize] = 
{
	{v[4],v[3],v[2],v[1],v[0],v[0],v[0]},
	{v[3],v[4],v[3],v[2],v[1],v[0],v[0]},
	{v[2],v[3],v[4],v[3],v[2],v[1],v[0]},
	{v[1],v[2],v[3],v[4],v[3],v[2],v[1]},
	{v[0],v[1],v[2],v[3],v[4],v[3],v[2]},
	{v[0],v[0],v[1],v[2],v[3],v[4],v[3]},
	{v[0],v[0],v[0],v[1],v[2],v[3],v[4]}

};
void setup()
{
	for (int i = 0; i < _pinsSize; i++)
	{
		pinMode(_pins[i],OUTPUT);
		analogWrite(_pins[i],0);
	}
}

void loop()
{
	for (int x = 0; x < _pinsSize; x++)
	{
		for (int y = 0; y < _pinsSize; y++)
		{
			analogWrite(_pins[y],_power[x][y]);
		}
		delay(_pause);
	}

	for (int x = _pinsSize-1-stop; x >= 0+stop; x--)
	{
		for (int y = 0; y < _pinsSize; y++)
		{
			analogWrite(_pins[y],_power[x][y]);
		}
		delay(_pause);
	}
}


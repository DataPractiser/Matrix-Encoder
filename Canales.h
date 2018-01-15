#ifndef __CANALES_H_INCLUDED__
#define __CANALES_H_INCLUDED__


template <typename T1>
struct Estereo
{
	T1 L;
	T1 R;
};

template <typename T2>
struct SixChannel : Estereo<T2>
{
	T2 C;
	T2 LFE;
	T2 SL;
	T2 SR;
};

template <typename T3>
struct EightChannels : SixChannel<T3>
{
	T3 RL;
	T3 RR;
};

#endif

%����Ƶ��
SwitchFrequency = 16e3;
Ts = 1/SwitchFrequency;
SpeedloopFrequency = 1e3;
SpeedloopTs = 1/SpeedloopFrequency;
PWM_Period = 1000;

Rs_realvalue = 0.08;%���ӵ���  ou
Ld_realvalue = 0.25e-3;% Ld  H
Lq_realvalue = 0.25e-3;% Ld  H
%Lq_realvalue = 10.8e-3;% Lq  H  
Np = 5;%������
Lam_vrms_krpm = 6.2; %1000rpm�ķ��綯����Чֵ
Lam_realvalue = ((Lam_vrms_krpm*1.414)/1.732)/(2*pi*(1000/(60/Np)));%��������Ӧ���ѹ��ֵ
J_realvalue = 0.69e-4;%ת������
Friction = 0.003;%Ħ��ϵ�� 
Tn = 1.27;%����� NM
fn = 500;%�ת�� Hz 
In = 14.5;%��ߵ�����Чֵ Arms
Un = 36;%��ߵ�ѹ��Чֵ Vrms
Speedn = 60*fn/Np;%�ת�� rpm
Telectrical = Ld_realvalue/Rs_realvalue;%����ʱ�䳣��
Tf = 0;  %��ʼ���ش�С 
initial_degree = 0/Np;%��ʼ�Ƕ�
Vdc = 36;

%��������ѹ
Vphase = Vdc/sqrt(3); %�����������ѹ

%���ۻ�ֵ%���еı���ֵ����������ķ�ֵ��Ϊ��ֵ��
Ib = 16;
Vb = Un/sqrt(3); %��ѹ��ֵ
Wb = 2*pi*fn; %��Ƶ�ʻ�ֵ
tb = 1/Wb; %ʱ��Ļ�ֵ
Rb = Vb/Ib;
Lb = Rb*tb; 
Pb = 1.5*Vb*Ib; 
Tb = Pb*tb*Np;
fluxB = Vb*tb;
Jb = Np*Tb/((fn*2*pi)^2);%ת��������ֵ

%����ֵ����
Rs = Rs_realvalue/Rb;%�������ֵ
Ld = Ld_realvalue/Lb;%��б���ֵ
Lq = Lq_realvalue/Lb;%��б���ֵ
fluxF = Lam_realvalue/fluxB;%��������ֵ
TsPu = Ts/tb;%�������ڱ���ֵ
JPu = J_realvalue/Jb;%ת����������ֵ

%Q��ʽ
Q12 = 4096;
Q13 = 8192;
Q14 = 16384;
Q15 = 32767;

Rs_Q14 = Q14*Rs_realvalue/Rb;%�������ֵ
Ld_Q14 = Q14*Ld_realvalue/Lb;%��б���ֵ
Lq_Q14 = Q14*Lq_realvalue/Lb;%��б���ֵ
fluxF_Q14 = Q14*fluxF;

%�������������
CurrentLoopBandwidth = 300*2*pi/Wb;
Id_Kp = Q14*CurrentLoopBandwidth*Ld;
Id_Ki = Q14*CurrentLoopBandwidth*Rs;

Iq_Kp = Q14*CurrentLoopBandwidth*Lq;
Iq_Ki = Q14*CurrentLoopBandwidth*Rs;

CurrentLoopMax = Q14*1.2;

%�ٶȻ��������
SpeedLoopBandwidth = 50*2*pi/Wb;
Speed_Kp = Q14*SpeedLoopBandwidth*JPu/fluxF;
Speed_Ki = Q14*SpeedLoopBandwidth;
SpeedOutmax = 1.2*Q14;

%���໷
PLL_Bandwidth = 2*pi*100/Wb;
PLL_KP = Q15*2*PLL_Bandwidth;
PLL_KI = Q15*PLL_Bandwidth*PLL_Bandwidth;
PLL_OUTMax_W = Q14*1.2;

%��̬��ѹ����
SVCM_GAIN = 0.8;
SVCM_GAIN_Q = Q15*SVCM_GAIN;
EstOutMax_Speed = 2.0;
EstOutMax_Speed_Q = Q14*1.2;

%������������
LamObserverGain = 0.8;

%��Ĥ�۲��������
SMO_Gain = Q14*0.85;
SMO_I_ERROR = Q14*0.05;
Factor1 = Q15*Ts*Rb/Lq_realvalue;
Factor2 = Q15*Ts*Rs_realvalue/Lq_realvalue;

%һ�׵�ͨ�˲���
LowPassFilterBandWidth_Emf = 2*pi*150/Wb;
LowPassFilterBandWidth_Emf_Q = Q14*LowPassFilterBandWidth_Emf;
LowPassFilterCoeff_Emf = Q15*(1/(1+LowPassFilterBandWidth_Emf*TsPu));
LowPassFilterBandWidth_Speed = 2*pi*80/Wb;
LowPassFilterCoeff_Spd = Q15*(1/(1+LowPassFilterBandWidth_Speed*SpeedloopTs/tb));

%������MTPA
KP_fieldweaken = 1.0*Q14;
KI_fieldweaken = 0.1*Q14;
fieldweaken_Max = 0;
fieldweaken_Min = -0.5*Q14;

%�ٶȿ�����ջ�ʹ�ܿ���
SpdClosedLoopEnable = 0.0;
AngleSpdClosedLoopEnable = 0.0;
AngleEncoderEn = 1;
OverModulationEn = 0;
FieldWeakenEn = 0;

%��������
SpeedIncreased = 0.1*Wb;
SpeedSwitch = 0.6*Wb;
SpeedTarget = 0.8*Wb;

IFCurrDecreased = 1;
IFCurrTarget = 5;
IFCurrStart = 8;
IFIdref = 0;
%ʸ��׷�ٹ۲���
Omega0 = 0.4;

MOVE=1;
STOP=0;
thres=0.1;
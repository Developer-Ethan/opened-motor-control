%开关频率
SwitchFrequency = 16e3;
Ts = 1/SwitchFrequency;
SpeedloopFrequency = 1e3;
SpeedloopTs = 1/SpeedloopFrequency;

Rs_realvalue = 0.08;%定子电阻  ou
Ld_realvalue = 0.25e-3;% Ld  H
Lq_realvalue = 0.25e-3;% Ld  H
%Lq_realvalue = 10.8e-3;% Lq  H  
Np = 5;%极对数
Lam_vrms_krpm = 6.2; %1000rpm的反电动势有效值
Lam_realvalue = ((Lam_vrms_krpm*1.414)/1.732)/(2*pi*(1000/(60/Np)));%磁链，对应相电压幅值
J_realvalue = 0.69e-4;%转动惯量
Friction = 0.003;%摩擦系数 
Tn = 1.27;%额定力矩 NM
fn = 500;%额定转速 Hz 
In = 14.5;%额定线电流有效值 Arms
Un = 36;%额定线电压有效值 Vrms
Speedn = 60*fn/Np;%额定转速 rpm
Telectrical = Ld_realvalue/Rs_realvalue;%电气时间常数
Tf = 0;  %初始负载大小 
initial_degree = 0/Np;%初始角度
Vdc = 36;

%控制器电压
Vphase = Vdc/sqrt(3); %相电流侧最大电压

%标幺基值%所有的标幺值，都是以相的幅值作为基值；
Ib = 1.5*In;
Vb = Un/sqrt(3); %电压基值
Wb = 2*pi*fn; %角频率基值
tb = 1/Wb; %时间的基值
Rb = Vb/Ib;
Lb = Rb*tb; 
Pb = 1.5*Vb*Ib; 
Tb = Pb*tb*Np;
fluxB = Vb*tb;
Jb = Np*Tb/((fn*2*pi)^2);%转动惯量基值

%标幺值计算
Rs = Rs_realvalue/Rb;%电阻标幺值
Ld = Ld_realvalue/Lb;%电感标幺值
Lq = Lq_realvalue/Lb;%电感标幺值
fluxF = Lam_realvalue/fluxB;%磁链标幺值
TsPu = Ts/tb;%开关周期标幺值
JPu = J_realvalue/Jb;%转动惯量标幺值

%Q格式
Q13 = 8192;
Q14 = 16384;
Q15 = 32767;
%电流环带宽计算
CurrentLoopBandwidth = 400*2*pi/Wb;
Id_Kp = Q15*CurrentLoopBandwidth*Ld;
Id_Ki = Q15*CurrentLoopBandwidth*Rs;

Iq_Kp = Q15*CurrentLoopBandwidth*Lq;
Iq_Ki = Q15*CurrentLoopBandwidth*Rs;

CurrentLoopMax = Q14*1.2;

%速度环带宽计算
SpeedLoopBandwidth = 50*2*pi/Wb;
Speed_Kp = SpeedLoopBandwidth*JPu/fluxF;
Speed_Ki = SpeedLoopBandwidth;
SpeedOutmax = 1.5;

%锁相环
PLL_Bandwidth = 2*pi*100/Wb;
PLL_KP = Q15*2*PLL_Bandwidth;
PLL_KI = Q15*PLL_Bandwidth*PLL_Bandwidth;
PLL_OUTMax_W = Q14*1.2;

%静态电压补偿
SVCM_GAIN = 0.8;
EstOutMax_Speed = 2.0;
EstOutMax_Theta = 2*pi;

%磁链参数整定
LamObserverGain = 0.8;

%滑膜观测参数整定
SMO_Gain = Q14*0.85;
SMO_I_ERROR = Q14*0.05;
Factor1 = Q15*Ts*Rb/Lq_realvalue;
Factor2 = Q15*Ts*Rs_realvalue/Lq_realvalue;

%一阶低通滤波器
LowPassFilterBandWidth_Emf = 2*pi*150/Wb;
LowPassFilterBandWidth_Emf_Q = Q14*LowPassFilterBandWidth_Emf;
LowPassFilterCoeff_Emf = Q15*(1/(1+LowPassFilterBandWidth_Emf*TsPu));
LowPassFilterBandWidth_Speed = 2*pi*100/Wb;

%弱磁与MTPA
KP_fieldweaken = 1.0;
KI_fieldweaken = 0.1;
fieldweaken_Max = 0;
fieldweaken_Min = -0.5;

%速度开环与闭环使能开关
SpdClosedLoopEnable = 0.0;
AngleClosedLoopEnable = 1.0;
AngleEncoderEn = 0;

%开环控制
SpeedIncreased = 0.1*Wb;
SpeedSwitch = 0.6*Wb;
SpeedTarget = 0.8*Wb;

IFCurrDecreased = 1;
IFCurrTarget = 5;
IFCurrStart = 8;
IFIdref = 0;
%矢量追踪观测器
Omega0 = 0.4;

MOVE=1;
STOP=0;
thres=0.1;
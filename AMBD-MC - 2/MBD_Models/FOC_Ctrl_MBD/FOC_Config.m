clear;clc;

%% Load Structures
load('struct_FOC_Crtl.mat');

% %% Model parameters
% Ts = 0.0001;
% Tctr = 0.0000625;
% Ts_PIL = 0.0000125;
% Fpwm = 16000;
% Ts_simscape = 1/40000000;
% 
% %% Motor parameters
 motor.DC = 12;                      % [V]
% motor.Rs = 0.56;                    % [ohm]
% motor.Ld = 0.000375;                % [H]
% motor.Lq = 0.000435;                % [H]
% motor.L0 = (motor.Ld + motor.Ld)/2; % [H]
% motor.Prs = 2;                      % [-]
% motor.Flux = 0.0039052261;          % [Wb]
% motor.J = 0.12e-4;                  % [Kg.m^2]
% motor.B = 0.0005;                   % [N.m.s/rad]
% motor.Tf = 0;                       % [N.m]
% motor.Kt = 1.5*motor.Flux*motor.Prs;                      % Torque constant [N.m/A]
% motor.Ke = sqrt(3)*1000*motor.Prs*2*pi/60*motor.Flux;     % Back-emf [V/krpm]
% 
% 
% %% Current Controller
% % D axis PI design
% innerPI.iD.f0 = 200;
% innerPI.iD.w0 = 2*pi*innerPI.iD.f0;
% innerPI.iD.ksi = 1;
% 
% innerPI.iD.Continuous.Kp = 2*innerPI.iD.ksi*innerPI.iD.w0*motor.Ld - motor.Rs;
% innerPI.iD.Continuous.Ki = innerPI.iD.w0^2*motor.Ld;
% innerPI.iD.Continuous.Kzc = innerPI.iD.Continuous.Kp/innerPI.iD.Continuous.Ki;
% 
% innerPI.BandWidth = 480;
% innerPI.iD.Discrete.Kp = 10;
% innerPI.iD.Discrete.Ki = 480;
% innerPI.iD.Discrete.KiTctr = innerPI.iD.Discrete.Ki*Tctr;
% 
% % Q axis PI design
% innerPI.iQ.f0 = 200;
% innerPI.iQ.w0 = 2*pi*innerPI.iQ.f0;
% innerPI.iQ.ksi = 1;
% 
% innerPI.iQ.Continuous.Kp = 2*innerPI.iQ.ksi*innerPI.iQ.w0*motor.Lq - motor.Rs;
% innerPI.iQ.Continuous.Ki = innerPI.iQ.w0^2*motor.Lq;
% innerPI.iQ.Continuous.Kzc = innerPI.iQ.Continuous.Kp/innerPI.iQ.Continuous.Ki;
% 
% innerPI.iQ.Discrete.Kp = 10;
% innerPI.iQ.Discrete.Ki = 640;
% innerPI.iQ.Discrete.KiTctr = innerPI.iQ.Discrete.Ki*Tctr;
% 
% %% Speed Controller
% outerPI.Spd.f0 = 4;
% outerPI.Spd.w0 = 2*pi*outerPI.Spd.f0;
% outerPI.Spd.ksi = 1;
% outerPI.Spd.Continuous.Kp = (2*outerPI.Spd.ksi*outerPI.Spd.w0*motor.J - motor.B)/motor.Kt;
% outerPI.Spd.Continuous.Ki = outerPI.Spd.w0^2*motor.J/motor.Kt;
% outerPI.Spd.Continuous.Kzc = outerPI.Spd.Continuous.Kp/outerPI.Spd.Continuous.Ki;
% 
% outerPI.Spd.Discrete.Kp = 0.07;
% outerPI.Spd.Discrete.Ki = 0.32;
% outerPI.Spd.Discrete.KiTctr = outerPI.Spd.Discrete.Ki*Tctr;

%% used constant define and used Pu form 
%% PWM Frequency
SwitchFrequency = 16e3;
Ts = 1/SwitchFrequency;
SpeedloopFrequency = 1e3;
SpeedloopTs = 1/SpeedloopFrequency;
PWM_Period = 1000;

%% Model parameters
Rs_realvalue = 0.025;%定子电阻  ou
Ld_realvalue = 0.06e-3;% Ld  H
Lq_realvalue = 0.06e-3;% Ld  H
%Lq_realvalue = 10.8e-3;% Lq  H  
Np = 5;%极对数
Lam_vrms_krpm = 8.3; %1000rpm的反电动势有效值 7.85
Lam_realvalue = ((Lam_vrms_krpm*1.414)/1.732)/(2*pi*(1000/(60/Np)));%磁链，对应相电压幅值
J_realvalue = 2.47e-4;%转动惯量
Friction = 0.003;%摩擦系数 
Tn = 0.59;%额定力矩 NM
fn = 250;%额定转速 Hz 
In = 15;%额定线电流有效值 Arms
Un = 14;%额定线电压有效值 Vrms
Speedn = 60*fn/Np;%额定转速 rpm
Telectrical = Ld_realvalue/Rs_realvalue;%电气时间常数
Tf = 0;  %初始负载大小 
initial_degree = 0;%初始角度
Vdc = 14;

%% Based value
%控制器电压
Vphase = Vdc/sqrt(3); %相电流侧最大电压

%标幺基值%所有的标幺值，都是以相的幅值作为基值；
Ib = sqrt(2)*In;
Vb = Un/sqrt(3); %电压基值
Wb = 2*pi*fn; %角频率基值
tb = 1/Wb; %时间的基值
Rb = Vb/Ib;
Lb = Rb*tb; 
Pb = 1.5*Vb*Ib; 
Tb = Pb*tb*Np;
fluxB = Vb*tb;
Jb = Np*Tb/((fn*2*pi)^2);%转动惯量基值

%% Pu Value
Rs = Rs_realvalue/Rb;%电阻标幺值
Ld = Ld_realvalue/Lb;%电感标幺值
Lq = Lq_realvalue/Lb;%电感标幺值
fluxF = Lam_realvalue/fluxB;%磁链标幺值
TsPu = Ts/tb;%开关周期标幺值
JPu = J_realvalue/Jb;%转动惯量标幺值

%% Current Controller
CurrentLoopBandwidth = 250*2*pi/Wb;
Id_Kp = CurrentLoopBandwidth*Ld;
Id_Ki = CurrentLoopBandwidth*Rs;

Iq_Kp = CurrentLoopBandwidth*Lq;
Iq_Ki = CurrentLoopBandwidth*Rs;

CurrentLoopMax = 1.2;

%% Speed Controller
SpeedLoopBandwidth = 50*2*pi/Wb;
Speed_Kp = SpeedLoopBandwidth*JPu/fluxF;
Speed_Ki = SpeedLoopBandwidth;
SpeedOutmax = 1.2;

%% PLL Controller
PLL_Bandwidth = 2*pi*100/Wb;
PLL_KP = 2*PLL_Bandwidth;
PLL_KI = PLL_Bandwidth*PLL_Bandwidth;
PLL_OUTMax_W = 1.2;

%% Svcm Observer
SVCM_GAIN = 0.8;
EstOutMax_Speed = 2.0;

%% Nonlinear Flux Observer
LamObserverGain = 0.4;

%% Smo Observer
SMO_Gain = 0.85;
SMO_I_ERROR = 0.05;
Factor1 = Ts*Rb/Lq_realvalue;
Factor2 = Ts*Rs_realvalue/Lq_realvalue;

%% PLL Observer
%Omega0 = 0.4;

%% LPF
LowPassFilterBandWidth_Emf = 2*pi*150/Wb;
LowPassFilterCoeff_Emf = (1/(1+LowPassFilterBandWidth_Emf*TsPu));
LowPassFilterBandWidth_Speed = 2*pi*100/Wb;
LowPassFilterCoeff_Spd = (1/(1+LowPassFilterBandWidth_Speed*SpeedloopTs/tb));

%% WeakenField and MTPA
KP_fieldweaken = 1.0;
KI_fieldweaken = 0.1;
fieldweaken_Max = 0;
fieldweaken_Min = -0.5;

%% Enable Information
SpdClosedLoopEnable = 1.0;
AngleSpdClosedLoopEnable = 0.0;
AngleEncoderEn = 1;
OverModulationEn = 1;
SecondOverMod = 0;
FieldWeakenEn = 0;

%% OpenLoop Controller
SpeedIncreased = 0.1*Wb;
SpeedSwitch = 0.6*Wb;
SpeedTarget = 0.8*Wb;

IFCurrDecreased = 1;
IFCurrTarget = 5;
IFCurrStart = 8;
IFIdref = 0;

%% SVPWM
ZeroSeqInjectEn = 1.0;


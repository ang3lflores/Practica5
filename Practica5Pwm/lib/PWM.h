#ifndef PWM_H_
#define PWM_H_

#define PWM_0                 0
#define PWM_1                 1
#define GEN_0                 0
#define GEN_1                 1
#define GEN_2                 2
#define GEN_3                 3
#define ACTZERO               0
#define ACTLOAD               2
#define ACTCMPAU              4
#define ACTCMPAD              6
#define ACTCMPBU              8
#define ACTCMPBD              10

extern void Configurar_PWMM0G0(int cargad, int DUTY);
extern void Configurar_PWMM0G1(int cargad, int DUTY);
extern void Configurar_PWMM0G2(int cargad, int DUTY);
extern void Configurar_PWM(int PWM,int GEN, uint32_t F, int DUTY_CYCLE, int Priority);
extern void IniciarIntPWM(int PWM,int GEN, int Priority);

#endif /* PWM_PWM_H_ */
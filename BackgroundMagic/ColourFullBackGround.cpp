// MouseMove.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>
#include <random>

void SleepTime(int ms);
void linearInterpolation(int delay, int control_time, int x, int y);
void LinearlySmoothing(double totalTime, double control_time, int X, int Y);


struct Weapon_Recoil{
    const float customX[30] = { -13.9306f, -6.7788, -0.4073, 6.2480, 10.4567, 11.5526, 9.5355, 4.4055, -3.1726, -9.0352, -11.5846, -10.8178, -6.7348, 0.2566, 6.3470, 9.8395, 10.7665, 9.1280, 4.9239, -0.9875, -4.7353, -6.3062, -5.7881 };
    const float customY[30] = { 27.9232, 27.6898, 26.9380, 25.6679, 23.8793, 21.5724, 18.7471, 16.0817, 14.6362, 13.3281, 12.1185, 11.0074, 9.9947, 9.0805, 8.2648, 7.5476, 6.9289, 6.4086, 5.9868, 5.6635, 5.4387, 5.3123, 5.2844 };

    const float thompsonX[30] = { -15.8279, -5.8047, 3.5853, 11.3567, 13.8312, 10.9266, 2.6596, -7.7474, -13.3286, -13.1795, -7.3000, 2.7772, 10.0402, 12.8529, 11.2323, 5.1785, -2.8139, -6.8923, -7.3495 };
    const float thompsonY[30] = { 33.4964, 33.0110, 31.6299, 29.3530, 26.1803, 22.1118, 18.7347, 16.7660, 14.9674, 13.3390, 11.8808, 10.5928, 9.4749, 8.5271, 7.7496, 7.1422, 6.7050, 6.4380, 6.3412 };

    //    const float mp5a4X[30] = { 0.0000, 0.0000, 0.0000, 13.3435, 30.7689, 34.3019, 23.9426, 0.8672, -18.9216, -26.0428, -20.6460, -3.9165, 8.0986, 14.5347, 17.5745, 17.2181, 13.4654, 6.3166, -1.4959, -5.6295, -8.8974, -11.3639, -13.0287, -13.8921, -13.9539, -13.2142, -11.6730, -9.3302, -6.1859 };
    const float mp5a4X[30] = { 0.0000, 0.0000, 0.0000, 13.3435, 30.7689, 34.3019, 23.9426, 0.8672, -18.9216, -26.0428, -20.6460, -3.9165, 8.0986, 14.5347, 17.5745, 17.2181, 13.4654, 6.3166, -1.4959, -5.6295, -8.8974, -11.3639, -13.0287, -13.8921, -13.9539, -13.2142, -11.6730, -9.3302, -6.1859 };
    const float mp5a4Y[30] = { 22.7147, 30.6766, 34.7248, 34.8592, 31.0798, 23.3867, 13.7070, 11.2690, 10.0634, 8.9233, 7.8488, 6.8398, 5.8965, 5.0187, 4.2065, 3.4598, 2.7788, 2.1633, 1.6134, 1.1290, 0.7103, 0.3571, 0.0695, -0.1525, -0.3089, -0.3999, -0.4251, -0.3848, -0.2790 };
    
    const float lrX[30] = { -2.5716, -6.4990, -10.5691, -15.0501, -16.5015, -14.8903, -10.2167, -2.3359, 9.5645, 18.0725, 21.0806, 18.5887, 10.5968, -0.4584, -5.8302, -9.7352, -12.7238, -14.7961, -15.9520, -16.1917, -15.5149, -13.9219, -11.4124, -7.9867, -3.5444, 14.0846, 32.0283, 37.8660, 31.5974, };
    const float lrY[30] = { 26.2726, 32.5123, 34.6882, 32.8004, 26.8927, 21.6664, 18.6228, 15.8424, 13.3251, 11.0709, 9.0797, 7.3517, 5.9258, 5.1813, 4.6544, 4.1882, 3.7826, 3.4377, 3.1534, 2.9299, 2.7669, 2.6647, 2.6231, 2.6421, 2.7219, 2.8623, 3.0633, 3.3250, 3.6474 };

    const float akX[30] = { -36.3583, 5.6019, -57.7970, -44.4413, -0.1867, 17.4687, 30.7335, 39.6080, 44.0919, 44.1854, 39.8884, 31.2010, 18.1232, 0.9701, -15.7055, -28.9507, -38.7704, -45.1648, -48.1337, -47.6774, -43.7956, -36.4885, -25.7559, -11.5980, 12.5535, 37.8676, 50.8869, 51.5930, 39.9856 };
    const float aky[30] = { 52.3906, 48.1107, 43.7258, 39.2358, 34.6408, 29.9408, 25.1358, 20.2258, 15.2107, 10.0906, 10.3678, 19.1802, 26.1569, 31.1046, 34.0233, 34.9129, 33.7734, 30.6050, 25.4073, 18.1807, 8.9251, 5.1987, 14.5390, 21.8952, 26.8223, 29.3207, 29.3899, 27.0302, 22.2415 };

    const float m249Y[100] = { 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70};
    const float m249X[100] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    const float pythonX[6] = {0, 0, 0, 0, 0, 0};
    const float pythonY[6] = {66, 66, 66, 66, 66, 66};

    const float m39X[20] = {};
    const float m39Y[20] = {};

    const float m92X[15] = {};
    const float m92Y[15] = {};

    const float reviX[8] = {};
    const float reviY[8] = {};

    const float semiRifleX[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const float semiRifleY[16] = {-35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35};

    const float semiPistolX[10] = {};
    const float semiPistolY[10] = {};
};

struct Weapon_FireRate {
    const float AK = 132.3333333f;
    const float Thompson = 129.22f;
    const float MP5 = 99.99f;
    const float SMG = 100.0f;
    const float LR = 118;
    const float m249 = 120;
    const float controltimeAK[30] = { 121.96149709966872,92.6333814724611,138.60598637206294,113.37874368443146,66.25151186427745,66.29530438019354,75.9327831420658,85.05526144256157,89.20256669256554,86.68010184667988,78.82145888317788,70.0451048111144,60.85979604582978,59.51642457624619,71.66762996283607,86.74060009403034,98.3363599080854,104.34161954944257,104.09299204005345,97.58780746901739,85.48062700875559,70.4889202349561,56.56417811530545,47.386907899993936,56.63787408680247,91.5937793023631,112.38667610336424,111.39338971888095,87.5067801164596 };
    const float semiRifle = 5;
    const float semiPistol = 0;
    const float revi = 0;
    const float m92 = 0;
    const float m39 = 0;
    const float python = 100;
    const float MP5A4ControlTime[30] = { 43.441909, 58.669031, 66.411108, 71.385438, 83.641583, 79.398875, 52.763157, 21.615756, 40.987258, 52.649410, 42.242421, 15.073904, 19.158961, 29.407978, 34.560589, 33.587834, 26.295315, 12.769285, 4.207833, 10.980831, 17.070518, 21.744130, 24.917849, 26.570261, 26.693439, 25.283775, 22.339392, 17.859221, 11.842602 };
    const double AssaultRifleControlTime[30] = { 121.96149709966872, 92.6333814724611, 138.60598637206294, 113.37874368443146, 66.25151186427745, 66.29530438019354, 75.9327831420658, 85.05526144256157, 89.20256669256554, 86.68010184667988, 78.82145888317788, 70.0451048111144, 60.85979604582978, 59.51642457624619, 71.66762996283607, 86.74060009403034, 98.3363599080854, 104.34161954944257, 104.09299204005345, 97.58780746901739, 85.48062700875559, 70.4889202349561, 56.56417811530545, 47.386907899993936, 56.63787408680247, 91.5937793023631, 112.38667610336424, 111.39338971888095, 87.5067801164596 };
};

struct Modifier
{
    const float AK = 1;
    const float MP5 = 1;
    const float Thompson = 1.3;
    const float SMG = 1.1;
    const float LR = 1;
};

int main()
{      
    Weapon_Recoil weapon_recoil;
    Weapon_FireRate weapon_firerate;
    Modifier modifier;
    SetPriorityClass(GetCurrentProcess(), 0x00000080);


    std::random_device rd;
    std::default_random_engine generator(rd()); 
    std::uniform_real_distribution<float> distributionR(0.01, 0.09);
    std::uniform_real_distribution<float> distributionDelay(0.001, 0.002);
    std::uniform_real_distribution<float> distributionSmoothing(6, 8);
    std::uniform_real_distribution<float> distributionDelayDelay(99, 101);

    float randomiserR;
    float randomiserDelay;
    float randomiserSmoothing;
    float randomiserDelayDelay;
   
    float recoil = 1;
    float scope = 1;
    float attachment = 1;
    int currentwep = 0;
    bool active = false; 
    int check = 0;

        while (true)
        {     
            if(GetAsyncKeyState(VK_NUMPAD8))
            {
                std::cout << "Current scope: 8x" << std::endl;
                scope = 3.84f;
            }
            if (GetAsyncKeyState(VK_NUMPAD9))
            {
                std::cout << "Current scope: 16x" << std::endl;
                scope = 8.68f;
            }
            if (GetAsyncKeyState(VK_NUMPAD7))
            {
                std::cout << "Current scope: Holo" << std::endl;
                scope = 1.2f;
            }
            if (GetAsyncKeyState(VK_NUMPAD6))
            {
                std::cout << "Current Weapon: m249" << std::endl;
                currentwep = 6;
            }

            if (GetAsyncKeyState(VK_NUMPAD0))
            {
                std::cout << "Current weapon: NONE" << std::endl;
                currentwep = 0;
                attachment = 1;
                scope = 1;
            }
            if (GetAsyncKeyState(VK_NUMPAD1))
            {
                std::cout << "Current weapon: AK" << std::endl;
                currentwep = 1;
            }
            if (GetAsyncKeyState(VK_NUMPAD2))
            {
                std::cout << "Current weapon: MP5" << std::endl;
                currentwep = 2;
            }
            if (GetAsyncKeyState(VK_NUMPAD3))
            {
                std::cout << "Current weapon: THOMPSON" << std::endl;
                currentwep = 3;
            }
            if (GetAsyncKeyState(VK_NUMPAD4))
            {
                std::cout << "Current weapon: SMG" << std::endl;
                currentwep = 4;
            }
            if (GetAsyncKeyState(VK_NUMPAD5))
            {
                std::cout << "Current weapon: LR30" << std::endl;
                currentwep = 5;
            }      
            if (GetAsyncKeyState(VK_ADD))
            {
                std::cout << "Current Attachment: Surpressor" << std::endl;
                attachment = 0.8f;
            }


           // Sleep(1);
            
            while ((GetAsyncKeyState(VK_LBUTTON) & 0x8000 && GetAsyncKeyState(VK_RBUTTON) & 0x8000)) {
                {

                    randomiserR = distributionR(generator);
                    randomiserDelay = 0; //distributionDelay(generator);
                    randomiserSmoothing = distributionSmoothing(generator);
                    randomiserDelayDelay = distributionDelayDelay(generator);

            if(currentwep == 1)
            {            
                LinearlySmoothing(133, weapon_firerate.AssaultRifleControlTime[check], (weapon_recoil.akX[check] * scope * attachment), (weapon_recoil.aky[check] * scope * attachment));
                //linearInterpolation(randomiserSmoothing, weapon_firerate.AK, ((weapon_recoil.akX[check]  * attachment)* scope), ((weapon_recoil.aky[check] * attachment) * scope));
           }
            if (currentwep == 2)
            {
              //  linearInterpolation(randomiserSmoothing, (weapon_firerate.MP5) * (1 + 0), ((weapon_recoil.mp5a4X[check] * 1 )), (((weapon_recoil.mp5a4Y[check] * 1) * (1 + 0) * scope)) * 1);
                LinearlySmoothing(randomiserDelayDelay, (weapon_firerate.MP5A4ControlTime[check]), (weapon_recoil.mp5a4X[check] * scope * (1 + randomiserR) * attachment), (weapon_recoil.mp5a4Y[check] * scope * attachment * (1 + randomiserR)));
            }
            if (currentwep == 3)
            {
                linearInterpolation(randomiserSmoothing, weapon_firerate.Thompson * (1 + 0), (((weapon_recoil.thompsonX[check] * recoil) * (1 + randomiserR) *(scope * 1.2) * attachment)), (((weapon_recoil.thompsonY[check] * recoil) * (1 + randomiserR) * (scope * 1.2))) * attachment);
            }
            if (currentwep == 4)
            {
                linearInterpolation(randomiserSmoothing, weapon_firerate.SMG * (1 + 0), (((weapon_recoil.customX[check] * recoil) * (1 + randomiserR) * scope) * attachment), (((weapon_recoil.customY[check] * recoil) * (1 + randomiserR) * scope) *attachment));
            }
            if (currentwep == 5)
            {
               
                linearInterpolation(randomiserSmoothing, weapon_firerate.LR, ((weapon_recoil.lrX[check] * recoil) * (1 + randomiserR) * scope) * attachment, (((weapon_recoil.lrY[check] * recoil) * (1 + randomiserR) * scope) * attachment));
            }                  

            if (currentwep == 6)
            {
                linearInterpolation(randomiserSmoothing, weapon_firerate.m249, ((weapon_recoil.m249X[check] * recoil ) * (1) * scope) * attachment, (((weapon_recoil.m249Y[check] * recoil) * (1) * scope) * attachment));
            }


            check++;
            if (check == 30)
            {
                break;
            }
                }
            }
            check = 0;
        }    
}


void linearInterpolation(int smoothing, int delay, int x, int y)
{

    for (int i = 0; i < smoothing; i++) {
        mouse_event(1, x / smoothing, y / smoothing, 0, 0);
        SleepTime(delay / smoothing);
    }
    mouse_event(1, x % smoothing, y % smoothing, 0, 0);
    Sleep(delay % smoothing);
}

void LinearlySmoothing(double totalTime, double control_time, int X, int Y)
{
    int oX = 0, oY = 0, oT = 0;
    for (int i = 1; i <= (int)control_time; ++i)
    {
        int nX = i * X / (int)control_time;
        int nY = i * Y / (int)control_time;
        int nT = i * (int)control_time / (int)control_time;
        mouse_event(1, nX - oX, nY - oY, 0, 0);
        SleepTime(nT - oT);
        oX = nX; oY = nY; oT = nT;
    }
    SleepTime((int)totalTime - (int)control_time);
}



void SleepTime(int ms)
{
    LONGLONG timerResolution;
    LONGLONG wantedTime;
    LONGLONG currentTime;

    QueryPerformanceFrequency((LARGE_INTEGER*)&timerResolution);
    timerResolution /= 1000;

    QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
    wantedTime = currentTime / timerResolution + ms;
    currentTime = 0;
    while (currentTime < wantedTime)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
        currentTime /= timerResolution;
    }
}


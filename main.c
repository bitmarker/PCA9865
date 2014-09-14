#include "general.h"
#include "chip.h"
#include "i2c.h"
#include "pca9685.h"

/* System oscillator rate and clock rate on the CLKIN pin */
const uint32_t OscRateIn = 12000000;
const uint32_t ExtRateIn = 0;


volatile float dc = 1;
float add = 0.5;

void SysTick_Handler()
{
  if(dc >= 100 || dc <= 0)
  {
    add = add * -1;
  }
  
  PCA9685_SetPWM(0, 0, dc / 100.0);
  PCA9685_SetPWM(1, 0, 1 - dc / 100.0);
  PCA9685_SetPWM(2, 0, 1 - 2 * dc / 100.0);
  
  dc += add;
}


int main()
{
  SystemCoreClockUpdate();
  
  
  Chip_GPIO_Init(LPC_GPIO);
  Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 10);
  Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 11);

  SysTick_Config(SystemCoreClock / 100);
  
  I2C_Init();
  
  PCA9685_SetAddress(0x40);
  
  if(PCA9685_Init() == NO_ERROR)
  {
    

    if(PCA9685_SetPWM(0, 0, 0.5) == NO_ERROR)
    {
      Chip_GPIO_SetPinState(LPC_GPIO, 1, 11, false);
    }
    else
    {
      Chip_GPIO_SetPinState(LPC_GPIO, 1, 10, false);
    }
  }
  else
  {
    Chip_GPIO_SetPinState(LPC_GPIO, 1, 10, false);
  }
  
  
  
  while(1)
  {
    PCA9685_Idle();
  }
}

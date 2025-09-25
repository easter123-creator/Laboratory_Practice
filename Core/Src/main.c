#include <stdint.h>
#include "init.h"
int main(void){
    *(uint32_t*)(0x40023800UL + 0x30UL) |= 0x06UL; //Включение тактирования порта GPIOB

    *(uint32_t*)(0x40020400UL+0x00UL) |= 0x4000UL; //Настройка работы 7-го пина GPIOB в режиме вывода сигнала
    *(uint32_t*)(0x40020400UL+0x04UL) |= 0x00UL; //Настройка на PushPull работу 7-го пина GPIOB
    *(uint32_t*)(0x40020400UL+0x08UL) |= 0x4000UL; //Настройка скорости работы 7-го пина GPIOB на среднюю
    *(uint32_t*)(0x40020400UL+0x18UL) |= 0x800000UL; //Отключение PU/PDрезисторов для 7-го пина GPIOB
    // Кнопку подключаем к PC13 или к PC12 если кнопка сломана
    while(1)
    {
        if (*(uint32_t*)(0x40020800UL + 0x10UL) & 0x2000UL)
        {
            *(uint32_t*)(0x40020400UL+0x18UL) |= 0x80UL;
        }
        else
        {
            *(uint32_t*)(0x40020400UL+0x18UL) |= 0x800000UL;
        }
    
    
    }
}
int main(void)
{
     GPIO_init_7_pin ();
     GPIO_init_14_pin ();
    while (1)
    {
        if (BIT_READ(GPIOC_IDR, GPIO_PIN_13)) // опереатор if, в котором логически умножается IDR на значение
        {
            BIT_SET(GPIOB_BSRR, GPIO_PIN_SET_7);    //Синий светодиод
            BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_14);   // Включает светодиод BSSR, если нажата кнопка
        }
        else
        {
            BIT_SET(GPIOB_BSRR, GPIO_PIN_SET_14);
            BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_7);
        }
    }
}
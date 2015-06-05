/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 文件名  ：ANO_Thread.c
 * 描述    ：用户线程
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 开发人员：茶不思、秋雨魂
 * 技术Q群 ：190169595
**********************************************************************************/

#include "board.h"
#include <rtthread.h>

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[ 512 ];
static struct rt_thread led_thread;
static void led_thread_entry(void* parameter)
{
    unsigned int count=0;

    //rt_hw_led_init();

    while (1)
    {
        /* led0 on */
        count++;
        //rt_hw_led_on(0);
        rt_thread_delay( RT_TICK_PER_SECOND/5 ); /* sleep 0.5 second and switch to other thread */

        /* led0 off */
        //rt_hw_led_off(0);
        rt_thread_delay( RT_TICK_PER_SECOND/5 );
    }
}


int rt_application_init(void)
{
    rt_err_t result;

    /* init led thread */
    result = rt_thread_init(&led_thread,
                            "led",
                            led_thread_entry,
                            RT_NULL,
                            (rt_uint8_t*)&led_stack[0],
                            sizeof(led_stack),
                            20,
                            5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led_thread);
    }
				
    return 0;
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

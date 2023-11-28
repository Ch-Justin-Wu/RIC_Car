# 大秦科技——RIC小车电控技术文档

## 一、简介

本文档针对该项目的各个重点模块进行简要介绍，涵盖小车底盘控制、机械臂控制、Xbox控制器数据包接收等方面。

## 二、引脚配置
![Alt text](image.png)

<center>图1 引脚配置图<center>

## 三、采用C/C++混合编写

基于C++类的特性，封装了remote_control、Servos、chassis、motor多个类的成员变量和成员函数。

类相较于结构体可设置成员变量的访问权限，让成员变量不被随意访问和修改（虽然没有怎么用上这个特性）；类相较于结构体另一个突出的特点是可以封装成员函数，相当于结构体Pro Max,利用好这个特性调用类中成员函数在编写代码时非常方便，例如：

```c++
		Mec_Chassis.mec_chassis_wheel_speed();
		for (uint8_t i = 0; i < 4; i++)
		{

			motors[i].wheel_linear_speed_to_rpm(i);
			motors[i].motor_pwm_tx(i);
		}
```

这样可以非常方便的访问底盘和电机的相关成员函数，从而控制电机转速。

## 四、底盘控制

### 1.卡尔曼滤波处理电机转速

对于电机转速，我采用的是M法测速，但由于编码器测速得到的速度值是离散的，如果电机的速度值刚好卡在两个离散值中间，我们测得的速度值就会在这两个离散值中间来回震荡。为改善此现象，我决定采用卡尔曼滤波处理电机转速，经过多次调参终于达到一个比较理想的速度曲线。

### 2.PID自适应P系数

为更灵活地调节控制电机转速，我采用了自调节P系数，根据误差值灵活调节p的大小

```c
 // 自适应Kp调节 auto control Kp
    if (pid->k1 != 0 || pid->k2 != 0 || pid->k3 != 0)
    {
        pid->p = pid->k1 * log10f(pid->k2 * ABS(pid->err[NOW]) + pid->k3);
    }
    else
    {
        // Calculate the proportional component
        pid->pout = pid->p * pid->err[NOW];
    }
    
```



## 五、遥控器数据包解析

### 1.串口空闲中断+DMA接收




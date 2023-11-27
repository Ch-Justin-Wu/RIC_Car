# 大秦科技--RIC小车电控技术文档

## 简介

​	本文档针对该项目的各个重点模块进行简要介绍，涵盖小车底盘控制、机械臂控制、Xbox控制器数据包接收等方面。

## 引脚配置
引脚配置图
![Alt text](image.png)

​	                                                       



## 采用C/C++混合编写

​	基于C++类的特性，封装了remote_control、Servos、chassis、motor多个类的成员变量和成员函数。

​	类相较于结构体可设置成员变量的访问权限，让成员变量不被随意访问和修改（虽然没有怎么用上这个特性）；类相较于结构体另一个突出的特点是可以封装成员函数，相当于结构体Pro Max,利用好这个特性调用类中的public的成员函数在编写代码时非常方便，例如：

```c++
		Mec_Chassis.mec_chassis_wheel_speed();
		for (uint8_t i = 0; i < 4; i++)
		{

			motors[i].wheel_linear_speed_to_rpm(i);
			motors[i].motor_pwm_tx(i);
		}
```



## 遥控器数据包解析
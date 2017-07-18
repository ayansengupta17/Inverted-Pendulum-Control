# Inverted-Pendulum-Control
Design of a linear Quadratic Regulator balance controller for the Inverted Pendulum. After manually initializing the pendulum in the upright vertical position, the balance controller moves the rotary arm to keep the pendulum in this upright position. Moreover it is capable of balancing itself, even if minor external disturbances are given.

## Documentation

This project is a part of the control and computing lab project for IIT Bombay. I have attached the relevant Chapter from our lab report. All the harware details, the mathematical model and the codes are explained in details in that report, so I am not explaining anything in this readme anymore. 

## Breif details about setup

For this project we used a rotary inverted pendulum kit by Quanser.
![Inverted pendulum kit](https://github.com/ayansengupta17/Inverted-Pendulum-Control/blob/master/ped.png)

 Arduino Mega was used for the control of the DC Motor voltage.
![Arduino Mega](https://github.com/ayansengupta17/Inverted-Pendulum-Control/blob/master/mega.png)

The circuit diagram is shown here: [circuit diagram](https://github.com/ayansengupta17/Inverted-Pendulum-Control/blob/master/Inverted%20Pendulum%20Circuit.svg) 
The decoder datasheet can be found here: [HCTL 2022](https://github.com/ayansengupta17/Inverted-Pendulum-Control/blob/master/AV02-0096EN.pdf)
The encoder datasheet can be found here: [Avago Encoder](https://github.com/ayansengupta17/Inverted-Pendulum-Control/blob/master/AV02-1046EN_DS_HEDM-55xx_2014-11-20.pdf)


## Demo

![Demo](https://github.com/ayansengupta17/Inverted-Pendulum-Control/blob/master/demo.gif)

